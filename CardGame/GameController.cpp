#include "GameController.h"

GameController::GameController(GameSettings& settings):Controller(settings){
	this->settings = &settings;
	game = new Game(this->settings->players.size());
	view = new GameView(settings, &game->player, &game->deck, &game->triumph, &selection);

	command = "";
	codes.x = codes.y = 0;
	selection = -1;

	gameData.players = &game->player;
	gameData.playersSettings = &settings.players;
	gameData.triumph = &game->triumph;
	gameData.rounds = &settings.rounds;
	gameData.table = game;
	gameData.roundsPlayed = 0;
	gameData.cardsOnTable = 0;
	gameData.cardsPlayed = 0;
	gameData.playerToMove = -1;
}

GameController::~GameController() {
	delete game;
}

std::string saveAs(HWND owner){
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = "Planowanie\0*.save\0";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR | MB_APPLMODAL | MB_TOPMOST;
	ofn.lpstrDefExt = "";
	ofn.lpstrInitialDir = "";

	std::string fileNameStr;
	if (GetSaveFileName(&ofn))
		fileNameStr = fileName;

	if (fileNameStr.find(".save") != std::string::npos) {	// Usuniêcie potencjalnej koñcóki .save
		fileNameStr.resize(fileNameStr.length() - 5);
	}

	for (int i = 0; i < 4; i++) {
		if (fileNameStr[fileNameStr.length() - 1 - i]) {
			
		}
	}

	return fileNameStr;
}

std::string loadAs(HWND owner) {
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = "Planowanie\0*.save\0";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR | MB_APPLMODAL | MB_TOPMOST;
	ofn.lpstrDefExt = "";
	ofn.lpstrInitialDir = "";

	std::string fileNameStr;
	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;

	return fileNameStr;
}

bool GameController::prepareGame() {
	if (settings->newGame == true) {//Przystosowanie gry jeœli jest to NowaGra
		game->player.clear();
		game->player.resize(gameData.playersSettings->size());
		gameData.reset();
		game->player.clear();
		game->player.resize(gameData.playersSettings->size());
		settings->newGame = false;
	}
	else if (settings->load == true) { 
		std::string loadPath = loadAs(settings->window->getSystemHandle());
		if (loadPath.length() == 0) {
			settings->load = false;
			return false;
		}
		else {
			std::ifstream file(loadPath, std::ios_base::binary);
			file >> gameData;
			file.close();
			settings->load = false;
		}
	}
	else if (settings->save == true) {
		if (game->player[0].getDeckSize() == 0) {
			settings->save = false;
			return false;
		}
		std::string  savePath = saveAs(settings->window->getSystemHandle());
		if (savePath.length() == 0) {
			settings->save = false;
			return false;
		}
		else {
			std::ofstream file(savePath + ".save", std::ios_base::binary);
			file << gameData;
			file.close();
			settings->save = false;
			return false;
		}
	}
	return true;
}

int GameController::start() {
	view->start();
	if (!prepareGame()) return MAINMENU;

	for(gameData.roundsPlayed; gameData.roundsPlayed < int(gameData.rounds->size()); gameData.roundsPlayed++){ //Partia
		game->prepareRound(gameData.rounds->at(gameData.roundsPlayed), settings->newGame);

		for (int declared = 0, i = gameData.roundsPlayed; declared < int(gameData.players->size()); declared++) { // Deklaracje przez parti¹
			
			if (game->player.at(i).getDeclaration() == -1000) {
				if (i == 0) {
					view->drawScene("Start");
					view->drawScene("Declaration");
					view->display();
					if (waitForEvent("Declaration")) return MAINMENU;
					game->setDeclaration(i, codes.x);
				}
				else
					game->setDeclaration(i, game->ai->declare(1, i));
			}
			if (i == gameData.playersSettings->size() - 1)
				i = 0;
			else i++;
		}

		for(gameData.cardsPlayed; gameData.cardsPlayed < gameData.rounds->at(gameData.roundsPlayed); gameData.cardsPlayed++){ //Runda		
			for (gameData.playerToMove, gameData.cardsOnTable; gameData.cardsOnTable < int(gameData.players->size()); gameData.cardsOnTable++) { //Rzucanie kart¹ przez wszytkich graczy
				if (gameData.playerToMove == -1) 
					gameData.playerToMove = gameData.roundsPlayed;
				
				view->drawScene("Start");
				view->drawScene("Table");
				view->display();

				int card_id = -1;
				if (gameData.playersSettings->at(gameData.playerToMove) == 0) {
					view->clearCommands();
					if (waitForEvent("ThrowCard")) return MAINMENU;
					card_id = codes.x;
				}
				else card_id = game->aiCardSelection(gameData.playerToMove, gameData.playersSettings->at(gameData.playerToMove));
				
				game->makeAMove(gameData.playerToMove, card_id);

				if (gameData.playerToMove == gameData.playersSettings->size() - 1) 
					gameData.playerToMove = 0;
				else gameData.playerToMove++;
			}

			view->drawScene("Start");
			view->drawScene("Table");
			view->display();
			view->addCommand(sf::FloatRect(0, 0, settings->window->getSize().x, settings->window->getSize().y), "Proceed", selection);
			if (waitForEvent("Proceed")) return MAINMENU;
			game->sumUpTable();		
			gameData.cardsOnTable = 0;
			gameData.playerToMove = game->getRoundWinner();
		}
		gameData.cardsPlayed = 0;
		gameData.playerToMove = -1;
		view->drawScene("Background");
		view->display();
		view->drawScene("Start");
		game->sumUpRound();
	}
	view->drawScene("Scoreboard");
	view->display();
	view->addCommand(sf::FloatRect(0, 0, settings->window->getSize().x, settings->window->getSize().y), "Proceed", selection);
	if (waitForEvent("Proceed")) return MAINMENU;
	game->roundWinner = 0;
	gameData.reset();
	return MAINMENU;
}

bool GameController::waitForEvent(sf::String event) {
	bool result;
	while (true) {
		while (command == "")
			checkEvent();
		interpretEvent();

		if (command == "CLOSE") {
			settings->window->close();
			result = true;
			break;
		}
		else if (command == "MAINMENU") {
			result = true;
			break;
		}
		else if (command == event) {
			result = false;
			break;
		}
		else command = "";

		if (event == "Declaration") {
			view->drawScene("Start");
			view->drawScene("Declaration");
			view->display();
		}
		else if (event == "ThrowCard") {
			view->drawScene("Start");
			view->drawScene("Table");
			view->display();
		}
		
	}
	view->clearCommands();
	command = "";
	return result;
}

void GameController::saveGame() {

}

void GameController::checkEvent() {
	sf::Event action;

	if (command != "") return;
	
	if (!view->checkEvent(action)) return;
	else {
		switch (action.type) {

		case sf::Event::MouseButtonReleased:
			if (action.mouseButton.button == sf::Mouse::Left)
				command = "MouseLeft";
			else if (action.mouseButton.button == sf::Mouse::Right)
				command = "MouseRight";
			codes.x = action.mouseButton.x;
			codes.y = action.mouseButton.y;
			break;

		case sf::Event::MouseMoved:
			command = "MouseMove";
			codes.x = action.mouseButton.button;
			codes.y = action.mouseButton.x;
			break;

		case sf::Event::KeyReleased:
			command = "KeyReleased";
			codes.x = codes.y = action.key.code;
			break;

		case sf::Event::KeyPressed:
			command = "KeyPressed";
			codes.x = codes.y = action.key.code;
			break;

		case sf::Event::Closed:
			command = "CLOSE";
			break;
		default:
			command = "";
			break;
		}
	}
}

void GameController::interpretEvent() {

	if (command == "MouseMove") {
		command = view->checkCoords(codes);
		if (command != "") {
			selection = codes.x;
			command = "";
		}
		else selection = -1;
	}

	if (command == "MouseLeft") {
		command = view->checkCoords(codes);
		selection = -1;
	}
	else if (command == "KeyReleased") {
		if (view->getLowestCommand() > selection) selection = view->getLowestCommand() - 1; //Warunek na wyj¹tek (kiedy pierwsze karty s¹ niedowzwolene)
		if ((codes.x == 0 || codes.x == 71) && selection > view->getLowestCommand()) {//A lub strza³ka w lewo
			selection--;
		}
		else if ((codes.x == 3 || codes.x == 72) && selection < view->getHighestCommand()) {//D lub strza³ka w prawo
			selection++;
		}
		else if (codes.x == 58 || codes.x == 73 || codes.x == 22) {//Enter lub strza³ka w górê lub w
			command = view->checkCode(selection);
			codes.x = codes.y = selection;
			selection = -1;
		}
		else if (codes.x == 36) {//Escape
			command = "MAINMENU";
		}
	}
	else if (command == "KeyPressed") {
		if (codes.x == 60 && gameData.roundsPlayed < settings->rounds.size()) {
			view->drawScene("Start");
			view->drawScene("Scoreboard");
			view->display();
			sf::Event action;	
			while (true) {
				view->checkEvent(action);
				if (action.type == sf::Event::KeyReleased) {
					if (action.key.code == 60)
						break;
				}
				else if (action.type == sf::Event::Closed) {
						command = "CLOSE";
					break;
				}
			}
			view->drawScene("Start");
			view->drawScene("Table");
			view->display();
		}
	}
	else if (command == "CLOSE") {
		std::cout << "Closing";
	}
	else command = "";
}
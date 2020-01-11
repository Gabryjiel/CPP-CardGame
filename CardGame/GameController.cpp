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
	gameData.playerToMove = 0;
}

GameController::~GameController() {
	delete game;
	delete view;
}

void GameController::prepareGame() {
	if (game->player.size() == 0) {	//Przystosowanie gry je�li jest to NowaGra
		game->player.clear();
		game->player.resize(gameData.playersSettings->size());
	}
	
	if (settings->newGame == true) {
		gameData.reset();
		game->player.clear();
		game->player.resize(gameData.playersSettings->size());
		settings->newGame = false;
	}
}

int GameController::start() {
	view->start();
	prepareGame();

	for(gameData.roundsPlayed; gameData.roundsPlayed < int(settings->rounds.size()); gameData.roundsPlayed++){ //Partia
		game->prepareRound(settings->rounds[gameData.roundsPlayed]);

		for (int i = 0; i < int(settings->players.size()); i++) { // Deklaracje przez parti�
			if (game->player.at(i).getDeclaration() == -1) {
				if (i == 0) {
					view->drawScene("Start");
					view->drawScene("Declaration");
					view->display();
					if (waitForEvent("Declaration")) return MAINMENU;
					game->setDeclaration(i, codes.x);
				}
				else
					game->setDeclaration(i, game->ai->declare(1));
			}
		}

		for(gameData.cardsPlayed; gameData.cardsPlayed < settings->rounds[gameData.roundsPlayed]; gameData.cardsPlayed++){ //Runda		
			for (gameData.playerToMove = game->getRoundWinner(), gameData.cardsOnTable; gameData.cardsOnTable < int(settings->players.size()); gameData.cardsOnTable++) { //Rzucanie kart� przez wszytkich graczy
				int card_id = -1;
				if (settings->players[gameData.playerToMove] == 0) {
					view->clearCommands();
					view->drawScene("Start");
					view->drawScene("Table");
					view->display();
					if (waitForEvent("ThrowCard")) return MAINMENU;
					card_id = codes.x;
				}
				else card_id = game->aiCardSelection(gameData.playerToMove, settings->players[gameData.playerToMove]);
				
				game->makeAMove(gameData.playerToMove, card_id);
				//view->drawScene("Start");
				//view->drawScene("Table");
				//view->display();

				if (gameData.playerToMove == settings->players.size() - 1) 
					gameData.playerToMove = 0;
				else gameData.playerToMove++;
			}

			view->drawScene("Start");
			view->drawScene("Table");
			view->addCommand(sf::FloatRect(0, 0, settings->window->getSize().x, settings->window->getSize().y), "Proceed", selection);
			view->display();
			if (waitForEvent("Proceed")) return MAINMENU;
			game->sumUpTable();		
			gameData.cardsOnTable = 0;
		}
		gameData.cardsPlayed = 0;
		view->drawScene("Background");
		view->display();
		game->sumUpRound();
	}
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

		case sf::Event::MouseButtonPressed:
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
			command = "Key";
			codes.x = codes.y = action.key.code;
			break;

		case sf::Event::Closed:
			command = "CLOSE";
			break;
		default:
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
	else if (command == "Key") {
		if ((codes.x == 0 || codes.x == 71) && selection > 0) {//A lub strza�ka w lewo
			selection--;
		}
		else if ((codes.x == 3 || codes.x == 72) && selection < view->getCommandsSize() - 1) {//D lub strza�ka w prawo
			selection++;
		}
		else if (codes.x == 58 || codes.x == 73 || codes.x == 22) {//Enter lub strza�ka w g�r� lub w
			command = view->checkCode(selection);
			codes.x = codes.y = selection;
			selection = -1;
		}
		else if (codes.x == 36) {//Escape
			command = "MAINMENU";
		}
		
	}
	else if (command == "CLOSE") {
		std::cout << "Closing";
	}
	else command = "";
}
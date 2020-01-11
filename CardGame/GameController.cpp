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
	delete view;
}

void GameController::prepareGame() {
	if (game->player.size() == 0) {	//Przystosowanie gry jeœli jest to NowaGra
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
		game->prepareRound(settings->rounds[gameData.roundsPlayed], settings->newGame);

		for (int i = 0; i < int(settings->players.size()); i++) { // Deklaracje przez parti¹
			if (game->player.at(i).getDeclaration() == -1000) {
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
			for (gameData.playerToMove, gameData.cardsOnTable; gameData.cardsOnTable < int(settings->players.size()); gameData.cardsOnTable++) { //Rzucanie kart¹ przez wszytkich graczy
				if (gameData.playerToMove == -1) 
					gameData.playerToMove = game->getRoundWinner();
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
			gameData.playerToMove = game->getRoundWinner();
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
		if (codes.x == 60) {
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
		}
	}
	else if (command == "CLOSE") {
		std::cout << "Closing";
	}
	else command = "";
}
#include "GameController.h"

GameController::GameController(GameSettings& settings):Controller(settings){
	this->settings = &settings;
	game = new Game(this->settings->players.size());
	//game = new Game();
	view = new GameView(settings, &game->player, &game->deck, &game->triumph);
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
		game->prepareRound(settings->rounds[gameData.roundsPlayed]);

		for (int i = 0; i < int(settings->players.size()); i++) { // Deklaracje przez parti¹
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
			view->drawScene("Start");
			view->drawScene("Table");
			view->display();
		
			for (gameData.playerToMove = game->getRoundWinner(), gameData.cardsOnTable; gameData.cardsOnTable < int(settings->players.size()); gameData.cardsOnTable++) { //Rzucanie kart¹ przez wszytkich graczy
				int card_id = -1;
				if (settings->players[gameData.playerToMove] == 0) {
					if (waitForEvent("ThrowCard")) return MAINMENU;
					card_id = codes.x;
				}
				else card_id = game->aiCardSelection(gameData.playerToMove, settings->players[gameData.playerToMove]);
				
				game->makeAMove(gameData.playerToMove, card_id);
				view->drawScene("Start");
				view->drawScene("Table");
				view->display();

				if (gameData.playerToMove == settings->players.size() - 1) 
					gameData.playerToMove = 0;
				else gameData.playerToMove++;
			}

			view->drawScene("Start");
			view->drawScene("Table");
			view->addCommand(sf::FloatRect(0, 0, settings->window->getSize().x, settings->window->getSize().y), "Proceed", 0);
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
	}
	view->clearCommands();
	command = "";
	return result;
}

void GameController::saveGame() {

}

void GameController::gameStart() {
	settings->window->setActive(false);
	std::thread eventThread(&GameController::gameStart, this);
	int mode = 1;
	while (true) {
		command = "";
		codes.x = codes.y = 0;
		while (command == "")
			checkEvent();
			
		interpretEvent();

		if (command == "Declaration")
			command = "";
		else if (command == "CLOSE") {
			eventThread.join();
			mode = 0;
			command = "";
			break;
		}
		
	}
	return ;
}

bool GameController::checkCommand(const sf::String command) {
	if (this->command == command) return true;
	return false;
}

inline void GameController::waitForCommand(const sf::String command){
	bool result = false;
	while (true) {
		if (this->command == "CLOSE") return;
		if (this->command == command) break;
	}
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

		case sf::Event::KeyPressed:
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
	static int selection;

	if (command == "MouseLeft")
		command = view->checkCoords(codes);
	else if (command == "Key") {
		if ((codes.x == 'a' || codes.x == 'A') && selection > 0) {
			selection--;
		}
		else if ((codes.x == 'd' || codes.x == 'D') && selection < game->player[0].getDeckSize()) {
			selection++;
		}
		else if (codes.x == 58) {
			command = "ThrowCard";
			codes.x = codes.y = selection;
		}
		else if (codes.x == 36) {
			command = "MAINMENU";
		}
		
	}
	else if (command == "CLOSE") {
		std::cout << "Closing";
	}
	else command = "";
}
#include "GameController.h"

GameController::GameController(GameSettings& settings) {
	this->settings = &settings;
	game = new Game();
	view = new GameInterface(settings, game->player, &game->deck, game->numberOfPlayers);
}

GameController::~GameController() {
	delete game;
	delete view;
}

void GameController::gameStart() {
	view->setPositions();
	while (!settings->rounds.empty()) {
		game->prepareRound();
		view->displayStart();
		view->displayTriumph(game->triumph);
		
		//view->display();
		view->drawDeclaration();
		view->display();
		while (true) {
			if(checkCommand("CLOSE")) return;
			if(checkCommand("Declaration")) break;
		}

		waitForCommand("Declaration");
		game->setDeclaration(codes.x);
		//int roundLength = settings->rounds.front();
		while (settings->rounds[0]--) {
			for (int i = game->getRoundWinner(), cardsOnTable = 0; cardsOnTable < int(settings->players.size()); cardsOnTable++) {
				int card_id = -1;
				if (settings->players[i] == 0) {
					while (true) {
						if (checkCommand("CLOSE")) return;
						if (checkCommand("ThrowCard")) break;
					}
					//card_id = makeAMove(i);
				}
				else
					card_id = game->aiCardSelection(i, settings->players[i]);
				game->makeAMove(i, card_id);
				
				view->displayStart();
				view->displayTable();

				if (i == settings->players.size() - 1) i = 0;
				else i++;
			}
			game->sumUpTable();
			view->displayTable();
		}
		game->sumUpRound();
		view->displayStart();
		view->displayTable();
		settings->rounds.erase(settings->rounds.begin());
	}
}

int GameController::start() {
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
	return mode;
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
		command = view->checkCoords(&codes);
	else if (command == "Key") {
		if ((codes.x == 'w' || codes.x == 'W') && selection > 0) {
			selection--;
		}
		else if ((codes.x == 's' || codes.x == 'S') && selection < game->player[0].getDeckSize()) {
			selection++;
		}
		else if (codes.x == 13) {
			command = "ThrowCard";
			codes.x = codes.y = selection;
		}
	}
	else if (command == "CLOSE") {
		std::cout << "Closing";
	}
	else command = "";
}
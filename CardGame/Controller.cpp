#include "Controller.h"

Controller::Controller() {
	game = new Game();
	view = new GameInterface(game->player, &game->deck, game->triumph, game->numberOfPlayers);
	command = "";
}

Controller::~Controller() {
	delete view;
	delete game;
}

void Controller::mainMenu() {
	//display MainMenu
	while (true) {
		codes.x = codes.y = 0;
		while (command == "")
			checkEvent();

		interpretEvent();

		if (command == "") {
			continue;
		}
		else if (command == "QuickGame") {

		}
		else if (command == "CustomGame") {

		}
		else if (command == "Continue") {

		}
		else if (command == "Options") {

		}
		else if (command == "CLOSE") {

		}
	}
}

void Controller::checkEvent() {
	sf::Event action;

	if (command != "") return;

	if (!view->getEvent(action)) return;
	else {
		switch (action.type) {
		case sf::Event::MouseButtonPressed:
			if (action.mouseButton.button == sf::Mouse::Left)
				command = "MouseLeft";
			else if (action.mouseButton.button == sf::Mouse::Right)
				command = "MouseRight";
			codes.x = action.mouseButton.x;
			codes.y = action.mouseButton.y;
		case sf::Event::KeyPressed:
			command = "Key";
			codes.x = codes.y = action.key.code;
			break;
		case sf::Event::Closed:
			command = "CLOSE";
			break;
		default:
		}
	}
}

void Controller::interpretEvent() {
	static int selection;

	if (command == "MouseLeft")
		command = checkCoords(codes);
	else if (command == "Key") {
		if ((codes.x == 'w' || codes.x == 'W') && selection > 0) {
			selection--;
		}
		else if ((codes.x == 's' || codes.x == 'S') && selection < 4) {
			selection++;
		}
		else if (codes.x == 13) {
			switch (selection) {
			case 0:
				command = "QuickGame";
				break;
			case 1:
				command = "CustomGame";
				break;
			case 2:
				command = "Continue";
				break;
			case 3:
				command = "Options";
				break;
			case 4:
				command = "CLOSE";
				break;
			}
		}
	}
	else command = "";
}

void
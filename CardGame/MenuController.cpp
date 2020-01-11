#include "MenuController.h"

MenuController::MenuController(GameSettings& settings):Controller(settings) {
	view = new MenuView(settings);
	command = "";
}

MenuController::~MenuController() {
	delete view;
}

int MenuController::start() {
	view->drawScene("MainMenu");
	while (true) {
		command = "";
		codes.x = codes.y = 0;
		while (command == "")
			checkEvent();

		interpretEvent();

		if (command == "QuickGame") {
			settings->players = { 0, 1111, 2222, 3333 };
			settings->rounds = { 4, 11, 10 ,9, 8,7,6,5,4,3,2,1,1,1,1 };
			settings->newGame = true;
			return STARTGAME;
		}
		else if (command == "CustomGame" || command == "Options" || command == "MainMenu") {
			view->drawScene(command);
		}
		else if (command == "Continue" && !settings->rounds.empty()) {
			return STARTGAME;
		}
		else if (command == "CLOSE") {
			view->close();
			return CLOSEPROGRAM;
		}
		else if (command == "Resolution") {

		}
		else if (command == "BackgroudColour") {

		}
		else if (command == "CardTheme") {

		}
	}
}

void MenuController::checkEvent() {
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

void MenuController::interpretEvent() {
	static int selection;

	if (command == "MouseLeft")
		command = view->checkCoords(codes);
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
}
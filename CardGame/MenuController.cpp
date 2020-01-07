#include "MenuController.h"

MenuController::MenuController(GameSettings& settings) {
	this->settings = &settings;
	view = new MenuInterface(*(settings.window));
	command = "";
}

MenuController::~MenuController() {
	delete view;
}

int MenuController::start() {
	view->menu("MainMenu");
	while (true) {
		command = "";
		codes.x = codes.y = 0;
		while (command == "")
			checkEvent();

		interpretEvent();

		if (command == "QuickGame") {
			return STARTGAME;
		}
		else if (command == "CustomGame" || command == "Options" || command == "MainMenu") {
			view->menu(command);
		}
		else if (command == "Continue") {

		}
		else if (command == "CLOSE") {
			view->close();
			return CLOSEGAME;
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
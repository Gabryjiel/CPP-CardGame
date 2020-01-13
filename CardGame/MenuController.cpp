#include "MenuController.h"

MenuController::MenuController(GameSettings& settings):Controller(settings) {
	view = new MenuView(settings);
	command = "";
}

MenuController::~MenuController() {
}

int MenuController::start() {
	view->drawScene("MainMenu");
	view->display();
	while (true) {
		while (command == "")
			checkEvent();

		interpretEvent();

		if (command == "QuickGame") {
			settings->players = { 0, 1111, 7777, 5555 };
			settings->rounds = {12, 11, 10 ,9, 8,7,6,5,4,3,2,1,1,1,1 };
			command = "StartNew";
		}
		else if (command == "CustomGame" || command == "Options" || command == "MainMenu" || 
			command == "ResolutionMenu" || command == "CardThemeMenu" || command == "BackgroundColourMenu" ||
			command == "RoundsMenu" || command == "PlayersMenu") {
			view->drawScene(command);
			view->display();
		}
		else if (command == "Continue" && !settings->rounds.empty()) {
			return STARTGAME;
		}
		else if (command == "CLOSE") {
			view->close();
			return CLOSEPROGRAM;
		}
		else if (command == "SaveGame") {
			settings->save = true;
			return STARTGAME;
		}
		else if (command == "LoadGame") {
			settings->load = true;
			return STARTGAME;
		}
		else if (command == "ChangeResolution") {
			settings->window->close();
			switch (codes.x) {
			case 0: settings->window->create(sf::VideoMode(640, 480), "Planowanie", sf::Style::Close); break;
			case 1: settings->window->create(sf::VideoMode(800, 640), "Planowanie", sf::Style::Close); break;
			case 2: settings->window->create(sf::VideoMode(1024, 768), "Planowanie", sf::Style::Close); break;
			case 3: settings->window->create(sf::VideoMode(1280, 720), "Planowanie", sf::Style::Close); break;
			case 4: settings->window->create(sf::VideoMode(1600, 900), "Planowanie", sf::Style::Close); break;
			case 5: settings->window->create(sf::VideoMode(1920, 1080), "Planowanie", sf::Style::Close); break;
			case 6: settings->window->create(sf::VideoMode::getFullscreenModes()[0], "Planowanie", sf::Style::Fullscreen); break;
			default: settings->window->create(sf::VideoMode(1280, 720), "Planowanie", sf::Style::Close);
			}
			settings->window->requestFocus();
			view->drawScene("ResolutionMenu");
			view->display();
		}
		else if (command == "ChangeBColour") {
			switch (codes.x) {
			case 0: settings->backgroundColour = sf::Color(0, 0, 102); break;
			case 1: settings->backgroundColour = sf::Color(64, 64, 64); break;
			case 2: settings->backgroundColour = sf::Color(102, 0, 0); break;
			case 3: settings->backgroundColour = sf::Color(102, 102, 0); break;
			case 4: settings->backgroundColour = sf::Color(51, 0, 51); break;
			case 5: settings->backgroundColour = sf::Color(0, 102, 0); break;
			default: settings->backgroundColour = sf::Color(44, 89, 56);
			}
			view->drawScene("BackgroundColourMenu");
			view->display();
		}
		else if (command == "ChangeCardTheme") {
			switch (codes.x) {
			case 0: settings->cardTheme = "images//cards//card_back_green.png"; break;
			case 1: settings->cardTheme = "images//cards//card_back_blue.png"; break;
			case 2: settings->cardTheme = "images//cards//card_back_red.png"; break;
			case 3: settings->cardTheme = "images//cards//card_back_orange.png"; break;
			case 4: settings->cardTheme = "images//cards//card_back_purple.png"; break;
			default:settings->cardTheme = "images//cards//card_back_black.png"; break;
			}
			view->drawScene("CardThemeMenu");
			view->display();
		}

		if (command == "StartNew") {
			settings->newGame = true;
			return STARTGAME;
		}
	}
}

void MenuController::checkEvent() {
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

void MenuController::interpretEvent() {
	static int selection;

	if (command == "CLOSE")
		return;
	else if (command == "MouseLeft")
		command = view->checkCoords(codes);
	else if (command == "Key") {
		if ((codes.x == 2 || codes.x == 'W') && selection > 0) {
			selection--;
		}
		else if ((codes.x == 's' || codes.x == 'S') && selection < 4) {
			selection++;
		}
		else if (codes.x == 58) {
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
		else if (codes.x == 36) {
			if (view->getCommandsSize() > 10)
				command = "MainMenu";
			else if (view->getCommandsSize() > 5)
				command = "Options";
			else if (int(view->getCommandsSize()) == 3 || int(view->getCommandsSize()) == 2)
				command = "MainMenu";
			else
				command = "CLOSE";
		}
		else command = "";
	}
	else if (command == "+r") {
		if ((settings->rounds[codes.x] + 1) * settings->players.size() < 51) {
			settings->rounds[codes.x] += 1;
		}
		command = "RoundsMenu";
	}
	else if (command == "-r") {
		if (settings->rounds[codes.x] > 1) {
			settings->rounds[codes.x] -= 1;
		}
		command = "RoundsMenu";
	}
	else if (command == "+R") {
		if (settings->rounds.size() < 20) {
			settings->rounds.push_back(1);
		}
		command = "RoundsMenu";
	}
	else if (command == "-R") {
		if (settings->rounds.size() > 1) {
			settings->rounds.pop_back();
		}
		command = "RoundsMenu";
	}
	
	else if (command == "+g") {
		if (settings->players[codes.x] < 10) {
			settings->players[codes.x] += 1;
		}
		command = "PlayersMenu";
	}
	else if (command == "-g") {
		if (settings->players[codes.x] > 1) {
			settings->players[codes.x] -= 1;
		}
		command = "PlayersMenu";
	}
	else if (command == "+G") {
		if (settings->players.size() < 10) {
			settings->players.push_back(1);
			for (int i = 0; i < int(settings->rounds.size()); i++) {
				if (settings->rounds[i] * settings->players.size() > 51) {
					settings->rounds[i] -= 1;
					i--;
					continue;
				}
			}
		}
		command = "PlayersMenu";
	}
	else if (command == "-G") {
		if (settings->players.size() > 2) {
			settings->players.pop_back();
		}
		command = "PlayersMenu";
	}
	else command = "";
}
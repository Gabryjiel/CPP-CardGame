#include "Launcher.h"

Launcher::Launcher() {
	settings = new GameSettings();
	controller = nullptr;
}

Launcher::~Launcher() {
	delete settings;
}

void Launcher::startGame() {
	MenuController menu_controller(*settings);
	GameController game_controller(*settings);
	int mode = 1;

	while (mode != 0) {
		if (mode == 1)
			controller = &menu_controller;
		else if (mode == 2)
			controller = &game_controller;
		
		mode = controller->start();

		if (settings->window->isOpen() == false)
			break;
	}
	controller = nullptr;
}
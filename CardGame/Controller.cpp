#include "Controller.h"

void Controller::startGame() {
	int mode = 1;
	settings->window->clear();
	settings->window->display();
	settings->window->display();

	while (mode != 0) {
		if (mode == 1)
			mode = menu_controller->start();
		else if (mode == 2)
			mode = game_controller->start();
	}
}
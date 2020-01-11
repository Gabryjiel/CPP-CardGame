#include "Launcher.h"

void Launcher::startGame() {
	int mode = 1;

	while (mode != 0) {
		if (mode == 1)
			mode = menu_controller->start();
		else if (mode == 2)
			mode = game_controller->start();

		if (settings->window->isOpen() == false)
			break;
	}
}
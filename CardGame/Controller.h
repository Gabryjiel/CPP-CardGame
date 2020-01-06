#pragma once
#include "MenuController.h"
#include "GameController.h"

class Controller{
	GameSettings * settings = new GameSettings();
	MenuController* menu_controller = new MenuController(*settings);
	GameController* game_controller = new GameController(*settings);
	
public:
	void startGame();
};


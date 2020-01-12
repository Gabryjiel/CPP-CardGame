#pragma once
#include "MenuController.h"
#include "GameController.h"

class Launcher{
	GameSettings* settings;
	Controller* controller;
	
public:
	Launcher();
	~Launcher();

	void startGame();
};


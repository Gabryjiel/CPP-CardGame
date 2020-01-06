#pragma once
#include "MenuInterface.h"
#include "GameSettings.h"

#define STARTGAME 2
#define CLOSEGAME 0

class MenuController{
	MenuInterface *view;
	GameSettings* settings;

	sf::String command;
	sf::Vector2u codes;
	
	void checkEvent();
	void interpretEvent();
public:
	MenuController(GameSettings& settings);
	~MenuController();

	int start();
};


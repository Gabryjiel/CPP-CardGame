#pragma once
#include "Game.h"
#include "GameInterface.h"
#include "MenuInterface.h"

class Controller{
	Game *game;
	GameInterface *view;

	std::string command;
	sf::Vector2u codes;
	
public:
	Controller();
	void mainMenu();

private:
	~Controller();

	void checkEvent();
	void interpretEvent();
	void gameStart();
};


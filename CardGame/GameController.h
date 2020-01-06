#pragma once
#include "GameInterface.h"
#include "Game.h"

class GameController{
	Game* game;
	GameInterface* view;
	GameSettings* settings;

	sf::String command;
	sf::Vector2u codes;

	void userAction();
	void checkEvent();
	void interpretEvent();
	int makeDeclaration();
	int makeAMove(int player);
public:
	GameController(GameSettings& settings);
	~GameController();

	int start();
};
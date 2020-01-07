#pragma once
#include "GameInterface.h"
#include "Game.h"
#include <thread>
#include <mutex>

class GameController{
	Game* game;
	GameInterface* view;
	GameSettings* settings;
	std::mutex mutex;

	sf::String command;
	sf::Vector2u codes;

	void userAction();
	void checkEvent();
	void interpretEvent();
	int makeDeclaration();
	int makeAMove(int player);
	void events();
	void gameStart();
	bool checkCommand(const sf::String command);
	inline void waitForCommand(const sf::String command) ;
public:
	GameController(GameSettings& settings);
	~GameController();

	int start();
};
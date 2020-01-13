#pragma once
#include "Controller.h"
#include "GameView.h"
#include "Game.h"
#include <thread>
#include <mutex>
#include "SaveData.h"
#include <fstream>

class GameController : public Controller{
	
	Game* game;
	SaveData gameData;

	sf::String command;
	sf::Vector2u codes;
	int selection;

	void userAction();
	void checkEvent();
	void interpretEvent();
	int makeDeclaration();
	int makeAMove(int player);
	void events();
	bool prepareGame();
	void gameStart();
	bool checkCommand(const sf::String command);
	bool waitForEvent(sf::String);
	inline void waitForCommand(const sf::String command) ;
	void saveGame();
public:
	GameController(GameSettings& settings);
	~GameController();
	

	int start();
};
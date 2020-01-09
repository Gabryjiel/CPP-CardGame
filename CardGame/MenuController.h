#pragma once
#include "Controller.h"
#include "MenuView.h"

class MenuController : public Controller{

	sf::String command;
	sf::Vector2u codes;
	
	void checkEvent();
	void interpretEvent();
public:
	MenuController(GameSettings& settings);
	~MenuController();

	int start();
};


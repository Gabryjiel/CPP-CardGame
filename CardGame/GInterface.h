#pragma once
#include "Player.h"
#include "Button.h"

class GInterface {
	sf::RenderWindow window;
	Button temp;

	void menu();
public:
	GInterface();
	void start();
	
};
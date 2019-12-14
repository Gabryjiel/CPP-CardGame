#pragma once
#include "Button.h"

class MenuInterface {
	sf::RenderWindow window;
	Button temp;

	void menu();
public:
	MenuInterface();
	void start();
	
};
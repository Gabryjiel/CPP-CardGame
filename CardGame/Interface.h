#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"

class Interface{
protected:
	sf::RenderWindow* window;
	std::vector <Button> options;

public:
	Interface() {
		window = new sf::RenderWindow();
		window->create(sf::VideoMode(640, 800), "Planowanie");
	}

	~Interface() {
		delete window;
	}

};
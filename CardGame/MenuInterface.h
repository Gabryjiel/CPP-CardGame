#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"

class MenuInterface{

	sf::RenderWindow* window;
	std::vector<Button> options;
	std::vector<sf::String> commands;

public:
	MenuInterface(sf::RenderWindow& window);
	~MenuInterface();

	void close();
	void menu(sf::String menu);
	bool checkEvent(sf::Event& event);
	std::string checkCoords(sf::Vector2u coords);
};
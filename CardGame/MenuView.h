#pragma once
#include "View.h"
#include "Button.h"

class MenuView : public View{

	std::vector<Button> options;
	std::vector<sf::String> commands;

public:
	MenuView(GameSettings & settings);
	~MenuView();

	void drawScene(const sf::String menu);
	bool checkEvent(sf::Event& event);
	sf::String checkCoords(sf::Vector2u &coords);
	void start();
};
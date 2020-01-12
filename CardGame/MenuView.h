#pragma once
#include "View.h"
#include "Button.h"
#include "Picture.h"

class MenuView : public View{

	std::vector<Button> options;
	std::vector<sf::String> command;

public:
	MenuView(GameSettings & settings);
	~MenuView();

	void drawScene(const sf::String menu);
	void drawRoundsMenu();
	void drawOptions();
	bool checkEvent(sf::Event& event);
	void drawPlayersMenu();
	sf::String checkCoords(sf::Vector2u &coords);
	sf::String checkCode(int code);

	void start();
};
#pragma once
#include "SFML/Graphics.hpp"
#include "Commands.h"
#include "GameSettings.h"

class View{
	
protected:
	GameSettings* settings;
	std::vector<Commands> commands;

	void draw(sf::Drawable& object);
public:
	View(GameSettings& settings);
	~View();

	virtual void drawScene(const sf::String mode) = 0;
	virtual bool checkEvent(sf::Event& event) = 0;
	virtual sf::String checkCoords(sf::Vector2u& codes) = 0;
	virtual sf::String checkCode(int code) = 0;
	virtual void start() = 0;

	void close();
	void display();
	void addCommand(sf::FloatRect hitbox, sf::String command, int code);
	int getCommandsSize();
	int getLowestCommand();
	int getHighestCommand();
	void clearCommands();;
};


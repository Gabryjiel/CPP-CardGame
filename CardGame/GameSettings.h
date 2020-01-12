#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

struct GameSettings {
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Planowanie", sf::Style::Close);;
	std::vector <int> players = { 0, 1, 3, 8 };
	std::vector <int> rounds = {12,11,10,9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1};
	bool newGame = false;
	bool save = false;
	bool load = false;
	sf::String loadPath = "gamedata.txt";
	sf::String cardTheme = "images\\cards\\card_back_black.png";
	int backgroundColor[3] = { 44, 89, 56 };
	sf::Color backgroundColour = sf::Color(44, 89, 56);
	sf::Color primaryColour = sf::Color::Blue;
	sf::Color outlineColour = sf::Color::White;
	sf::Color secondaryColour = sf::Color(51, 51, 255);
};
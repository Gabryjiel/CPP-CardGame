#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

struct GameSettings {
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 640), "Planowanie");;
	std::vector <int> players = {0, 1111, 2222, 3333};
	std::vector <int> rounds = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int cardTheme = 0;
	int backgroundColor[3] = { 44, 89, 56 };
	sf::Color backgroundColour = sf::Color(44, 89, 56);
};
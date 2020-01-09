#pragma once
#include "SFML//Graphics/Rect.hpp"
#include "SFML/System/String.hpp"

struct Commands {
	sf::FloatRect hitbox;
	sf::String command;
	int code;
};
#pragma once
#include  "SFML/Graphics.hpp"
#include <Windows.h>
#include "resource.h"

class GCard : public sf::Sprite{
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	GCard();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void loadImage(sf::String path);
	void loadImageA();
	sf::FloatRect getSize();
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f vec);
	void scale(float x, float y);
};
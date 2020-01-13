#pragma once
#include  "SFML/Graphics.hpp"
#include <Windows.h>


class Picture : public sf::Drawable{
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape opacity;

public:
	Picture();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void loadImage(sf::String path);

	sf::FloatRect getSize();
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f vec);
	void scale(float x, float y);
	void setOpacityColour(sf::Color color);
	void setOpacityLevel(int opacityLevel);
	int getOpacityLevel();
};
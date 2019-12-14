#pragma once
#include  "SFML/Graphics.hpp"

class GCard : public sf::Sprite{
	sf::Texture image;
	sf::Sprite sprite;

public:
	GCard();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void loadImage(sf::String path);
	sf::FloatRect getSize();
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f vec);
};
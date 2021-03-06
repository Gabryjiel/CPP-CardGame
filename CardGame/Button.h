#pragma once
#include "SFML/Graphics.hpp"
class Button : public sf::Drawable{
	sf::RectangleShape background;
	sf::Text text;
	int hFormat;
	int vFormat;
	sf::Font defaultFont;
public:
	Button(sf::String newString = "");
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void setText(sf::String newString);
	void setTextColour(sf::Color color);
	void setPosition(float x, float y);
	void setFormating(int hFormat, int vFormat);
	void setSize(float height, float width);
	void setOutlineThickness(float size);
	void setOutlineColor(sf::Color color);
	void setBackgroundColor(sf::Color color);
	void setTextSize(int size);
	
	bool isOn(float x, float y);
	sf::FloatRect getGlobalBounds();
};


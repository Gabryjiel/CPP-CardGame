#include "Button.h"

Button::Button(const char* newString) {
	hFormat = 0;
	vFormat = 0;
	if (defaultFont.getInfo().family == "")
		defaultFont.loadFromFile("C:\\WINDOWS\\Fonts\\arial.ttf");
	text.setFont(defaultFont);
	setText(newString);
	
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(background);
	target.draw(text);
}

void Button::setText(sf::String newString) {
	text.setString(newString);
	sf::FloatRect a = this->text.getGlobalBounds();
	background.setSize(sf::Vector2f(a.width, float(text.getCharacterSize())));
	background.setFillColor(sf::Color::Red);
	background.setOutlineColor(sf::Color::Red);
	background.setOutlineThickness(2);
}

void Button::setPosition(float x, float y) {
	background.setPosition(x, y);

	float outlineThickness = background.getOutlineThickness();
	background.setOutlineThickness(0);
	int tmpX = int(x), tmpY = int(y);
	
	if (hFormat == 0)
		tmpX = int(x) - 1;
	else if (hFormat == 1)
		tmpX = int(x) - 1 + int(background.getGlobalBounds().width) / 2 - int(text.getLocalBounds().width)/2 - 1;
	else if (hFormat == 2)
		tmpX = int(x) - 1 + int(background.getGlobalBounds().width) - int(text.getLocalBounds().width);

	if (vFormat == 0)
		tmpY = int(y) - text.getCharacterSize() + int(text.getLocalBounds().height);
	else if (vFormat == 1)
		tmpY = int(y) - text.getCharacterSize() + int(text.getLocalBounds().height) 
		+ int(background.getGlobalBounds().height) / 2 - int(text.getLocalBounds().height) / 2;
	else if (vFormat == 2)
		tmpY = int(y) - text.getCharacterSize() + int(text.getLocalBounds().height)
		+ int(background.getGlobalBounds().height) - text.getCharacterSize();
	
	text.setPosition(float(tmpX), float(tmpY));
	background.setOutlineThickness(outlineThickness);
}

void Button::setFormating(int hFormat, int vFormat){
	this->hFormat = hFormat;
	this->vFormat = vFormat;
}

void Button::setSize(float height, float width) {
	background.setSize(sf::Vector2f(width, height));
}

void Button::setOutlineThickness(float size) {
	background.setOutlineThickness(size);
}

void Button::setOutlineColor(sf::Color color) {
	background.setOutlineColor(color);
}

void Button::setBackgroundColor(sf::Color color) {
	background.setFillColor(color);
}

bool Button::isOn(float x, float y) {
	return background.getGlobalBounds().contains(x, y);
}
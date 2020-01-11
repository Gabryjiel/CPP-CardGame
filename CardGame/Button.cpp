#include "Button.h"

Button::Button(sf::String newString) {
	hFormat = 0;
	vFormat = 0;
	sf::Font::Info fontInfo = defaultFont.getInfo();
	if (fontInfo.family == "")
		defaultFont.loadFromFile("C:\\WINDOWS\\Fonts\\arial.ttf");
	text.setFont(defaultFont);
	setText(newString);
	
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(background);
	target.draw(text);
}

void Button::setText(sf::String newString) {
	text.setString(newString);
	/*sf::FloatRect a = this->text.getGlobalBounds();
	background.setSize(sf::Vector2f(a.width, float(text.getCharacterSize())));
	background.setFillColor(sf::Color::Red);
	background.setOutlineColor(sf::Color::Red);
	background.setOutlineThickness(2);*/
}

void Button::setTextColour(sf::Color color){
	text.setFillColor(color);
}

void Button::setPosition(float x, float y) {
	background.setPosition(x, y);

	float outlineThickness = background.getOutlineThickness();
	background.setOutlineThickness(0);
	float tmpX = x, tmpY = y;

	if (hFormat == 0)
		tmpX = x - 1;
	else if (hFormat == 1)
		tmpX = x - 1 + int(background.getGlobalBounds().width) / 2 - text.getGlobalBounds().width/2 - 1;
	else if (hFormat == 2)
		tmpX = x - 1 + background.getGlobalBounds().width - text.getGlobalBounds().width;

	if (vFormat == 0)
		tmpY = y - text.getCharacterSize() + text.getGlobalBounds().height;
	else if (vFormat == 1)
		tmpY = y - text.getCharacterSize() + text.getGlobalBounds().height
		+ background.getGlobalBounds().height / 2 - text.getGlobalBounds().height / 2;
	else if (vFormat == 2)
		tmpY = y - text.getCharacterSize() + text.getGlobalBounds().height
		+ background.getGlobalBounds().height - text.getCharacterSize();
	
	text.setPosition(tmpX, tmpY);
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

void Button::setTextSize(int size){
	text.setCharacterSize(size);
}

bool Button::isOn(float x, float y) {
	return background.getGlobalBounds().contains(x, y);
}

sf::FloatRect Button::getGlobalBounds(){
	return background.getGlobalBounds();
}

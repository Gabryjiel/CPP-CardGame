#include "Picture.h"

Picture::Picture() {
	opacity.setFillColor(sf::Color(0, 0, 0, 0));
}

void Picture::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
	target.draw(opacity);
}

void Picture::loadImage(sf::String path) {
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	opacity.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
}

sf::FloatRect Picture::getSize(){
	return this->sprite.getGlobalBounds();
}

void Picture::setPosition(float x, float y){
	sprite.setPosition(x, y);
	opacity.setPosition(x, y);
}

void Picture::setPosition(sf::Vector2f vec) {
	sprite.setPosition(vec);
	opacity.setPosition(vec);
}

void Picture::scale(float x, float y){
	sprite.scale(x, y);
	opacity.scale(x, y);
}

void Picture::setOpacityLevel(int opacityLevel){
	sf::Color colour = opacity.getFillColor();
	colour.a = opacityLevel;
	opacity.setFillColor(colour);
}

void Picture::setOpacityColour(sf::Color color) {
	opacity.setFillColor(color);
}

int Picture::getOpacityLevel(){
	return opacity.getFillColor().a;
}
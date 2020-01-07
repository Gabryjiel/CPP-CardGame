#include "GCard.h"

GCard::GCard() {

}

void GCard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);
}

void GCard::loadImage(sf::String path) {
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	sprite.scale(float(0.15), float(0.15));
}

sf::FloatRect GCard::getSize(){
	return this->sprite.getGlobalBounds();
}

void GCard::setPosition(float x, float y){
	sprite.setPosition(x, y);
}

void GCard::setPosition(sf::Vector2f vec) {
	sprite.setPosition(vec);
}

void GCard::scale(float x, float y){
	sprite.scale(x, y);
}

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


void GCard::loadImageA() {
		HRSRC rsrcData = FindResource(NULL, MAKEINTRESOURCE(IDB_PNG1), RT_RCDATA);
		if (!rsrcData)
			throw std::runtime_error("Failed to find resource.");

		DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
		if (rsrcDataSize <= 0)
			throw std::runtime_error("Size of resource is 0.");

		HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
		if (!grsrcData)
			throw std::runtime_error("Failed to load resource.");

		LPVOID firstByte = LockResource(grsrcData);
		if (!firstByte)
			throw std::runtime_error("Failed to lock resource.");

		if (!image.loadFromMemory(firstByte, rsrcDataSize))
			throw std::runtime_error("Failed to load image from memory.");
		texture.loadFromImage(image);
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

#include "Card.h"

int Card::_id = 0;

int Card::getId() const {
	return id;
}

int Card::getColor() const {
	return id / CARDS;
}

int Card::getFigure() const {
	return id % CARDS;
}
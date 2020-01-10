#include "Card.h"

int Card::_id = 1;

int Card::getId() const {
	return id;
}

int Card::getColor() const {
	return (id - 1) / CARDS;
}

int Card::getFigure() const {
	return (id - 1) % CARDS;
}
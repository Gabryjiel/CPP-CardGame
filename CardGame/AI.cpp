#include "AI.h"

AI::AI(std::vector<Player>* players, Card** triumph, std::vector<Card*>* deck) {
	player = players;
	this->triumph = triumph;
	this->table = deck;
}

AI::~AI() {
	player = nullptr;
	triumph = nullptr;
}

int AI::declare(int playerNr, int aiLevel) {
	int triumphColor = (*triumph)->getColor();
	float declaration = 0;
	int cardsInColor = 0;

	std::vector<Card*> deck = player->at(aiLevel % 1000).getDeck();
	for (int color = 0; color < 4; color++) {
		float temp = 0;
		int cardsInColor = 0;
		for (int i = 0; i < int(deck.size()); i++) {
			temp = float(deck[i]->getFigure()) / 13;
			if (deck[i]->getColor() == color)
				cardsInColor++;
		}
		if (color == triumphColor) {
			declaration += temp;
		}
		else {
			if(cardsInColor > 0)
				declaration += (temp / cardsInColor);
		}
	}
	if ((10 - (aiLevel % 100)) <= int(declaration * 10) % 10)
		return ceil(declaration);
	else
		return floor(declaration);
}

int AI::selectCard(int playerNr, int difficulty) {
	std::vector<Card*> deck = player->at(playerNr).getDeck();
	std::vector<bool> allowed;
	std::vector<int> cardValue;
	int topColour = -1, triumphColour = (*triumph)->getColor();
	int topCCards = 0, triumphCCards = 0;

	for (int i = 0; i < int(table->size()); i++) {
		if (table->at(i) == NULL) {

		}
		else if (topColour == -1)
			topColour = table->at(i)->getColor();
		else if (i > 0 && table->at(i - 1) == NULL)
			topColour = table->at(i)->getColor();
	}

	allowed.resize(deck.size(), false);
	cardValue.resize(deck.size(), false);

	for (int i = 0; i < deck.size(); i++) {
		cardValue[i] = deck[i]->getId();
		if (deck[i]->getColor() == topColour) {
			cardValue[i] += 100;
			topCCards++;
		}
		if (deck[i]->getColor() == triumphColour) {
			cardValue[i] += 200;
			triumphCCards++;
		}
	}

	for (int i = 0; i < allowed.size(); i++) {
		if (topColour == -1 || deck[i]->getColor() == topColour || (topCCards == 0 && (triumphCCards == 0 || deck[i]->getColor() == triumphColour)) )
			allowed[i] = true;
	}

	
	int cardToThrow = 0, index = 0, value;

	if (player->at(playerNr).getTaken() > player->at(playerNr).getDeclaration()) {
		for (int i = 0, value = -1; i < deck.size(); i++) {
			if (cardValue[i] > value && allowed[i] == true)
				index = i;
		}
	}
	else{
		for (int i = 0, value = INT16_MAX; i < deck.size(); i++) {
			if ((cardValue[i] < value || value == -1) && allowed[i] == true)
				index = i;
		}
	}
	
	return index;
}
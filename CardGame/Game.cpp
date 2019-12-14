#include "Game.h"
#include <windows.h>

Game::~Game(){
	delete console;
	delete[] player;
	delete ai;
}

void Game::start() {
	this->startRound();
	for (int i = round; i > 0; i--) {
		this->singleRound();
		this->sumUpRound();
	}
	this->endRound();
}

void Game::startRound() {
	this->setDefaultDeck();
	//this->mainDeck.shuffle();

	for (int i = 0; i < round * numberOfPlayers; i++) {
		player[i % numberOfPlayers].addCard(throwCard(0));
	}
	triumph = throwCard(0);
	clearDeck();

	for (int i = 0; i < numberOfPlayers; i++)
		player[i].sortDeck();
	
	console2->displayStart();
	console->displayStart();
	console->displayTriumph(triumph);

	for (int i = 0; i < this->numberOfPlayers; i++) {
		int aiLevel = this->player[i].getAI();
		if (!aiLevel)
			console->declare(round);
		else
			ai->declare(aiLevel);
	}
	
}

int Game::cardSelector(int player) {
	int selection;
	if (this->player[player].getAI() != 0)
		selection = ai->selectCard(player);
	else {
		bool check;
		do {
			check = false;;
			selection = console->selectCard(player);
			if (deck.size() != 0) {
				int topColor = getDeck()[0]->getColor();
				if (this->player[player].getDeck()[selection]->getColor() != topColor) {
					if (!this->player[player].checkForColor(topColor)) {//Brak koloru
						if (this->player[player].checkForColor(this->triumph->getColor())) {//Jest triumf
							if (this->player[player].getDeck()[selection]->getColor() != triumph->getColor()) {
								//ERROR
								check = true;
							}
						}
					}
					else {//Jest kolor
						if (this->player[player].getDeck()[selection]->getColor() != topColor) {
							//ERROR
							check = true;
						}
					}
				}
			}
		} while (check);
	}
	return selection;
}

void Game::singleRound() {
	for (int i = roundWinner; getDeckSize() != numberOfPlayers;) {
		addCard(player[i].throwCard(cardSelector(i)));
		console->displayStart();
		console->displayTable();

		if (i == this->numberOfPlayers - 1) i = 0;
		else i++;
		}
}

void Game::sumUpRound() {
	Card* analyzer;
	int topColor = deck[0]->getColor();
	int max = 0;
	for (unsigned int i = 0; i < deck.size(); i++) {
		analyzer = deck[i];
		
		int cardValue = analyzer->getFigure();
		
		if (analyzer->getColor() == triumph->getColor()) 
			cardValue += 200;
		else if (analyzer->getColor() == topColor) 
			cardValue += 100;

		if (cardValue > max) {
			max = cardValue;
			roundWinner = (roundWinner + i) % numberOfPlayers;
		}
		
	}
	player[roundWinner].setTaken(player[roundWinner].getTaken() + 1);
	clearDeck();
	console->displayWinner(roundWinner);
}


void Game::endRound() {
	console->displayResult();

	for (int i = 0; i < numberOfPlayers; i++) {
		this->player[i].clearDeck();
	}
	this->round--;
}
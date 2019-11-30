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

void Game::singleRound() {
	for (int i = roundWinner; getDeckSize() != numberOfPlayers;) {
		if (player[i].getAI() == 0) {
			addCard(player[i].throwCard(console->selectCard(i)));
		}
		else {
			addCard(player[i].throwCard(0));
		}

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
			roundWinner = i;
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
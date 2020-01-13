#include "Game.h"
#include <windows.h>

Game::Game(int nOP) {
	numberOfPlayers = nOP;
	player.resize(numberOfPlayers);
	this->deck.resize(numberOfPlayers);
	ai = new AI(&player, &triumph, &deck);
	roundWinner = 0;
	round = 0;
}

Game::~Game(){
	player.clear();
	delete ai;
}

void Game::prepareRound(int numberOfCards, bool newGame) {
	
	numberOfPlayers = player.size();
	if (player[0].getDeckSize() == 0) {
		if (newGame) {
			player.clear();
			player.resize(numberOfPlayers);
		}
		setDefaultDeck();
		shuffle();
		for (int i = 0; i < numberOfCards * numberOfPlayers; i++) {
			if (i > 52) throw std::runtime_error("Not enough cards in the deck.");
			player[i % numberOfPlayers].addCard(throwCard(0));
		}
		triumph = throwCard(0);
		clearDeck();
		deck.resize(numberOfPlayers);

		for (int i = 0; i < numberOfPlayers; i++)
			player[i].sortDeck();
	}

	for (int i = 0; i < int(player.size()); i++) {
		int aiLevel = player[i].getAI();
		if (!aiLevel)
			ai->declare(i, aiLevel);
	}
	
}

void Game::setDeclaration(int player, int declaration){
	this->player[player].setDeclaration(declaration);
}

void Game::sumUpTable() {
	int max = 0;
	int topColor = deck[roundWinner]->getColor();
	
	for (int i = 0; i < int(deck.size()); i++) {
		Card* temp = deck[i];
		if (temp != NULL) {
			int tempId = deck[i]->getId();
			if (deck[i]->getColor() == topColor)
				tempId += 100;
			if (deck[i]->getColor() == triumph->getColor())
				tempId += 200;
			if (tempId > max) {
				roundWinner = i;
				max = tempId;
			}
		}
	}

	player[roundWinner].setTaken(player[roundWinner].getTaken() + 1);
	clearDeck();
	this->deck.resize(numberOfPlayers);
}

void Game::sumUpRound(){
	for (int i = 0; i < numberOfPlayers; i++) {
		if (player[i].getDeclaration() == player[i].getTaken()) {
			player[i].pointsScore(true);
		}
		else player[i].pointsScore(false);

		player[i].setTaken(0);
	}
}

int Game::getRoundWinner(){
	return roundWinner;
}

void Game::makeAMove(int player, int card){
	if (card == -1)
		card = ai->selectCard(player, 0);
	addCard(player, this->player[player].throwCard(card));
}

int Game::aiCardSelection(int player, int difficulty){
	return ai->selectCard(player, difficulty);
}
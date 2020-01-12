#include "Game.h"
#include <windows.h>

Game::~Game(){
	player.clear();
	delete ai;
}

void Game::start() {
	this->prepareRound(round, true);
	for (int i = round; i > 0; i--) {
		this->singleRound();
		this->sumUpRound();
	}
	this->endRound();
}

void Game::prepareRound(int numberOfCards, bool newGame) {
	//this->shuffle();
	numberOfPlayers = player.size();
	if (player[0].getDeckSize() == 0) {
		if (newGame) {
			player.clear();
			player.resize(numberOfPlayers);
		}
		setDefaultDeck();
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
	console2->displayStart();
	

	for (int i = 0; i < player.size(); i++) {
		int aiLevel = player[i].getAI();
		if (!aiLevel)
			ai->declare(aiLevel);
	}
	
}

void Game::setDeclaration(int player, int declaration){
	this->player[player].setDeclaration(declaration);
}

int Game::cardSelector(int player) {
	int selection;
	if (this->player[player].getAI() != 0)
		selection = ai->selectCard(player, 0);
	else {
		bool check;
		do {
			check = false;;
//			selection = console->selectCard(player);
			selection = 0;
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
		addCard(i, player[i].throwCard(cardSelector(i)));
//		console->displayStart();
//		console->displayTable();

		if (i == this->numberOfPlayers - 1) i = 0;
		else i++;
		}
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
//	console->displayWinner(roundWinner);
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


void Game::endRound() {
//	console->displayResult();

	for (int i = 0; i < numberOfPlayers; i++) {
		this->player[i].clearDeck();
	}
	this->round--;
}
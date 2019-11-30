#include "deck.h"
#include <cstdlib>
#include <ctime>

Card* Deck::allDeck = new Card[DEFAULTDECK];
int Deck::numberOfDecks = 0;
//std::unique_ptr<Card> allDeck = std::make_unique<Card>(52);

Deck::Deck() {
	numberOfDecks++;
}

Deck::~Deck() {
	deck.clear();
	numberOfDecks--;
	if (numberOfDecks == 0)
		delete[] allDeck;
}

std::vector <Card*> Deck::getDeck() const{
	return deck;
}

int Deck::getDeckSize() const {
	return deck.size();
}

bool Deck::shuffle() {
	srand((int) time(0));
	for (int i = 0; i < 52*52; i++) {
		std::swap(deck[rand() % deck.size()], deck[rand() % deck.size()]);
	}
	return true;
}

void Deck::setDefaultDeck() {
	deck.resize(DEFAULTDECK);
	for (int i = 0; i < DEFAULTDECK; i++)
		deck[i] = &allDeck[i];
}

void Deck::addCard(Card* newCard) {
	this->deck.push_back(newCard);
}

Card * Deck::throwCard(int id) {
	Card* temp = deck[id];
	this->deck.erase(this->deck.begin() + id);
	return temp;
}

void Deck::clearDeck() {
	this->deck.clear();
}

void Deck::sortDeck() {
	for (unsigned int i = 0; i < deck.size(); i++) {
		for (unsigned int j = 0; j < deck.size(); j++) {
			if (deck[i]->getId() < deck[j]->getId()) {
				std::swap(deck[i], deck[j]);
			}
		}
	}
}
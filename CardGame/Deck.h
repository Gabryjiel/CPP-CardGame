#pragma once
#include "Card.h"
#include <iostream>
#include <vector>
//#include <memory>

class Deck{
protected:
	std::vector <Card*> deck;
	static int numberOfDecks;
	static Card* allDeck;
	//std::unique_ptr<Card> allDeck;
public:
	Deck();
	~Deck();

	std::vector<Card*> getDeck() const;	//Return "deck"
	int getDeckSize() const;	//Returns number of Cards in the vector
	void clearDeck();	//Removes all elements from "deck"

	void setDefaultDeck();

	bool checkForColor(int color);
	void addCard(int player, Card* newCard);
	void addCard(int id);
	void addCard(Card* newCard);
	bool shuffle();	//Randomizes position of Cards in the vector
	Card * throwCard(int id);	//Removes Card from the vector with id
	void sortDeck();

};
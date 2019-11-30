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

	void addCard(Card* newCard);	//Adds Card to the vector
	bool shuffle();	//Randomizes position of Cards in the vector
	Card * throwCard(int id);	//Removes Card from the vector with id
	void sortDeck();

};
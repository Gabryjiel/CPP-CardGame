#pragma once
#include "Player.h"
#include <vector>
#include <iostream>

struct SaveData {

	std::vector<Player>* players;
	Deck* table;
	Card** triumph;
	int roundsPlayed;
	int cardsPlayed;
	int playerToMove;
	int cardsOnTable;
	std::vector<int>* rounds;
	std::vector<int>* playersSettings;

	friend std::ostream& operator<<(std::ostream& output, const SaveData& save);
	friend std::istream& operator>>(std::istream& input, SaveData& save);
	void reset();
};

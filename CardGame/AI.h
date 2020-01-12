#pragma once
#include "Player.h"

class AI {
	Card** triumph;
	std::vector<Player>* player;
	std::vector<Card*>* table;

public:
	AI(std::vector<Player>* players, Card** triumph, std::vector<Card*>* deck);
	~AI();

	int declare(int playerNr, int aiLevel);
	int selectCard(int player, int difficulty);

};
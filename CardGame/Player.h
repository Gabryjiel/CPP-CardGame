#pragma once
#include "Deck.h"
class Player : public Deck{
private:
	int AI;
	int taken;
	std::vector<int> points;

public:
	Player();
	Player(const Player& pattern);
	~Player();

	int getAI();	//Returns isAI
	int getTaken();
	int getPoints(int position = -1);
	int getDeclaration();

	void setAI(int AI);	//Sets isAI (0 - Player, 1 - Easy, 2 - Normal, 3 - Hard)
	void setTaken(int taken);
	void setDeclaration(int declaration);
	void pointsScore(bool result);

};


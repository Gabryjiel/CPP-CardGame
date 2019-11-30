#pragma once

#define CARDS 13 //How many figures are in game (13 means from 2 to Ace; no Jokers)
#define DEFAULTDECK 52 //Number of Cards in default deck needed for game

class Card {
private:
	const int id;
	static int _id;

public:
	Card() :id{ _id++ } {
		if (DEFAULTDECK - 1 < _id) _id = 0;
	}
	//Returns ID of the Card
	int getId() const;
	//Returns Color of the Card
	int getColor() const;
	//Return Figure of the Card
	int getFigure() const;
};

/* Ids are from 0 to 51*/

/* Colors:
0 - Spades
1 - Clubs
2 - Diamonds
3 - Hearts*/

/* Figures
0  - Two
1  - Three
2  - Four
3  - Five
4  - Six
5  - Seven
6  - Eight
7  - Nine
8  - Ten
9  - Jack
10 - Queen
11 - King
12 - Ace*/
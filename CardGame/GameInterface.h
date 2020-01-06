#pragma once
#include "GCard.h"
#include "Player.h"
#include "GameSettings.h"
#include <functional>

#define BACKGROUNDCOLOR sf::Color(44, 89, 56)

typedef struct{
	sf::Vector2f hand;
	sf::Vector2f table;
	std::function <sf::Vector2f(int, int, sf::FloatRect, sf::Vector2f)> gap;
}Position;

class GameInterface{
	sf::RenderWindow* window;
	GCard* cards;
	Position* positions;
	GameSettings* settings;

	Player* player;
	std::vector <Card*>* table;
	int numberOfPlayers;

public:
	GameInterface(GameSettings& settings, Player* player, std::vector<Card*>* table, int nOP = 0);
	~GameInterface();

	void displayStart();
	void displayTriumph(Card* triumph);
	void displayResult();
	void displayTable();
	void displayWinner(int roundWinner);
	void drawBackground();

	int selectCard(int player);
	int declare(int round);
	void loadCards();
	void setPositions();
	void display();
	bool checkEvent(sf::Event& event);
	sf::String checkCoords(sf::Vector2u* codes);
};


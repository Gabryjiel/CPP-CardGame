#pragma once
#include "View.h"
#include "GCard.h"
#include "Player.h"
#include "GameSettings.h"
#include "Button.h"
#include <functional>

typedef struct{
	sf::Vector2f hand;
	sf::Vector2f table;
	std::function <sf::Vector2f(int, int, sf::FloatRect, sf::Vector2f)> gap;
}Position;

class GameView : public View{
	GCard* cards;
	std::vector<Position> positions;

	std::vector<Player>* player;
	std::vector <Card*>* table;
	Card** triumph;
	int numberOfPlayers;

public:
	GameView(GameSettings& settings, std::vector<Player>* player, std::vector<Card*>* table, Card** triumph, int nOP = 0);
	~GameView();
	
	void drawScene(const sf::String mode);
	bool checkEvent(sf::Event& event);
	sf::String checkCoords(sf::Vector2u& codes);
	
	void drawStart();
	void drawTriumph();
	void drawResult();
	void drawTable();
	void displayWinner(int roundWinner);
	void drawBackground();
	void drawDeclaration();

	int selectCard(int player);
	int declare(int round);
	void loadCards();
	void setPositions();
	
};


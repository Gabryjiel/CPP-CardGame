#pragma once
#include "View.h"
#include "Picture.h"
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
	Picture* cards;
	Picture back;
	std::vector<Position> positions;
	int* selection;

	std::vector<Player>* player;
	std::vector <Card*>* table;
	Card** triumph;
	int numberOfPlayers;

	int getBestCard();
public:
	GameView(GameSettings& settings, std::vector<Player>* player, std::vector<Card*>* table, Card** triumph, int* code);
	~GameView();
	
	void drawScene(const sf::String mode);
	bool checkEvent(sf::Event& event);
	sf::String checkCoords(sf::Vector2u& codes);
	sf::String checkCode(int code);
	void start();
	
	void drawStart();
	void drawTriumph();
	void drawResult();
	void drawTable();
	void displayWinner(int roundWinner);
	void drawScen(const std::initializer_list<sf::String>& mode);
	void drawScene(const sf::String mode ...);
	void drawBackground();
	int getTopColour(bool reset = false);
	bool allowedCard(int id);
	int getNumberOfCardsInDeck(std::vector<Card*> vector);
	void drawDeclaration();

	void drawScoreboard();

	int selectCard(int player);
	int declare(int round);
	void loadCards();
	void scaleAllCards();
	void setPositions();
	
};


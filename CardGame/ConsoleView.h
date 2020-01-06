#pragma once
#include <Windows.h>
#include "Player.h"

class ConsoleView {
private:
	Player* player;
	std::vector <Card*>* table;
	Card* triumph;
	int numberOfPlayers;

	void setCursor(int x, int y);
	int prepareConsole();
	void cursorDown();
	void printCard(const Card* card);
	void printDeck(const std::vector<Card*> deck);
	void printDeck(const std::vector <Card*>* deck);

public:
	ConsoleView(Player* player, std::vector<Card*> *table, Card* triumph, int nOP = 0);
	int selectCard(int player);

	void displayStart();
	void displayTriumph(Card* triumph);
	void displayResult();
	void displayWinner(int winner);
	void displayTable();
	
	int declare(int round);
	
};
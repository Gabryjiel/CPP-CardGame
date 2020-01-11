#pragma once
#include "Player.h"
#include "ConsoleView.h"
#include "AI.h"

class Game : public Deck{
	friend class GameController;
	friend struct SaveData;
	//friend Controller::Controller();
	int round; 
	int roundWinner;
	int numberOfPlayers;

	std::vector<Player> player;
	Card* triumph;
	ConsoleView* console2;
	AI* ai;
	

	//Sets up the round
	//Sets up "mainDeck", players "hand" and "triumph"
	

	int cardSelector(int player);

	//Sums up the round
	//Clears players "deck", "collected" and "table", decrements "round",
	void endRound();
	
	//Round through
	void singleRound();

public:
	Game(int nOP) {
		numberOfPlayers = nOP;
		player.resize(numberOfPlayers);
		this->deck.resize(numberOfPlayers);
		ai = new AI;
		roundWinner = 0;
		console2 = new ConsoleView(&player, &deck, triumph, nOP);
	};
	~Game();
	
	void start();
	void prepareRound(int numberOfCards, bool newGame);
	void setDeclaration(int player, int declaration);
	void sumUpTable();
	void sumUpRound();
	int getRoundWinner();
	void makeAMove(int player, int card);
	int aiCardSelection(int player, int difficulty);
};


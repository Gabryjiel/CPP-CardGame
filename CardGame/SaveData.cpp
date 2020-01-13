#include "SaveData.h"

std::ostream& operator<<(std::ostream& output, const SaveData& save){
	std::vector<Card*> temp;
	
	for (int player = 0; player < int(save.players->size()); player++) { //Zapis kart graczy
		temp = save.players->at(player).getDeck();
		for (int deckSize = 0; deckSize < int(temp.size()); deckSize++) {
			output << (temp.at(deckSize)->getId()) << ' ';
		}
		output << -100 << '\n';
	}
	output << -200 << '\n';

	for (int i = 0; i < int(save.players->size()); i++) { //Zapis punktów i deklaracji graczy
		for(int j = 0; ; j++){
			if (save.players->at(i).getPoints(j) == 1000)
				break;
			output << save.players->at(i).getPoints(j) << ' ';	
		}
		output << -100 << '\n';
	}
	
	for (int i = 0; i < int(save.players->size()); i++) { //Zapis zawartoœci sto³u
		std::vector<Card*> temp = save.table->getDeck();
		if (temp.at(i) != NULL)
			output << temp.at(i)->getId() << ' ';
		else
			output << -1 << ' ';
	}
	output << -100 << '\n';

	output << ((*(save.triumph))->getId()) << '\n'; //Zapis triumfa

	for (int i = 0; i < int(save.rounds->size()); i++)	//Zapis rund
		output << save.rounds->at(i) << ' ';
	output << -100 << '\n';

	for (int i = 0; i < int(save.playersSettings->size()); i++)	//Zapis ustawien graczy
		output << save.playersSettings->at(i) << ' ';
	output << -100 << '\n';

	output << save.roundsPlayed << ' ' << save.cardsPlayed << ' ' // Zapis ustawien gry
		<< save.playerToMove << ' ' << save.cardsOnTable;

	return output;
}

std::istream& operator>>(std::istream& input, SaveData& save){
	int temp = 0;
	bool exit = true;

	int i = 0;
	if(save.players->size() > 0)
		save.players->clear();
	while (exit) {	//Wczytanie kart graczy
		while (true) {
			input >> temp;
			if (temp == -100)
				break;
			else if (temp == -200) {
				exit = false;
				break;
			}
			else {
				if (save.players->size() <= i)
					save.players->resize(save.players->size() + 1);
				save.players->at(i).addCard(temp);
			}
		}
		i++;
	}
	exit = true;

	for (int i = 0; i < int(save.players->size()); i++) {	//Wczytanie punktów i deklaracji graczy
		while (true) {
			input >> temp;
			if (temp == -100) break;
			save.players->at(i).setDeclaration(temp);
		}
	}

	save.table->clearDeck(); //Wczytanie zawartoœci sto³u
	while (true) {
		input >> temp;
		if (temp == -100) break;
		if (temp == NULL || temp == -1)
			save.table->addCard(nullptr);
		else
			save.table->addCard(temp);
	}

	input >> temp;	//Wczytanie trumfa
	save.table->addCard(temp);
	*(save.triumph) = save.table->throwCard(save.table->getDeckSize() - 1);

	save.rounds->clear();	//Wczytanie rund
	while (true) {
		input >> temp;
		if (temp == -100) break;
		save.rounds->push_back(temp);
	}

	save.playersSettings->clear();	//Wczytanie ustawien graczy
	while (true) {
		input >> temp;
		if (temp == -100) break;
		save.playersSettings->push_back(temp);
	}

	input >> save.roundsPlayed >> save.cardsPlayed >> save.playerToMove >> save.cardsOnTable; //Wczytanie ustawien gry

	return input;
}

void SaveData::reset(){
	roundsPlayed = 0;
	cardsOnTable = 0;
	cardsPlayed = 0;
	playerToMove = -1;
}

#include "SaveData.h"

std::ostream& operator<<(std::ostream& output, const SaveData& save){
	std::vector<Card*> temp;
	for (int player = 0; player < int(save.players->size()); player++) {
		temp = save.players->at(player).getDeck();
		for (int deckSize = 0; deckSize < int(temp.size()); deckSize++) {
			output << (temp.at(deckSize)->getId()) << ' ';
		}
		output << -2 << '\n';
	}

	for (int i = 0; i < int(save.players->size()); i++) {
		output << save.players->at(i).getDeclaration() << ' ';
	}
	output << '\n';
	
	for (int i = 0; i < int(save.players->size()); i++) {
		std::vector<Card*> temp = save.table->getDeck();
		if (temp.at(i) != NULL)
			output << temp.at(i)->getId() << ' ';
		else
			output << NULL << ' ';
	}

	output << -2 << '\n' << ((*(save.triumph))->getId()) << '\n';

	for (int i = 0; i < int(save.rounds->size()); i++)
		output << save.rounds->at(i) << ' ';
	output << -2 << '\n';
	for (int i = 0; i < int(save.playersSettings->size()); i++)
		output << save.playersSettings->at(i) << ' ';
	output << -2 << '\n' << save.roundsPlayed << ' ' << save.cardsPlayed << ' '
		<< save.playerToMove << ' ' << save.cardsOnTable;

	return output;
}

std::istream& operator>>(std::istream& input, SaveData& save){
	int temp;
	
	for (int player = 0; player < int(save.players->size()); player++) {
		save.players->at(player).clearDeck();
		while (true) {
			input >> temp;
			if (temp == -2) break;
			save.players->at(player).addCard(temp);
		}
	}
	for (int i = 0; i < int(save.players->size()); i++) {
		input >> temp;
		save.players->at(i).setDeclaration(temp);
	}

	save.table->clearDeck();
	while (true) {
		input >> temp;
		if (temp == -2) break;
		if (temp == NULL)
			save.table->addCard(nullptr);
		else
			save.table->addCard(temp);
	}
	input >> temp;
	save.table->addCard(temp);
	*(save.triumph) = save.table->throwCard(save.table->getDeckSize() - 1);
	save.rounds->clear();
	while (true) {
		input >> temp;
		if (temp == -2) break;
		save.rounds->push_back(temp);
	}
	save.playersSettings->clear();
	while (true) {
		input >> temp;
		if (temp == -2) break;
		save.playersSettings->push_back(temp);
	}
	input >> save.roundsPlayed >> save.cardsPlayed >> save.playerToMove >> save.cardsOnTable;
	return input;
}

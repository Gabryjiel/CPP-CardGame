#include "GameView.h"
#include <Windows.h>

GameView::GameView(GameSettings& settings, std::vector<Player>* player, std::vector<Card*> *table, Card** triumph, int* code):View(settings){
	this->cards = new Picture[52];
	this->player = player;
	this->table = table;
	this->triumph = triumph;
	this->selection = code;
	loadCards();
}

GameView::~GameView() {
	delete[] this->cards;
}

sf::Vector2f gap_front_big(int cardNr, int size, sf::FloatRect CSize, sf::Vector2f input) {
	sf::Vector2f temp(input);
	if (size % 2 == 0) temp.x += float((-(size / 2) + 1.0 * cardNr + 0.5) * CSize.width);
	else temp.x += (-(size / 2) + cardNr) * CSize.width;
	
	return temp;
}

sf::Vector2f gap_front_small(int cardNr, int size, sf::FloatRect CSize, sf::Vector2f input) {
	if (size % 2 == 0) input.x += float((-(size / 2) + 1.0 * cardNr + 0.5) * (CSize.width/2));
	else input.x += (-(size / 2) + cardNr) * (CSize.width/2);
	return input;
}

sf::Vector2f gap_front_tiny(int cardNr, int size, sf::FloatRect CSize, sf::Vector2f input) {
	if (size % 2 == 0) input.x += float((-(size / 2) + 1.0 * cardNr + 0.5) * (CSize.width / 10));
	else input.x += (-(size / 2) + cardNr) * (CSize.width / 10);
	return input;
}

sf::Vector2f gap_side_big(int cardNr, int size, sf::FloatRect CSize, sf::Vector2f input) {
	if (size % 2 == 0) input.y += - CSize.height + (-(size / 2) + cardNr) * (CSize.height/5);
	else input.y += -CSize.height + (-(size / 2) + cardNr) * (CSize.height / 5);
	return input;
}

sf::Vector2f gap_side_small(int cardNr, int size, sf::FloatRect CSize, sf::Vector2f input) {
	if (size % 2 == 0) input.y += -CSize.height + (-(size / 2) + cardNr) * (CSize.height / 10);
	else input.y += -CSize.height + (-(size / 2) + cardNr) * (CSize.height / 10);
	return input;
}

void GameView::setPositions() {
	sf::Vector2f handPos[12], tablePos[12];
	float x = float(settings->window->getSize().x), y = float(settings->window->getSize().y);
	float cardX = cards[0].getSize().width, cardY = cards[0].getSize().height;
	handPos[0] = { x / 2 - cardX / 2 , y - cardY };

	handPos[1] = { x - cardX, y * 9 / 10 };
	handPos[2] = { x - cardX, y * 7 / 10 };
	handPos[3] = { x - cardX, y * 6 / 10 };

	handPos[4] = { x * 9 / 10 - cardX * 1 / 2, 0 };
	handPos[5] = { x * 7 / 10 - cardX * 1 / 2, 0 };
	handPos[6] = { x * 5 / 10 - cardX * 1 / 2, 0 };
	handPos[7] = { x * 3 / 10 - cardX * 1 / 2, 0 };
	handPos[8] = { x * 1 / 10 - cardX * 1 / 2, 0 };

	handPos[9] = { 0, y * 6 / 10 };
	handPos[10] = { 0, y * 7 / 10 };
	handPos[11] = { 0, y * 9 / 10 };

	tablePos[0] = { x / 2 - cardX / 2 , y - cardY * 2.5f };

	tablePos[1] = { x - cardX * 2.5f, y * 5 / 7 };
	tablePos[2] = { x - cardX * 2.5f, y * 4 / 7 };
	tablePos[3] = { x - cardX * 2.5f, y * 3 / 7 };

	tablePos[4] = { x * 9 / 10 - cardX * 1 / 2, cardY * 1.25f };
	tablePos[5] = { x * 7 / 10 - cardX * 1 / 2, cardY * 1.25f };
	tablePos[6] = { x * 5 / 10 - cardX * 1 / 2, cardY * 1.25f };
	tablePos[7] = { x * 3 / 10 - cardX * 1 / 2, cardY * 1.25f };
	tablePos[8] = { x * 1 / 10 - cardX * 1 / 2, cardY * 1.25f };

	tablePos[9] = { cardX * 1.5f, y * 3 / 7 };
	tablePos[10] = { cardX * 1.5f, y * 4 / 7 };
	tablePos[11] = { cardX * 1.5f, y * 5 / 7 };

	positions[0].hand = handPos[0];
	positions[0].table = tablePos[0];
	positions[0].gap = gap_front_small;
	int temp = numberOfPlayers - 1;
	if (numberOfPlayers - 1 > 4) {
		temp -= 4;
		positions[1].hand = handPos[1];
		positions[1].table = tablePos[1];
		positions[1].gap = gap_side_small;
		positions[2].hand = handPos[3];
		positions[2].table = tablePos[3];
		positions[2].gap = gap_side_small;
		positions[numberOfPlayers - 2].hand = handPos[9];
		positions[numberOfPlayers - 2].table = tablePos[9];
		positions[numberOfPlayers - 2].gap = gap_side_small;
		positions[numberOfPlayers - 1].hand = handPos[11];
		positions[numberOfPlayers - 1].table = tablePos[11];
		positions[numberOfPlayers - 1].gap = gap_side_small;
	}
	else if (numberOfPlayers - 1 > 2) {
		temp -= 2;
		positions[1].hand = handPos[2];
		positions[1].table = tablePos[2];
		positions[1].gap = gap_side_big;
		positions[numberOfPlayers - 1].hand = handPos[10];
		positions[numberOfPlayers - 1].table = tablePos[10];
		positions[numberOfPlayers - 1].gap = gap_side_big;
	}
	
	for (int i = ceil((numberOfPlayers - 1) / 2.0f), pom = 1; pom <= temp; i++, pom++) {
		if (temp == 1) {
			positions[i].hand = handPos[6];
			positions[i].table = tablePos[6];
			positions[i].gap = gap_front_small;
		}
		else if (temp == 2) {
			positions[i].hand = handPos[3 + 2 * pom];
			positions[i].table = tablePos[3 + 2 * pom];
			positions[i].gap = gap_front_small;
		}
		else if (temp == 3) {
			positions[--i].hand = handPos[2 + 2 * pom];
			positions[i].table = tablePos[2 + 2 * pom];
			positions[i++].gap = gap_front_tiny;
		}
		else if (temp == 4) {
			i--;
			positions[i].hand = handPos[i > 4 ? i + 2: i + 1];
			positions[i].table = tablePos[i + 1 > 5 ? i + 1: i + 2];
			positions[i++].gap = gap_front_tiny;
		}
		else if (temp == 5) {
			i -= 2;
			positions[i].hand = handPos[i+1];  
			positions[i].table = tablePos[i+1];
			positions[i].gap = gap_front_tiny;
			i += 2;
		}
	}
}

void GameView::start() {
	numberOfPlayers = settings->players.size();
	positions.resize(numberOfPlayers);
	setPositions();
}

void GameView::loadCards() {
	for (int i = 0; i < 52; i++) {
		sf::String cardname;

		if (i % 13 == 0) cardname = "2_of_";
		else if (i % 13 == 1) cardname = "3_of_";
		else if (i % 13 == 2) cardname = "4_of_";
		else if (i % 13 == 3) cardname = "5_of_";
		else if (i % 13 == 4) cardname = "6_of_";
		else if (i % 13 == 5) cardname = "7_of_";
		else if (i % 13 == 6) cardname = "8_of_";
		else if (i % 13 == 7) cardname = "9_of_";
		else if (i % 13 == 8) cardname = "10_of_";
		else if (i % 13 == 9) cardname = "jack_of_";
		else if (i % 13 == 10) cardname = "queen_of_";
		else if (i % 13 == 11) cardname = "king_of_";
		else if (i % 13 == 12) cardname = "ace_of_";

		if (i / 13 == 0) cardname += "spades";
		else if (i / 13 == 1) cardname += "clubs";
		else if (i / 13 == 2) cardname += "diamonds";
		else if (i / 13 == 3) cardname += "hearts";

		cards[i].loadImage("images\\cards\\" + cardname + ".png");
		cards[i].scale(0.15f, 0.15f);
	}
	back.loadImage(settings->cardTheme);
	back.scale(0.15f, 0.15f);
}

void GameView::drawScene(const sf::String mode) {
	if (mode == "Background")
		drawBackground();
	else if (mode == "Start")
		drawStart();
	else if (mode == "Result")
		drawResult();
	else if (mode == "Declaration")
		drawDeclaration();
	else if (mode == "Table")
		drawTable();
}

void GameView::drawBackground() {
	settings->window->clear(sf::Color(settings->backgroundColor[0], settings->backgroundColor[1], settings->backgroundColor[2]));
}

int GameView::getTopColour() {
	int topColour = -1;
	for (int i = 0, counter = 0; i < int(table->size()); i++) {
		if (table->at(i) == NULL)
			counter++;
		else if (topColour == -1)
			topColour = table->at(i)->getColor();
		else if (i > 0 && table->at(i - 1) == NULL)
			topColour = table->at(i)->getColor();
	}
	return topColour;
}

bool GameView::allowedCard(int id) {
	if (getTopColour() != -1) {

		std::vector <Card*> deck = player->at(0).getDeck();
		
		int cTopColor = 0, cTriumphColor = 0;
		for (int x = 0; x < deck.size(); x++) {
			if (deck[x]->getColor() == getTopColour()) {
				cTopColor++;
			}
			if (deck[x]->getColor() == (*triumph)->getColor()) {
				cTriumphColor++;
			}
		}

		for (int x = 0, nrCard = 0; x < deck.size(); x++) {
			if (cTopColor == 0) {
				if (cTriumphColor != 0) {
					if (deck[x]->getColor() != (*triumph)->getColor()) {
						if (id == deck[x]->getId())
							return false;
					}
				}
			}
			else {
				if (deck[x]->getColor() != getTopColour()) {
					if (id == deck[x]->getId())
						return false;
				}
			}
		}
	}
	return true;
}

void GameView::drawStart(){
	drawBackground();

	for (int i = 0; i < numberOfPlayers; i++) { //Gracze
		std::vector <Card*> deck = player->at(i).getDeck();
		int max = 0;

		for (unsigned int j = 0; j < deck.size(); j++) { //Deck
			int temp = deck[j]->getId();
			
			if (i == 0) {
				sf::Vector2f cardPos = positions[i].gap(j, deck.size(), cards->getSize(), positions[i].hand);
				if (j == *selection && commands[0].command == "ThrowCard") //Pozycja je�li jest selection na karcie
					cardPos.y -= (cards->getSize().height / 2);
				cards[temp].setPosition(cardPos);

				bool ameno = allowedCard(temp);
				if (!ameno) {
					cards[temp].setOpacityColour(sf::Color::Red);
					cards[temp].setOpacityLevel(100);
				}
				else max++;

				if ((commands.size() == 0 || j != 0) && i == 0 && commands.size() < max && ameno)
					addCommand(cards[temp].getSize(), "ThrowCard", j);
				draw(cards[temp]);
				cards[temp].setOpacityLevel(0);
			}
			else {
				back.setPosition(positions[i].gap(j, deck.size(), cards->getSize(), positions[i].hand));
				draw(back);
			}
		}
	}
	
	drawTriumph();
}

void GameView::drawTriumph(){
	int triumphId = (*triumph)->getId();
	cards[triumphId].scale(2, 2);
	cards[triumphId].setPosition(settings->window->getSize().x/2 - cards[triumphId].getSize().width/2,
		settings->window->getSize().y/2 - cards[triumphId].getSize().height/2);
	
	cards[triumphId].setOpacityColour(settings->backgroundColour);
	cards[triumphId].setOpacityLevel(170);

	draw(cards[triumphId]);
	cards[triumphId].scale(0.5, 0.5);
	cards[triumphId].setOpacityLevel(0);
}

void GameView::drawResult()
{
}

int GameView::getBestCard() {
	int max = -1, maxValue = 0, triumphColor = (*triumph)->getColor();
	static int topColor = getTopColour();

	for (int i = 0; i < int(table->size()); i++) {
		Card* temp = table->at(i);
		if (temp != NULL) {
			int tempId = table->at(i)->getId();
			if (table->at(i)->getColor() == topColor)
				tempId += 100;
			if (table->at(i)->getColor() == triumphColor)
				tempId += 200;
			if (tempId > maxValue) {
				max = i;
				maxValue = tempId;
			}
		}
	}
	return max;
}

void GameView::drawTable(){
	int max = getBestCard();
	for (int i = 0; i < int(settings->players.size()); i++) {
		Card* temp = table->at(i);
		if (!temp == NULL) {
			if (i == max) {
				cards[temp->getId()].setOpacityColour(sf::Color::Yellow);
				cards[temp->getId()].setOpacityLevel(100);
			}
			cards[temp->getId()].setPosition(positions[i].table);
			draw(cards[temp->getId()]);

			cards[temp->getId()].setOpacityColour(sf::Color::White);
			cards[temp->getId()].setOpacityLevel(0);
		}
	}
	
	
}

void GameView::displayWinner(int roundWinner)
{
}

void GameView::drawDeclaration() {
	int sum = 0;
	int numberOfCards = player->at(0).getDeckSize();
	for (int i = 0; i < numberOfPlayers; i++)
		sum += player->at(i).getDeclaration();

	Button declaration;
	declaration.setBackgroundColor(sf::Color::Blue);
	declaration.setOutlineColor(sf::Color::White);
	declaration.setOutlineThickness(1);
	declaration.setFormating(1, 1);
	declaration.setText(L"Zadeklaruj ile sztych�w we�miesz");
	declaration.setSize(40, 470);
	declaration.setPosition(float(settings->window->getSize().x / 2 - declaration.getGlobalBounds().width / 2), float(settings->window->getSize().y / 2));
	draw(declaration);

	clearCommands();
	declaration.setSize(40, 30);

	for (int i = 0; i < numberOfCards + 1; i++) {
		if (sum + i != numberOfCards || sum == 0 || numberOfCards < 3) {
			if (i == *selection) declaration.setBackgroundColor(sf::Color(51, 51, 255));
			else declaration.setBackgroundColor(sf::Color::Blue);

			declaration.setText(sf::String(std::to_string(i)));
			declaration.setPosition( float(settings->window->getSize().x / 2 + declaration.getGlobalBounds().width * (i -( (numberOfCards + 1)/2) ) ), float(settings->window->getSize().y * 3 / 4) );
			draw(declaration);
			if (commands.size() == 0 || i != 0)
				addCommand(declaration.getGlobalBounds(), "Declaration", i);
		}
	}

}

int GameView::selectCard(int player)
{
	return 0;
}

int GameView::declare(int round)
{
	return 0;
}

bool GameView::checkEvent(sf::Event& event) {
	return settings->window->waitEvent(event);
}

sf::String GameView::checkCoords(sf::Vector2u& codes){
	for (int i = commands.size() - 1; i >= 0; i--) {
		if (commands[i].hitbox.contains(float(codes.x), float(codes.y))) {
			codes.x = codes.y = commands[i].code;
			return commands[i].command;
		}
			
	}
	return "";
}

sf::String GameView::checkCode(int code){
	for (int i = commands.size() - 1; i >= 0; i--) {
		if (commands[i].code == code)
			return commands[i].command;
	}
	return "";
}

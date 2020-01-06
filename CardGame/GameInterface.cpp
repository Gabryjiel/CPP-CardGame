#include "GameInterface.h"
#include <Windows.h>

GameInterface::GameInterface(GameSettings& settings, Player* player, std::vector<Card*> *table, int nOP){
	this->settings = &settings;
	this->window = settings.window;
	this->cards = new GCard[52];
	this->player = player;
	this->table = table;
	this->numberOfPlayers = nOP;
	this->positions = new Position[numberOfPlayers];

	loadCards();
}

GameInterface::~GameInterface() {
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

void GameInterface::setPositions() {
	sf::Vector2f pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9, pos10;
	float x = float(window->getSize().x), y = float(window->getSize().y);
	pos1 = { x / 2 - cards->getSize().width/2 , y - cards->getSize().height};
	pos2 = { x, y * (2/3)};
	pos3 = { x - cards->getSize().width, y / 2};
	pos4 = { x, y * (1/3)};
	pos5 = { x * (2/3), 0};
	pos6 = { x / 2 - cards->getSize().width / 2, 0};
	pos7 = { x * (1/3), 0};
	pos8 = { 0, y * (1/3)};
	pos9 = { 0, y / 2};
	pos10 = { 0, y * (2/3)};

	positions[0].hand = pos1;
	positions[0].gap = gap_front_big;
	if (numberOfPlayers > 4) {
		positions[1].hand = pos2;
		positions[1].gap = gap_side_small;
		positions[2].hand = pos4;
		positions[2].gap = gap_side_small;
	}
	else {
		positions[1].hand = pos3;
		positions[1].gap = gap_side_big;
		positions[2].hand = pos6;
		positions[2].gap = gap_front_small;
		positions[3].hand = pos9;
		positions[3].gap = gap_side_small;
		return;
	}
	if (numberOfPlayers > 5) {
		positions[3].hand = pos5;
		positions[3].gap = gap_front_small;
		positions[4].hand = pos7;
		positions[4].gap = gap_front_small;
	}
	else {
		positions[3].hand = pos6;
		positions[3].gap = gap_front_big;
		positions[4].hand = pos9;
		positions[4].gap = gap_side_big;
		return;
	}
	if (numberOfPlayers > 6) {
		positions[5].hand = pos8;
		positions[5].gap = gap_side_small;
		positions[7].hand = pos10;
		positions[7].gap = gap_side_small;
	}
	else {
		positions[5].hand = pos9;
		positions[5].gap = gap_side_big;
	}
}

void GameInterface::display(){
	window->display();
}

void GameInterface::loadCards() {
	
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
	}
}

void GameInterface::drawBackground() {
	window->clear(sf::Color(settings->backgroundColor[0], settings->backgroundColor[1], settings->backgroundColor[2]));
}

void GameInterface::displayStart(){
	drawBackground();
	for (int i = 0; i < numberOfPlayers; i++) {
		std::vector <Card*> deck = player[i].getDeck();
		for (unsigned int j = 0; j < deck.size(); j++) {
			cards[deck[j]->getId()].setPosition(positions[i].gap(j, deck.size(), cards->getSize(), positions[i].hand));
			window->draw(cards[deck[j]->getId()]);
		}
	}
	window->display();
}

void GameInterface::displayTriumph(Card* triumph){
	cards[triumph->getId()].scale(2, 2);
	cards[triumph->getId()].setPosition(window->getSize().x/2 - cards[triumph->getId()].getSize().width/2,
		window->getSize().y/2 - cards[triumph->getId()].getSize().height/2);
	

	sf::RectangleShape opacity;
	opacity.setSize(sf::Vector2f(cards[triumph->getId()].getSize().width, cards[triumph->getId()].getSize().height));
	opacity.setPosition(window->getSize().x / 2 - cards[triumph->getId()].getSize().width / 2,
		window->getSize().y / 2 - cards[triumph->getId()].getSize().height / 2);
	opacity.setFillColor(sf::Color(44, 89, 56, 170));

	window->draw(cards[triumph->getId()]);
	window->draw(opacity);
	cards[triumph->getId()].scale(0.5, 0.5);
}

void GameInterface::displayResult()
{
}

void GameInterface::displayTable()
{
}

void GameInterface::displayWinner(int roundWinner)
{
}

int GameInterface::selectCard(int player)
{
	return 0;
}

int GameInterface::declare(int round)
{
	return 0;
}

bool GameInterface::checkEvent(sf::Event& event) {
	return window->pollEvent(event);
}

sf::String GameInterface::checkCoords(sf::Vector2u* codes){
	for (int i = 0; i < 52; i++) {
		if (cards[i].getGlobalBounds().contains(float(codes->x), float(codes->y))) {
			codes->x = codes->y = i;
			return "ThrowCard";
		}
	}
	return "";
}

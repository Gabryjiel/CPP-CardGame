#include "Interface.h"
#include <iostream>
#include <conio.h>
#include <vector>

Interface::Interface(Player* player, std::vector <Card*> *table, Card* triumph, int nOP) {
	this->player = player;
	this->table = table;
	this->triumph = triumph;
	this->numberOfPlayers = nOP;
	this->prepareConsole();
	setCursor(0, 0);
}

int Interface::prepareConsole(){
	int WindowX = 100, WindowY = 40;

	SetConsoleTitle("Planowanie");
	HANDLE outHnl = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX fontInf;
	GetCurrentConsoleFontEx(outHnl, TRUE, &fontInf);
	fontInf.cbSize = sizeof(fontInf);
	fontInf.nFont = 0;
	fontInf.FontFamily = FF_DONTCARE;
	fontInf.FontWeight = FW_NORMAL;
	fontInf.dwFontSize.X = 12;
	fontInf.dwFontSize.Y = 16;
	wcscpy_s(fontInf.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(outHnl, TRUE, &fontInf);

	COORD sizeB = { WindowX,WindowY };
	SetConsoleScreenBufferSize(outHnl, sizeB);

	SMALL_RECT sizeW = { 0, 0, WindowX - 1, WindowY - 1 };
	SetConsoleWindowInfo(outHnl, true, &sizeW);

	CONSOLE_CURSOR_INFO cursorInfo = { 100,false };
	SetConsoleCursorInfo(outHnl, &cursorInfo);

	return 0;
}

void Interface::setCursor(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Interface::cursorDown() {
	std::cout << "\n\r";
}

int Interface::selectCard(int player) {
	int klik;
	int selection = 0;

	do {
		setCursor(11 + selection * 4, 0);
		std::cout << '<';
		klik = _getch();
		setCursor(11 + selection * 4, 0);
		std::cout << ' ';
		if (klik == 'd' && selection < this->player[player].getDeckSize() - 1)
			selection++;
		else if (klik == 'a' && selection > 0)
			selection--;
	} while (klik != 13);

	return selection;
}

void Interface::displayStart() {
	setCursor(0, 0);
	for (int i = 0; i < numberOfPlayers; i++) {
		std::cout << '(' << player[i].getDeclaration() << ") P" << i << ": ";
		printDeck(player[i].getDeck());
		std::cout << "      " << std::endl;
	}
}

void Interface::displayTriumph(Card * triumph) {
	std::cout << "Triumph: ";
	printCard(triumph);
}

void Interface::displayResult(){
	cursorDown();
	for (int i = 0; i < numberOfPlayers; i++) {
		std::cout << 'P' << i << ": " << player[i].getTaken() << std::endl;
	}
}

void Interface::displayWinner(int winner){
	std::cout << 'P' << winner << " takes it!";
}
 
void Interface::displayTable() {
	static int posY;
	setCursor(0, numberOfPlayers + 2 + posY);
	printDeck(table);
	if (table->size() == 4)
		posY += 1 ;
}

void Interface::printCard(const Card* card) {
	int figure = card->getFigure();
	int color = card->getColor();
	char signF = -1;
	char signC = -1;

	if (figure < 9) signF = figure + '2';
	else if (figure == 9) signF = 'J';
	else if (figure == 10) signF = 'Q';
	else if (figure == 11) signF = 'K';
	else if (figure == 12) signF = 'A';

	if (color == 0) signC = 6;
	else if (color == 1) signC = 5;
	else if (color == 2) signC = 4;
	else if (color == 3) signC = 3;

	if (signF == ':') std::cout << "10" << signC << ' ';
	else std::cout << ' ' << signF << signC << ' ';
}

void Interface::printDeck(const std::vector <Card*> deck) {
	for (unsigned int i = 0; i < deck.size(); i++) {
		int figure = deck[i]->getFigure();
		int color = deck[i]->getColor();
		char signF = -1;
		char signC = -1;

		if (figure < 9) signF = figure + '2';
		else if (figure == 9) signF = 'J';
		else if (figure == 10) signF = 'Q';
		else if (figure == 11) signF = 'K';
		else if (figure == 12) signF = 'A';

		if (color == 0) signC = 6;
		else if (color == 1) signC = 5;
		else if (color == 2) signC = 4;
		else if (color == 3) signC = 3;

		if (signF == ':') std::cout << "10" << signC << ' ';
		else std::cout << ' ' << signF << signC << ' ';
	}
}

void Interface::printDeck(const std::vector <Card*>* deck){
	for (unsigned int i = 0; i < deck->size(); i++) {
		int figure = deck->at(i)->getFigure();
		int color = deck->at(i)->getColor();
		char signF = -1;
		char signC = -1;

		if (figure < 9) signF = figure + '2';
		else if (figure == 9) signF = 'J';
		else if (figure == 10) signF = 'Q';
		else if (figure == 11) signF = 'K';
		else if (figure == 12) signF = 'A';

		if (color == 0) signC = 6;
		else if (color == 1) signC = 5;
		else if (color == 2) signC = 4;
		else if (color == 3) signC = 3;

		if (signF == ':') std::cout << "10" << signC << ' ';
		else std::cout << ' ' << signF << signC << ' ';
	}
}

int Interface::declare(int round) {
	int declaration;
	int sum = 0;
	int allow = 0;

	for (int i = 0; i < numberOfPlayers; i++)
		sum += player[i].getDeclaration();

	while (true) {
		this->setCursor(0, 11);
		
		std::cout << "Ile sztychów weŸmiesz?";

		if (sum != 0) {
			allow = round - sum;
			std::cout << " Nie mo¿esz " << allow;
		}

		std::cin >> declaration;

		if (declaration != allow || allow == 0)
			break;
	}

	this->setCursor(0, 11);
	std::cout << "							";
	this->setCursor(1, 0);
	std::cout << declaration;

	return declaration;
}
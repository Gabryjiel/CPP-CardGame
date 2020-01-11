#include "MenuView.h"

MenuView::MenuView(GameSettings & settings):View(settings) {
}

MenuView::~MenuView() {
}

bool MenuView::checkEvent(sf::Event &event){
	return settings->window->pollEvent(event);
}

void MenuView::drawScene(sf::String menu) {
	int numberOfOptions;
	std::vector<sf::String> textTable;
	std::vector<sf::String> commandTable;
	
	if (menu == "MainMenu") {
		numberOfOptions = 5;
		textTable = { "Szybka gra", L"W³asna gra", "Opcje", L"Wyjœcie", "Kontynuuj" };
		commandTable = { "QuickGame", "CustomGame", "Options", "CLOSE", "Continue" };
	}
	else if (menu == "Options") {
		numberOfOptions = 4;
		textTable = { L"Menu g³ówne", L"Rozdzielczoœæ", L"Kolor t³a", "Motyw kart" };
		commandTable = { "MainMenu", "Resolution", "BackgroundColour", "CardTheme" };
	}
	else if (menu == "CustomGame") {
		numberOfOptions = 3;
		textTable = { L"Menu g³ówne", L"Iloœæ rund", L"Iloœæ graczy" };
		commandTable = { "MainMenu", "Round", "Players" };
	}

	options.clear();
	options.resize(numberOfOptions);
	commands.clear();

	settings->window->clear(sf::Color(44, 89, 56));
	for (int i = 0; i < numberOfOptions; i++) {
		commands.push_back(commandTable[i]);
		options[i].setText(textTable[i]);
		options[i].setSize(50, 200);
		options[i].setOutlineThickness(4);
		options[i].setOutlineColor(sf::Color(0, 53, 138));
		options[i].setBackgroundColor(sf::Color(0, 53, 138));
		options[i].setFormating(1, 1);
		options[i].setPosition(4, float(10 + i * 70));
		options[i].setFormating(1, 1);
		draw(options[i]);
	}
	display();
}

sf::String MenuView::checkCoords(sf::Vector2u& coords) {
	for (int i = 0; i < int(options.size()); i++) {
		if (options[i].isOn(float(coords.x), float(coords.y)))
			return commands[i];
	}
	return "";
}

void MenuView::start() {

}
/*
void MenuInterface::menu() {
	setOptions();
	drawOptions();

	while (window.isOpen()){

		sf::Event event;
		while (window.pollEvent(event)){

			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					for (int i = 0; i < 4; i++) {
						if (options[i].isOn(float(event.mouseButton.x), float(event.mouseButton.y))) {
							options[i].setBackgroundColor(sf::Color(0, 76, 199));
							options[i].setOutlineColor(sf::Color(0, 76, 199));
						}
						window.draw(mainMenu[i]);
					}
					window.display();
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					for (int i = 0; i < 4; i++) {
						mainMenu[i].setBackgroundColor(sf::Color(0, 53, 138));
						mainMenu[i].setOutlineColor(sf::Color(0, 53, 138));
						window.draw(mainMenu[i]);
					}
					window.display();

				}
			}
		}

	}
}*/
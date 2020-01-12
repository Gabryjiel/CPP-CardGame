#include "MenuView.h"

MenuView::MenuView(GameSettings & settings):View(settings) {
}

MenuView::~MenuView() {
}

bool MenuView::checkEvent(sf::Event &event){
	return settings->window->pollEvent(event);
}

void MenuView::drawScene(sf::String menu) {
	std::vector<sf::String> textTable;
	std::vector<sf::String> commandTable;
	
	settings->window->clear(settings->backgroundColour);

	if (menu == "MainMenu") {
		textTable = { "Szybka gra", L"W³asna gra", "Opcje", L"Wyjœcie", "Kontynuuj" };
		commandTable = { "QuickGame", "CustomGame", "Options", "CLOSE", "Continue" };
	}
	else if (menu == "Options") {	
		textTable = { L"Rozdzielczoœæ", L"Kolor t³a", "Motyw kart" };
		commandTable = { "ResolutionMenu", "BackgroundColourMenu", "CardThemeMenu" };
	}
	else if (menu == "CustomGame") {
		textTable = { L"Iloœæ rund", L"Iloœæ graczy" };
		commandTable = { "Round", "Players" };
	}
	else if (menu == "ResolutionMenu") {
		textTable = { "640x480", "800x640", "1024x768", "1280x720" , "1600x900", "1920x1080", "Fullscreen"};
		commandTable = { "ChangeResolution", "ChangeResolution", "ChangeResolution", "ChangeResolution", "ChangeResolution", "ChangeResolution", "ChangeResolution"};
	}
	else if (menu == "BackgroundColourMenu") {
		textTable = { "Niebieski", "Szary", "Czerwony", L"¯ó³ty", "Fioletowy", "Zielony", L"Domyœlny" };
		commandTable = { "ChangeBColour", "ChangeBColour" , "ChangeBColour" , "ChangeBColour" , "ChangeBColour" , "ChangeBColour", "ChangeBColour" };
	}
	else if (menu == "CardThemeMenu") {
		textTable = { "Zielony", "Niebieski", "Czerwony", L"Pomarañczowy", "Fioletowy", "Czarny" };
		commandTable = { "ChangeCardTheme", "ChangeCardTheme", "ChangeCardTheme", "ChangeCardTheme", "ChangeCardTheme", "ChangeCardTheme" };
	
		Picture card;
		card.loadImage(settings->cardTheme);
		card.setPosition(settings->window->getSize().x / 2, settings->window->getSize().y / 2);
		card.scale(0.2f, 0.2f);
		draw(card);
	}

	if (textTable.size() > 0 && textTable.size() == commandTable.size()) {
		Button text;
		text.setBackgroundColor(settings->primaryColour);
		text.setOutlineColor(settings->secondaryColour);
		text.setOutlineThickness(2);
		text.setSize(50, 200);
		text.setFormating(1, 1);

		clearCommands();

		for (int i = 0; i < int(textTable.size()); i++) {
			text.setText(textTable[i]);
			text.setPosition(4, 10 + i * 70);
			draw(text);
			addCommand(text.getGlobalBounds(), commandTable[i], i);
		}
	}
	display();
}


sf::String MenuView::checkCoords(sf::Vector2u& coords) {
	for (int i = 0; i < int(commands.size()); i++) {
		if (commands[i].hitbox.contains(float(coords.x), float(coords.y))) {
			coords.x = coords.y = commands[i].code;
			return commands[i].command;
		}
	}
	return "";
}

sf::String MenuView::checkCode(int code){
	return sf::String("No");
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
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
		textTable = { "Szybka gra", L"W³asna gra", "Kontynuuj", L"Zapisz grê", L"Wczytaj grê", "Opcje", L"Wyjœcie" };
		commandTable = { "QuickGame", "CustomGame", "Continue", "SaveGame", "LoadGame", "Options", "CLOSE" };
	}
	else if (menu == "Options") {	
		textTable = { L"Rozdzielczoœæ", L"Kolor t³a", "Motyw kart" };
		commandTable = { "ResolutionMenu", "BackgroundColourMenu", "CardThemeMenu" };
	}
	else if (menu == "CustomGame") {
		textTable = { L"Iloœæ rund", L"Iloœæ graczy", "Start gry" };
		commandTable = { "RoundsMenu", "PlayersMenu", "StartNew" };
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
		card.scale(0.2f, 0.2f);
		card.setPosition(settings->window->getSize().x / 2 - card.getSize().width / 2, settings->window->getSize().y / 2 - card.getSize().height /2);
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
			text.setPosition(4, float(10 + i * 70));
			draw(text);
			addCommand(text.getGlobalBounds(), commandTable[i], i);
		}
	}

	if (menu == "RoundsMenu") {
		drawRoundsMenu();
	}
	else if (menu == "PlayersMenu") {
		drawPlayersMenu();
	}
}

void MenuView::drawRoundsMenu() {
	clearCommands();
	drawScene("CustomGame");

	Button text;
	text.setBackgroundColor(sf::Color(255, 255, 255, 0));
	text.setTextColour(sf::Color::White);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(1);
	text.setTextSize(13);
	text.setFormating(1, 1);
	text.setSize(float(settings->window->getSize().y) / 22, 80);

	for (int i = 0; i < int(settings->rounds.size()); i++) {
		text.setBackgroundColor(sf::Color(255, 255, 255, 0));
		text.setText("Runda " + std::to_string(i + 1));
		text.setPosition(300, 10 + i * text.getGlobalBounds().height);
		draw(text);

		text.setText(std::to_string(settings->rounds[i]));
		text.setPosition(300 + text.getGlobalBounds().width * 3, 10 + i * text.getGlobalBounds().height);
		draw(text);

		text.setBackgroundColor(settings->primaryColour);
		text.setText("-");
		text.setPosition(300 + text.getGlobalBounds().width * 2, 10 + i * text.getGlobalBounds().height);
		addCommand(text.getGlobalBounds(), "-r", i);
		draw(text);

		text.setText("+");
		text.setPosition(300 + text.getGlobalBounds().width * 4, 10 + i * text.getGlobalBounds().height);
		addCommand(text.getGlobalBounds(), "+r", i);
		draw(text);
	}
	if (settings->rounds.size() < 20) {
		text.setText("+");
		text.setPosition(300 + text.getGlobalBounds().width, 10 + (settings->rounds.size()- 1) * text.getGlobalBounds().height);
		addCommand(text.getGlobalBounds(), "+R", settings->rounds.size());
		draw(text);
	}
	if (settings->rounds.size() > 1) {
		text.setText("-");
		text.setPosition(300 - text.getGlobalBounds().width, 10 + (settings->rounds.size() - 1) * text.getGlobalBounds().height);
		addCommand(text.getGlobalBounds(), "-R", settings->rounds.size());
		draw(text);
	}
}

void MenuView::drawPlayersMenu(){
	clearCommands();
	drawScene("CustomGame");

	Button text;
	text.setBackgroundColor(sf::Color(255, 255, 255, 0));
	text.setTextColour(sf::Color::White);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(1);
	text.setTextSize(13);
	text.setFormating(1, 1);
	text.setSize(30, 60);

	for (int i = 0; i < int(settings->players.size()); i++) {
		text.setBackgroundColor(sf::Color(255, 255, 255, 0));
		text.setText("Gracz " + std::to_string(i));
		text.setPosition(300, 10 + i * text.getGlobalBounds().height);
		draw(text);

		text.setText(std::to_string(settings->players[i]));
		text.setPosition(300 + text.getGlobalBounds().width * 3, 10 + i * text.getGlobalBounds().height);
		draw(text);
		if (i != 0) {
			text.setBackgroundColor(settings->primaryColour);
			text.setText("-");
			text.setPosition(300 + text.getGlobalBounds().width * 2, 10 + i * text.getGlobalBounds().height);
			addCommand(text.getGlobalBounds(), "-g", i);
			draw(text);

			text.setText("+");
			text.setPosition(300 + text.getGlobalBounds().width * 4, 10 + i * text.getGlobalBounds().height);
			addCommand(text.getGlobalBounds(), "+g", i);
			draw(text);
		}
	}
	if (settings->players.size() < 10) {
		text.setText("+");
		text.setPosition(300 + text.getGlobalBounds().width, 10 + (settings->players.size() - 1) * text.getGlobalBounds().height);
		addCommand(text.getGlobalBounds(), "+G", settings->players.size());
		draw(text);
	}
	if (settings->players.size() > 2) {
		text.setText("-");
		text.setPosition(300 - text.getGlobalBounds().width, 10 + (settings->players.size() - 1) * text.getGlobalBounds().height);
		addCommand(text.getGlobalBounds(), "-G", settings->players.size());
		draw(text);
	}


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
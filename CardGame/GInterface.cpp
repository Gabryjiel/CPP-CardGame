#include "GInterface.h"

GInterface::GInterface() {
	temp.setText("Szybka Gra");
	temp.setFormating(2, 1);
	temp.setPosition(20, 20);
	window.create(sf::VideoMode(800, 600), "My window");
}

void GInterface::start() {

	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		menu();
		window.display();
	}

}

void GInterface::menu() {
	Button mainMenu[4];

	mainMenu[0].setText("Szybka Gra");
	mainMenu[1].setText(L"W≥asna Gra");
	mainMenu[2].setText("Opcje");
	mainMenu[3].setText(L"Wyjdü");
	
	window.clear(sf::Color(44, 89, 56));

	for (int i = 0; i < 4; i++) {
		mainMenu[i].setSize(50, 200);
		mainMenu[i].setOutlineThickness(4);
		mainMenu[i].setOutlineColor(sf::Color::Blue);
		mainMenu[i].setBackgroundColor(sf::Color::Blue);
		mainMenu[i].setFormating(2, 1);
		mainMenu[i].setPosition(0, 10 + i * 70);
		window.draw(mainMenu[i]);
	}
}
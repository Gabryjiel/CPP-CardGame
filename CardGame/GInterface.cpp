#include "GInterface.h"

GInterface::GInterface() {
	temp.setText("Szybka Gra");
	temp.setFormating(2, 1);
	temp.setPosition(20, 20);
	window.create(sf::VideoMode(800, 600), "My window");
}

void GInterface::start() {
	menu();
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
		mainMenu[i].setOutlineColor(sf::Color(0, 53, 138));
		mainMenu[i].setBackgroundColor(sf::Color(0, 53, 138));
		mainMenu[i].setFormating(2, 1);
		mainMenu[i].setPosition(0, 10 + i * 70);
		window.draw(mainMenu[i]);
	}
	window.display();
	while (window.isOpen()){
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					for (int i = 0; i < 4; i++) {
						if (mainMenu[i].isOn(event.mouseButton.x, event.mouseButton.y)) {
							mainMenu[i].setBackgroundColor(sf::Color(0, 76, 199));
							mainMenu[i].setOutlineColor(sf::Color(0, 76, 199));
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
}
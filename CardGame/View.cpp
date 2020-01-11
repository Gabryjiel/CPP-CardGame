#include "View.h"

View::View(GameSettings& settings) {
	this->settings = &settings;
}

View::~View() {
	settings = nullptr;
}

void View::close() {
	settings->window->close();
}

void View::display() {
	settings->window->display();
}

void View::addCommand(sf::FloatRect hitbox, sf::String command, int code){
	commands.resize(commands.size() + 1);
	commands[commands.size() - 1].hitbox = hitbox;
	commands[commands.size() - 1].command = command;
	commands[commands.size() - 1].code = code;
}

int View::getCommandsSize(){
	return commands.size();
}

void View::clearCommands(){
	commands.clear();
}

void View::draw(sf::Drawable& object) {
	settings->window->draw(object);
}
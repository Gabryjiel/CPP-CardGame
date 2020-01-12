#include "Controller.h"

Controller::Controller(GameSettings& settings) {
	this->settings = &settings;
	this->settings->window->setFramerateLimit(60);
}

Controller::~Controller() {
	this->settings = nullptr;
	delete this->view;
}
#include "Controller.h"

Controller::Controller(GameSettings& settings) {
	this->settings = &settings;
}

Controller::~Controller() {
	this->settings = nullptr;
	delete this->view;
}
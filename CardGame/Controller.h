#pragma once
#include "GameSettings.h"
#include "View.h"

#define CLOSEPROGRAM 0
#define MAINMENU 1
#define STARTGAME 2

class Controller{

protected:
	View* view = nullptr;
	GameSettings* settings;

public:
	Controller(GameSettings & settings);
	~Controller();

	virtual int start() = 0;
};


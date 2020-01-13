#include "Launcher.h"

int main(){

	Launcher launcher;
	launcher.startGame();

	return 0;
}

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
	Launcher launcher;
	launcher.startGame();
	return 0;
}
# include "Game.h"

Game::Game(Frame& mainFrame, HDC& hdc, int& diff, const int& map)
	:mainFrame{ mainFrame }, hdc{ hdc }, diff{ diff }
{
	if (map == 0) {
		playMap = new StreetMap(hdc, &mainFrame, diff);
	}
	else if (map == 1) {
		playMap = new ChessMap(hdc, &mainFrame, diff);
	}
	/*else {
		playMap = new TrainMap(hdc, &mainFrame, diff);
	}*/
}

Game::~Game() {
	delete playMap;
}

int Game::startGame() {
	playMap->drawMap();
	return playMap->getDiff();
}

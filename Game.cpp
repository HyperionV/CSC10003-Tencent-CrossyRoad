# include "Game.h"

Game::Game(Frame& mainFrame, HDC& hdc, int& diff, const int& map)
	:mainFrame{ mainFrame }, hdc{ hdc }, diff{ diff }
{
	screen = Screen::getInstance(&mainFrame, &hdc);
	if (map == STREET_MAP) {
		playMap = new StreetMap(hdc, &mainFrame, diff, screen);
	}
	else if (map == CHESS_MAP) {
		playMap = new ChessMap(hdc, &mainFrame, diff, screen);
	}
	else {
		playMap = new TrainMap(hdc, &mainFrame, diff, screen);
	}
}

Game::~Game() {
	delete playMap;
}

int Game::startGame() {
	playMap->drawMap();
	return playMap->getDiff();
}

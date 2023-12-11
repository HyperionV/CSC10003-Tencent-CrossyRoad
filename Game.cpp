# include "Game.h"

Game::Game(Frame& mainFrame, HDC& hdc, int& diff, const int& map)
	:mainFrame{ mainFrame }, hdc{ hdc }, diff{ diff }
{
	screen = MenuScreen::getInstance(&mainFrame, &hdc);
    playMap = nullptr;
//	if (map == STREET_MAP) {
//		playMap = new StreetMap(hdc, &mainFrame, diff, screen);
//	}
//	else if (map == CHESS_MAP) {
//		playMap = new ChessMap(hdc, &mainFrame, diff, screen);
//	}
//	else {
//		playMap = new TrainMap(hdc, &mainFrame, diff, screen);
//	}
}

Game::~Game() {
	delete playMap;
}

int Game::startGame() {
    while(true) {
        int map = CONTINUE;
        while(map == CONTINUE)
            map = screen->startGame();
        if (map == QUIT_GAME) {
            return 0;
        }
        if (playMap != nullptr) {
            delete playMap;
        }
//        string playerName = screen->screenPlayerName();
        string playerName = "player";
        switch (map) {
            case 0:
                playMap = new StreetMap(hdc, &mainFrame, diff, screen, playerName);
                playMap->drawMap();
                break;
            case 1:
                playMap = new ChessMap(hdc, &mainFrame, diff, screen, playerName);
                playMap->drawMap();
                break;
            case 2:
                playMap = new TrainMap(hdc, &mainFrame, diff, screen, playerName);
                playMap->drawMap();
                break;
            case 3:
                // todo
                break;

            case 4:
                //quit
                return 0;
        }
        mainFrame.removeAllSprite();
    }
}

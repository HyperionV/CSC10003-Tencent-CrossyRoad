#include "Game.h"

Game::Game(Frame& mainFrame, HDC& hdc, int& diff, const int& map)
	:mainFrame{ &mainFrame }, hdc{ hdc }, diff{ diff }
{
	screen = MenuScreen::getInstance(&mainFrame, &hdc);
    playMap = nullptr;
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
            playMap = nullptr;
        }
        string playerName;
        if(map != LOAD_MAP)
            playerName = screen->screenPlayerName();
        mainFrame->removeAllSprite();
        switch (map) {
            case 0: {
                playMap = new StreetMap(hdc, mainFrame, diff, screen, playerName);
                playMap->drawMap();
                break;
            }
            case 1: {
                playMap = new ChessMap(hdc, mainFrame, diff, screen, playerName);
                playMap->drawMap();
                break;
            }
            case 2: {
                playMap = new TrainMap(hdc, mainFrame, diff, screen, playerName);
                playMap->drawMap();
                break;
            }
            case 3: {
                //load map
                string mapString = fileDialog.ShowOpenFileDialog();
                stringstream ss(mapString);
                string mapName;
                ss >> mapName;
                int difficulty;
                ss >> difficulty;
                string playerName;
                ss >> playerName;
                if (mapName == "StreetMap") {
                    playMap = new StreetMap(hdc, mainFrame, difficulty, screen, playerName, mapString);
//                    playMap->loadMap(mapString);
                } else if (mapName == "ChessMap") {
                    playMap = new ChessMap(hdc, mainFrame, difficulty, screen, playerName, mapString);
//                    playMap->loadMap(mapString);
                } else if (mapName == "TrainMap") {
                    playMap = new TrainMap(hdc, mainFrame, difficulty, screen, playerName, mapString);
//                    playMap->loadMap(mapString);
                }
                if (playMap != nullptr) {
                    playMap->drawMap();
                }
                break;
            }
            case 4: {
                //quit
                mainFrame->removeAllSprite();
                return 0;
                break;
            }
            default:
                break;
        }
        mainFrame->removeAllSprite();

    }
}

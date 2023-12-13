#pragma once

#include <iostream>
#include <Windows.h>
#include <winuser.h>
#include <cmath>
#include <chrono>
#include <thread>
#include "Player.h"
#include "MenuScreen.h"
#include "TrafficLight.h"
#include "Map.h"
#include "FileDialog.h"


class Game {
private:
	Frame* mainFrame;
	HDC hdc;
	int diff;
	Map* playMap;
	MenuScreen* screen;
    FileDialog fileDialog;
public:
	Game(Frame& mainFrame, HDC& hdc, int& diff, const int& map);
	~Game();

	int startGame();
};
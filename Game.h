#pragma once

#include <iostream>
#include <Windows.h>
#include <winuser.h>
#include <cmath>
#include <chrono>
#include <thread>

class Game {
	HWND window;

public:
	Game();
	~Game();

	Game(int width, int height, int fpsCap);
};
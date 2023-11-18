#pragma once

#include <iostream>
#include <Windows.h>
#include <winuser.h>
#include <cmath>
#include <chrono>
#include <thread>
#include "Player.h"

class Game {
private:
	Player* _player;
public:
	Game();
	~Game();

	Game(int width, int height, int fpsCap);

	
};
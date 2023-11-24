#pragma once

#include "Utilities.h"
#include "Sprite.h"
#include "Entity.h"
#include "Lane.h"

class Map {
	int difficulty;
	HDC hdc;
	Frame *mainFrame;
	vector<Lane*> mapLane;
	Entity background;
public:
	Map();
	Map(HDC hdc, Frame* mapFrame, int levelDifficulty);
	~Map();

	void drawMap();
};
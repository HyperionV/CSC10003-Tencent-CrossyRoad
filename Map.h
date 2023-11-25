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
    Texture* bgTexture;
    Sprite* bg;
public:
	Map(HDC hdc, Frame* mapFrame, int levelDifficulty, vector<Lane> &mapLane);
	~Map();

	void checkLane();
	void drawMap();
};
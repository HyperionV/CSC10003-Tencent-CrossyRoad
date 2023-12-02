#pragma once

#include "Utilities.h"
#include "Sprite.h"
#include "Entity.h"
#include "TrafficLight.h"
#include "Lane.h"
#include <thread>

class Map {
	int difficulty;
	HDC hdc;
	Frame *mainFrame;
	vector<Lane*> mapLane;
    Texture* bgTexture;
    Sprite* bg;
	vector<TrafficLight> trafficLight;
	Player player;
public:
	Map(HDC hdc, Frame* mapFrame, int levelDifficulty, vector<Lane> &mapLane);
	~Map();

	void drawMap();
};
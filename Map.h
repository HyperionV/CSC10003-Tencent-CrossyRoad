#pragma once

#include "Sprite.h"
#include "Entity.h"
#include "TrafficLight.h"
#include "Lane.h"
#include "Supportive.h"
#include <thread>

class Map {
protected:
	int difficulty;
	HDC hdc;
	Frame* mainFrame;
	vector<Lane*> mapLane;
	vector<Entity>vehicle;
	vector<Slime>slime;
	vector<Coin> coin;
	Screen* screen;
	Texture* bgTexture;
	Sprite* bg;
	Player player;
public:
	virtual void shiftResource() = 0;
	virtual ~Map() {};
	virtual void drawMap() = 0;
	virtual void loadResource() = 0;
};

class StreetMap : public Map {
private : 
	vector<TrafficLight>trafficLight;
public : 
	StreetMap(HDC hdc, Frame* mapFrame, int levelDifficulty, Screen* screen);
	~StreetMap();
	void drawMap();
	void loadResource();
	void shiftResource();
};


class ChessMap : public Map {
public:
	ChessMap(HDC hdc, Frame* mapFrame, int levelDifficulty, Screen* screen);
	~ChessMap();
	void drawMap();
	void loadResource();
	void shiftResource() {};
};


class TrainMap : public Map {
private:
	vector<TrafficLight>trafficLight;
public:
	TrainMap::TrainMap(HDC hdc, Frame* mapFrame, int levelDifficulty, Screen* screen);
	~TrainMap();
	void drawMap();
	void loadResource();
	void shiftResource();
};


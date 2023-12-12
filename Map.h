#pragma once

#include "Sprite.h"
#include "Entity.h"
#include "TrafficLight.h"
#include "Lane.h"
#include "Supportive.h"
#include "FileDialog.h"
#include <thread>
#include <mutex>

class Map {
protected:
    string mapName;
    FileDialog fileDialog;
	int difficulty;
	HDC hdc;
	Frame* mainFrame;
	vector<Lane*> mapLane;
	vector<Entity>vehicle;

	vector<Entity>slime;
	vector<Entity>coin;
	MenuScreen* screen;

	Texture* bgTexture;
	Sprite* bg;
	Player player;

	bool gameRunning;
public:
    Map(Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName);
    virtual ~Map();
    virtual void shiftResource() = 0;
	virtual void drawMap() = 0;
	virtual void loadResource() = 0;

    string saveMap();
    void loadMap(string);

	int getDiff() const;
	void randomItemSpawner();
};

class StreetMap : public Map {
private:
	vector<TrafficLight>trafficLight;

public : 
	StreetMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName);
    StreetMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName, string mapString);
	~StreetMap();
	void drawMap();
	void loadResource();
	void shiftResource();

//    string saveMap();
//    void loadMap(string);
};


class ChessMap : public Map {
public:
	ChessMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName);
	ChessMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName, string mapString);
    ~ChessMap();
	void drawMap();
	void loadResource();

	void shiftResource();

//    string saveMap();
//    void loadMap(string);

};


class TrainMap : public Map {
private:
	vector<TrafficLight>trafficLight;
public:
	TrainMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName);
	TrainMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName, string mapString);
    ~TrainMap();
	void drawMap();
	void loadResource();
	void shiftResource();

//    string saveMap();
//    void loadMap(string);
};

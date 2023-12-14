#pragma once

#include "Sprite.h"
#include "Entity.h"
#include "TrafficLight.h"
#include "Lane.h"
#include "Supportive.h"
#include "FileDialog.h"
#include <thread>
#include <mutex>

/* 
 * Map Class
 * Encapsulate every object relates to the gameplay. Contains the main loop for drawing textures and process gameplay.
 * 
 * StreetMap, TrainMap, ChessMap: classes that derived from Map Class.
 * These classes controls the behaviour of the corresponding theme of the game.
 */

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
};


class ChessMap : public Map {
public:
	ChessMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName);
	ChessMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName, string mapString);
    ~ChessMap();
	void drawMap();
	void loadResource();

	void shiftResource();
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

};

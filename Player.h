#pragma once
#include "Sprite.h"
#include "Entity.h"
//#include "Supportive.h"
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100


class Map;
class StreetMap;
class ChessMap;
class TrainMap;

class Player: Rect2D {
private:
    string playerName;
    Frame* mainFrame;
    static vector<vector<int>>lanePos;
    int mapType;
    int cnt = 0;
    vector<Entity*>model;
    Sprite* _player;
    size_t point = 0;
    int state = 1; // left - 0; up - 1; right - 2;
    bool isRunning;
//    string dateTime;
public:
    Player() {};
    Player(Frame&, const int&);
    Player(Frame&, const int& mapType, const Vector2f& pos, const int& point);
    ~Player();

    void setPosition(const float& x, const float& y, const char& dir);
    void animatePlayer();
    void addPoint();
    void addPoint(const int& value);
    void setSpritePriotity(const int&);
    void stopPlayerHandler();
    void resumePlayerHandler();
    void playerHandler(char curr);

    void setPlayerName(string name);
    string getPlayerName();

    void setMap(int map);
    int getMap();

//    void setDateTime();
//    string getDateTime();

    static void INIT();
    Vector2f getHitbox() const;
    Vector2f getCurrentPos() const;
//    thread launchHandler();
    int getPoint() const;
    int convertLane(const int& mapType);
    int summon_Megumin();

    friend Map;
    friend StreetMap;
    friend ChessMap;
    friend TrainMap;
};
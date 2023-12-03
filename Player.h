#pragma once
#include "Utilities.h"
#include "Sprite.h"
#include "Entity.h"
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100

class Player: Rect2D {
private:
    static vector<vector<int>>lanePos;
    int mapType;
    int cnt = 0;
    vector<Entity*> model;
    Sprite* _player;
    size_t point = 0;
    int state = 1; // left - 0; up - 1; right - 2;
    bool isRunning;
public:
    Player() {};
    Player(Frame&, const int&);
    ~Player();

    Vector2f getCurrentPos() const;
    void setPosition(const float& x, const float& y, const char& dir);
    void animatePlayer();
    Vector2f getHitbox() const;
    void addPoint();
    void addPoint(const int& value);
    int convertLane();

    static void INIT();
    void playerHandler();
    thread launchHandler();
    void stopPlayerHandler();
    int let_Megumin_cook();
};
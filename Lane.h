#pragma once
#include "Entity.h"
#include <cmath>
#include <thread>
#include "Player.h"

class Lane {
private:
    int difficulty;
    vector<Sprite*> vehicles;
    int timeBetweenSpawn;
    Vector2f start;
    Vector2f end;
    float speed{5};
    Frame* mainFrame;
    int vehicleCounter;
public:
    Entity model;
    Lane(Frame*, const int&, const Entity&, const int&);
    ~Lane();
    void resetLane(); 
    void startLane();
    bool checkCollision(Player*);
    void animateLane();
    //void update();
    thread spawnThread();
};
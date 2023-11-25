#pragma once
#include "Entity.h"
#include <cmath>
#include <thread>
#include "Player.h"

class Lane {
private:
    int difficulty;
    int timeBetweenSpawn;
    Vector2f start;
    Vector2f end;
    float speed{5};
    Frame* mainFrame;
    int vehicleCounter;
    Entity model;
    vector<Sprite*> vehicles;
public:
    Lane(Frame*, const int&, const Entity&, const int&);
    ~Lane();
    void resetLane(); 
    void startLane();
    bool checkCollision(Player*);
    void animateLane();

    thread spawnThread();
    int getTotalVehicle();
    void printStart();
    void printEnd();
};
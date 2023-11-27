#pragma once
#include "Entity.h"
#include <cmath>
#include <thread>
#include <chrono>
#include <time.h>
#include <random>
#include "Player.h"

class Lane {
private:
    const int RANDOM_INTERVAL = 4000;

    int difficulty;
    int timeBetweenSpawn;

    Vector2f start;
    Vector2f end;
    float speed{5};
    Frame* mainFrame;
    int vehicleCounter;
    Entity model;
    vector<Sprite*> vehicles;
    clock_t lastSpawn;
    deque<int> nextSpawn;
    bool isRunning;
    vector<bool> onTrack;

    float timeTilNextSpawn;
    mt19937 rand;

public:
    Lane(Frame*, const int&, const Entity&, const int&);
    ~Lane();
    void resetLane(); 
    void startLane();
    void stopLane();
    void slowdownLane();

    void spawnCar();

    bool checkCollision(Player*);
    void animateLane();

    void update();

    thread spawnThread();
    int getTotalVehicle();
    void printStart();
    void printEnd();
};
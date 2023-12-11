#pragma once
#include <cmath>
#include <thread>
#include <chrono>
#include <time.h>
#include <random>
#include "Entity.h"
#include "Player.h"
#include "Supportive.h"
#include "Item.h"
#include <mutex>

#define STREET_MAP 0
#define CHESS_MAP 1
#define TRAIN_MAP 2
#define LOAD_MAP 3
#define QUIT_GAME 4
#define CONTINUE 5

class Lane {
private:
    const int RANDOM_INTERVAL = 4000;

    int difficulty;
    int timeBetweenSpawn;
    int priority;
    vector<Entity*> model;
    vector<Sprite*> vehicles;
    static vector<vector<int>>lanePos;

    Vector2f start;
    Vector2f end;
    float speed{5};
    Frame* mainFrame;
    int vehicleCounter;
    clock_t lastSpawn;
    deque<int> nextSpawn;
    bool isRunning;
    vector<bool> onTrack;
    vector<Item*> items;

    mutex _mutex;
    float timeTilNextSpawn;
    mt19937 rand;

public:
    Lane();
    Lane(Frame*, const int&, vector<Entity>& _entity, const int&, const int&,const int&);
    Lane(Frame*, const int&, vector<Entity>& _entity, const int&, const int&, const int&, const int&);
    ~Lane();
    void resetLane(); 
    void startLane();
    void stopLane();
    static void INIT();

    void spawnCar();

    bool checkCollision(Player*);
    void addItem(const string& itemName, const Vector2f& postion);

    void animateLane();
    void animateItem();
    void clearItems();
    void updateItem();
    void update();
    Vector2f getStart() const;

    int getTotalVehicle();
    void printStart();
    void printEnd();
    void setVehicleCounter(const int&);

    string saveLane();
};
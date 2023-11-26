#pragma once
#include "Entity.h"
#include <cmath>
#include <thread>
#include "Player.h"
#include "Item.h"

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
    vector<Item> items;
public:
    Lane(Frame*, const int&, const Entity&, const int&);
    ~Lane();
    void resetLane(); 
    void startLane();
    bool checkCollision(Player*);
    void animateLane();
    void addItem(const string& itemName, const Entity& model, const Vector2f& postion);

    thread spawnThread();
    int getTotalVehicle();
    void printStart();
    void printEnd();
    Vector2f getStart() const;
};
#pragma once
#include "Entity.h"
#include <cmath>
#include <thread>
#include "Player.h"



// save a list of to-be-loaded entities to a vector.
// + Use a different thread to shift the resource every loop.

// make a Lane class
// - Private:
// + a vector containing sprites that will appear in the current level.
// # Every sprite will point to the corresponding Entity and will change texture every loop. 
// + an Entity containing the resource for the current Vehicles in the lane. The entity is copied from the original Entity list.

// Mechanism:
// - User choose a theme, theme is a global parameter and will be used for every lane. 
// - When start the game, generate a vector of Lane, the difficulty will be determined by the current level counter. The level counter will also be a global variable. 
// - Every lane will operate on a different thread.

// Time between car spawn: (3 - difficulty*1.0/2) * 1000 (ms)
// Speed = Speed + (difficulty%5)/4

// Lane mechanism:
// + When the game starts, every lane will begin to generate cars. When a car comes to its final position, it will automatically come back to the start position and travel again
// + When a level is ended, the `resetLane` function will be called.
    // + update the difficulty and other statistics. 
    // + bring all the cars back to the beginning position and run the startLane function again to start the level


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
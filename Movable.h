#pragma once

#include "Utilities.h"

using namespace std;
using namespace utility;

class Movable
{
protected:
    Vector2f position;
    Vector2f startingPosition;
    Vector2f velocity;
    Vector2f acceleration;
    Vector2f destination;
    bool isMoving;
    float speed;

public:
    bool reachedDestination();
    Movable();
    Movable(Vector2f position, Vector2f velocity, Vector2f acceleration);
    Movable(const Movable& other);
    ~Movable();

    Vector2f getPosition();
    Vector2f getVelocity();
    Vector2f getAcceleration();
    Vector2f getDestination();
    bool getIsMoving();
    float getSpeed();

    void setPosition(Vector2f position);
    void setVelocity(Vector2f velocity);
    void setAcceleration(Vector2f acceleration);
    void setDestination(Vector2f destination);
    void setIsMoving(bool isMoving);
    void setSpeed(float speed);

    void update();
    void setEndPos(Vector2f endPos, float speed);
};
#include "Movable.h"
#include <math.h>
#include <iostream>

using namespace std;
using namespace utility;

Movable::Movable() {
    position = Vector2f();
    startingPosition = Vector2f();
    velocity = Vector2f();
    acceleration = Vector2f();
    destination = Vector2f();
    isMoving = false;
    speed = 0;
}

Movable::Movable(Vector2f position, Vector2f velocity, Vector2f acceleration) {
    this->position = position;
    this->startingPosition = position;
    this->velocity = velocity;
    this->acceleration = acceleration;
    destination = Vector2f();
    isMoving = false;
    speed = 0;
}

Movable::Movable(const Movable& other) {
    position = other.position;
    startingPosition = other.startingPosition;
    velocity = other.velocity;
    acceleration = other.acceleration;
    destination = other.destination;
    isMoving = other.isMoving;
    speed = other.speed;
}

Movable::~Movable() {
    // Do nothing
}

Vector2f Movable::getPosition() {
    return position;
}

Vector2f Movable::getVelocity() {
    return velocity;
}

Vector2f Movable::getAcceleration() {
    return acceleration;
}

Vector2f Movable::getDestination() {
    return destination;
}

bool Movable::getIsMoving() {
    return isMoving;
}

float Movable::getSpeed() {
    return speed;
}

void Movable::setPosition(Vector2f position) {
    this->position = position;
}

void Movable::setVelocity(Vector2f velocity) {
    this->velocity = velocity;
}

void Movable::setAcceleration(Vector2f acceleration) {
    this->acceleration = acceleration;
}

void Movable::setDestination(Vector2f destination) {
    this->destination = destination;
}

void Movable::setIsMoving(bool isMoving) {
    this->isMoving = isMoving;
}

void Movable::setSpeed(float speed) {
    this->speed = speed;
}

bool Movable::reachedDestination() {
    if (position.x > destination.x || position.x < destination.x && destination.x < 0) 
        return true;
    if (position.x == destination.x && position.y == destination.y)
        return true;
    return false;
}

void Movable::update() {
//    cerr << "Movable::update()" << endl;
//    cerr << "isMoving: " << isMoving << endl;
//    cerr << "velocity: " << velocity.x << ", " << velocity.y << endl;
//    cerr << "acceleration: " << acceleration.x << ", " << acceleration.y << endl;
    if (isMoving) {
        if (reachedDestination()) {
            // isMoving = false;
            // velocity = Vector2f();
            // acceleration = Vector2f();
            // system("pause");
            position = startingPosition;
            // startingPosition = destination;
        }
        else {
            Vector2f firstHalf = position - startingPosition;
            Vector2f secondHalf = destination - startingPosition;
            if(firstHalf.modulus() / secondHalf.modulus() < 0.6)
                velocity += acceleration;
            else
                velocity -= acceleration;
            position += velocity;
        }
    }
}

void Movable::setEndPos(Vector2f endPos, float speed) {
    destination = endPos;
    startingPosition = position;
    isMoving = true;
    Vector2f distance = destination - position;
    float distanceModulus = distance.modulus();
    float time = distanceModulus / speed;
    velocity = distance / time;
    acceleration = Vector2f();
    // acceleration = Vector2f(0,0);
    // velocity = Vector2f();
}







#pragma once
#include "Utilities.h"
#include "Sprite.h"
#include "Entity.h"

using namespace std;

class Player: Rect2D {
private:
    int cnt = 0;
    Entity model;
    Sprite* _player;
    size_t point = 0;
public:
    Player() {};
    Player(const Entity&, Frame&);
    ~Player();

    Vector2f getCurrentPos() const;
    void setPosition(const float& x, const float& y, const char& dir);
    void animatePlayer();
    void setModel(const Entity&);
    Vector2f getHitbox() const;
    void addPoint();
    void addPoint(const int& value);
};
#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "Frame.h"
#include <deque>
#include "Utilities.h"

class Entity : public Rect2D {
private:
    deque<Texture*> motion;
    string entityName{};    
public:
    Entity();
    //~Entity();
    Entity(const string&);
    Entity(const string&, bool);
    void shiftResource();
    Texture* getCurrentTexture() const;
    Texture* getPreviousTexture();
    int getMotionSize();

    void setName(const string&);
};


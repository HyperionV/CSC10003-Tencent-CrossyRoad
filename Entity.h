#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "Frame.h"
#include <deque>
#include "Utilities.h"

class Entity : protected Rect2D {
private:
    deque<Texture*> motion;
    string entityName{};    
public:
    Entity();

    Entity(const string&);
    void getResource();
    void shiftResource();
    Texture* getCurrentTexture();
    Texture* getPreviousTexture();
};


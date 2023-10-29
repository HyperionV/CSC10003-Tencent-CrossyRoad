#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "Frame.h"
#include <deque>

class Entity {
private:

    deque<Texture*> motion;
    string entityName{};
    
public:
    Entity();

    Entity(const string&);
    void getResource();
    void shiftResource(Sprite*);
    Texture* getCurrentTexture();
};
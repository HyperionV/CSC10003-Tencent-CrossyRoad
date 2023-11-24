#pragma once

#include "Utilities.h"

class Drawable {
public:
    Drawable* next;
    Drawable* prev;

    Drawable();

    virtual void draw(void* bits, utility::Vector2i frameSize) = 0;
    virtual void update() = 0;
};


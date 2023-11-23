#pragma once

#include "Utilities.h"

class Drawable{
    public:
        Drawable* next;
        Drawable* prev;

        Drawable(){
            next = NULL;
            prev = NULL;
        }

        virtual void draw(void* bits, Vector2i frameSize) = 0;
        virtual void update() = 0;

};


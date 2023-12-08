#pragma once
#include "Utilities.h"

using namespace utility;
using namespace std;

class Drawable {
public:
    Drawable* next;
    Drawable* prev;
    Drawable();
    Drawable(Drawable* next, Drawable* prev);
    ~Drawable();
    virtual void draw(void* bits, Vector2i frameSize) = 0;
    virtual void update() = 0;
    virtual void onEvent(Event& event);
};
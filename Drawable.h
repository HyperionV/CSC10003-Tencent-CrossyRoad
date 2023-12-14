#pragma once
#include "Utilities.h"
#include "Event.h"

using namespace utility;
using namespace std;

/*
 * Drawable class
 * This class is the base class for all drawable objects in the game. Contains priority.
 * Supports drawing to screen and updating.
 * Is also a node of a doubly linked list.
 * */

class Drawable {
protected:
    int priority;
public:
    Drawable* next;
    Drawable* prev;
    Drawable();
    Drawable(Drawable* next, Drawable* prev);
    ~Drawable();

    int getPriority();
    void setPriority(int priority);

    virtual void draw(void* bits, Vector2i frameSize) = 0;
    virtual void update() = 0;
    virtual void onEvent(Event& event);
};
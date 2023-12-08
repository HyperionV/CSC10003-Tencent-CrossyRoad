#pragma once
#include "Utilities.h"
#include "Event.h"

using namespace utility;
using namespace std;

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
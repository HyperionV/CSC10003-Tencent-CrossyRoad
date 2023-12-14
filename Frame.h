#pragma once
#include "Utilities.h"
#include "Sprite.h"
#include "Drawable.h"
#include "Texture.h"
#include "Event.h"
#include <iostream>
#include <algorithm>

using namespace std;

class Frame
/*
 * Frame class
 * This class is the representation of a frame on screen. Is a container for managing, updating and drawing sprites.
 * Contains a doubly linked list of sprites.
 * Supports adding and removing sprites, updating and drawing frame to screen.
 * Sprites are drawn in order of priority.
 * Sprites must be drawn using the draw function of the frame for performance reasons.
 * */
{
private:
    Drawable* first;
    Drawable* last;

    Vector2i size;
    Vector2i position;

public:
    Frame();
    Frame(Vector2i size, Vector2i position);
    ~Frame();

    void addSprite(Sprite* sprite);
    Sprite* addSprite(Texture& texture, Vector2f position, int priority = 0);
    Sprite* addSprite(Texture* texture, Vector2f position, int priority = 0);
    void removeSprite(Sprite*& sprite);
    void removeAllSprite();
    void removeAllSprites(); 
    void update();
    void onEvent(Event& event);
    void draw(HDC hdc);
    void draw(HDC hdc, Sprite* curSprite);
};
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
#pragma once
#include "Utilities.h"
#include "Sprite.h"
#include "Texture.h"
#include <iostream>

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
    Sprite* addSprite(Texture texture, Vector2f position);
    void removeSprite(Drawable*& sprite);
    void removeAllSprite(); 
    void removeAllSprites(); 
    void update();
    void draw(HDC hdc);
    void draw(HDC hdc, Sprite* curSprite);
};
#pragma once
#include "Utilities.h"
#include "Sprite.h"
#include "Texture.h"
#include <iostream>

using namespace std;

class Frame
{
private:
    Sprite* first;
    Sprite* last;

    Vector2i size;
    Vector2i position;

public:
    Frame();
    Frame(Vector2i size, Vector2i position);
    ~Frame();


    Sprite* addSprite(Texture texture, Vector2f position);
    void removeSprite(Sprite*& sprite);
    void update();
    void draw(HDC hdc);
    void draw(HDC hdc, Sprite* curSprite);
};
#pragma once

#include <Windows.h>
#include "Utilities.h"
#include "Pixel.h"
#include "Movable.h"
#include "Texture.h"

class Sprite : public Movable
{
private:
    Texture texture;
    Rect2D textureRect;
public:
    Sprite();
    Sprite(Vector2f position ,Texture* texture);
    ~Sprite();
    void setTexture(Texture* texture);
    Texture getTexture();

    Sprite* next;
    Sprite* prev;

    void setTextureRect(int top, int left, int width, int height);
    void updateSprite();
    void draw(void* bits, Vector2i frameSize);
};
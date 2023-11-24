#pragma once

#include <Windows.h>
#include "Utilities.h"
#include "Pixel.h"
#include "Movable.h"
#include "Texture.h"

class Sprite : public Movable
{
private:
    Texture* texture;
    Rect2D textureRect;
public:
    Sprite();
    Sprite(Vector2f position, Texture* texture);
    ~Sprite();
    void setTexture(Texture* texture);
    Texture* getTexture();
    Vector2f getHitbox() const;

    Sprite* next;
    Sprite* prev;

    void setTextureRect(int top, int left, int width, int height);
    void update();
    void draw(void* bits, Vector2i frameSize);
};
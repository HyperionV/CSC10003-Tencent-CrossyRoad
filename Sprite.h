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
    int priority;
public:
    Sprite();
    Sprite(Vector2f position, Texture* texture, int priority = 0);
    ~Sprite();
    void setTexture(Texture* texture);
    Texture* getTexture();
    Vector2f getHitbox() const;
    Sprite* next;
    Sprite* prev;
    int getPriority();
    void setPriority(int priority);
    void setHeight(const int& height);

    void printPosition();
    void setTextureRect(int top, int left, int width, int height);
    void update();
    void draw(void* bits, Vector2i frameSize);
};
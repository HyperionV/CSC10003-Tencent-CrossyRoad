#pragma once

#include <Windows.h>
#include "Utilities.h"
#include "Pixel.h"
#include "Movable.h"
#include "Texture.h"
#include "Drawable.h"

class Sprite : public Movable, public Drawable
{
private:
    Texture* texture;
    Rect2D textureRect;
public:
    Sprite();
    Sprite(Vector2f position, Texture* texture, int priority = 0);
    ~Sprite();
    void setTexture(Texture* texture);
    Texture* getTexture();
    Vector2f getHitbox() const;
    void setHeight(const int& height);

    void printPosition();
    void setTextureRect(int top, int left, int width, int height);
    void update();
    void draw(void* bits, Vector2i frameSize);
};
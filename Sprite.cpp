#include "Sprite.h"
#include <iostream>
using namespace std;
using namespace utility;



Sprite::Sprite():Movable()
{
    next = nullptr;
    prev = nullptr;
    this->texture = Texture();
    this->textureRect = Rect2D();
}

Sprite::Sprite(Vector2f position, Texture* texture):Movable(position, Vector2f(), Vector2f())
{
    next = nullptr;
    prev = nullptr;
    this->texture = *texture;
    this->textureRect = Rect2D(0, 0, texture->getWidth(), texture->getHeight());
}

Sprite::~Sprite()
{
    delete next;
    delete prev;
    next = nullptr;
    prev = nullptr;
}

void Sprite::setTexture(Texture* texture)
{
    this->texture = *texture;
    this->textureRect = Rect2D(0, 0, texture->getWidth(), texture->getHeight());
}

Texture Sprite::getTexture()
{
    return this->texture;
}

void Sprite::setTextureRect(int top, int left, int width, int height)
{
    this->textureRect.top = top;
    this->textureRect.left = left;
    this->textureRect.width = width;
    this->textureRect.height = height;
}

void Sprite::updateSprite() {
    Movable::update();
}

void Sprite::draw(void* bits, Vector2i frameSize)
{
    texture.drawTexture((int)position.y, (int)position.x, textureRect, bits, frameSize);
}






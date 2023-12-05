#pragma warning(disable:4244)
#include "Sprite.h"
#include <iostream>
using namespace std;
using namespace utility;

Sprite::Sprite() : Movable()
{
    next = nullptr;
    prev = nullptr;    
    priority = 0;
    //this->texture = Texture();
    this->textureRect = Rect2D();
}

Sprite::Sprite(Vector2f position, Texture* texture, int priority) : Movable(position, Vector2f(), Vector2f())
{
    next = nullptr;
    prev = nullptr;
    this->priority = priority;
    this->texture = texture;
    this->textureRect = Rect2D(0, 0, texture->getWidth(), texture->getHeight());
}
Sprite::~Sprite()
{
    next = nullptr;
    prev = nullptr;
}
void Sprite::setTexture(Texture* texture)
{
    this->texture = texture;
    this->textureRect = Rect2D(0, 0, texture->getWidth(), texture->getHeight());
}

Texture* Sprite::getTexture()
{
    return this->texture;
}
Vector2f Sprite::getHitbox() const {
    return Vector2f(textureRect.width, textureRect.height);
}
void Sprite::printPosition() {
    cerr << "position: " << position.x << " " << position.y << '\n';
}

void Sprite::setTextureRect(int top, int left, int width, int height)
{
    this->textureRect.top = top;
    this->textureRect.left = left;
    this->textureRect.width = width;
    this->textureRect.height = height;
}
int Sprite::getPriority() {
    return priority;
}
void Sprite::setPriority(int priority) {
    this->priority = priority;
}
void Sprite::update() {
    Movable::update();
}
void Sprite::draw(void* bits, Vector2i frameSize)
{
    texture->drawTexture((int)position.y, (int)position.x, textureRect, bits, frameSize);
}
void Sprite::setHeight(const int& height) {
    this->textureRect.height;
}
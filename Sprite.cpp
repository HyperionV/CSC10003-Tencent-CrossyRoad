#include "Sprite.h"
#include <iostream>
using namespace std;
using namespace utility;


//class Sprite : public Movable
//{
//private:
//    Texture texture;
//    Rect2D textureRect;
//public:
//    Sprite();
//    Sprite(Vector2f position ,Texture texture);
//    void setTexture(Texture texture);
//    Texture getTexture();
//    void setPosition(Vector2f position);
//
//    void setTextureRect(int top, int left, int width, int height);
//    void update();
//    void drawSprite(HDC hdc);
//};

Sprite::Sprite():Movable()
{
    this->texture = Texture();
    this->textureRect = Rect2D();
}

Sprite::Sprite(Vector2f position, Texture texture):Movable(position, Vector2f(), Vector2f())
{
    this->texture = texture;
    this->textureRect = Rect2D(0, 0, texture.getWidth(), texture.getHeight());
}

void Sprite::setTexture(Texture texture)
{
    this->texture = texture;
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

void Sprite::draw(HDC hdc)
{
    texture.drawTexture(position.y, position.x, textureRect, hdc);
}






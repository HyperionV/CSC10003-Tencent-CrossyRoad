#pragma once

#include "Texture.h"
#include "Sprite.h"
#include "Frame.h"
#include <deque>
#include "Utilities.h"

/*
 * Entity class
 * This class is the representation of animation. Contains some textures;
 * Supports getting current texture, and shift to the next frame of the animation.
 * */

class Entity : public Rect2D {
private:
    deque<Texture*> motion;
public:
    Entity();
    ~Entity();
    Entity(const string&);
    Entity(const string&, char);
    Entity(const string&, int);
    Entity(const string&, bool);
    Entity(const Entity&);
    void shiftResource();
    Texture* getCurrentTexture() const;
    Texture* getPreviousTexture();
    int getMotionSize();
    void flipHorizontal();
};


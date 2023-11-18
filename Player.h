#include "Utilities.h"
#include "Sprite.h"
#include "Entity.h"

using namespace std;

class Player: Rect2D {
private:
    Entity model;
    Sprite* _player;
public:
    Player(const Entity&, Frame&);
    ~Player();

    Vector2f getCurrentPos() const;
    void setPosition(const float& x, const float& y);
    void animatePlayer();
    void setModel(const Entity&);
    Vector2f getHitbox() const;
};
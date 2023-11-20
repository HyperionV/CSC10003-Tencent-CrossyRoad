#include "Player.h"
float pos[] = { 665, 610, 570, 500, 460, 391, 350, 284, 242, 180, 140 };

Player::Player(const Entity& _model, Frame& mainFrame) {
    model = _model;
    _player = mainFrame.addSprite(model.getCurrentTexture(), Vector2f(1280/2, 655));
    width = 38;
    height = 45;
    cnt = 0;
}


Player::~Player() {
    // delete _player; 
    // _player = nullptr;
}

Vector2f Player::getCurrentPos() const {
    return _player->getPosition();
}

void Player::setPosition(const float& x, const float& y,const char& dir) {

    if (dir == 'w')
        this->cnt++;
    else if (dir == 's')
        this->cnt--;

    if (this->cnt == 11 || this->cnt == -1)
        this->cnt = 0;
    
    if (x < 0) {
        _player->setPosition(Vector2f(0, pos[cnt]));
        return;
    }
    if (x > 1200) {
        _player->setPosition(Vector2f(1200, pos[cnt]));
        return;
    }

    _player->setPosition(Vector2f(x, pos[cnt]));


}

void Player::animatePlayer() {
    model.shiftResource();
    _player->setTexture(model.getCurrentTexture());
}

void Player::setModel(const Entity& _model) {
    model = _model;
}

Vector2f Player::getHitbox() const {
    return Vector2f(width, height);
}

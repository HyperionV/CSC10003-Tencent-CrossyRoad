#include "Player.h"

Player::Player(const Entity& _model, Frame& mainFrame) {
    model = _model;
    _player = mainFrame.addSprite(model.getCurrentTexture(), Vector2f(1280/2, 670));
    width = 38;
    height = 45;
}

Player::~Player() {
    // delete _player; 
    // _player = nullptr;
}

Vector2f Player::getCurrentPos() const {
    return _player->getPosition();
}

void Player::setPosition(const float& x, const float& y) {
    _player->setPosition(Vector2f(x, y));
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

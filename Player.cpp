#pragma warning(disable:4244)
#include "Player.h"
float pos[] = { 665, 610, 570, 500, 460, 391, 350, 284, 242, 180, 140 };

Player::Player(Frame& mainFrame) {
    model.push_back(new Entity("player/left"));
    model.push_back(new Entity("player/up"));
    model.push_back(new Entity("player/right"));
    _player = mainFrame.addSprite(model[state]->getCurrentTexture(), Vector2f(1280 / 2, 655));
    width = 36;
    height = 40;
    cnt = 0;
}

// Memory leak here: unable to delete vector of Entity
Player::~Player() {
    /*for (auto& s : model) {
        delete s;
    }
    model.clear();*/
    // delete _player; 
    // _player = nullptr;
}

Vector2f Player::getCurrentPos() const {
    return _player->getPosition();
}

void Player::setPosition(const float& x, const float& y,const char& dir) {

    if (dir == 'w')
    {
        state = 1;
        this->cnt++;
    }
    else if (dir == 's')
    {
        state = 1;
        this->cnt--;
    }

    if (this->cnt == 11 || this->cnt == -1)
        this->cnt = 0;
    
    if (x < 0) {
        _player->setPosition(Vector2f(0, pos[cnt]));
        return;
    }
    if (x > 1210) {
        _player->setPosition(Vector2f(1200, pos[cnt]));
        return;
    }

    _player->setPosition(Vector2f(x, pos[cnt]));
}

void Player::animatePlayer() {
    model[state]->shiftResource();
    _player->setTexture(model[state]->getCurrentTexture());
}

//void Player::setModel(const Entity& _model) {
//    model = _model;
//}

Vector2f Player::getHitbox() const {
    return Vector2f(width, height);
}

void Player::addPoint() {
    point++;
}

void Player::addPoint(const int& value) {
    point += value;
}

int Player::convertLane() {
    return 10 - cnt;
}

void Player::playerHandler()
{
    while (true) {
        int vertical{}, horizon{};
        animatePlayer();
        if (_kbhit()) {
            this_thread::sleep_for(50ms);
            int curr = _getch();
            Vector2f currPos = _player->getPosition();
            switch (curr) {
            case KEY_LEFT:
                state = 0;
                setPosition(currPos.x - 40, currPos.y, 'a');
                break;
            case KEY_RIGHT:
                state = 2;
                setPosition(currPos.x + 40, currPos.y, 'd');
                break;
            case KEY_DOWN:
                setPosition(currPos.x, currPos.y, 's');
                break;
            case KEY_UP:
                state = 1;
                point += 5;
                setPosition(currPos.x, currPos.y, 'w');
                break;
            case 'q':
                system("pause");
                break;
            }
        }
    }
}

thread Player::launchHandler() {
    return thread([this]() { 
        this->playerHandler(); 
    });
}
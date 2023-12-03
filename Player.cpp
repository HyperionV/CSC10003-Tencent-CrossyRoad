#pragma warning(disable:4244)
#include "Player.h"
//float pos[] = { 650, 595, 555, 485, 450, 376, 332, 269, 227, 165, 125 };
int Priority[]{21, 11};
int mapLim[]{ 11, 6 };

void Player::INIT() {
    vector<int>street;
    vector<int>chess;

    street.push_back(650);
    street.push_back(595);
    street.push_back(555);
    street.push_back(485);
    street.push_back(450);
    street.push_back(376);
    street.push_back(332);
    street.push_back(269);
    street.push_back(227);
    street.push_back(165);
    street.push_back(125);


    chess.push_back(650);
    chess.push_back(580);
    chess.push_back(470);
    chess.push_back(370);
    chess.push_back(270);
    chess.push_back(170);

    lanePos.push_back(street);
    lanePos.push_back(chess);
}


Player::Player(Frame& mainFrame, const int& mapType) {
    model.push_back(new Entity("character/left"));
    model.push_back(new Entity("character/up"));
    model.push_back(new Entity("character/right"));
    _player = mainFrame.addSprite(model[state]->getCurrentTexture(), Vector2f(1280 / 2, 650));
    _player->setPriority(Priority[mapType]);
    width = 36;
    height = 55;
    cnt = 0;
    this->mapType = mapType;
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

    if (this->cnt == mapLim[mapType] || this->cnt == -1)
        this->cnt = 0;
    
    if (x < 0) {
        _player->setPosition(Vector2f(0, lanePos[mapType][cnt]));
        return;
    }
    if (x > 1210) {
        _player->setPosition(Vector2f(1200, lanePos[mapType][cnt]));
        return;
    }

    _player->setPriority(Priority[mapType] - cnt * 2);
    _player->setPosition(Vector2f(x, lanePos[mapType][cnt]));
}

void Player::animatePlayer() {
    model[state]->shiftResource();
    _player->setTexture(model[state]->getCurrentTexture());
}

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
    while (true && isRunning) {
        int vertical{}, horizon{};
        animatePlayer();
        if (_kbhit()) {
            //this_thread::sleep_for(50ms);
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
    isRunning = true;
    return thread([this]() { 
        this->playerHandler(); 
    });
}

void Player::stopPlayerHandler() {
    isRunning = false;
}

int Player::let_Megumin_cook() {
    state = 3;
    return model[state]->getMotionSize();
}
#pragma warning(disable:4244)
#include "Player.h"
//float pos[] = { 650, 595, 555, 485, 450, 376, 332, 269, 227, 165, 125 };
int Priority[]{21, 11, 21};
int mapLim[]{ 11, 6, 11};

#define STREET_MAP 0
#define CHESS_MAP 1
#define TRAIN_MAP 2

void Player::INIT() {
    vector<int>street = { 650, 595, 555, 485, 450, 376, 332, 269, 227, 165, 125 };
    vector<int>chess = {650, 580, 470, 370, 270, 170};
    vector<int>train = { 650, 595, 555, 485, 450, 376, 332, 269, 227, 165, 125};

    lanePos.push_back(street);
    lanePos.push_back(chess);
    lanePos.push_back(train);
}


Player::Player(Frame& mainFrame, const int& mapType) {
    this->mainFrame = &mainFrame;
    model.push_back(new Entity("character/left"));
    model.push_back(new Entity("character/up"));
    model.push_back(new Entity("character/right"));
    model.push_back(new Entity("character/down"));
    model.push_back(new Entity("effect/explode"));
    _player = mainFrame.addSprite(model[state]->getCurrentTexture(), Vector2f(1280 / 2, 655));    
    _player->setPriority(Priority[mapType]);
    width = 36;
    height = 40;
    cnt = 0;
    point = 0;
    this->mapType = mapType;
}

Player::Player(Frame& mainFrame, const int& mapType, const Vector2f& pos, const int& point) {
    this->mainFrame = &mainFrame;
    model.push_back(new Entity("character/left"));
    model.push_back(new Entity("character/up"));
    model.push_back(new Entity("character/right"));
    model.push_back(new Entity("effect/explode"));
    _player = mainFrame.addSprite(model[state]->getCurrentTexture(), pos);
    _player->setPriority(Priority[mapType]);
    width = 36;
    height = 40;
    cnt = 0;
    this->point = point;
    this->mapType = mapType;
    setPosition(pos.x, pos.y, 'w');
}

// Memory leak here: unable to delete vector of Entity
Player::~Player() {
    mainFrame->removeSprite(_player);

    for (auto& s : model) {
        delete s;
    }
    model.clear();
    // delete _player; 
    // _player = nullptr;
}

Vector2f Player::getCurrentPos() const {
    return _player->getPosition();
}

void Player::setPosition(const float& x, const float& y, const char& dir) {

    if (dir == 'w')
    {
        this->cnt++;
    }
    else if (dir == 's')
    {
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
    if (state == 4)
        _player->setPosition(Vector2f(0, 0));
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

void Player::playerHandler(char curr)
{
    if (isRunning) {
        int vertical{}, horizon{};
        animatePlayer();
        if (curr != 0) {
//            this_thread::sleep_for(50ms);
//            int curr = _getch();
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
                state = 3;
                setPosition(currPos.x, currPos.y, 's');
                break;
            case KEY_UP:
                state = 1;
                //if(point % 10 != 0 || cnt == 0)
                //    point += 1;
                setPosition(currPos.x, currPos.y, 'w');
                break;
            case 'q':
//                system("pause");
                break;
            }
        }
    }
}

//thread Player::launchHandler() {
//    isRunning = true;
//    return thread([this]() {
//        this->playerHandler();
//    });
//}

void Player::stopPlayerHandler() {
    isRunning = false;
}

void Player::resumePlayerHandler() {
    isRunning = true;
}

int Player::summon_Megumin() {
    state = 4;
    _player->setPosition(Vector2f(0, 0));
    return model[state]->getMotionSize();
}

int Player::getPoint() const {
    return point;
}

int Player::convertLane(const int& mapType) {
    if (mapType == TRAIN_MAP || mapType == STREET_MAP)
        return 10 - cnt;
    else return 10 - cnt;
}
void Player::setSpritePriotity(const int& i) {
    _player->setPriority(i);
}

void Player::setPlayerName(string name) {
    this->playerName = name;
}

string Player::getPlayerName() {
    return this->playerName;
}

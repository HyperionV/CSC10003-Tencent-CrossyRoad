#include "Lane.h"

int lanePos[] {143, 183, 252, 292, 355, 395, 465, 505, 575, 615};
pair<int, int> path = pair<int, int>(-132, 1280);

Lane::Lane(const int& laneCounter, const Entity& _entity, const int& _difficulty) {
    if (laneCounter % 2) {
        start = Vector2f(path.first, lanePos[laneCounter]);
        end = Vector2f(path.second, lanePos[laneCounter]);
    }
    else {
        start = Vector2f(path.second, lanePos[laneCounter]);
        end = Vector2f(path.first, lanePos[laneCounter]);
    }
    difficulty = _difficulty;
    timeBetweenSpawn = 2000 - (150 * (difficulty % 5)) * (1 + (difficulty % 5) / 4);
    vehicleCounter = floor(12000/timeBetweenSpawn);
    speed += floor(difficulty/5);
}

Lane::~Lane() {}

void Lane::resetLane() {
    timeBetweenSpawn = 2000 - (150 * (difficulty % 5)) * (1 + (difficulty % 5) / 4);
    vehicleCounter = floor(12000/timeBetweenSpawn);
    speed += floor((difficulty % 5) / 4);
    for (auto& _sprite: vehicles) {
        _sprite->setPosition(start);
        _sprite->setEndPos(end, 0);
    }
}

void Lane::startLane(Frame& mainFrame) {
    // system("pause");
    for (int i = 0; i < vehicleCounter; i++) {
        vehicles.push_back(mainFrame.addSprite(*model.getCurrentTexture(), start));
        vehicles[i]->setEndPos(end, speed);
        this_thread::sleep_for(chrono::milliseconds(timeBetweenSpawn));
    }
    cout << vehicles.size() << std::endl;
}

void Lane::animateLane() {
    model.shiftResource();
    for (auto _sprite: vehicles) {
        _sprite->setTexture(model.getCurrentTexture());
    }
}

bool Lane::checkCollision(Player* _p) {
    Vector2f topLeft = _p->getCurrentPos();
    Vector2f bottomRight = topLeft + _p->getHitbox();
    for (auto _sprite: vehicles) {
        Vector2f vTopLeft = _sprite->getPosition();
        Vector2f vBottomRight = vTopLeft + _sprite->getHitbox();
        if (bottomRight.x > bottomRight.x && vBottomRight.y > vBottomRight.y) 
            if (topLeft.x < vTopLeft.x && topLeft.y < topLeft.y) return true;
        return false;
    }
    return false;
}
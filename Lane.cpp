#include "Lane.h"

int lanePos[] {143, 183, 252, 292, 355, 395, 465, 505, 575, 615};
pair<int, int> path = pair<int, int>(-132, 1280);



Lane::Lane(Frame* mainFrame, const int& laneCounter, const Entity& _entity, const int& _difficulty) :
	rand(time(NULL) + laneCounter)
{
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
	speed += floor((float) difficulty/5);
	this->mainFrame = mainFrame;
	model = _entity;

	
}

Lane::~Lane() {}

void Lane::resetLane() {
	timeBetweenSpawn = 2000 - (150 * (difficulty % 5)) * (1 + (difficulty % 5) / 4);
	vehicleCounter = floor(12000/timeBetweenSpawn);
	nextSpawn.clear();
	for (int i = 0; i < vehicleCounter; i++) {
		nextSpawn.push_back(i);
	}
	onTrack.resize(vehicleCounter, false);
	while (vehicles.size() < vehicleCounter) {
		vehicles.push_back(mainFrame->addSprite(*model.getCurrentTexture(), start));
	}
	speed += floor((difficulty % 5) / 4);
	for (auto& _sprite: vehicles) {
		_sprite->setPosition(start);
		//_sprite->setEndPos(start, 0);
	}
	lastSpawn = clock();
	timeTilNextSpawn = rand() % RANDOM_INTERVAL / 1000.0;
	isRunning = false;
}

void Lane::spawnCar() {
	int spawnNow = nextSpawn.front();
	nextSpawn.pop_front();
	nextSpawn.push_back(spawnNow);

	vehicles[spawnNow]->setEndPos(end, speed);

	lastSpawn = clock();
	timeTilNextSpawn = 1.f * timeBetweenSpawn / 1000 + rand() % RANDOM_INTERVAL / (float) 1000;
}

thread Lane::spawnThread() {
	return std::thread([this]() {
			this->startLane();
		});
}

void Lane::startLane() {
	//for (int i = 0; i < vehicleCounter; i++) {
	//    //cerr << "i: " << i << " " << vehicleCounter << '\n';
	//    vehicles.push_back(mainFrame->addSprite(*model.getCurrentTexture(), start));
	//    vehicles[i]->setEndPos(end, speed);
	//    //cerr << "time: " << timeBetweenSpawn << '\n';
	//    //this_thread::sleep_for(chrono::milliseconds(timeBetweenSpawn));
	//}
	isRunning = true;
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->setIsMoving(true);
	}
}

void Lane::stopLane() {
	isRunning = false;
	for (int i = 0; i<vehicles.size();i++) {
		vehicles[i]->setIsMoving(false);
	}
}



void Lane::animateLane() {
	model.shiftResource();
	for (auto _sprite: vehicles) {
		_sprite->setTexture(model.getCurrentTexture());
	}
}

void Lane::update() {
	animateLane();
	if ((float)(clock() - lastSpawn) / CLOCKS_PER_SEC >= timeTilNextSpawn && isRunning) {
		spawnCar();
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
int Lane::getTotalVehicle() {
	return (int) vehicles.size();
}

void Lane::printStart() {
	cerr << "start pos: " << start.x << " " << start.y << '\n';
}
void Lane::printEnd() {
	cerr << "end pos: " << end.x << " " << end.y << '\n';
}
//void Lane::draw
#pragma warning(disable:4244)
#include "Lane.h"

int lanePos[] {143, 183, 252, 292, 355, 395, 465, 505, 575, 615};
pair<int, int> path = pair<int, int>(-132, 1280);



Lane::Lane(Frame* mainFrame, const int& laneCounter, const Entity& _entity, const int& _difficulty) 
	: rand(time(NULL) + laneCounter)
{
	if (laneCounter % 2) {
		start = Vector2f(path.first, lanePos[laneCounter]*1.0);
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
	for (auto& _item : items) {
		cout << _item->getItemName() << endl;
		if (_item->getItemSprite() == nullptr) {
			_item->setSprite(mainFrame->addSprite(_item->getTexture(), _item->getPosition()));
			if (_item->getItemName() == "Slime") {
				_item->getItemSprite()->setEndPos(_item->getDestination(), speed);
			}
		}
	}
	speed += floor((difficulty % 5) / 4);
	for (auto& _sprite: vehicles) {
		_sprite->setPosition(start);
		//_sprite->setEndPos(start, 0);
	}
	lastSpawn = clock();
	timeTilNextSpawn = rand() % RANDOM_INTERVAL / 1000.0;
	isRunning = false;
	//clearItems();
}

void Lane::clearItems() {
	for (auto& _item : items) {
		delete _item;
	}
	items.clear();
}

void Lane::spawnCar() {
	int spawnNow = nextSpawn.front();
	nextSpawn.pop_front();
	nextSpawn.push_back(spawnNow);

	vehicles[spawnNow]->setEndPos(end, speed);

	
	lastSpawn = clock();
	timeTilNextSpawn = 1.f * timeBetweenSpawn / 1000 + rand() % RANDOM_INTERVAL / (float) 1000;
}

void Lane::startLane() {
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

//void Lane::slowdownLane() {
//	isRunning = true;
//	for (int i = 0; i < vehicles.size(); i++) {
//		vehicles[i]->setSpeed(speed - 50);
//	}
//}


void Lane::animateLane() {
	model.shiftResource();
	for (auto _sprite: vehicles) {
		_sprite->setTexture(model.getCurrentTexture());
	}
}

void Lane::animateItem() {
	for (auto& _item : items) {
		_item->animateItem();
	}
}

void Lane::update() {
	animateItem();
	animateLane();
	if ((float)(clock() - lastSpawn) / CLOCKS_PER_SEC >= timeTilNextSpawn && isRunning) {
		spawnCar();
	}
}

Vector2f Lane::getStart() const {
	return start;
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
	for (auto& _item : items) {
		if (_item->useItem(_p)) {
			mainFrame->removeSprite(_item->getItemSprite());
			delete _item;
			items.erase(find(items.begin(), items.end(), _item));
		}
	}
	return false;
}

void Lane::addItem(const string& itemName, const Entity& model, const Vector2f& position) {
	if (itemName == "Slime") {
		items.push_back(new Slime(itemName, start));
	}
	else {
		items.push_back(new Coin(itemName, position));
	}
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
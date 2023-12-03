#pragma warning(disable:4244)
#include "Lane.h"

//int laneStreetPos[] {130, 170, 240, 276, 344, 384, 450, 490, 559, 602};
//int laneChessPos[] { 130, 170, 240, 276, 344 };


pair<int, int> path = pair<int, int>(-150, 1280);

void Lane::INIT() {
	vector<int>street;
	vector<int>chess;
	vector<int>train;


	street.push_back(130);
	street.push_back(170);
	street.push_back(240);
	street.push_back(276);
	street.push_back(344);
	street.push_back(384);
	street.push_back(450);
	street.push_back(490);
	street.push_back(559);
	street.push_back(602);


	chess.push_back(90);
	chess.push_back(200);
	chess.push_back(300);
	chess.push_back(400);
	chess.push_back(510);

	lanePos.push_back(street);
	lanePos.push_back(chess);
	return;

}

Lane::Lane() {}
void Lane::setVehicleCounter(const int& counter) {
	this->vehicleCounter = counter;
	return;
}

Lane::Lane(Frame* mainFrame, const int& laneCounter, vector<Entity>& _entity, const int& _difficulty, const int& mapType, const int& priority) 
	: rand(time(NULL) + laneCounter)
{
	for (int i = 0; i < _entity.size(); i++) {
		if (laneCounter % 2 != i % 2) {
			Entity* temp = &_entity[i];
			model.push_back(temp);
		}
	}
	if (laneCounter % 2) {
		start = Vector2f(path.first, lanePos[mapType][laneCounter]*1.0);
		end = Vector2f(path.second, lanePos[mapType][laneCounter]);
	}
	else {
		start = Vector2f(path.second, lanePos[mapType][laneCounter]);
		end = Vector2f(path.first, lanePos[mapType][laneCounter]);
	}
	this->priority = priority;
	difficulty = _difficulty;
	timeBetweenSpawn = 2000 - (150 * (difficulty % 5)) * (1 + (difficulty % 5) / 4);
	vehicleCounter = floor(12000/timeBetweenSpawn);
	speed += floor((float) difficulty/5);
	this->mainFrame = mainFrame;

}

Lane::~Lane() {}

void Lane::resetLane() {
	timeBetweenSpawn = 2000 - (150 * (difficulty % 5)) * (1 + (difficulty % 5) / 4);
	vehicleCounter = model.size();
	nextSpawn.clear();

	for (int i = 0; i < vehicleCounter; i++) {
		nextSpawn.push_back(i);
	}
	onTrack.resize(vehicleCounter, false);
	while (vehicles.size() < vehicleCounter) {
		int idx = vehicles.size() % model.size();
		vehicles.push_back(mainFrame->addSprite(model[idx]->getCurrentTexture(), start));
		vehicles[idx]->setPriority(priority);
	}
	for (auto& _item : items) {
		//cout << _item->getItemName() << endl;
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
	for (auto& _item : items) {
		_item->getItemSprite()->setEndPos(_item->getItemSprite()->getPosition(), 0);
	}
}

void Lane::animateLane() {
	for(int i= 0; i< vehicles.size(); i++) {
		vehicles[i]->setTexture(model[i]->getCurrentTexture());
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
	if (!isRunning) {
		lastSpawn = clock();
	}
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
	if (topLeft.x > bottomRight.x) {
		swap(topLeft.x, bottomRight.x);
	}
	if (topLeft.y < bottomRight.y) {
		swap(topLeft.y, bottomRight.y);
	}
	for (auto _sprite: vehicles) {
		Vector2f vTopLeft = _sprite->getPosition();
		Vector2f vBottomRight = vTopLeft + _sprite->getHitbox();
		if (vTopLeft.x > vBottomRight.x) {
			swap(vTopLeft.x, vBottomRight.x);
		}
		if (vTopLeft.y < vBottomRight.y) {
			swap(vTopLeft.y, vBottomRight.y);
		}
		if (bottomRight.x < vTopLeft.x || vBottomRight.x < topLeft.x)
			continue; // no overlap
		if (vBottomRight.y < ((bottomRight.y - topLeft.y) / 2 + bottomRight.y))
			continue;
		if (vTopLeft.y > (topLeft.y - (bottomRight.y - topLeft.y) / 2 ))
			continue;
		if (topLeft.y < vBottomRight.y || vTopLeft.y < bottomRight.y)
			continue; // no overlap
		return true; // overlap
	}
	//return false;

	for (auto& _item : items) {
		if (_item->checkCollision(_p)) {
			_p->addPoint(_item->getValue());
			cout << "Item used" << endl;
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

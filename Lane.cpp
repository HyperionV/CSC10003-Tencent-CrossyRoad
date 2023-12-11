#pragma warning(disable:4244)
#include "Lane.h"

//int laneStreetPos[] {130, 170, 240, 276, 344, 384, 450, 490, 559, 602};
//int laneChessPos[] { 130, 170, 240, 276, 344 };


pair<int, int> path = pair<int, int>(-420, 1280);

void Lane::INIT() {
	vector<int>street = { 130, 170, 240, 276, 344, 384, 450, 490, 554, 602 };
	vector<int>chess = { 90, 200, 300, 400, 510 };
	vector<int>train = { 80, 122, 185, 226, 287, 334, 398, 443, 511, 561 };

	lanePos.push_back(street);
	lanePos.push_back(chess);
	lanePos.push_back(train);

	vector<int>streetItem = { 130, 170, 244, 280, 344, 384, 450, 490, 554, 600 };
	vector<int>chessItem = { 170, 270, 370, 470, 580, 650 };
	vector<int>trainItem = { 130, 170, 232, 274, 337, 381, 455, 490, 560, 600, 655 };

	itemLanePos.push_back(streetItem);
	itemLanePos.push_back(chessItem);
	itemLanePos.push_back(trainItem);

	return;

}

Lane::Lane() {}
void Lane::setVehicleCounter(const int& counter) {
	this->vehicleCounter = counter;
	return;
}

Lane::Lane(Frame* mainFrame, const int& laneCounter, vector<Entity>& _entityVehicle, const int& _difficulty, const int& mapType, const int& priority)
	: rand(time(NULL) + laneCounter)
{
	for (int i = 0; i < _entityVehicle.size(); i++) {
		if (laneCounter % 2 != i % 2) {
			Entity* temp = &_entityVehicle[i];
			model.push_back(temp);
		}
	}
	if (laneCounter % 2) {
		start = Vector2f(path.first, lanePos[mapType][laneCounter]);
		end = Vector2f(path.second, lanePos[mapType][laneCounter]);
	}
	else {
		start = Vector2f(path.second, lanePos[mapType][laneCounter]);
		end = Vector2f(path.first, lanePos[mapType][laneCounter]);
	}
	this->priority = priority;
	difficulty = _difficulty;
	timeBetweenSpawn = 2000 - (150 * (difficulty % 5)) * (1 + (difficulty % 5) / 4);
	vehicleCounter = floor(12000 / timeBetweenSpawn);
	speed += floor((float)difficulty / 5);
	this->mainFrame = mainFrame;
	this->mapType = mapType;
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
		int idx = vehicles.size();
		vehicles.push_back(mainFrame->addSprite(model[idx]->getCurrentTexture(), start));
		vehicles[idx]->setPriority(priority);
	}
	speed += floor((difficulty % 5) / 4);
	for (auto& _sprite : vehicles) {
		_sprite->setPosition(start);
	}
	lastSpawn = clock();
	timeTilNextSpawn = rand() % RANDOM_INTERVAL / 1000.0;
	isRunning = false;
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
	timeTilNextSpawn = 1.f * timeBetweenSpawn / 1000 + rand() % RANDOM_INTERVAL / (float)1000;
}

void Lane::startLane() {
	isRunning = true;
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->setIsMoving(true);
	}

	for (auto& _item : items) {
		if (_item->getItemSprite() == nullptr) {
			items.erase(find(items.begin(), items.end(), _item));
			continue;
		}
		if (_item->getItemName() == "Slime")
		{
			_item->getItemSprite()->setIsMoving(true);
		}
	}
}

void Lane::stopLane() {
	isRunning = false;
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->setIsMoving(false);
	}
	for (auto& _item : items) {
		if (_item->getItemSprite() == nullptr) {
			items.erase(find(items.begin(), items.end(), _item));
			continue;
		}
		_item->getItemSprite()->setIsMoving(false);
	}
}

void Lane::animateLane() {
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->setTexture(model[i % model.size()]->getCurrentTexture());
	}

}

void Lane::animateItem() {
	for (int i = 0; i< items.size(); i++) {
		if (items[i]->getItemSprite() == nullptr) {
			items.erase(items.begin() + i);
			continue;
		}
		items[i]->animateItem();
	}
}

void Lane::updateItem() {
	_mutex.lock();
	for(int i= 0; i< items.size(); i++) {
		Sprite* _s = items[i]->getItemSprite();
		if (_s == nullptr) {
			items[i]->setSprite(mainFrame->addSprite(items[i]->getTexture(), items[i]->getPosition()));
			items[i]->getItemSprite()->setPriority(priority - 1);
			items[i]->getItemSprite()->setEndPos(items[i]->getDestination(), 0);
			if (items[i]->getItemName() == "Slime") {
				if (isRunning)
					items[i]->getItemSprite()->setEndPos(items[i]->getDestination(), speed);
			}
			continue;
		}
		if (items[i]->getItemName() == "Coin") {
			if (time(NULL) - items[i]->getCreateTime() > 5) {
				mainFrame->removeSprite(_s);
				items[i]->setSprite(nullptr);
			}
			continue;
		}
		if (_s->reachedDestination()) {
			mainFrame->removeSprite(_s);
			items[i]->setSprite(nullptr);
		}
	}
	_mutex.unlock();
}

void Lane::update() {
	updateItem();
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
	for (auto _sprite : vehicles) {
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
		if (topLeft.y < vBottomRight.y || vTopLeft.y < bottomRight.y)
			continue; // no overlap
		return true; // overlap
	}
	//return false;

	for(int i= 0; i< items.size(); i++) {
		if (items[i]->checkCollision(_p)) {
			_mutex.lock();
			playSound("sound/coin.wav");
			_p->addPoint(items[i]->getValue());
			mainFrame->removeSprite(items[i]->getItemSprite());
			delete items[i];
			items.erase(items.begin() + i);
			_mutex.unlock();
		}
	}
	return false;
}

void Lane::addItem(const string& itemName, const Vector2f& position, vector<Entity>&slime, vector<Entity>& coin, const int& laneCounter) {
	_mutex.lock();
	if (itemName == "Slime" && slime.size() != 0) {
		Slime* newSlime = new Slime(Vector2f(start.x, itemLanePos[mapType][laneCounter]), Vector2f(end.x, itemLanePos[mapType][laneCounter]));
		int rand = getRandomInRange(0, slime.size() - 1);
		newSlime->setModel(&slime[rand]);
		items.push_back(newSlime);
	}
	else {
		int rand = getRandomInRange(2, 4);
		Coin* newCoin = new Coin(Vector2f(position.x, itemLanePos[mapType][laneCounter]), rand);
		newCoin->setModel(&coin[rand - 2]);
		items.push_back(newCoin);
	}
	_mutex.unlock();
}

int Lane::getTotalVehicle() {
	return (int)vehicles.size();
}

void Lane::printStart() {
	cerr << "start pos: " << start.x << " " << start.y << '\n';
}
void Lane::printEnd() {
	cerr << "end pos: " << end.x << " " << end.y << '\n';
}

#pragma warning(disable:4244)
#include "Map.h"

StreetMap::StreetMap(HDC hdc, Frame* mapFrame, int levelDifficulty) {

	mainFrame = mapFrame;
	this->hdc = hdc;
	difficulty = levelDifficulty;
	loadResource();
	for (int i = 0, prio = 2; i < 10; i++, prio+=2) {
		Lane* cur = new Lane(mainFrame, i, vehicle, levelDifficulty, STREET_MAP, prio);
		this->mapLane.push_back(cur);
	}

	bgTexture = new Texture("image_bin/street.bin");
    bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
	getTraffic(STREET_MAP, mapLane, trafficLight);
	for (int i = 0; i < 5; i++) {
		Sprite* tmp = trafficLight[i].getSprite();
		mainFrame->addSprite(tmp);
	}
	player = Player(*mapFrame, STREET_MAP);
	player.addPoint(difficulty);
}

StreetMap::~StreetMap() {
	for (auto ptr:mapLane) {
		delete ptr;
	}
	mapLane.clear();
	trafficLight.clear();
}


void StreetMap::drawMap() {
	gameRunning = true;
	for (int i = 0; i < (int)mapLane.size(); i++) {
		mapLane[i]->resetLane();
		mapLane[i]->startLane();
	}
	thread t = player.launchHandler();
	thread spawner([this]() {
		return this->randomItemSpawner();
	});
	bool collide = 0;
	while (gameRunning) {
		shiftResource();
		trafficControl(trafficLight);
		for (int i = 0; i < (int)mapLane.size(); i++) {
			mapLane[i]->update();
		}
		int playerCurrentLane = player.convertLane();
		if (playerCurrentLane < 10) {
			if (mapLane[playerCurrentLane]->checkCollision(&player))
				collide = 1;
		}
		mainFrame->update();
		mainFrame->draw(hdc);
		if (collide) {
			gameRunning = 0;
			player.stopPlayerHandler();
			t.join();
			spawner.join();
			for (auto& s : mapLane) {
				s->stopLane();
			}
			int sz = player.summon_Megumin();
			player.setSpritePriotity(INT_MAX);
			while (sz--) {
				this_thread::sleep_for(200ms);
				player.animatePlayer();
				mainFrame->update();
				mainFrame->draw(hdc);
			}
			return;
		}
	}
}


void StreetMap::loadResource() {
	for (int i = 0; i < 7; i++) {
		Entity car("street/car" + to_string(i + 1));
		vehicle.push_back(car);
		car.flipHorizontal();
		vehicle.push_back(car);
	}
	return;
}

void StreetMap::shiftResource() {
	for (int i = 0; i < vehicle.size(); i++) {
		vehicle[i].shiftResource();
	}
	return;
}


ChessMap::ChessMap(HDC hdc, Frame* mapFrame, int levelDifficulty)  {
	mainFrame = mapFrame;
	this->hdc = hdc;
	difficulty = levelDifficulty;
	loadResource();
	for (int i = 0, prio = 2; i < 5; i++, prio += 2) {
		Lane* cur = new Lane(mainFrame, i, vehicle, levelDifficulty, CHESS_MAP, prio);
		this->mapLane.push_back(cur);
	}

	bgTexture = new Texture("image_bin/chess/chess.bin");
	bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
	player = Player(*mapFrame, CHESS_MAP);
}
ChessMap::~ChessMap() {
	for (auto ptr : mapLane) {
		delete ptr;
	}
	mapLane.clear();
}

void ChessMap::drawMap() {
	gameRunning = true;
	for (int i = 0; i < (int)mapLane.size(); i++) {
		mapLane[i]->resetLane();
		mapLane[i]->startLane();
	}
	thread t = player.launchHandler();
	/*thread spawner([this]() {
		return this->randomItemSpawner();
		});*/
	while (true) {
		//randomItemSpawner();
		for (int i = 0; i < (int)mapLane.size(); i++) {
			mapLane[i]->update();
		}
		bool collide = 0;
		for (int i = 0; i < (int)mapLane.size(); i++) {
			if (mapLane[i]->checkCollision(&player)) {
				collide = 1;
				break;
			}
		}
		mainFrame->update();
		mainFrame->draw(hdc);
		if (collide)
		{
			gameRunning = 0;
			player.stopPlayerHandler();
			t.join();
			for (auto& s : mapLane) {
				s->stopLane();
			}
			int sz = player.summon_Megumin();
			player.setSpritePriotity(1);
			while (sz--) {
				this_thread::sleep_for(200ms);
				player.animatePlayer();
				mainFrame->update();
				mainFrame->draw(hdc);
			}
			break;
		}
	}
}


void ChessMap::loadResource() {
	for (int i = 0; i < 15; i++) {
		Entity chess = ("chess/chess" + to_string(i + 1));
		chess.flipHorizontal();
		vehicle.push_back(chess);
		chess.flipHorizontal();
		vehicle.push_back(chess);
	}
	return;
}

TrainMap::TrainMap(HDC hdc, Frame* mapFrame, int levelDifficulty, vector<Lane>& maplane)  {
	mainFrame = mapFrame;
	this->hdc = hdc;
	difficulty = levelDifficulty;
	bgTexture = new Texture("image_bin/train.bin");
	bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
	for (int i = 0; i < (int)maplane.size(); i++) {
		this->mapLane.push_back(&maplane[i]);
	}
	Entity playerEntity("up");

	getTraffic(TRAIN_MAP, mapLane, trafficLight);

	for (int i = 0; i < 5; i++) {
		Sprite* tmp = trafficLight[i].getSprite();
		tmp->setPriority(10);
		mainFrame->addSprite(trafficLight[i].getSprite());
	}

}
TrainMap::~TrainMap() {
	for (auto ptr : mapLane) {
		delete ptr;
	}
	mapLane.clear();
}


void TrainMap::loadResource() {
	;
}

void Map::randomItemSpawner() {
	while (gameRunning) {
		srand(time(NULL));
		int seed = ((rand() + 139) * 491);
		this_thread::sleep_for(3s);
		if (seed % 2) {
			mapLane[seed % 10]->addItem("Slime", Vector2f());
		}
		else {
			mapLane[seed % 10]->addItem("Coin", Vector2f(seed % 1280, seed % 760));
		}
	}
}

int Map::getDiff() const {
	return player.getPoint();
}
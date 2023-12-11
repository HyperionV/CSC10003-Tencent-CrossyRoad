#pragma warning(disable:4244)
#include "Map.h"

StreetMap::StreetMap(HDC hdc, Frame* mapFrame, int levelDifficulty, Screen* screen) {
	this->screen = screen;
	mainFrame = mapFrame;
	this->hdc = hdc;
	difficulty = levelDifficulty;
	loadResource();
	for (int i = 0, prio = 2; i < 10; i++, prio += 2) {
		Lane* cur = new Lane(mainFrame, i, vehicle, levelDifficulty, STREET_MAP, prio);
		this->mapLane.push_back(cur);
	}
	bgTexture = new Texture("image_bin/street/street.bin");
	bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
	getTraffic(STREET_MAP, mapLane, trafficLight);
	for (int i = 0; i < 5; i++) {
		Sprite* tmp = trafficLight[i].getSprite();
		mainFrame->addSprite(tmp);
	}

	player = Player(*mapFrame, STREET_MAP);
}

StreetMap::~StreetMap() {
	for (auto ptr : mapLane) {
		delete ptr;
	}
	mapLane.clear();
	trafficLight.clear();
}


void StreetMap::drawMap() {
	screen->addScore();
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
		screen->updateScoreSprite(player.getPoint());
		shiftResource();
		trafficControl(trafficLight);
		for (int i = 0; i < (int)mapLane.size(); i++) {
			mapLane[i]->update();
		}
		bool collide = 0;
		int playerCurrentLane = player.convertLane(STREET_MAP);
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
				this_thread::sleep_for(50ms);
				player.animatePlayer();
				mainFrame->update();
				mainFrame->draw(hdc);
			}
			return;
		}
	}
}


void StreetMap::loadResource() {
	for (int i = 0; i < 5; i++) {
		Entity Slime("slime/slime" + to_string(i + 1));
		slime.push_back(Slime);
		Slime.flipHorizontal();
		slime.push_back(Slime);
	}
	for (int i = 0; i < 3; i++) {
		Entity Coin("coin/coin" + to_string(i + 1));
		coin.push_back(Coin);
	}
	for (int i = 0; i < 11; i++) {
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
	for (int i = 0; i < slime.size(); i++) {
		slime[i].shiftResource();
	}
	for (int i = 0; i < coin.size(); i++) {
		coin[i].shiftResource();
	}

	return;
}


ChessMap::ChessMap(HDC hdc, Frame* mapFrame, int levelDifficulty, Screen* screen) {
	this->screen = screen;
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
	screen->addScore();
	gameRunning = true;
	for (int i = 0; i < (int)mapLane.size(); i++) {
		mapLane[i]->resetLane();
		mapLane[i]->startLane();
	}
	thread t = player.launchHandler();
	cout << mapLane.size() << endl;
	thread spawner([this]() {
		return this->randomItemSpawner();
		});
	while (gameRunning) {
		shiftResource();
		screen->updateScoreSprite(player.getPoint());
		for (int i = 0; i < (int)mapLane.size(); i++) {
			mapLane[i]->update();
		}

		bool collide = 0;
		int playerCurrentLane = player.convertLane(CHESS_MAP);
		if (playerCurrentLane < 5) {
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
			player.setSpritePriotity(1);
			while (sz--) {
				this_thread::sleep_for(50ms);
				player.animatePlayer();
				mainFrame->update();
				mainFrame->draw(hdc);
			}
			return;
		}
	}
}

void ChessMap::shiftResource() {
	for (int i = 0; i < slime.size(); i++) {
		slime[i].shiftResource();
	}
	for (int i = 0; i < coin.size(); i++) {
		coin[i].shiftResource();
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
	for (int i = 0; i < 3; i++) {
		Entity Coin("coin/coin" + to_string(i + 1));
		coin.push_back(Coin);
	}
	return;
}

TrainMap::TrainMap(HDC hdc, Frame* mapFrame, int levelDifficulty, Screen* screen) {

	this->screen = screen;
	mainFrame = mapFrame;
	this->hdc = hdc;
	difficulty = levelDifficulty;
	loadResource();
	for (int i = 0, prio = 2; i < 10; i++, prio += 2) {
		Lane* cur = new Lane(mainFrame, i, vehicle, levelDifficulty, TRAIN_MAP, prio);
		this->mapLane.push_back(cur);
	}

	bgTexture = new Texture("image_bin/train/train.bin");
	bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
	getTraffic(TRAIN_MAP, mapLane, trafficLight);
	for (int i = 0; i < 5; i++) {
		Sprite* tmp = trafficLight[i].getSprite();
		mainFrame->addSprite(tmp);
	}
	player = Player(*mapFrame, TRAIN_MAP);
}


void TrainMap::drawMap() {
	screen->addScore();
	gameRunning = true;
	for (int i = 0; i < (int)mapLane.size(); i++) {
		mapLane[i]->resetLane();
		mapLane[i]->startLane();
	}

	thread t = player.launchHandler();
	thread spawner([this]() {
		return this->randomItemSpawner();
		});
	while (gameRunning) {
		screen->updateScoreSprite(player.getPoint());
		shiftResource();
		trafficControl(trafficLight);
		for (int i = 0; i < (int)mapLane.size(); i++) {
			mapLane[i]->update();
		}
		bool collide = 0;
		int playerCurrentLane = player.convertLane(TRAIN_MAP);
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
			player.setSpritePriotity(25);
			while (sz--) {
				this_thread::sleep_for(50ms);
				player.animatePlayer();
				mainFrame->update();
				mainFrame->draw(hdc);
			}
			return;
		}
	}
}


void TrainMap::loadResource() {
	for (int i = 0; i < 8; i++) {
		Entity train("train/train" + to_string(i + 1));
		vehicle.push_back(train);
		train.flipHorizontal();
		vehicle.push_back(train);
	}
	for (int i = 0; i < 5; i++) {
		Entity Slime("slime/slime" + to_string(i + 1));
		slime.push_back(Slime);
		Slime.flipHorizontal();
		slime.push_back(Slime);
	}
	for (int i = 0; i < 3; i++) {
		Entity Coin("coin/coin" + to_string(i + 1));
		coin.push_back(Coin);
	}
	return;
}

void TrainMap::shiftResource() {
	for (int i = 0; i < vehicle.size(); i++) {
		vehicle[i].shiftResource();
	}
	for (int i = 0; i < slime.size(); i++) {
		slime[i].shiftResource();
	}
	for (int i = 0; i < coin.size(); i++) {
		coin[i].shiftResource();
	}
	return;
}

TrainMap::~TrainMap() {
	for (auto ptr : mapLane) {
		delete ptr;
	}
	mapLane.clear();
	trafficLight.clear();
}

int Map::getDiff() const {
	return player.getPoint();
}

void Map::randomItemSpawner() {
	while (gameRunning) {
		long long epoch = chrono::system_clock::now().time_since_epoch().count();
		srand(epoch);
		int seed = rand() + 1;
		seed = seed * 2 + seed % 2;
		this_thread::sleep_for(1s);
		if (seed % 10 < 2) {
			seed = getRandomInRange(0, mapLane.size() - 1);
			mapLane[seed]->addItem("Slime", Vector2f(), slime, coin, seed);
		}
		else {
			int rand = getRandomInRange(0, mapLane.size() - 1);
			mapLane[rand]->addItem("Coin", Vector2f(((seed % 30) + 1) * 40, mapLane[rand]->getStart().y), slime, coin, rand);
		}
	}
}
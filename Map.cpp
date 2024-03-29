#pragma warning(disable:4244)
#include "Map.h"
#include <sstream>

Map::Map(Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName) :player(*mapFrame, STREET_MAP)
{
    this->player.setPlayerName(playerName);
}

Map::~Map() {
    mainFrame->removeAllSprite();
    if(bgTexture != nullptr){
        delete bgTexture;
        bgTexture = nullptr;
    }
    for (auto ptr : mapLane) {
        delete ptr;
    }
}

StreetMap::StreetMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName) :
    Map(mapFrame, levelDifficulty, screen, playerName)
{
    mapName = "StreetMap";
    player.setMap(STREET_MAP);
	this->screen = screen;
	mainFrame = mapFrame;
	this->hdc = hdc;
	difficulty = levelDifficulty;
	loadResource();

    this->screen->addScore();
	for (int i = 0, prio = 2; i < 10; i++, prio+=2) {
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
    for (int i = 0; i < (int)mapLane.size(); i++) {
        mapLane[i]->resetLane();
        mapLane[i]->startLane();
    }

}

StreetMap::StreetMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName, string mapString) :
        Map(mapFrame, levelDifficulty, screen, playerName) {
    mapName = "StreetMap";
    player.setMap(STREET_MAP);
    this->screen = screen;
    mainFrame = mapFrame;
    this->hdc = hdc;
    difficulty = levelDifficulty;
    loadResource();

    this->screen->addScore();
    for (int i = 0, prio = 2; i < 10; i++, prio+=2) {
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
    for (int i = 0; i < (int)mapLane.size(); i++) {
        mapLane[i]->resetLane();
        mapLane[i]->startLane();
    }
    loadMap(mapString);
    screen->updateScoreSprite(player.getPoint());
    for (int i = 0; i < (int)mapLane.size(); i++) {
        mapLane[i]->startLane();
    }
}



StreetMap::~StreetMap() {
	for (auto ptr : mapLane) {
		delete ptr;
	}
	mapLane.clear();
	trafficLight.clear();
    mainFrame->removeAllSprite();
}

void StreetMap::drawMap() {
	screen->startMusic(STREET_MAP);
	gameRunning = true;
    player.resumePlayerHandler();
	thread spawner([this]() {
		return this->randomItemSpawner();
		});
	bool collide = 0;
	while (gameRunning) {
        char c = 0;
        if(_kbhit()){
            c = _getch();
            bool continuePlaying = true;
            if(c == 'q') {
                continuePlaying = screen->screenPause();
                if (continuePlaying == true) {
                    gameRunning = false;
					player.stopPlayerHandler();
                    spawner.join();
                    fileDialog.ShowSaveFileDialog(saveMap(), player.getPlayerName() + "_" + to_string(player.getPoint()) + "_" + mapName);
                    mainFrame->removeAllSprite();
					if (screen->getMuicStatus() == 0) screen->stopMusic();
                    return;
                }
                else{
                }
            }
        }
        player.playerHandler(c);
		shiftResource();
		trafficControl(trafficLight);
		screen->updateScoreSprite(player.getPoint());
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
			spawner.join();
			for (auto& s : mapLane) {
				s->stopLane();
			}
			int sz = player.summon_Megumin();
			player.setSpritePriotity(25);

            for(int i = 0; i < 5; i++)
                for(int j = 0; j < sz; j++) {
                    this_thread::sleep_for(10ms);
                    player.animatePlayer();
                    mainFrame->update();
                    mainFrame->draw(hdc);
                }
			player.setSpritePriotity(0);
			if (screen->getMuicStatus() == 0) screen->stopMusic();
			screen->screenGameOver(player.getPoint(), player.getPlayerName());
            this_thread::sleep_for(500ms);
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

ChessMap::ChessMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName) :
        Map(mapFrame, levelDifficulty, screen, playerName)
{
    mapName = "ChessMap";
    player.setMap(CHESS_MAP);
	this->screen = screen;
	mainFrame = mapFrame;
	this->hdc = hdc;
	difficulty = levelDifficulty;
	loadResource();
    this->screen->addScore();
	for (int i = 0, prio = 2; i < 5; i++, prio += 2) {
		Lane* cur = new Lane(mainFrame, i, vehicle, levelDifficulty, CHESS_MAP, prio);
		this->mapLane.push_back(cur);
	}
    for (int i = 0; i < (int)mapLane.size(); i++) {
        mapLane[i]->resetLane();
        mapLane[i]->startLane();
    }

	bgTexture = new Texture("image_bin/chess/chess.bin");
	bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
}

ChessMap::ChessMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName,string mapString) :
        Map(mapFrame, levelDifficulty, screen, playerName)
{
    mapName = "ChessMap";
    player.setMap(CHESS_MAP);
    this->screen = screen;
    mainFrame = mapFrame;
    this->hdc = hdc;
    difficulty = levelDifficulty;
    loadResource();
    this->screen->addScore();
    for (int i = 0, prio = 2; i < 5; i++, prio += 2) {
        Lane* cur = new Lane(mainFrame, i, vehicle, levelDifficulty, CHESS_MAP, prio);
        this->mapLane.push_back(cur);
    }
    for (int i = 0; i < (int)mapLane.size(); i++) {
        mapLane[i]->resetLane();
        mapLane[i]->startLane();
    }

    bgTexture = new Texture("image_bin/chess/chess.bin");
    bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
    loadMap(mapString);
    screen->updateScoreSprite(player.getPoint());
    for (int i = 0; i < (int)mapLane.size(); i++) {
        mapLane[i]->startLane();
    }
}

ChessMap::~ChessMap() {
	for (auto ptr : mapLane) {
		delete ptr;
	}
	mapLane.clear();
    mainFrame->removeAllSprite();
}

void ChessMap::drawMap() {
	screen->startMusic(CHESS_MAP);
	gameRunning = true;

    player.resumePlayerHandler();
	thread spawner([this]() {
		return this->randomItemSpawner();
		});
	while (gameRunning) {
        char c = 0;
        if(_kbhit()){
            c = _getch();
            bool continueplaying = true;
            if(c == 'q') {
                continueplaying = screen->screenPause();
                if (continueplaying == true) {
                    gameRunning = false;
                    player.stopPlayerHandler();
                    spawner.join();
                    fileDialog.ShowSaveFileDialog(saveMap(), player.getPlayerName() + "_" + to_string(player.getPoint()) + "_" + mapName);
					if (screen->getMuicStatus() == 0) screen->stopMusic();
                    return;
                }
                else{
                }
            }
        }
        player.playerHandler(c);
		screen->updateScoreSprite(player.getPoint());
        shiftResource();
		for (int i = 0; i < (int)mapLane.size(); i++) {
			mapLane[i]->update();
		}

		bool collide = 0;
		int playercurrentlane = player.convertLane(CHESS_MAP);
		if (playercurrentlane < 5) {
			if (mapLane[playercurrentlane]->checkCollision(&player))
				collide = 1;
		}
		mainFrame->update();
		mainFrame->draw(hdc);
		if (collide) {
			gameRunning = 0;
			player.stopPlayerHandler();
            spawner.join();
			for (auto& s : mapLane) {
				s->stopLane();
			}
			int sz = player.summon_Megumin();
			player.setSpritePriotity(1);

			for (int i = 0; i < 5; i++)
				for (int j = 0; j < sz; j++) {
					this_thread::sleep_for(10ms);
					player.animatePlayer();
					mainFrame->update();
					mainFrame->draw(hdc);
				}
			player.setSpritePriotity(0);
			if (screen->getMuicStatus() == 0) screen->stopMusic();
			screen->screenGameOver(player.getPoint(), player.getPlayerName());
			this_thread::sleep_for(500ms);
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

TrainMap::TrainMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName) :
        Map(mapFrame, levelDifficulty, screen, playerName){
    mapName = "TrainMap";
    player.setMap(TRAIN_MAP);
	this->screen = screen;
	mainFrame = mapFrame;
	this->hdc = hdc;
	difficulty = levelDifficulty;
	loadResource();
	this->screen->addScore();
	for (int i = 0, prio = 2; i < 10; i++, prio += 2) {
		Lane* cur = new Lane(mainFrame, i, vehicle, levelDifficulty, TRAIN_MAP, prio);
		this->mapLane.push_back(cur);
	}

    for (int i = 0; i < (int)mapLane.size(); i++) {
        mapLane[i]->resetLane();
        mapLane[i]->startLane();
    }

	bgTexture = new Texture("image_bin/train/train.bin");
	bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
	getTraffic(TRAIN_MAP, mapLane, trafficLight);
	for (int i = 0; i < 5; i++) {
		Sprite* tmp = trafficLight[i].getSprite();
		mainFrame->addSprite(tmp);
	}
}

TrainMap::TrainMap(HDC hdc, Frame* mapFrame, int levelDifficulty, MenuScreen* screen, string playerName, string mapString) :
        Map(mapFrame, levelDifficulty, screen, playerName){
    mapName = "TrainMap";
    player.setMap(TRAIN_MAP);
    this->screen = screen;
    mainFrame = mapFrame;
    this->hdc = hdc;
    difficulty = levelDifficulty;
    loadResource();
    this->screen->addScore();
    for (int i = 0, prio = 2; i < 10; i++, prio += 2) {
        Lane* cur = new Lane(mainFrame, i, vehicle, levelDifficulty, TRAIN_MAP, prio);
        this->mapLane.push_back(cur);
    }

    for (int i = 0; i < (int)mapLane.size(); i++) {
        mapLane[i]->resetLane();
        mapLane[i]->startLane();
    }

    bgTexture = new Texture("image_bin/train/train.bin");
    bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
    getTraffic(TRAIN_MAP, mapLane, trafficLight);
    for (int i = 0; i < 5; i++) {
        Sprite* tmp = trafficLight[i].getSprite();
        mainFrame->addSprite(tmp);
    }
    loadMap(mapString);
    screen->updateScoreSprite(player.getPoint());
    for (int i = 0; i < (int)mapLane.size(); i++) {
        mapLane[i]->startLane();
    }
}


void TrainMap::drawMap() {
	screen->startMusic(TRAIN_MAP);
	gameRunning = true;
    player.resumePlayerHandler();
    thread spawner([this]() {
        return this->randomItemSpawner();
    });
	while (gameRunning) {
        char c = 0;
        if(_kbhit()){
            c = _getch();
            bool continuePlaying = true;
            if(c == 'q') {
                continuePlaying = screen->screenPause();
                if (continuePlaying == true) {
                    gameRunning = false;
                    spawner.join();
                    fileDialog.ShowSaveFileDialog(saveMap(), player.getPlayerName() + "_" + to_string(player.getPoint()) + "_" + mapName);
					if (screen->getMuicStatus() == 0) screen->stopMusic();
                    return;
                }
                else{
                }
            }
        }
        player.playerHandler(c);
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
			spawner.join();
			for (auto& s : mapLane) {
				s->stopLane();
			}
			int sz = player.summon_Megumin();
			player.setSpritePriotity(25);
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < sz; j++) {
					this_thread::sleep_for(10ms);
					player.animatePlayer();
					mainFrame->update();
					mainFrame->draw(hdc);
				}
			if (screen->getMuicStatus() == 0) screen->stopMusic();
			player.setSpritePriotity(0);
			screen->screenGameOver(player.getPoint(), player.getPlayerName());
			this_thread::sleep_for(500ms);
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
	mainFrame->removeAllSprite();
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

string Map::saveMap() {
    stringstream ss;
    ss << mapName << endl;
    ss << difficulty << endl;
    // Player info
    ss << player.cnt << endl;
    ss << player.getPlayerName() << endl;
    ss << player.getCurrentPos().x << " " << player.getCurrentPos().y << endl;
    ss << player.getPoint() << endl;
    ss << player.state << endl;


//     Lane info
    ss << mapLane.size() << endl;
    for (int i = 0; i < mapLane.size(); i++) {
        ss << mapLane[i]->saveLane();
    }

    return ss.str();
}

void Map::loadMap(string mapString) {
    stringstream ss(mapString);
    string mapName;
    ss >> mapName;
    ss >> difficulty;
    // Player info
    ss >> player.cnt;
    string playerName;
    ss >> playerName;
    player.setPlayerName(playerName);
    int x, y;
    ss >> x >> y;
    player.setPosition(x, y, 'l');
    int point;
    ss >> point;
    player.addPoint(point);
    int state;
    ss >> state;
    player.state = state;

    // Lane info
    int laneSize;
    ss >> laneSize;
    for (int i = 0; i < laneSize; i++) {
        mapLane[i]->loadLane(ss);
    }
    return;
}
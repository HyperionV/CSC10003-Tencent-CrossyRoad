#pragma warning(disable:4244)
#include "Map.h"


StreetMap::StreetMap(HDC hdc, Frame* mapFrame, int levelDifficulty) {

	mainFrame = mapFrame;
	this->hdc = hdc;
	difficulty = levelDifficulty;
	loadResource();
	for (int i = 0; i < 10; i++) {
		Lane* cur = new Lane(mainFrame, i, vehicle, levelDifficulty, STREET_MAP);
		this->mapLane.push_back(cur);
	}

	bgTexture = new Texture("image_bin/street.bin");
	bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
	//for (int i = 0; i < (int)maplane.size(); i++) {
	//	this->mapLane.push_back(&maplane[i]);
	//}

	Entity playerEntity("up");
	player = Player(playerEntity, *mapFrame);

	getTraffic(STREET_MAP, mapLane, trafficLight);
	for (int i = 0; i < 5; i++) {
		Sprite* tmp = trafficLight[i].getSprite();
		tmp->setPriority(9);
		mainFrame->addSprite(trafficLight[i].getSprite());
	}
}
StreetMap::~StreetMap() {
	for (auto ptr:mapLane) {
		delete ptr;
	}
	mapLane.clear();
	trafficLight.clear();
}


void StreetMap::drawMap() {
	//mapLane[0]->resetLane();
	//mapLane[0]->printStart();
	//mapLane[0]->printEnd();
	//cerr << "\n\n";
	for (int i = 0; i < (int)mapLane.size(); i++) {
		mapLane[i]->resetLane();
		mapLane[i]->startLane();
	}
	clock_t time = clock();
	while (true) {
		//if ((clock() - time)/CLOCKS_PER_SEC > 4)
		//	for (int i = 0; i < (int)mapLane.size(); i++) {
		//		mapLane[i]->stopLane();
		//	}
		//if ((clock() - time)/CLOCKS_PER_SEC > 6)
		//	for (int i = 0; i < (int)mapLane.size(); i++) {
		//		mapLane[i]->startLane();
		//	}
		shiftResource();
		//mapLane[1]->vehicles[0]->printPosition(); 
		trafficControl(trafficLight);
		for (int i = 0; i < (int)mapLane.size(); i++) {
			mapLane[i]->update();
		}
		mainFrame->update();
		mainFrame->draw(hdc);
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
	for (int i = 0; i < 5; i++) {
		Lane* cur = new Lane(mainFrame, i, vehicle, levelDifficulty, CHESS_MAP);
		this->mapLane.push_back(cur);
	}

	bgTexture = new Texture("image_bin/chess/chess.bin");
	bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
	Entity playerEntity("up");
	player = Player(playerEntity, *mapFrame);
}
ChessMap::~ChessMap() {
	for (auto ptr : mapLane) {
		delete ptr;
	}
	mapLane.clear();
}

void ChessMap::drawMap() {
	//mapLane[0]->resetLane();
	//mapLane[0]->printStart();
	//mapLane[0]->printEnd();
	//cerr << "\n\n";
	for (int i = 0; i < (int)mapLane.size(); i++) {
		//mapLane[i]->setVehicleCounter(14);
		mapLane[i]->resetLane();
		mapLane[i]->startLane();
	}
	clock_t time = clock();
	while (true) {
		//if ((clock() - time)/CLOCKS_PER_SEC > 4)
		//	for (int i = 0; i < (int)mapLane.size(); i++) {
		//		mapLane[i]->stopLane();
		//	}
		//if ((clock() - time)/CLOCKS_PER_SEC > 6)
		//	for (int i = 0; i < (int)mapLane.size(); i++) {
		//		mapLane[i]->startLane();
		//	}
		for (int i = 0; i < (int)mapLane.size(); i++) {
			mapLane[i]->update();
		}
		//mapLane[1]->vehicles[0]->printPosition(); 
		mainFrame->update();
		mainFrame->draw(hdc);
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
	//Entity carEntity = Entity("car4_motion");
	bgTexture = new Texture("image_bin/train.bin");
	bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
	for (int i = 0; i < (int)maplane.size(); i++) {
		this->mapLane.push_back(&maplane[i]);
	}
	Entity playerEntity("up");
	player = Player(playerEntity, *mapFrame);

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

void TrainMap::drawMap() {
	//mapLane[0]->resetLane();
	//mapLane[0]->printStart();
	//mapLane[0]->printEnd();
	//cerr << "\n\n";
	for (int i = 0; i < (int)mapLane.size(); i++) {
		mapLane[i]->resetLane();
		mapLane[i]->startLane();
	}
	clock_t time = clock();
	while (true) {
		//if ((clock() - time)/CLOCKS_PER_SEC > 4)
		//	for (int i = 0; i < (int)mapLane.size(); i++) {
		//		mapLane[i]->stopLane();
		//	}
		//if ((clock() - time)/CLOCKS_PER_SEC > 6)
		//	for (int i = 0; i < (int)mapLane.size(); i++) {
		//		mapLane[i]->startLane();
		//	}
		for (int i = 0; i < (int)mapLane.size(); i++) {
			mapLane[i]->update();
		}
		//mapLane[1]->vehicles[0]->printPosition(); 
		trafficControl(trafficLight);
		mainFrame->update();
		mainFrame->draw(hdc);
	}
}

void TrainMap::loadResource() {
	;
}

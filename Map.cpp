#include "Map.h"

Map::Map(HDC hdc, Frame* mapFrame, int levelDifficulty, vector<Lane> &MapLane) {
	mainFrame = mapFrame;
	this->hdc = hdc;
	difficulty = levelDifficulty;
	//Entity carEntity = Entity("car4_motion");
	bgTexture = new Texture("image_bin/street.bin");
    bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
	for (int i = 0; i < (int)MapLane.size(); i++) {
		this->mapLane.push_back(&MapLane[i]);
	}
	TrafficLight tl1(Vector2f(216, 70.2), mapLane[0], mapLane[1], 0);
	TrafficLight tl2(Vector2f(809.6, 180.4), mapLane[2], mapLane[3], 0);
	TrafficLight tl3(Vector2f(635, 284), mapLane[4], mapLane[5], 0);
	TrafficLight tl4(Vector2f(1195.4, 392.9), mapLane[6], mapLane[7], 0);
	TrafficLight tl5(Vector2f(211.1, 500.8), mapLane[8], mapLane[9], 0);
	trafficLight.emplace_back(tl1);
	trafficLight.emplace_back(tl2);
	trafficLight.emplace_back(tl3);
	trafficLight.emplace_back(tl4);
	trafficLight.emplace_back(tl5);
	for (int i = 0; i < 5; i++) {
		mainFrame->addSprite(trafficLight[i].getSprite());
	}
}

Map::~Map() {
	for (auto ptr:mapLane) {
		delete ptr;
	}
	mapLane.clear();
}

void Map::drawMap() {
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
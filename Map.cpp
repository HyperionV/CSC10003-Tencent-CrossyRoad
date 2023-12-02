#pragma warning(disable:4244)
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
	TrafficLight tl1(Vector2f(216, 70.2f), mapLane[0], mapLane[1], 0);
	TrafficLight tl2(Vector2f(809.6f, 180.4f), mapLane[2], mapLane[3], 0);
	TrafficLight tl3(Vector2f(635, 284.f), mapLane[4], mapLane[5], 0);
	TrafficLight tl4(Vector2f(1195.4f, 392.9f), mapLane[6], mapLane[7], 0);
	TrafficLight tl5(Vector2f(211.1f, 500.8f), mapLane[8], mapLane[9], 0);
	trafficLight.emplace_back(tl1);
	trafficLight.emplace_back(tl2);
	trafficLight.emplace_back(tl3);
	trafficLight.emplace_back(tl4);
	trafficLight.emplace_back(tl5);
	for (int i = 0; i < 5; i++) {
		Sprite* tmp = trafficLight[i].getSprite();
		tmp->setPriority(10);
		mainFrame->addSprite(trafficLight[i].getSprite());
	}
	player = Player(*mapFrame);
}

Map::~Map() {
	for (auto ptr:mapLane) {
		delete ptr;
	}
	mapLane.clear();
}

void Map::drawMap() {
	for (int i = 0; i < (int)mapLane.size(); i++) {
		mapLane[i]->resetLane();
		mapLane[i]->startLane();
	}
	clock_t time = clock();
	thread t = player.launchHandler();
	//player.playerHandler();
	while (true) {
		for (int i = 0; i < (int)mapLane.size(); i++) {
			mapLane[i]->update();
		}
		trafficControl(trafficLight);
        mainFrame->update();
        mainFrame->draw(hdc);
    }
}
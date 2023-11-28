#include "Map.h"

Map::Map(HDC hdc, Frame* mapFrame, int levelDifficulty, vector<Lane> &mapLane) {
	mainFrame = mapFrame;
	this->hdc = hdc;
	difficulty = levelDifficulty;
	//Entity carEntity = Entity("car4_motion");
	bgTexture = new Texture("image_bin/street.bin");
    bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));
	for (int i = 0; i < (int)mapLane.size(); i++) {
		this->mapLane.push_back(&mapLane[i]);
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
        mainFrame->update();
        mainFrame->draw(hdc);
    }
}
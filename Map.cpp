#include "Map.h"

Map::Map() {
//	background = Entity("street");
}

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

void Map::checkLane() {
	for (int i = 0; i < (int)mapLane.size(); i++) {
		cerr << "lane siz: " << mapLane[i]->model.getMotionSize() << '\n';
	}
}

void Map::drawMap() {
	//mapLane[0]->resetLane();
	while (true) {
		mapLane[0]->startLane();
		mapLane[0]->animateLane();

		//cerr << "3\n";
        mainFrame->update();
        mainFrame->draw(hdc);
    }
}
#include "Map.h"

Map::Map() {
//	background = Entity("street");
}

Map::Map(HDC hdc, Frame* mapFrame, int levelDifficulty) {
	mainFrame = mapFrame;
	this->hdc = hdc;
	difficulty = levelDifficulty;
	Entity carEntity("car4_motion");
	for (int i = 0; i < 10; i++) {
		Lane tmp = Lane(mainFrame, i, carEntity, difficulty);
		mapLane.push_back(&tmp);
	}
	bgTexture = new Texture("image_bin/street.bin");
    bg = mainFrame->addSprite(*bgTexture, Vector2f(0, 0));

}

Map::~Map() {
	for (auto ptr:mapLane) {
		delete ptr;
	}
	mapLane.clear();
}

void Map::update() {

}

void Map::drawMap() {
	while (true) {
        //cout << "here\n";
        mainFrame->update();
        mainFrame->draw(hdc);
    }
}
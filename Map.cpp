#include "Map.h"

Map::Map() {
	background = Entity("street");
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
	background = Entity("street");
}

Map::~Map() {
	for (auto ptr:mapLane) {
		delete ptr;
	}
	mapLane.clear();
}

void Map::drawMap() {
	Sprite* bg = mainFrame->addSprite(*(background.getCurrentTexture()), Vector2f(0, 0));
	bg->setEndPos(Vector2f(1280, 720), 0);

	while (true) {
		//cout << "here\n";
		mainFrame->update();
		mainFrame->draw(hdc);
	}

	delete bg;
}
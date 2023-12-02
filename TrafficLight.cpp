#include "TrafficLight.h"

void TrafficLight::INIT() {
	for (int i = 0; i < 3; i++) {
		lightTexture.push_back(Entity("trafficLight/light" + to_string(i + 1)));
	}
	return;
}

TrafficLight::TrafficLight(Vector2f pos, Lane* lane1, Lane* lane2, const int& status) {
	sprite = new Sprite(pos, lightTexture[0].getCurrentTexture());
	lane.push_back(lane1);
	lane.push_back(lane2);
}

TrafficLight::~TrafficLight() {
	
}

void TrafficLight::green() {
	lane[0]->startLane();
	lane[1]->startLane();
	status = 0;
}

void TrafficLight::yellow() {
	status = 1;
}

void TrafficLight::red() {
	lane[0]->stopLane();
	lane[1]->stopLane();
	status = 2;
	//sprite->setTexture(lightTexture[0].getCurrentTexture());
}

void TrafficLight::setStatus(const int& Status) {
	sprite->setTexture(lightTexture[Status].getCurrentTexture());
	switch (Status) {
	case 0:
		green();
		break;
	case 1:
		yellow();
		break;
	case 2:
		red();
		break;
	}

	return;
}

Sprite* TrafficLight::getSprite() const {
	return sprite;
}

void trafficControl(vector<TrafficLight> trafficLight) {
	int random1 = getRandomInRange(0, 4);
	int random2 = getRandomInRange(0, 4);
	int light = getRandomInRange(0, 2);
	trafficLight[random1].setStatus(light);
	return;
}
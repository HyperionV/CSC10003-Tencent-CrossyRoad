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

void getTraffic(const int& mapType, vector<Lane*>mapLane, vector<TrafficLight>& trafficLight) {
	if (mapType == STREET_MAP) {
		TrafficLight tl1(Vector2f(216, 70.2f), mapLane[0], mapLane[1], 0);
		tl1.getSprite()->setPriority(1);
		TrafficLight tl2(Vector2f(809.6f, 180.4f), mapLane[2], mapLane[3], 0);
		tl2.getSprite()->setPriority(5);
		TrafficLight tl3(Vector2f(635, 284.f), mapLane[4], mapLane[5], 0);
		tl3.getSprite()->setPriority(9);
		TrafficLight tl4(Vector2f(1195.4f, 392.9f), mapLane[6], mapLane[7], 0);
		tl4.getSprite()->setPriority(13);
		TrafficLight tl5(Vector2f(211.1f, 500.8f), mapLane[8], mapLane[9], 0);
		tl5.getSprite()->setPriority(17);

		trafficLight.push_back(tl1);
		trafficLight.push_back(tl2);
		trafficLight.push_back(tl3);
		trafficLight.push_back(tl4);
		trafficLight.push_back(tl5);
		return;
	}
	else {
		TrafficLight tl1(Vector2f(216, 70.2f), mapLane[0], mapLane[1], 0);
		tl1.getSprite()->setPriority(1);
		TrafficLight tl2(Vector2f(950.6f, 180.4f), mapLane[2], mapLane[3], 0);
		tl2.getSprite()->setPriority(5);
		TrafficLight tl3(Vector2f(500, 284.f), mapLane[4], mapLane[5], 0);
		tl3.getSprite()->setPriority(9);
		TrafficLight tl4(Vector2f(1050.4f, 392.9f), mapLane[6], mapLane[7], 0);
		tl4.getSprite()->setPriority(13);
		TrafficLight tl5(Vector2f(211.1f, 500.8f), mapLane[8], mapLane[9], 0);
		tl5.getSprite()->setPriority(17);

		trafficLight.push_back(tl1);
		trafficLight.push_back(tl2);
		trafficLight.push_back(tl3);
		trafficLight.push_back(tl4);
		trafficLight.push_back(tl5);
		return;
	}
}

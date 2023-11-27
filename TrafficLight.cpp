#include "TrafficLight.h"

void TrafficLight::INIT() {
	for (int i = 0; i < 3; i++) {
		lightTexture.push_back(Entity("trafficLight/light" + to_string(i + 1)));
	}
	return;
}

TrafficLight::TrafficLight(Vector2f pos, const int& status) {
	sprite = new Sprite(pos, lightTexture[0].getCurrentTexture());
}

TrafficLight::~TrafficLight() {
	;
}

void TrafficLight::green() {
	status = 0;
}

void TrafficLight::yellow() {
	status = 1;
}

void TrafficLight::red() {
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
void TrafficLight::randomLight() {
	int random = getRandomInRange(0, 1000000);

	//if (random <= 1000000 - 70) {
	//	status = 0;
	//}
	//else if (random <= 1000000 - 50) {
	//	status = 1;
	//}
	//else status = 2;
	setStatus(random % 3);
}

void trafficControl(vector<TrafficLight> trafficLight) {
	int random1 = getRandomInRange(0, 4);
	int random2 = getRandomInRange(0, 4);
	int light = getRandomInRange(0, 2);
	trafficLight[random1].setStatus(light);
	return;
}
#pragma once

#include <cstdlib> 
#include <ctime>
#include "Entity.h"
#include "Sprite.h"
#include "Supportive.h"

//#define TRAFFIC_LIGHT_POS_1 Vector2f()

class TrafficLight {
private :
	int status; //0 is green, 1 is yellow, 2 is red
	int preStatus;
	Sprite* sprite;
	static vector<Entity>lightTexture;
	vector<Lane*> lane;
public : 
	static void INIT();
	TrafficLight() {};
	TrafficLight(Vector2f pos, Lane* lane1, Lane* lane2, const int& status = 0);
	~TrafficLight();
	Sprite* getSprite() const;
	void setStatus(const int& status);
	void green();
	void yellow();
	void red();
};
void trafficControl(vector<TrafficLight> trafficLight);








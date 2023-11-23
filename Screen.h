#pragma once

#include "Sprite.h"
#include "Entity.h"
#include "Frame.h"
#include "Audio.h"
#include "Lane.h"
#include <conio.h>
#include <thread>
#include <chrono>
#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100
#define ON_CLICK 0


#define mainScreen Vector2f(1280, 720)
class Screen {
public:
	void crossyRoad();
	void screenAbout();
	void screenHelp();
	void startGame();
	void screenGame();
	bool screenPause();
	void screenOption();
	void screenPlay();
	void updateScoreSprite(int& score, int bonus);
	void changeTexture(const int& idx);
	Screen(const Screen& screen) = delete;

	static Screen* getInstance(Frame* curFrame, HDC* hdc) {
		if (instancePtr == nullptr) {
			instancePtr = new Screen(curFrame, hdc);
			return instancePtr;
		}
		else {
			return instancePtr;
		}
	}

	void setMusic();
	void playSound(const int& type);
	~Screen();
private :
	static Screen* instancePtr;
	Screen(Frame*, HDC* hdc);
	Screen();
	Frame* mainFrame;
	Sprite* backGround;
	vector<Entity> resources;
	vector<Sprite*> score;
	HDC* hdc;
	Audio* music;
	Audio* soundEffect;
	bool isMusicOff;
};

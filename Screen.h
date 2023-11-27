#pragma once

#include "Sprite.h"
#include "Entity.h"
#include "Frame.h"
#include "Audio.h"
#include "Supportive.h"
#include "Lane.h"
#include "Text.h"
#include <conio.h>
#include <thread>
#include <chrono>
#include <fstream>
#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100
#define ON_CLICK 0
#define NAME_COLUMN_WIDTH 309
#define NAME_COLUMN_OFFSET 216
#define SCORE_COLUMN_WIDTH 220
#define SCORE_COLUMN_OFFSET 542
#define DATE_COLUMN_WIDTH 265
#define DATE_COLUMN_OFFSET 763
#define ROW1_OFFSET 237
#define ROW2_OFFSET 317
#define ROW3_OFFSET 397
#define ROW4_OFFSET 478
#define ROW5_OFFSET 560
#define NAME_COL 1
#define SCORE_COL 2
#define DATE_COL 3




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
	void screenLeaderboard();
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

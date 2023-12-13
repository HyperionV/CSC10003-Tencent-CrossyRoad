#pragma once

#include "Sprite.h"
#include "Entity.h"
#include "Frame.h"
#include "Audio.h"
#include "Supportive.h"
#include "Lane.h"
#include "Text.h"
#include "FileDialog.h"
#include "TextBox.h"
#include <conio.h>
#include <thread>
#include <chrono>
#include <fstream>
#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100
#define ON_CLICK "sound/on_click.wav"
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
class MenuScreen {
public:
    int map;
    // 0 - street map
    // 1 - chess map
    // 2 - train map
    // 3 - load map
	void screenGameOver(const int& score);
	void screenAbout();
	void screenHelp();
	int startGame();
	int screenChooseMap();
	bool screenPause();
	void screenOption();
	void screenPlay();
	void screenLeaderboard();
    string screenPlayerName();
	void updateScoreSprite(const int& score);
	void changeTexture(const int& idx);
	void addScore();
	bool getMuicStatus() const;
	MenuScreen(const MenuScreen& screen) = delete;

	static MenuScreen* getInstance(Frame* curFrame, HDC* hdc) {
		if (instancePtr == nullptr) {
			instancePtr = new MenuScreen(curFrame, hdc);
			return instancePtr;
		}
		else {
			return instancePtr;
		}
	}

	void setMusic(const int& mapType = -1);
	void startMusic(const int& mapType);
	void stopMusic();

	~MenuScreen();

private :
	static MenuScreen* instancePtr;
	MenuScreen(Frame*, HDC* hdc);
	MenuScreen();
	Frame* mainFrame;
	Sprite* backGround;
	vector<Entity> resources;
	vector<Sprite*> score;
	HDC* hdc;
	Audio* music;
	Audio* soundEffect;
	bool isMusicOff;
};

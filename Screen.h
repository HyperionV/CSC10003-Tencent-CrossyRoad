#pragma once

#include "Sprite.h"
#include "Entity.h"
#include "Frame.h"
#include "Audio.h"
#include <conio.h>
#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100



#define mainScreen Vector2f(1280, 720)
class Screen {
public:
	void screenAbout();
	void screenHelp();
	void startGame();
	void screenGame();
	bool screenPause();
	void screenOption();
	void screenPlay();
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
	vector<Sprite*>menu;
	vector<Sprite*>option;
	vector<Sprite*>pause;
	vector<Sprite*>loadGame;
	Sprite* leaderBoard;
	HDC* hdc;
	Audio* music;
	bool isMusicOff;
};

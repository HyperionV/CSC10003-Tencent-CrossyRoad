#pragma once

#include "Utilities.h"
#include "Sprite.h"
#include "Frame.h"
#include "Text.h"
#include <time.h>
#include <conio.h>
#include <stdio.h>

const float tickRate = 0.5;

class TextCursor {
	Texture* cursorTexture;
	Sprite* cursorSprite;
	Text* textToDraw;
	Vector2i cursorInitPosition, cursorRightmostPosition, cursorCurrentPosition;
	clock_t curClock;
	string textContent;
	int nextClock;
	bool isTick;
	int cursorWidth, cursorHeight;
public:
	TextCursor();
	TextCursor(Vector2i cursorInit, Vector2i cursorRightmost);
	TextCursor(Vector2i cursorInit, Vector2i cursorRightmost, int cursorWidth, int cursorHeight);
	~TextCursor();
	int getTextLength();
	void checkCursor(Frame* mainFrame);
	bool cursorOutOfBound();
	bool textControl();
	void drawText(Frame* mainFrame);
	void setCursorSize(int width, int height);
	string getStringContent();
};
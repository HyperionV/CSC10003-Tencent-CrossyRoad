#pragma once

#include "Utilities.h"
#include "Sprite.h"
#include "Frame.h"
#include "Text.h"
#include <time.h>
#include <conio.h>
#include <stdio.h>

const float tickRate = 0.5;

/*
 * TextCursor Class
 * One of the few components of the text box (see TextBox.h).
 * The text cursor associate with the text written on the screen.
 */

class TextCursor {
	Texture* cursorTexture;
	Sprite* cursorSprite;
	Text* textToDraw;
    Frame* mainFrame;
	Vector2i cursorInitPosition, cursorRightmostPosition, cursorCurrentPosition;
	clock_t curClock;
	string textContent;
	int nextClock;
	bool isTick;
	int cursorWidth, cursorHeight;
public:
	TextCursor(Frame* mainFrame);
	TextCursor(Frame* mainFrame, Vector2i cursorInit, Vector2i cursorRightmost);
	TextCursor(Frame* mainFrame, Vector2i cursorInit, Vector2i cursorRightmost, int cursorWidth, int cursorHeight);
	~TextCursor();
	int getTextLength();
	void checkCursor();
	bool cursorOutOfBound();
	bool textControl();
	void drawText();
	void setCursorSize(int width, int height);
	string getStringContent();
};
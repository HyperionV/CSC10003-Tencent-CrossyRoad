#include "TextCursor.h"

TextCursor::TextCursor() {
	cursorWidth = 2, cursorHeight = 20;
	textToDraw = new Text;
	cursorTexture = new Texture(2, 20, 0, 0, 0, 255);
	cursorInitPosition = cursorCurrentPosition = Vector2i(0, 0);
	cursorRightmostPosition = Vector2i(190, 0);
	curClock = clock();
	isTick = 0;
	Vector2f tmp = Vector2f(cursorInitPosition.x, cursorInitPosition.y);
	cursorSprite = new Sprite(tmp, cursorTexture, 50);
}

TextCursor::TextCursor(Vector2i cursorInit, Vector2i cursorRightmost) {
	cursorWidth = 2, cursorHeight = 20;
	textToDraw = new Text;
	cursorTexture = new Texture(2, 20, 0, 0, 0, 255);
	cursorInitPosition = cursorCurrentPosition = cursorInit;
	cursorRightmostPosition = cursorRightmost;
	curClock = clock();
	isTick = 0;
	Vector2f tmp = Vector2f(cursorInitPosition.x, cursorInitPosition.y);
	cursorSprite = new Sprite(tmp, cursorTexture, 50);
}

TextCursor::TextCursor(Vector2i cursorInit, Vector2i cursorRightmost, int cursorWidth, int cursorHeight) {
	this->cursorWidth = cursorWidth, this->cursorHeight = cursorHeight;
	textToDraw = new Text;
	cursorTexture = new Texture(2, 20, 0, 0, 0, 255);
	cursorInitPosition = cursorCurrentPosition = cursorInit;
	cursorRightmostPosition = cursorRightmost;
	curClock = clock();
	isTick = 0;
	Vector2f tmp = Vector2f(cursorInitPosition.x, cursorInitPosition.y);
	cursorSprite = new Sprite(tmp, cursorTexture, 50);
}

TextCursor::~TextCursor() {
	delete cursorTexture;
	delete cursorSprite;
	delete textToDraw;
}

void TextCursor::checkCursor(Frame* mainFrame) {
	if (((-curClock + clock()) / CLOCKS_PER_SEC) >= tickRate) {
		isTick = !isTick;
		curClock = clock();
		if (!isTick) {
			mainFrame->removeSprite(cursorSprite);
		}
		else {
			Vector2f tmp = Vector2f(cursorCurrentPosition.x, cursorCurrentPosition.y);
			if (cursorSprite != nullptr) {
				delete cursorSprite;
				cursorSprite = nullptr;
			}
			cursorSprite = new Sprite(tmp, cursorTexture, 50);
			mainFrame->addSprite(cursorSprite);
		}
	}
}

bool TextCursor::cursorOutOfBound() {
	return cursorInitPosition.x > cursorRightmostPosition.x;
}

int SpaceChar[] = { 21, 21, 21, 21, 21, 21, 21, 21, 6, 10, 21, 10, 29, 21, 21, 21, 21, 18, 19, 16, 21, 21, 34, 21, 21, 21 };

int TextCursor::getTextLength() {
	int length = 0;
	for (int i = 0; i < textContent.length(); i++) {
		if (textContent[i] >= 'a' && textContent[i] <= 'z') {
			length += SpaceChar[textContent[i] - 'a'];
		}
		else if (textContent[i] >= '0' && textContent[i] <= '9') {
			if (textContent[i] == '1')
				length += 14;
			else length += 21;
		}
		else {
			length += 19;
		}
	}
	return length;
}

bool TextCursor::textControl() {
	if (_kbhit()) {
		//cerr << "cursor size: " << cursorHeight << '\n';
		char curChar = getch();
		int maxLength = cursorRightmostPosition.x - cursorInitPosition.x;
		if (('a' <= curChar && curChar <= 'z') || ('0' <= curChar && curChar <= '9')) { // character
			textContent.push_back(curChar);
			int textLength = getTextLength();
			//cerr << "maxLength, textLength: " << maxLength << " " << getTextLength() << '\n';
			if (maxLength < textLength) {
				textContent.pop_back();
				return false;
			}
			cursorCurrentPosition.x = textLength;
			curClock = clock() - clock();
		}
		else if (curChar == 8) { // backspace
			if (textContent.empty())
				return false;
			textContent.pop_back();
			int textLength = getTextLength();
			cursorCurrentPosition.x = textLength;
			curClock = clock() - clock();
		}
		else if (curChar == 13) { // enter
			if (textContent.empty())
				return false;
			return true;
		}
	}
	return false;
}

void TextCursor::drawText(Frame* mainFrame) {
	checkCursor(mainFrame);

	textToDraw->removeText(mainFrame);
	if (textToDraw != nullptr) {
		delete textToDraw;
		textToDraw = nullptr;
	}
	textToDraw = new Text(textContent);
	textToDraw->writeText(cursorInitPosition.x, cursorInitPosition.y, mainFrame, 50);
}

void TextCursor::setCursorSize(int width, int height) {
	cursorWidth = width, cursorHeight = height;
	if (cursorTexture != nullptr) {
		delete cursorTexture;
		cursorTexture = nullptr;
	}
	cursorTexture = new Texture(2, height, 0, 0, 0, 255);
}

string TextCursor::getStringContent() {
	return textContent;
}
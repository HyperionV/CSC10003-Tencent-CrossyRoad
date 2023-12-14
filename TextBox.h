#pragma once

#include "TextCursor.h" 

/*
 * TextBox Class
 * Defines basic behaviour of a standard text box. Contains TextCursor and Text (within TextCursor itself).
 * Limits the player to type within a given space, and some typing restrictions are given:
 * Only allows player to type lowercase latin letters and numbers.
 */

class TextBox {
	Texture* textFrame;
	Sprite* textSprite;
	TextCursor cursor;
	string enteredText;
    Frame* mainFrame;

public:
	TextBox();
	~TextBox();
	TextBox(Frame* mainFrame, Vector2i initPosition, Vector2i rightmostPosition);
	TextBox(Frame* mainFrame, Vector2i initPosition, Vector2i rightmostPosition, int width, int height);
	TextBox(Frame* mainFrame, Vector2i initPosition, Vector2i rightmostPosition, Texture* textFrameTexture);
	bool TextBoxControl();
	string getEnteredText();
	void addTextBoxSprite();
	void removeTextBoxSprite();
	void drawTextBox();
	void setCursorSize(int width, int height);
};
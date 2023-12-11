#pragma once

#include "TextCursor.h" 

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
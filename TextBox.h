#pragma once

#include "TextCursor.h" 

class TextBox {
	Texture* textFrame;
	Sprite* textSprite;
	TextCursor cursor;
	string enteredText;
public:
	TextBox();
	~TextBox();
	TextBox(Vector2i initPosition, Vector2i rightmostPosition);
	TextBox(Vector2i initPosition, Vector2i rightmostPosition, int width, int height);
	TextBox(Vector2i initPosition, Vector2i rightmostPosition, Texture* textFrameTexture);
	bool TextBoxControl();
	string getEnteredText();
	void addTextBoxSprite(Frame* mainFrame);
	void removeTextBoxSprite(Frame* mainFrame);
	void drawTextBox(Frame* mainFrame);
	void setCursorSize(int width, int height);
};
#include "TextBox.h"

TextBox::TextBox() {
	textFrame = new Texture(200, 30, 255, 255, 255, 255);
	Vector2f textBoxPosition = Vector2f(0, 0);
	textSprite = new Sprite(textBoxPosition, textFrame, 30);
}

TextBox::~TextBox() {
	delete textFrame;
	delete textSprite;
}

TextBox::TextBox(Vector2i initPosition, Vector2i rightmostPosition) {
	cursor = TextCursor(initPosition, rightmostPosition);
	textFrame = new Texture(200, 30, 255, 255, 255, 255);
	Vector2f textBoxPosition = Vector2f(initPosition.x - 10, initPosition.y - 5);
	textSprite = new Sprite(textBoxPosition, textFrame, 30);
}

TextBox::TextBox(Vector2i initPosition, Vector2i rightmostPosition, int width, int height) {
	cursor = TextCursor(initPosition, rightmostPosition);
	textFrame = new Texture(width, height, 255, 255, 255, 255);
	Vector2f textBoxPosition = Vector2f(initPosition.x - 10, initPosition.y - 5);
	textSprite = new Sprite(textBoxPosition, textFrame, 30);
}

TextBox::TextBox(Vector2i initPosition, Vector2i rightmostPosition, Texture* textFrameTexture) {
	cursor = TextCursor(initPosition, rightmostPosition);
	textFrame = new Texture;
	textFrame = textFrameTexture;
	Vector2f textBoxPosition = Vector2f(initPosition.x - 10, initPosition.y - 5);
	textSprite = new Sprite(textBoxPosition, textFrame, 30);
}

bool TextBox::TextBoxControl() {
	bool isEntered = cursor.textControl();
	if (isEntered) {
		return true;
	}
	return false;
}

string TextBox::getEnteredText() {
	return enteredText;
}

void TextBox::addTextBoxSprite(Frame* mainFrame) {
	mainFrame->addSprite(textSprite);
}
void TextBox::removeTextBoxSprite(Frame* mainFrame) {
	mainFrame->removeSprite(textSprite);
}

void TextBox::drawTextBox(Frame* mainFrame) {
	bool isEntered = TextBoxControl();
	cursor.drawText(mainFrame);
	if (isEntered) {
		enteredText = cursor.getStringContent();
	}
}

void TextBox::setCursorSize(int width, int height) {
	cursor.setCursorSize(width, height);
}
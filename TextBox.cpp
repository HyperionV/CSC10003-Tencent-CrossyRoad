#include "TextBox.h"

TextBox::TextBox() :
    cursor(nullptr, Vector2i(0, 0), Vector2i(0, 0))
{
	textFrame = new Texture(200, 30, 255, 255, 255, 255);
	Vector2f textBoxPosition = Vector2f(0, 0);
	textSprite = new Sprite(textBoxPosition, textFrame, 30);

}

TextBox::~TextBox() {
	delete textFrame;
    removeTextBoxSprite();
}

TextBox::TextBox(Frame* mainFrame, Vector2i initPosition, Vector2i rightmostPosition)
    : cursor(mainFrame ,initPosition, rightmostPosition)
{
	textFrame = new Texture(200, 30, 255, 255, 255, 255);
	Vector2f textBoxPosition = Vector2f(initPosition.x - 10, initPosition.y - 5);
	textSprite = new Sprite(textBoxPosition, textFrame, 30);
    this->mainFrame = mainFrame;
}

TextBox::TextBox(Frame* mainFrame, Vector2i initPosition, Vector2i rightmostPosition, int width, int height) :
    cursor(mainFrame ,initPosition, rightmostPosition)
{
	textFrame = new Texture(width, height, 255, 255, 255, 255);
	Vector2f textBoxPosition = Vector2f(initPosition.x - 10, initPosition.y - 5);
	textSprite = new Sprite(textBoxPosition, textFrame, 30);
    this->mainFrame = mainFrame;
}

TextBox::TextBox(Frame* mainFrame, Vector2i initPosition, Vector2i rightmostPosition, Texture* textFrameTexture) :
    cursor(mainFrame ,initPosition, rightmostPosition)
{
	textFrame = new Texture;
	textFrame = textFrameTexture;
	Vector2f textBoxPosition = Vector2f(initPosition.x - 10, initPosition.y - 5);
	textSprite = new Sprite(textBoxPosition, textFrame, 30);
    this->mainFrame = mainFrame;
}

bool TextBox::TextBoxControl() {
	bool isEntered = cursor.textControl();
	if (isEntered) {
		return true;
	}
	return false;
}

string TextBox::getEnteredText() {
	return cursor.getStringContent();
}

void TextBox::addTextBoxSprite() {
	mainFrame->addSprite(textSprite);
}
void TextBox::removeTextBoxSprite() {
	mainFrame->removeSprite(textSprite);
}

void TextBox::drawTextBox() {
	bool isEntered = TextBoxControl();
	cursor.drawText();
	if (isEntered) {
		enteredText = cursor.getStringContent();
	}
}

void TextBox::setCursorSize(int width, int height) {
	cursor.setCursorSize(width, height);
}
#pragma warning(disable:4244)
#include "Text.h"

int spaceChar[] = { 21, 21, 21, 21, 21, 21, 21, 21, 6, 10, 21, 10, 29, 21, 21, 21, 21, 18, 19, 16, 21, 21, 34, 21, 21, 21 };
// i was so dumb...
Text::Text() {

}

Text::Text(const string& text) {
	t = text;
	length = 0;
	for (int i = 0; i < text.length(); i++) {
		this->text.push_back(new Sprite);
	}

	for (int i = 0; i < text.length(); i++) {
		if (text[i] >= 'a' && text[i] <= 'z') {
			this->text[i]->setTexture(alphabet[text[i] - 'a'].getCurrentTexture());
			if (i != text.length() - 2)
				length += spaceChar[t[i] - 'a'];
		}
		else if (t[i] >= '0' && t[i] <= '9') {
			this->text[i]->setTexture(numeric[text[i] - '0'].getCurrentTexture());
			if (t[i] == '1')
				length += 14;
			else length += 21;
		}
		else {
			length += 19;
			this->text[i]->setTexture(numeric[10].getCurrentTexture());
		}
	}
}

void Text::writeText(const int& x, const int& y, Frame* frame, int priority) {
	int offset = 0;
	for (int i = 0; i < this->text.size(); i++) {
		this->text[i]->setPosition(Vector2f(x + offset, y));
		if (t[i] >= 'a' && t[i] <= 'z')
			offset += spaceChar[t[i] - 'a'];
		else if (t[i] >= '0' && t[i] <= '9') {
			if (t[i] == '1')
				offset += 14;
			else offset += 21;
		}
		else offset += 19;
		text[i]->setPriority(priority);
		frame->addSprite(text[i]);
	}
	return;
}

void Text::removeText(Frame* frame) {
	for (int i = 0; i < (int)text.size(); i++) {
		frame->removeSprite(text[i]);
	}
}

void Text::INIT() {
	for (int i = 0; i < 26; i++) {
		char c = 'a' + i;
		alphabet.push_back(Entity("alphabet/alpha_" + string(1, c), true));
	}
	for (int i = 0; i < 11; i++) {
		numeric.push_back(Entity("numeric/num_" + to_string(i), true));
	}
	return;
}

int Text::getLength() const {
	return this->length;
}
Text::~Text() {
	for (int i = 0; i < this->text.size(); i++) {
		delete this->text[i];
		this->text[i] = nullptr;
	}
}

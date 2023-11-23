#include "Font.h"
#include "Utilities.h"

using namespace utility;

Font::Font() {

}

Font::Font(string filename) {
	readFont(filename);
}

Font::~Font() {
	clearFont();
}

void Font::readFont(string fontName) {
	clearFont();
	string path = "font/" + fontName + "/" + fontName + "_";
	for (int i = 32; i <= 126; i++) {
		string filename = path + to_string(i) + ".bin";
		Texture* texture = new Texture(filename);
		characters[i] = texture;
	}
}

void Font::clearFont() {
	for (auto& x : characters) {
		delete x.second;
	}
	characters.clear();
}

Texture* Font::getCharacter(char c) {
	return characters[c];
}





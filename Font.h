#pragma once
#include "Texture.h"
#include <map>

using namespace std;

//docstring

/* Font class
* Filename format: fontName_character.png
* Only supports characters from ASCII 32 to 126
* This class is used to store a font
* A font is a map of characters to textures
* This class also provides methods to read a font from a file
*/

class Font {
	map<char, Texture*> characters;
public:
	Font();
	Font(const string& fontName);
	~Font();

	void readFont(const string& fontName);
	void clearFont();
	Texture* getCharacter(const char& c);
};


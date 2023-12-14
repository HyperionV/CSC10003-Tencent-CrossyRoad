#pragma once

#include "Entity.h"
#include "Sprite.h"
#include <iostream>
#include <vector>

/*
 * Text Class
 * Used for writing text to the console. A fixed font is pre-defined.
 */

class Text {
private : 
	vector<Sprite*> text;
	string t;
	int length;
    Frame* mainFrame;
	static vector<Entity>alphabet;
	static vector<Entity>numeric;
public :
	static void INIT();
	int getLength() const;
	Text(Frame* mainFrame);
	Text(Frame* mainFrame, const string& text);
	void writeText(const int& x, const int& y, int priority = 0);
	void removeText();
	~Text();

};

#pragma once


#include "Entity.h"
#include "Sprite.h"
#include <iostream>
#include <vector>

class Text {
private : 
	vector<Sprite*> text;
	string t;
	int length;
	static vector<Entity>alphabet;
	static vector<Entity>numeric;
public :
	static void INIT();
	int getLength() const;
	Text();
	Text(const string& text);
	void writeText(const int& x, const int& y, Frame* frame);
	~Text();

};

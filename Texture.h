#pragma once

#include <vector>
#include <string>
#include <Windows.h>
#include <winuser.h>
#include "Pixel.h"
#include "Utilities.h"

using namespace std;
using namespace utility;

class Texture
/*
* Texture class
 * This class is used to store the texture of sprites. Contains a 2D vector of pixels.
 * Multiple sprites can share the same texture, reducing memory usage.
 * Supports reading texture from file, printing texture to console, flipping texture horizontally and drawing texture to screen.
 * */
{
protected:
	int width;
	int height;
	vector<vector<Pixel>> pixels;
public:
	Texture();
	Texture(int width, int height);
	Texture(int width, int height, int r, int g, int b, int a);
    Texture(const string& filename);
	Texture(const Texture& other);
	Texture(Texture* other);
	~Texture();

	void setPixel(int x, int y, Pixel pixel);
	Pixel getPixel(int x, int y);
	int getWidth();
	int getHeight();

	void readTexture(string filename);
	void print();
	void flipHorizontal();
	void drawTexture(int top, int left, Rect2D textureRect, void* bits, Vector2i frameSize);
};
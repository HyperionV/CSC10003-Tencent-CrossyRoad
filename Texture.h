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
/* Texture class
 * This class is used to store a texture
 * A texture is a 2D array of pixels
 * This class also provides methods to read a texture from a file
 * and draw a texture to a device context
 */
{
protected:
	int width;
	int height;
	vector<vector<Pixel>> pixels;
public:
	Texture();
	Texture(int width, int height);
    Texture(const string& filename);
	Texture(const Texture& other);
	Texture(Texture* other);
	~Texture();

	void setPixel(int x, int y, Pixel pixel);
	Pixel getPixel(int x, int y);
	int getWidth();
	int getHeight();
	Vector2i getSize();

	void readTexture(string filename);
	void print();
	void drawTexture(int top, int left, Rect2D textureRect, HDC hdc);
	void drawTexture(int top, int left, Rect2D textureRect, void* bits, Vector2i frameSize);
};
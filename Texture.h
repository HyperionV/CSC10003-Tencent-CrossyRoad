#pragma once

#include <vector>
#include <string>
#include <Windows.h>
#include <winuser.h>
#include "Pixel.h"

using namespace std;

class Texture
{
private:
	int width;
	int height;
	vector<vector<Pixel>> pixels;
public:
	Texture();
	Texture(int width, int height);
	Texture(const Texture& other);
	~Texture();
	void setPixel(int x, int y, Pixel pixel);
	Pixel getPixel(int x, int y);
	int getWidth();
	int getHeight();

	void readTexture(string filename);
	void print();
	void drawTexture(int x, int y, HDC hdc);
    void drawToMem(HDC hdc);
    void fastDrawTexture(int x, int y, HDC hdc);
};
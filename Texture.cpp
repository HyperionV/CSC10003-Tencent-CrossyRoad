#include "Texture.h"
#include <fstream>
#include <iostream>

using namespace std;

Texture::Texture() {
    width = 0;
    height = 0;
    pixels = vector<vector<Pixel>>();
}

Texture::Texture(int width, int height) {
    this->width = width;
    this->height = height;
    pixels = vector<vector<Pixel>>(height, vector<Pixel>(width));
}

Texture::Texture(const Texture& other) {
    width = other.width;
    height = other.height;
    pixels = other.pixels;
}

Texture::~Texture() {
    // Do nothing
}

void Texture::setPixel(int x, int y, Pixel pixel) {
    pixels[y][x] = pixel;
}

Pixel Texture::getPixel(int x, int y) {
    return pixels[y][x];
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}

void Texture::readTexture(string filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Cannot open file " << filename << "\n";
        return;
    }
    file.read(reinterpret_cast<char*>(&width), sizeof(int));
    file.read(reinterpret_cast<char*>(&height), sizeof(int));
    pixels = vector<vector<Pixel>>(height, vector<Pixel>(width));

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++)
        {
            int a, r, g ,b;
            int color;
            file.read(reinterpret_cast<char*>(&color), sizeof(int));
            a = (color >> 24) & 0xFF;
            b = (color >> 16) & 0xFF;
            g = (color >> 8) & 0xFF;
            r = color & 0xFF;
            pixels[row][col] = Pixel(r, g, b, a);
        }
    }

    file.close();
}

void Texture::print() {
    cerr << "Width: " << width << "\n";
    cerr << "Height: " << height << "\n";
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++)
        {
            cout << "(" << row << ", " << col << "): ";
            pixels[row][col].print();
            cout << "\n";
        }
    }
}

void Texture::drawTexture(int x, int y, HDC hdc) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
        {
            pixels[i][j].drawPixel(x + j, y + i, hdc);
        }
    }
}
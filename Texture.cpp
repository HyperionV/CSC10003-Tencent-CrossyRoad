#include "Texture.h"
#include <fstream>
#include <iostream>
#include <thread>

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

Texture::Texture(const string& filename) {
    width = 0;
    height = 0;
    pixels = vector<vector<Pixel>>();
    readTexture(filename);
}

Texture::Texture(Texture* other) {
    width = other->width;
    height = other->height;
    pixels = other->pixels;
}

Texture::~Texture() {
    // Do nothing
}

void Texture::flipHorizontal() {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width / 2; col++) {
            Pixel temp = pixels[row][col];
            pixels[row][col] = pixels[row][width - col - 1];
            pixels[row][width - col - 1] = temp;
        }
    }
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
//    cerr << "Height: " << pixels.size() << "\n";
//    if(pixels.size() > 0)
//        cerr << "Width: " << pixels[0].size() << "\n";
//    else
//        cerr << "Width: 0\n";
//    cerr << "\n";

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
    cerr << "Height: " << pixels.size() << "\n";
    if(pixels.size() > 0)
        cerr << "Width: " << pixels[0].size() << "\n";
    else
        cerr << "Width: 0\n";
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++)
        {
            cout << "(" << row << ", " << col << "): ";
            pixels[row][col].print();
            cout << "\n";
        }
    }
}

void Texture::drawTexture(int top, int left, Rect2D textureRect, void *bits, Vector2i frameSize) {
    for (int y = 0; y < textureRect.height; y++) {
        for (int x = 0; x < textureRect.width; x++) {
            if (textureRect.top + y < 0 || textureRect.top + y >= frameSize.y || textureRect.left + x < 0 || textureRect.left + x >= frameSize.x)
                continue;
            if (textureRect.top + y >= (int) pixels.size() || textureRect.left + x >= (int) pixels[textureRect.top + y].size())
                continue;
            if(pixels[textureRect.top + y][textureRect.left + x].getA() == 0)
                continue;
            if(top + y < 0 || top + y >= frameSize.y || left + x < 0 || left + x >= frameSize.x)
                continue;
            // Get a pointer to the pixel at (top, left)
            BYTE* pPixel = (BYTE*)bits + ((top + y) * frameSize.x + (left + x)) * 4;

            // Set the pixel (R, G, B, A)
            pPixel[0] = pixels[textureRect.top + y][textureRect.left + x].getB();
            pPixel[1] = pixels[textureRect.top + y][textureRect.left + x].getG();
            pPixel[2] = pixels[textureRect.top + y][textureRect.left + x].getR();
            pPixel[3] = pixels[textureRect.top + y][textureRect.left + x].getA();
        }
    }
}
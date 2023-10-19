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

void Texture::drawToMem(HDC hdc) {

}

void Texture::fastDrawTexture(int x, int y, HDC hdc) {
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // Negative height to specify a top-down DIB
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32; // 32 bits per pixel (for RGBA)

    void* bits; // Pointer to the bitmap pixel data

    // Create a DIB section
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);

    if (hBitmap == NULL) {
        std::cerr << "Failed to create DIB section." << std::endl;
        return;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Get a pointer to the pixel at (x, y)
            BYTE* pPixel = (BYTE*)bits + (y * width + x) * 4;

            // Set the pixel (R, G, B, A)
            pPixel[0] = pixels[y][x].getB();
            pPixel[1] = pixels[y][x].getG();
            pPixel[2] = pixels[y][x].getR();
            pPixel[3] = pixels[y][x].getA();
        }
    }

    // Use BitBlt to draw the DIB section onto the HDC at position (x, y)
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

    BitBlt(hdc, x, y, width, height, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, hOldBitmap);
    DeleteDC(memDC);

    // Clean up the DIB section
    DeleteObject(hBitmap);
}
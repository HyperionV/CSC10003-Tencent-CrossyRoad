#include "Pixel.h"
#include <iostream>

using namespace std;

Pixel::Pixel() {
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}

Pixel::Pixel(int r, int g, int b, int a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Pixel::Pixel(const Pixel& other) {
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
}

Pixel::~Pixel() {
    // Do nothing
}

int Pixel::getR() {
    return r;
}

int Pixel::getG() {
    return g;
}

int Pixel::getB() {
    return b;
}

int Pixel::getA() {
    return a;
}

void Pixel::drawPixel(int x, int y, HDC hdc) {
    if (a == 0)
        return;
    COLORREF COLOR = RGB(r, g, b);
    SetPixel(hdc, x, y, COLOR);
}

void Pixel::print() {
    cerr << "(" << r << ", " << g << ", " << b << ", " << a << ")";
}
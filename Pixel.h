#pragma once

#include <Windows.h>
#include <winuser.h>

class Pixel
/*
 * Pixel class
 * This class is used to store the color of a pixel. Contains 4 integers: r, g, b, a.
 * Supports drawing pixel to screen and printing pixel to console for debugging.
 */
{
private:
    int r;
    int g;
    int b;
    int a;
public:
    Pixel();
    Pixel(int r, int g, int b, int a);
    Pixel(const Pixel& other);
    ~Pixel();

    int getR();
    int getG();
    int getB();
    int getA();

    void drawPixel(int x, int y, HDC hdc);
    void print();
};
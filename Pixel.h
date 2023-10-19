#pragma once

#include <Windows.h>
#include <winuser.h>

class Pixel
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

    void drawPixel(int x, int y, HDC hdc);
    void print();
};
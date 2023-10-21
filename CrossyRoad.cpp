#include <iostream>
#include <Windows.h>
#include <winuser.h>
#include <cmath>
#include <time.h>
#include <chrono>
#include <thread>
#include "Texture.h"
#include "Sprite.h"

#define _WIN32_WINNT 0x0500

using namespace std;

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main() {

	HWND console = GetConsoleWindow();

	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, 0, 0, 1280, 960, TRUE);

	//Fixed console size
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	//Hide scrollbar
	ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);

	//Hide cursor
	ShowConsoleCursor(false);


	HDC hdc = GetDC(console);
	HDC hdcMem = CreateCompatibleDC(hdc);
	system("cls");

//	//Choose any color
//	COLORREF COLOR = RGB(255, 255, 255);
//
//	//Draw pixels
//	SetPixel(hdc, 100, 100, COLOR);

	//Create a texture
    Texture texture;
    texture.readTexture("image_bin/xengu.bin");
    Texture bg;
    bg.readTexture("image_bin/lava.bin");

    //Create a sprite
    Sprite sprite(Vector2f(100, 100), texture);
    sprite.setEndPos(Vector2f(400, 400),0.3);

    Sprite bgSprite(Vector2f(0, 0), bg);
    time_t start = time(NULL);
    while (true) {
//        cout << "frame time: " << time(NULL) - start << endl;
        bgSprite.draw(hdc);
        sprite.draw(hdc);
        sprite.update();
//        cout << sprite.getPosition().x << " " << sprite.getPosition().y << endl;
        this_thread::sleep_for(chrono::milliseconds(12));
    }


	ReleaseDC(console, hdc);
	cin.ignore();
	return 0;
}
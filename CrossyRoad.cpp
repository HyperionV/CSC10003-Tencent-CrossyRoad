#include <iostream>
#include <Windows.h>
#include <winuser.h>
#include <cmath>
#include <time.h>
#include <chrono>
#include <thread>
#include "Texture.h"
#include "Sprite.h"
#include "Frame.h"

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

	//Create a texture
    Texture* xengu = new Texture("image_bin/xengu.bin");

    Frame mainFrame(Vector2i(1280, 960), Vector2i(0, 0));

    Sprite* xenguSprite[100];
    for (int i = 0; i < 100; i++) {
        xenguSprite[i] = mainFrame.addSprite(*xengu, Vector2f(i*10, 0));
        xenguSprite[i]->setEndPos(Vector2f(1280 + i*10, 960), 0.4);
    }


    clock_t start = clock();
    for (int i = 0; i < 100; i++) {
        mainFrame.update();
        mainFrame.draw(hdc);
    }
    clock_t end = clock();
    double fps = 100.0 / ((double)(end - start) / CLOCKS_PER_SEC);
    cout << "FPS: " << fps << endl;

	ReleaseDC(console, hdc);
	cin.ignore();
	return 0;
}
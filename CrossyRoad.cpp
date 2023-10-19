#include <iostream>
#include <Windows.h>
#include <winuser.h>
#include <cmath>
#include <time.h>
#include "Texture.h"

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

	MoveWindow(console, r.left, r.top, 1280, 960, TRUE);

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

	Texture texture;
	texture.readTexture("image_bin/lava.bin");

    clock_t start = clock();
    texture.fastDrawTexture(0,0,hdc);
    clock_t end = clock();

    cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

	ReleaseDC(console, hdc);
	cin.ignore();
	return 0;
}
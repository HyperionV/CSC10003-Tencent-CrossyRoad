#include <iostream>
#include <Windows.h>
#include <winuser.h>
#include <cmath>
#include <chrono>
#include <thread>

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
	system("cls");

	//Choose any color
	COLORREF COLOR = RGB(255, 255, 255);

	//Draw pixels
	for (int i = 1; i <= 100; i++) {
		SetPixel(hdc, 100, 100 + i, COLOR);
		SetPixel(hdc, 101, 100 + i, COLOR);
		SetPixel(hdc, 102, 100 + i, COLOR);
		SetPixel(hdc, 103, 100 + i, COLOR);
		SetPixel(hdc, 104, 100 + i, COLOR);
		SetPixel(hdc, 105, 100 + i, COLOR);
		SetPixel(hdc, 106, 100 + i, COLOR);
		SetPixel(hdc, 107, 100 + i, COLOR);
		SetPixel(hdc, 108, 100 + i, COLOR);
		SetPixel(hdc, 109, 100 + i, COLOR);
		SetPixel(hdc, 110, 100 + i, COLOR);
		Sleep(20);
	}

	ReleaseDC(console, hdc);
	cin.ignore();
	return 0;
}
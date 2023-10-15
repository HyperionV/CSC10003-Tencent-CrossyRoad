#include <iostream>
#include <Windows.h>
#include <winuser.h>
#include <cmath>

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
	SetPixel(hdc, 100, 100, COLOR);

	ReleaseDC(console, hdc);
	cin.ignore();
	return 0;
}
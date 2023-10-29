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
#include "Entity.h"

// #define _WIN32_WINNT 0x0500

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

	MoveWindow(console, 0, 0, 1560, 1010, TRUE);

	//Fixed console size
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	//Hide scrollbar
	ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);

	//Hide cursor
	ShowConsoleCursor(false);


	HDC hdc = GetDC(console);

	Entity e1("car2_motion");
	Entity e2("street");

	Frame mainFrame(Vector2i(1560, 960), Vector2i(0,0));
	Sprite* bg = mainFrame.addSprite(*(e2.getCurrentTexture()), Vector2f(0,0));
	Sprite* car1 = mainFrame.addSprite(*(e1.getCurrentTexture()), Vector2f(-780,75));

	car1->setEndPos(Vector2f(780, 75), 1);
	bg->setEndPos(Vector2f(1560, 960), 0);
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(50));
		e1.shiftResource(car1);
		mainFrame.update();
		mainFrame.draw(hdc);
	}

	ReleaseDC(console, hdc);
	system("cls");

	cin.ignore();
	return 0;
}
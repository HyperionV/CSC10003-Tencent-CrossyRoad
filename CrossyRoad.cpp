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

	MoveWindow(console, 0, 0, 1560, 960, TRUE);

	//Fixed console size
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	//Hide scrollbar
	ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);

	//Hide cursor
	ShowConsoleCursor(false);


	HDC hdc = GetDC(console);

	Entity e1("Car2_");
	vector<double> FPS;
	// Sprite* curr;
	// e1.addResource(mainFrame);
	while (true) {
		Frame mainFrame(Vector2i(1560, 960), Vector2i(0,0));

		Sprite* curr = mainFrame.addSprite(*(e1.getCurrentTexture()), Vector2f(0,0));
		curr->setEndPos(Vector2f(1560, 960), 0);
		e1.shiftResource();
		mainFrame.update();
		mainFrame.draw(hdc);
		// mainFrame.~Frame();
	}

	ReleaseDC(console, hdc);
	system("cls");
	for (int i = 0; i < 30; i++) {
		cout << "Run #" << i+1 << ": " << FPS[i] << " fps" << endl;
	}
	cin.ignore();
	return 0;
}
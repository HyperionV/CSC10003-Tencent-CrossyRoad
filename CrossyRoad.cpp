#pragma comment(lib, "winmm.lib")

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
#include <conio.h>
#include "Lane.h"
#include "Player.h"
#include "Screen.h"

// #define _WIN32_WINNT 0x0500


#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100

using namespace std;

Frame mainFrame(Vector2i(1280, 760), Vector2i(0,0));
Entity e1("car1_motion");


void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

Screen* Screen::instancePtr = nullptr;
int main() {

	HWND console = GetConsoleWindow();

	RECT r;
	GetWindowRect(console, &r); 
	
	// Size 1280 - 760
	MoveWindow(console, 0, 0, 1280, 760, TRUE);

	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
	ShowConsoleCursor(false);


	HDC hdc = GetDC(console);

	Entity bg1("street");
	Entity _char("up");	
	Screen* game = Screen::getInstance(&mainFrame, &hdc);
	game->startGame();

	Sprite* bg = mainFrame.addSprite(*(bg1.getCurrentTexture()), Vector2f(0,0));
	bg->setEndPos(Vector2f(1280, 720), 0);
	// Lane l1(1, e1, 1);

	Player _p(_char, mainFrame);
	while (true) {
		// this_thread::sleep_for(50ms);
		_p.animatePlayer();
		if (_kbhit()) {
			int curr = _getch();
			int step{2};
			Vector2f currPos = _p.getCurrentPos();
			switch(curr) {
				case KEY_LEFT:
					_p.setPosition(currPos.x - 40, currPos.y, 'a');
					break;
				case KEY_RIGHT:
					_p.setPosition(currPos.x+40, currPos.y, 'd');
					break;
				case KEY_DOWN:
					_p.setPosition(currPos.x, currPos.y, 's');
					break;
				case KEY_UP:
					_p.setPosition(currPos.x, currPos.y, 'w');
					break;
				case 'q':
					if (game->screenPause()) return 0;
					break;
				default:
					//cout << "Invalid key pressed" << endl;
					//system("pause");
					break;
			}
		}
		mainFrame.update();
		mainFrame.draw(hdc);
	}

	ReleaseDC(console, hdc);
	system("cls");

	cin.ignore();
	return 0;
}
#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <Windows.h>
#include <winuser.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <thread>
#include <time.h>
#include <conio.h>
#include "Texture.h"
#include "Sprite.h"
#include "Frame.h"
#include "Entity.h"
#include "Supportive.h"
#include "Lane.h"
#include "Player.h"
#include "Screen.h"
#include "Audio.h"
#include "Text.h"
#include "TrafficLight.h"
#include "Map.h"

// #define _WIN32_WINNT 0x0500


#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100

using namespace std;

Frame mainFrame(Vector2i(1280, 760), Vector2i(0,0));


void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

Screen* Screen::instancePtr = nullptr;
vector<Entity> Text::numeric;
vector<Entity> Text::alphabet;
vector<Entity> TrafficLight::lightTexture;
int main(int argc, char* argv[]) {
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
	Text::INIT();
	TrafficLight::INIT();

	int diff = 50;
	Entity carEntity("car4_motion");
	Entity revCarEntity("car4_motion");
	revCarEntity.flipHorizontal();
	Entity coin("blueSlime_run");
	vector<Lane> mapLane;
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 1) {
			Lane cur1 = Lane(&mainFrame, i, carEntity, diff);
			cur1.addItem("Slime", coin, cur1.getStart());
			mapLane.push_back(cur1);
		}
		else {
			Lane cur2 = Lane(&mainFrame, i, revCarEntity, diff);
			cur2.addItem("Slime", coin, cur2.getStart());
			mapLane.push_back(cur2);
		}
	}
	Map playMap(hdc, &mainFrame, diff, mapLane);
	playMap.drawMap();

	ReleaseDC(console, hdc);
	system("cls");

	cin.ignore();
	return 0;
}
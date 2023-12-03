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
//#include "Item.h"
//#include "Texture.h"
//#include "Sprite.h"
//#include "Frame.h"
//#include "Entity.h"
//#include "Supportive.h"
//#include "Lane.h"
//#include "Player.h"
//#include "Screen.h"
//#include "Audio.h"
//#include "Text.h"
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
vector<vector<int>> Lane::lanePos;
vector<vector<int>> Player::lanePos;
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
	Lane::INIT();
	Player::INIT();

	int diff = 90;
	ChessMap playMap(hdc, &mainFrame, diff);
	playMap.drawMap();

	ReleaseDC(console, hdc);
	system("cls");

	cin.ignore();
	return 0;
}
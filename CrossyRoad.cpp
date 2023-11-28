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

//    Texture *test = new Texture("image_bin/street.bin");

//	Entity bg1("street");
//	Entity _char("up");
//
//	Sprite* bg = mainFrame.addSprite(*(bg1.getCurrentTexture()), Vector2f(0, 0));
//	bg->setEndPos(Vector2f(1480, 960), 0);

//	Screen* game = Screen::getInstance(&mainFrame, &hdc);
//	game->startGame();
	int diff = 50;
	Entity carEntity("car4_motion");
	Entity coin("blueSlime_run");
	vector<Lane> mapLane;
	for (int i = 0; i < 10; i++) {
		Lane cur = Lane(&mainFrame, i, carEntity, diff);
		cur.addItem("Slime", coin, cur.getStart());
		mapLane.push_back(cur);
	}
	Map playMap(hdc, &mainFrame, diff, mapLane);
	playMap.drawMap();

	ReleaseDC(console, hdc);
	system("cls");

	cin.ignore();
	return 0;
}
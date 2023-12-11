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

#include "Screen.h"
#include "Map.h"
#include "Game.h"
#include "TextBox.h"

// #define _WIN32_WINNT 0x0500


#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100

using namespace std;

Frame mainFrame(Vector2i(1280, 760), Vector2i(0,0));
HWND console = GetConsoleWindow();
HDC hdc = GetDC(console);



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
vector<vector<int>> Lane::itemLanePos;
vector<vector<int>> Player::lanePos;

void InitResource() {
	Text::INIT();
	TrafficLight::INIT();
	Lane::INIT();
	Player::INIT();
	Screen::getInstance(&mainFrame, &hdc);
}


int main(int argc, char* argv[]) {
	RECT r;
	GetWindowRect(console, &r); 
	
	// Size 1280 - 760
	MoveWindow(console, 0, 0, 1280, 760, TRUE);

	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
	ShowConsoleCursor(false);


	HDC hdc = GetDC(console);
	//int diff = 50;
	//Screen* screen = Screen::getInstance(&mainFrame, &hdc);
	//screen->startGame();
	//ChessMap playMap(hdc, &mainFrame, diff, screen);
	//playMap.drawMap();

	int diff = 1000;
	Game g(mainFrame, hdc, diff, STREET_MAP);
	cout << g.startGame() << endl;

//	TextBox myTextBox;
//	myTextBox.addTextBoxSprite(&mainFrame);
//	myTextBox.setCursorSize(2, 35);
	//while (true) {
//		myTextBox.TextBoxControl();
//		myTextBox.drawTextBox(&mainFrame);
//		mainFrame.update();
//		mainFrame.draw(hdc);
//		string cur = myTextBox.getEnteredText();
	//}

	//Game g(mainFrame, hdc, diff, 0);
	//cout << g.startGame() << endl;
	system("pause");
	ReleaseDC(console, hdc);
	system("cls");

	return 0;
}
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

// #define _WIN32_WINNT 0x0500

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

void spawnCar1() {
	while (true) {
		int _seed = rand();
		srand(rand()*7+13);
		int rd = rand();
		this_thread::sleep_for(chrono::milliseconds(100)); 
		if (rd % 30 < 3) {
			Sprite* new_car1 = mainFrame.addSprite(*e1.getCurrentTexture(), Vector2f(-132, 143));
			new_car1->setEndPos(Vector2f(1280, 143), 5);
			this_thread::sleep_for(chrono::seconds(3));
		}
	}
}

void spawnCar2() {
	while (true) {
		int _seed = rand();
		srand(rand()*13+7);
		int rd = rand();
		this_thread::sleep_for(chrono::milliseconds(100)); 
		if (rd % 30 < 3) {
			Sprite* new_car1 = mainFrame.addSprite(*e1.getCurrentTexture(), Vector2f(-132, 183));
			new_car1->setEndPos(Vector2f(1280, 183), 5);
			this_thread::sleep_for(chrono::seconds(3));
		}
	}
}

void spawnCar3() {
	while (true) {
		int _seed = rand();
		srand(rand()*7+37);
		int rd = rand();
		this_thread::sleep_for(chrono::milliseconds(100)); 
		if (rd % 30 < 3) {
			Sprite* new_car1 = mainFrame.addSprite(*e1.getCurrentTexture(), Vector2f(-132, 252));
			new_car1->setEndPos(Vector2f(1280, 252), 5);
			this_thread::sleep_for(chrono::seconds(3));
		}
	}
}

void spawnCar4() {
	while (true) {
		int _seed = rand();
		srand(rand()*13+31);
		int rd = rand();
		this_thread::sleep_for(chrono::milliseconds(100)); 
		if (rd % 30 < 3) {
			Sprite* new_car1 = mainFrame.addSprite(*e1.getCurrentTexture(), Vector2f(-132, 292));
			new_car1->setEndPos(Vector2f(1280, 292), 5);
			this_thread::sleep_for(chrono::seconds(3));
		}
	}
}

void spawnCar5() {
	while (true) {
		int _seed = rand();
		srand(rand()*7+29);
		int rd = rand();
		this_thread::sleep_for(chrono::milliseconds(100)); 
		if (rd % 30 < 3) {
			Sprite* new_car1 = mainFrame.addSprite(*e1.getCurrentTexture(), Vector2f(-132, 355));
			new_car1->setEndPos(Vector2f(1280, 355), 5);
			this_thread::sleep_for(chrono::seconds(3));
		}
	}
}

void spawnCar6() {
	while (true) {
		int _seed = rand();
		srand(rand()*13+23);
		int rd = rand();
		this_thread::sleep_for(chrono::milliseconds(100)); 
		if (rd % 30 < 3) {
			Sprite* new_car1 = mainFrame.addSprite(*e1.getCurrentTexture(), Vector2f(-132, 395));
			new_car1->setEndPos(Vector2f(1280, 395), 5);
			this_thread::sleep_for(chrono::seconds(3));
		}
	}
}

void spawnCar7() {
	while (true) {
		int _seed = rand();
		srand(rand()*7+19);
		int rd = rand();
		this_thread::sleep_for(chrono::milliseconds(100)); 
		if (rd % 30 < 3) {
			Sprite* new_car1 = mainFrame.addSprite(*e1.getCurrentTexture(), Vector2f(-132, 465));
			new_car1->setEndPos(Vector2f(1280, 465), 5);
			this_thread::sleep_for(chrono::seconds(3));
		}
	}
}

void spawnCar8() {
	while (true) {
		int _seed = rand();
		srand(rand()*13+17);
		int rd = rand();
		this_thread::sleep_for(chrono::milliseconds(100)); 
		if (rd % 30 < 3) {
			Sprite* new_car1 = mainFrame.addSprite(*e1.getCurrentTexture(), Vector2f(-132, 505));
			new_car1->setEndPos(Vector2f(1280, 505), 5);
			this_thread::sleep_for(chrono::seconds(3));
		}
	}
}

void spawnCar9() {
	while (true) {
		int _seed = rand();
		srand(rand()*7+7);
		int rd = rand();
		this_thread::sleep_for(chrono::milliseconds(100)); 
		if (rd % 30 < 3) {
			Sprite* new_car1 = mainFrame.addSprite(*e1.getCurrentTexture(), Vector2f(-132, 575));
			new_car1->setEndPos(Vector2f(1280, 575), 5);
			this_thread::sleep_for(chrono::seconds(3));
		}
	}
}

void spawnCar10() {
	while (true) {
		int _seed = rand();
		srand(rand()*13+13);
		int rd = rand();
		this_thread::sleep_for(chrono::milliseconds(100)); 
		if (rd % 30 < 3) {
			Sprite* new_car1 = mainFrame.addSprite(*e1.getCurrentTexture(), Vector2f(-132, 615));
			new_car1->setEndPos(Vector2f(1280, 615), 5);
			this_thread::sleep_for(chrono::seconds(3));
		}
	}
}

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

	Entity e2("car4_motion");

	Entity bg1("street");

	Sprite* bg = mainFrame.addSprite(*(bg1.getCurrentTexture()), Vector2f(0,0));
	// Sprite* car1 = mainFrame.addSprite(*(e1.getCurrentTexture()), Vector2f(-132, 143));
	// Sprite* car2 = mainFrame.addSprite(*(e1.getCurrentTexture()), Vector2f(1280 + 132,183));
	// Sprite* car3 = mainFrame.addSprite(*(e2.getCurrentTexture()), Vector2f(- 132,252));
	// Sprite* car4 = mainFrame.addSprite(*(e2.getCurrentTexture()), Vector2f(1280 + 132,292));
	// Sprite* car5 = mainFrame.addSprite(*(e1.getCurrentTexture()), Vector2f(-132, 355));
	// Sprite* car6 = mainFrame.addSprite(*(e1.getCurrentTexture()), Vector2f(1280 + 132,395));
	// Sprite* car7 = mainFrame.addSprite(*(e2.getCurrentTexture()), Vector2f(-132,463));
	// Sprite* car8 = mainFrame.addSprite(*(e2.getCurrentTexture()), Vector2f(1280 + 132,503));
	// Sprite* car9 = mainFrame.addSprite(*(e1.getCurrentTexture()), Vector2f(-132, 570));
	// Sprite* car10 = mainFrame.addSprite(*(e1.getCurrentTexture()), Vector2f(1280 + 132,613));
	bg->setEndPos(Vector2f(1480, 960), 0);
	// car1->setEndPos(Vector2f(1280+132, 143), 0.5);
	// car2->setEndPos(Vector2f(-132, 188), 0.5);
	// car3->setEndPos(Vector2f(1280+132, 252), 0.5);
	// car4->setEndPos(Vector2f(-132, 292), 0.5);
	// car5->setEndPos(Vector2f(1280+132, 355), 0.5);
	// car6->setEndPos(Vector2f(-132, 395), 0.5);
	// car7->setEndPos(Vector2f(1280+132, 465), 0.5);
	// car8->setEndPos(Vector2f(-132, 505), 0.5);
	// car9->setEndPos(Vector2f(1280+132, 575), 0.5);
	// car10->setEndPos(Vector2f(-132, 615), 0.5);
	thread _newThread(spawnCar1);
	thread _lane2(spawnCar2);
	thread _lane3(spawnCar3);
	thread _lane4(spawnCar4);
	thread _lane5(spawnCar5);
	thread _lane6(spawnCar6);
	thread _lane7(spawnCar7);
	thread _lane8(spawnCar8);
	thread _lane9(spawnCar9);
	thread _lane10(spawnCar10);

	while (true) {

		// this_thread::sleep_for(chrono::milliseconds(20));
		e1.shiftResource();
		
		// car2->setTexture(e1.getCurrentTexture());
		// car5->setTexture(e1.getCurrentTexture());
		// car6->setTexture(e1.getCurrentTexture());
		// car9->setTexture(e1.getCurrentTexture());
		// car10->setTexture(e1.getCurrentTexture());
		// e2.shiftResource(car3);
		// car4->setTexture(e2.getCurrentTexture());
		// car7->setTexture(e2.getCurrentTexture());
		// car8->setTexture(e2.getCurrentTexture());

		// if (_kbhit()) {
		// 	Vector2f currPos = car1->getPosition();
		// 	cout << "Current position: " << currPos.x << " " << currPos.y << endl;
		// 	this_thread::sleep_for(chrono::seconds(1));
		// 	system("cls");
		// 	char curr = getch();
		// 	int step{5};
		// 	switch(curr) {
		// 		case 'w':
		// 			currPos.y -= step;
		// 			break;
		// 		case 'a':
		// 			currPos.x -= step;
		// 			break;
		// 		case 's':
		// 			currPos.y += step;
		// 			break;
		// 		case 'd':
		// 			currPos.x += step;
		// 			break;
		// 		default:
		// 			break;
		// 	}
		// 	car1->setPosition(currPos);
		// }
		// // system("cls");
		// system("pause");
		mainFrame.update();
		mainFrame.draw(hdc);
	}

	ReleaseDC(console, hdc);
	system("cls");

	cin.ignore();
	return 0;
}
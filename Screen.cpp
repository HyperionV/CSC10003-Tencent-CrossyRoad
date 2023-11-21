#include "Screen.h"
Screen::Screen() {
	this->mainFrame = nullptr;
}

Screen::Screen(Frame* curFrame, HDC* hdc) {

	this->isMusicOff = 0;
	this->hdc = hdc;
	this->mainFrame = curFrame;
	backGround = new Sprite;
	for (int i = 1; i <= 5; i++) { // 0 -> 4
		resources.push_back(Entity("menu"+to_string(i), true));
	}
	for (int i = 1; i <= 6; i++) { // 5 -> 10
		resources.push_back(Entity("option"+to_string(i), true));
	}
	for (int i = 1; i <= 6; i++) { // 11 -> 16
		resources.push_back(Entity("pause"+to_string(i), true));
	}
	for (int i = 1; i <= 3; i++) { // 17 -> 19
		resources.push_back(Entity("load_game"+to_string(i), true));
	}
	resources.push_back(Entity("leader_board", true));

	
}

void Screen::startGame() {
	int vertical = 0, horizon = 0;
	backGround->setTexture(resources[0].getCurrentTexture());
	mainFrame->draw(*hdc, backGround);
	while (true) {
		// this_thread::sleep_for(50ms);
		if (_kbhit()) {
			int curr = getch();
			switch (curr) {
			case KEY_LEFT:
				if (vertical < 3)
					break;
				if (horizon == 1) {
					horizon = 0;
					changeTexture(3);
				}
				break;
			case KEY_RIGHT:
				if (vertical < 3)
					break;
				if (horizon == 0) {
					horizon = 1;
					changeTexture(4);
				}
				break;
			case KEY_DOWN:
				switch (vertical) {
				case 0:
					changeTexture(1);
					vertical++;
					break;
				case 1:
					changeTexture(2);
					vertical++;
					break;
				case 2:
					changeTexture(3);
					vertical++;
					break;
				default:
					break;
				}
				break;
			case KEY_UP:
				switch (vertical) {
				case 1:
					changeTexture(0);
					vertical--;
					break;
				case 2:
					changeTexture(1);
					vertical--;
					break;
				case 3:
					horizon = 0;
					changeTexture(2);
					vertical--;
				default:
					break;
				}
				break;
				case '\r':
					switch (vertical) {
						case 0:
							this->screenPlay();
							vertical = 0, horizon = 0;
							break;
						case 1:
							this->screenOption();
							vertical = 0, horizon = 0;
							break;
						case 2:
							return;
						//case 3:
						//	if (horizon == 0)
						//		this->screenAbout();
						//	else this->screenHelp();
						default:
							break;
					}
			default:
				break;
			}
		}
		mainFrame->draw(*hdc, this->backGround);
	}
}
//static void screenGame();
bool Screen::screenPause() {
	int vertical = 0;
	changeTexture(11 + 3*isMusicOff);
	mainFrame->draw(*this->hdc, this->backGround);
	while (true) {
		// this_thread::sleep_for(50ms);
		if (_kbhit()) {
			int curr = getch();
			switch (curr) {
			case KEY_DOWN:
				switch (vertical) {
				case 0:
					vertical++;
					changeTexture(12 + 3 * isMusicOff);
					break;
				case 1:
					vertical++;
					changeTexture(13 + 3 * isMusicOff);
					break;
				default:
					break;
				}
				break;
			case KEY_UP:
				switch (vertical) {
				case 1:
					vertical--;
					changeTexture(11 + 3 * isMusicOff);
					break;
				case 2:
					vertical--;
					changeTexture(12 + 3 * isMusicOff);
					break;
				default:
					break;
				}
				break;
			case '\r':
				switch (vertical) {
				case 0:
					return 0;
				case 1:
					if (isMusicOff) isMusicOff = 0;
					else isMusicOff = 1;
					changeTexture(12 + 3 * isMusicOff);
					break;
				case 2:
					return 1;
				default:
					break;
				}
			default:
				break;
			}
		}
		mainFrame->draw(*hdc, this->backGround);
	}
	return 1;
}
void Screen::screenOption() {
	int vertical = 0;
	changeTexture(5 + 3 * isMusicOff);
	mainFrame->draw(*this->hdc, this->backGround);
	while (true) {
		// this_thread::sleep_for(50ms);
		if (_kbhit()) {
			int curr = getch();
			switch (curr) {
			case KEY_DOWN:
				switch (vertical) {
				case 0:
					vertical++;
					changeTexture(6 + 3 * isMusicOff);
					break;
				case 1:
					vertical++;
					changeTexture(7 + 3 * isMusicOff);
					break;
				default:
					break;
				}
				break;
			case KEY_UP:
				switch (vertical) {
				case 1:
					vertical--;
					changeTexture(5 + 3 * isMusicOff);
					break;
				case 2:
					vertical--;
					changeTexture(6 + 3 * isMusicOff);
					break;
				default:
					break;
				}
				break;
			case '\r':
				switch (vertical) {
				case 0:
					changeTexture(20);
					break;
				case 1:
					if (isMusicOff) isMusicOff = 0;
					else isMusicOff = 1;
					changeTexture(6 + 3 * isMusicOff);
					break;
				case 2:
					changeTexture(0);
					return;
				default:
					break;
				}
			default:
				break;
			}
		}
		mainFrame->draw(*hdc, this->backGround);
	}
	return;
}
void Screen::screenPlay() {
	int vertical = 0;
	changeTexture(17);
	mainFrame->draw(*this->hdc, this->backGround);
	while (true) {
		// this_thread::sleep_for(50ms);
		if (_kbhit()) {
			int curr = getch();
			switch (curr) {
			case KEY_DOWN:
				switch (vertical) {
				case 0:
					vertical++;
					changeTexture(18);
					break;
				case 1:
					vertical++;
					changeTexture(19);
					break;
				default:
					break;
				}
				break;
			case KEY_UP:
				switch (vertical) {
				case 1:
					vertical--;
					changeTexture(17);
					break;
				case 2:
					vertical--;
					changeTexture(18);
					break;
				default:
					break;
				}
				break;
			case '\r':
				switch (vertical) {
				case 2:
					changeTexture(0);
					return;
				default:
					break;
				}
			default:
				break;
			}
		}
		mainFrame->draw(*hdc, this->backGround);
	}
	return;
}

void Screen::changeTexture(const int& idx) {
	backGround->setTexture(resources[idx].getCurrentTexture());
}
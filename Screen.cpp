#include "Screen.h"
string sound[] = { "on_click", "coin1" };
Screen::Screen() {
	this->mainFrame = nullptr;
}

Screen::Screen(Frame* curFrame, HDC* hdc) {

	this->isMusicOff = 0;
	this->hdc = hdc;
	this->mainFrame = curFrame;
	this->music = new Audio;
	for (int i = 1; i <= 5; i++) {
		Entity menu("menu" + to_string(i));
		Sprite* menu1 = new Sprite(Vector2f(0, 0), &(*(menu.getCurrentTexture())));
		this->menu.push_back(menu1);
	}

	for (int i = 1; i <= 6; i++) {
		Entity option("option" + to_string(i));
		Sprite* option1 = new Sprite(Vector2f(0, 0), &(*(option.getCurrentTexture())));
		this->option.push_back(option1);
	}

	for (int i = 1; i <= 6; i++) {
		Entity pause("pause" + to_string(i));
		Sprite* pause1 = new Sprite(Vector2f(0, 0), &(*(pause.getCurrentTexture())));
		this->pause.push_back(pause1);
	}

	for (int i = 1; i <= 3; i++) {
		Entity loadGame("load_game" + to_string(i));
		Sprite* loadGame1 = new Sprite(Vector2f(0, 0), &(*(loadGame.getCurrentTexture())));
		this->loadGame.push_back(loadGame1);
	}

	
	Entity leaderBoard("leader_board");
	this->leaderBoard = new Sprite(Vector2f(0, 0), &(*(leaderBoard.getCurrentTexture())));

	
}

void Screen::startGame() {
	int vertical = 0, horizon = 0;
	this->backGround = menu[0];
	this->music->Play("gameSound.wav", 1, 1);
	mainFrame->draw(*this->hdc, this->backGround);
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
					this->backGround = menu[3];
				}
				break;
			case KEY_RIGHT:
				if (vertical < 3)
					break;
				if (horizon == 0) {
					horizon = 1;
					this->backGround = menu[4];
				}
				break;
			case KEY_DOWN:
				switch (vertical) {
				case 0:
					vertical++;
					this->backGround = menu[1];
					break;
				case 1:
					vertical++;
					this->backGround = menu[2];
					break;
				case 2:
					vertical++;
					this->backGround = menu[3];
					break;
				default:
					break;
				}
				break;
			case KEY_UP:
				switch (vertical) {
				case 1:
					vertical--;
					this->backGround = menu[0];
					break;
				case 2:
					vertical--;
					this->backGround = menu[1];
					break;
				case 3:
					vertical--;
					horizon = 0;
					this->backGround = menu[2];
				default:
					break;
				}
				break;
				case '\r':
					switch (vertical) {
						case 0:
							playSound(0);
							this->screenPlay();
							vertical = 0, horizon = 0;
							break;
						case 1:
							playSound(0);
							this->screenOption();
							vertical = 0, horizon = 0;
							break;
						case 2:
							playSound(0);
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
bool Screen::screenPause() {
	int vertical = 0;
	this->backGround = pause[0 + 3 * isMusicOff];
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
					this->backGround = pause[1 + 3 * isMusicOff];
					break;
				case 1:
					vertical++;
					this->backGround = pause[2 + 3 * isMusicOff];
					break;
				default:
					break;
				}
				break;
			case KEY_UP:
				switch (vertical) {
				case 1:
					vertical--;
					this->backGround = pause[0 + 3 * isMusicOff];
					break;
				case 2:
					vertical--;
					this->backGround = pause[1 + 3 * isMusicOff];
					break;
				default:
					break;
				}
				break;
			case '\r':
				switch (vertical) {
				case 0:
					playSound(0);
					return 0;
				case 1:
					playSound(0);
					setMusic();
					this->backGround = pause[1 + 3 * isMusicOff];
					break;
				case 2:
					playSound(0);
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
	this->backGround = option[0 + 3 * isMusicOff];
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
					this->backGround = option[1 + 3 * isMusicOff];
					break;
				case 1:
					vertical++;
					this->backGround = option[2 + 3 * isMusicOff];
					break;
				default:
					break;
				}
				break;
			case KEY_UP:
				switch (vertical) {
				case 1:
					vertical--;
					this->backGround = option[0 + 3 * isMusicOff];
					break;
				case 2:
					vertical--;
					this->backGround = option[1 + 3 * isMusicOff];
					break;
				default:
					break;
				}
				break;
			case '\r':
				switch (vertical) {
				case 0:
					playSound(0);
					this->backGround = leaderBoard;
					break;
				case 1:
					playSound(0);
					setMusic();
					this->backGround = option[1 + 3 * isMusicOff];
					break;
				case 2:
					playSound(0);
					this->backGround = menu[0];
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
	this->backGround = loadGame[0];
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
					this->backGround = loadGame[1];
					break;
				case 1:
					vertical++;
					this->backGround = loadGame[2];
					break;
				default:
					break;
				}
				break;
			case KEY_UP:
				switch (vertical) {
				case 1:
					vertical--;
					this->backGround = loadGame[0];
					break;
				case 2:
					vertical--;
					this->backGround = loadGame[1];
					break;
				default:
					break;
				}
				break;
			case '\r':
				switch (vertical) {
				case 2:
					playSound(0);
					this->backGround = menu[0];
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

void Screen::setMusic() {
	if (!isMusicOff) {
		isMusicOff = 1;
		music->Stop();
	}
	else {
		isMusicOff = 0;
		music->Play("gameSound.wav", 1 ,1);
	}
	return;
}

void Screen::playSound(const int& type) {
	PlaySound(0, 0, 0);
	PlaySound(TEXT("on_click.wav"), nullptr, SND_FILENAME | SND_ASYNC);
	return;
}
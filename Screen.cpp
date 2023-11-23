#include "Screen.h"
#include "Player.h"
Screen::Screen() {
	this->mainFrame = nullptr;
}

Screen::Screen(Frame* curFrame, HDC* hdc) {

	this->isMusicOff = 0;
	this->hdc = hdc;
	this->mainFrame = curFrame;
	this->backGround = new Sprite;
	 this->music = new Audio;
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
	resources.push_back(Entity("street", true));
	for (int i = 0; i < 10; i++) {
		resources.push_back(Entity("score_" + to_string(i), true));
	}
	for (int i = 1; i <= 5; i++) {
		Sprite* scoreSprite = new Sprite(Vector2f(900 + 60 * i, 40), resources[22].getCurrentTexture());
		score.push_back(scoreSprite);
	}
}

void Screen::startGame() {
	int vertical = 0, horizon = 0;
	backGround->setTexture(resources[0].getCurrentTexture());
	mainFrame->draw(*hdc, backGround);
	music->Play("gameSound.wav", 1, 1);
	Entity e1("car1_motion");
	Lane l1(mainFrame, 1, e1, 20);
	thread t1 = l1.spawnThread();
	while (true) {

		// this_thread::sleep_for(50ms);
		if (_kbhit()) {
			int curr = _getch();
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
							playSound(ON_CLICK);
							this->screenPlay();
							changeTexture(0);
							vertical = 0, horizon = 0;
							break;
						case 1:
							playSound(ON_CLICK);
							this->screenOption();
							vertical = 0, horizon = 0;
							break;
						case 2:
							playSound(ON_CLICK);
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
	changeTexture(11 + 3*isMusicOff);
	mainFrame->draw(*this->hdc, this->backGround);
	while (true) {
		// this_thread::sleep_for(50ms);
		if (_kbhit()) {
			int curr = _getch();
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
					playSound(0);
					changeTexture(21);
					return 0;
				case 1:
					setMusic();
					changeTexture(12 + 3 * isMusicOff);
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
	changeTexture(5 + 3 * isMusicOff);
	mainFrame->draw(*this->hdc, this->backGround);
	while (true) {
		// this_thread::sleep_for(50ms);
		if (_kbhit()) {
			int curr = _getch();
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
					playSound(ON_CLICK);
					break;
				case 1:
					playSound(ON_CLICK);
					setMusic();
					changeTexture(6 + 3 * isMusicOff);
					break;
				case 2:
					playSound(ON_CLICK);
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
			int curr = _getch();
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
				case 0:
					playSound(ON_CLICK);
					crossyRoad();
					changeTexture(0);
					return;
				case 2:
					playSound(ON_CLICK);
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

string updateScore(int& score, int bonus) {
	score += bonus;
	if (score > 99999)
		score = 99999;
	string res = to_string(score);
	while (res.length() < 5) {
		res = "0" + res;
	}
	return res;
 }

 void Screen::updateScoreSprite(int& score, int bonus) {
	 string Score = updateScore(score, bonus);
	 for (int i = 4; i > -1; i--) {
		 int idx = Score[i] - '0' + 22;
		 this->score[i]->setTexture(resources[idx].getCurrentTexture());
	 }
	 return;
 }

 void Screen::crossyRoad() {
	 int score = 0;
	 Entity _char("up");
	 Entity tl("trafficLight");
	 changeTexture(21);
	 mainFrame->addSprite(this->backGround);
	 mainFrame->addSprite(tl.getCurrentTexture(), Vector2f(0, 0));
	 for (int i = 0; i < 5; i++) {
		 mainFrame->addSprite(this->score[i]);
	 }
	 //mainFrame->update();
	 //mainFrame->draw(*this->hdc);
	 // Lane l1(1, e1, 1);

	 Player _p(_char, *mainFrame);
	 while (true) {
		 //this_thread::sleep_for(100ms);
		 _p.animatePlayer();
		 if (_kbhit()) {
			 int curr = _getch();
			 int step{ 2 };
			 Vector2f currPos = _p.getCurrentPos();
			 switch (curr) {
			 case KEY_LEFT:
				 _p.setPosition(currPos.x - 40, currPos.y, 'a');
				 break;
			 case KEY_RIGHT:
				 _p.setPosition(currPos.x + 40, currPos.y, 'd');
				 break;
			 case KEY_DOWN:
				 _p.setPosition(currPos.x, currPos.y, 's');
				 break;
			 case KEY_UP:
				 this->updateScoreSprite(score, 1);
				 _p.setPosition(currPos.x, currPos.y, 'w');
				 break;
			 case 'q':
				 playSound(ON_CLICK);
				 if (screenPause()) {
					 //mainFrame->removeAllSprite();
					 return;
				 }
				 break;
			 default:
				 //cout << "Invalid key pressed" << endl;
				 //system("pause");
				 break;
			 }
		 }
		 mainFrame->update();
		 mainFrame->draw(*hdc);
	 }
 }
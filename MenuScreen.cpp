#pragma warning(disable:4244)
#include "MenuScreen.h"
#include "Player.h"
#include "Text.h"
#include "TrafficLight.h"
MenuScreen::MenuScreen() {
	this->mainFrame = nullptr;
}

MenuScreen::MenuScreen(Frame* curFrame, HDC* hdc) {

	this->isMusicOff = 0;
	this->hdc = hdc;
	this->mainFrame = curFrame;
	this->backGround = new Sprite;
	this->music = new Audio;
	string folder = "UI/";
	for (int i = 1; i <= 5; i++) { // 0 -> 4
		resources.push_back(Entity(folder + "menu"+to_string(i), true));
	}
	for (int i = 1; i <= 6; i++) { // 5 -> 10
		resources.push_back(Entity(folder + "option"+to_string(i), true));
	}
	for (int i = 1; i <= 6; i++) { // 11 -> 16
		resources.push_back(Entity(folder + "pause"+to_string(i), true));
	}
	for (int i = 1; i <= 3; i++) { // 17 -> 19
		resources.push_back(Entity(folder + "load_game"+to_string(i), true));
	}
	for (int i = 0; i < 10; i++) { //20 -> 29
		resources.push_back(Entity(folder + "score_" + to_string(i), true));
	}
	for (int i = 1; i <= 3; i++) { //30 -> 32
		resources.push_back(Entity(folder + "choose_map" + to_string(i), true));
	}
	resources.push_back(Entity(folder + "leader_board", true)); // 33
	for (int i = 1; i <= 5; i++) { // 34 -> 38
		Sprite* scoreSprite = new Sprite(Vector2f(900 + 60 * i, 40), resources[22].getCurrentTexture());
		score.push_back(scoreSprite);
	}
}

int MenuScreen::startGame() {
	changeTexture(0);
	int vertical = 0, horizon = 0;
	backGround->setTexture(resources[0].getCurrentTexture());
	mainFrame->draw(*hdc, backGround);
	music->Play("gameSound.wav", 1, 1);
	//Lane l1(mainFrame, 1, e1, 20);
	//thread t1 = l1.spawnThread();
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
                            map = QUIT_GAME;
							return map;
						//case 3:
						//	if (horizon == 0)
						//		this->screenAbout();
						//	else this->screenHelp();
						default:
							break;
					}
                    return map;
			default:
				break;
			}
		}
		mainFrame->draw(*hdc, this->backGround);
	}
}
bool MenuScreen::screenPause() {
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
void MenuScreen::screenOption() {
	int vertical = 0;
	changeTexture(5 + 3 * isMusicOff);
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
					playSound(ON_CLICK);
					screenLeaderboard();
					changeTexture(5 + 3 * isMusicOff);
					break;
				case 1:
					playSound(ON_CLICK);
					setMusic();
					changeTexture(6 + 3 * isMusicOff);
					break;
				case 2:
					playSound(ON_CLICK);
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
void MenuScreen::screenPlay() {
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
					screenChooseMap();
					changeTexture(17);
					break;
				case 1 : 
					playSound(ON_CLICK);
                    map = LOAD_MAP;
					screenPause();
					return;
				case 2:
					playSound(ON_CLICK);
					return;
				default:
					break;
				}
                return;
			default:
				break;
			}
		}
		mainFrame->draw(*hdc, this->backGround);
	}
	return;
}

void MenuScreen::changeTexture(const int& idx) {
	backGround->setTexture(resources[idx].getCurrentTexture());
}
 void MenuScreen::setMusic() {
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

 void MenuScreen::playSound(const int& type) {
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

 void MenuScreen::updateScoreSprite(const int& score) {
	 string Score = to_string(score);
	 while (Score.length() < 5) Score = "0" + Score;
	 for (int i = 4; i > -1; i--) {
		 int idx = Score[i] - '0' + 20;
		 this->score[i]->setTexture(resources[idx].getCurrentTexture());
	 }
	 return;
 }

 //void MenuScreen::crossyRoad() {
	// int score = 0;
	// Entity _char("up");


	// changeTexture(21);
	// mainFrame->addSprite(this->backGround);
	// for (int i = 0; i < 5; i++) {
	//	 mainFrame->addSprite(this->score[i]);
	// }

	// Player _p(*mainFrame, STREET_MAP);
	// while (true) {
	//	 //this_thread::sleep_for(100ms);
	//	 _p.animatePlayer();
	//	 if (_kbhit()) {
	//		 int curr = _getch();
	//		 int step{ 2 };
	//		 Vector2f currPos = _p.getCurrentPos();
	//		 switch (curr) {
	//		 case KEY_LEFT:
	//			 _p.setPosition(currPos.x - 40, currPos.y, 'a');
	//			 break;
	//		 case KEY_RIGHT:
	//			 _p.setPosition(currPos.x + 40, currPos.y, 'd');
	//			 break;
	//		 case KEY_DOWN:
	//			 _p.setPosition(currPos.x, currPos.y, 's');
	//			 break;
	//		 case KEY_UP:
	//			 this->updateScoreSprite(score);
	//			 _p.setPosition(currPos.x, currPos.y, 'w');
	//			 break;
	//		 case 'q':
	//			 playSound(ON_CLICK);
	//			 if (screenPause()) {
	//				 //mainFrame->removeAllSprite();
	//				 return;
	//			 }
	//			 break;
	//		 default:
	//			 //cout << "Invalid key pressed" << endl;
	//			 //system("pause");
	//			 break;
	//		 }
	//	 }
	//	 //trafficControl(traff);
	//	 mainFrame->update();
	//	 mainFrame->draw(*hdc);
	// }
 //}


 void MenuScreen::screenLeaderboard() {
	 //vector<leaderBoardInfo> info = readLeaderBoardFromFile("leaderBoardInfo.bin");
	 changeTexture(33);
	 leaderBoardInfo A("ngobang", "99999", "27/11/2023");
	 mainFrame->addSprite(this->backGround);
	 Text a(A.getName());
	 Text b(A.getScore());
	 Text c(A.getDate());
	 a.writeText(getScoreBoardCoord(a.getLength(), NAME_COL), ROW2_OFFSET, mainFrame);
	 b.writeText(getScoreBoardCoord(b.getLength(), SCORE_COL), ROW2_OFFSET, mainFrame);
	 c.writeText(getScoreBoardCoord(c.getLength(), DATE_COL), ROW2_OFFSET, mainFrame);
	 
	 while (true) {
		 //this_thread::sleep_for(100ms);
		 if (_kbhit()) {
			 int curr = _getch();
			 int step{ 2 };
			 switch (curr) {
			 case 'q':
				 playSound(ON_CLICK);
				 mainFrame->removeAllSprite();
				 return;
			 default:
				 //cout << "Invalid key pressed" << endl;
				 //system("pause");
				 break;
			 }
		 }
		 mainFrame->draw(*hdc);
	 }

	 return;

 }

 int MenuScreen::screenChooseMap() {
	 int horizon = 0;
	 changeTexture(30);
	 mainFrame->draw(*this->hdc, this->backGround);
	 while (true) {
		 // this_thread::sleep_for(50ms);
		 if (_kbhit()) {
			 int curr = _getch();
			 switch (curr) {
			 case KEY_RIGHT:
				 switch (horizon) {
				 case 0:
					 horizon++;
					 changeTexture(31);
					 break;
				 case 1:
					 horizon++;
					 changeTexture(32);
					 break;
				 default : 
					 break;
				 }
				 break;
			 case KEY_LEFT:
				 switch (horizon) {
				 case 1:
					 horizon--;
					 changeTexture(30);
					 break;
				 case 2:
					 horizon--;
					 changeTexture(31);
					 break;
				 default:
					 break;
				 }
				 break;
			 case '\r':
				 switch (horizon) {
				 case 0:
					 playSound(ON_CLICK);
                     map = CHESS_MAP;
					 return CHESS_MAP;
				 case 1:
					 playSound(ON_CLICK);
                     map = STREET_MAP;
					 return STREET_MAP;
				 case 2:
					 playSound(ON_CLICK);
                     map = TRAIN_MAP;
					 return TRAIN_MAP;
				 default:
					 break;
				 }
			 default:
				 break;
			 }
		 }
		 mainFrame->draw(*hdc, this->backGround);
	 }
	 return -1;

 }

 void MenuScreen::addScore() {
	 for (int i = 0; i < 5; i++) {
		 mainFrame->addSprite(this->score[i]);
	 }
	 return;
 }
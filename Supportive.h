#pragma once
#include <iostream>
#include <chrono>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Text.h"
#include "Screen.h"

using namespace std;

class leaderBoardInfo {
private:
	string name;
	string score;
	string date;
public:
	leaderBoardInfo(const string& name, const string& score, const string& date) {
		this->name = name;
		this->score = score;
		this->date = date;
	}
	string getName() const {
		return name;
	}

	string getScore() const {
		return score;
	}
	string getDate() const {
		return date;
	}
};

string return_current_time_and_date();

string getExePath(string x);

vector<leaderBoardInfo>readLeaderBoardFromFile(const string& filename);

int getScoreBoardCoord(const int& len, const int& col);

void writeLeaderboardToFile(const vector<leaderBoardInfo>& leaderboard, const string& filename);

int getRandomInRange(int a, int b);

void playSound(const string& file);
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_DEPRECATE
#include "Supportive.h"



string return_current_time_and_date()
{
	auto now = chrono::system_clock::now();
	auto in_time_t = chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << put_time(std::localtime(&in_time_t), "%d/%m/%Y");

	string owo = ss.str();
	return ss.str();
}

string getExePath(string x) // removes fileName from path i.e "D:\path\to\exe\sample.exe" changes it into "D:\path\to\exe"
{
	std::string f = x;
	return f.substr(0, f.find_last_of("\\/"));
}

vector<leaderBoardInfo> readLeaderBoardFromFile(const string& filename) {
	vector<leaderBoardInfo> leaderboard;

	ifstream fin(filename, ios::in);
	if (!fin) {
		cerr << "Error opening file for reading: " << filename << endl;
		return leaderboard;
	}

	// Read the vector size
	size_t size;
	fin >> size;

	// Read each leaderBoardInfo object
	for (size_t i = 0; i < size; ++i) {
		char name[100], score[100], date[100];
		fin >> name >> score >> date;
		leaderboard.emplace_back(name, score, date);
	}

	fin.close();
	return leaderboard;
}

void writeLeaderboardToFile(const vector<leaderBoardInfo>& leaderboard, const string& filename) {
	ofstream fout(filename, ios::out);
	if (!fout) {
		cerr << "Error opening file for writing: " << filename << endl;
		return;
	}

	// Write the vector size (number of objects) first
	size_t size = leaderboard.size();
    fout << size << endl;

	// Write each leaderBoardInfo object
	for (const auto& entry : leaderboard) {
		fout << entry.getName() << " " << entry.getScore() << " " << entry.getDate() << endl;
	}

	fout.close();
}

int getScoreBoardCoord(const int& len, const int& col) {
	switch (col) {
	case 1 :
		return (NAME_COLUMN_WIDTH - len) / 2 + NAME_COLUMN_OFFSET;
		break;
	case 2 :
		return (SCORE_COLUMN_WIDTH - len) / 2 + SCORE_COLUMN_OFFSET;
		break;
	case 3 : 
		return (DATE_COLUMN_WIDTH - len) / 2 + DATE_COLUMN_OFFSET;
		break;
	default :
		return 0;
		break;
	}

	return 0;
}

int getRandomInRange(int a, int b) {
	// Seed the random number generator with the current time
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Calculate the range span
	int rangeSpan = b - a + 1;

	// Generate a random number within the range
	int randomNum = std::rand() % rangeSpan + a;

	return randomNum;
}
void playSound(const string& file) {
	PlaySound(0, 0, 0);
	PlaySound(TEXT(file.c_str()), nullptr, SND_FILENAME | SND_ASYNC);
	return;
}
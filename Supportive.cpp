#include "Supportive.h"

string return_current_time_and_date()
{
	auto now = chrono::system_clock::now();
	auto in_time_t = chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();
}

string getExePath(string x) // removes fileName from path i.e "D:\path\to\exe\sample.exe" changes it into "D:\path\to\exe"
{
	std::string f = x;
	return f.substr(0, f.find_last_of("\\/"));
}

vector<leaderBoardInfo> readLeaderBoardFromFile(const string& filename) {
	vector<leaderBoardInfo> leaderboard;

	ifstream fin(filename, ios::in | ios::binary);
	if (!fin) {
		cerr << "Error opening file for reading: " << filename << endl;
		return leaderboard;
	}

	// Read the vector size
	size_t size;
	fin.read(reinterpret_cast<char*>(&size), sizeof(size));

	// Read each leaderBoardInfo object
	for (size_t i = 0; i < size; ++i) {
		char name[100], score[100], date[100];
		fin.read(name, sizeof(name));
		fin.read(score, sizeof(score));
		fin.read(date, sizeof(date));
		leaderboard.emplace_back(name, score, date);
	}

	fin.close();
	return leaderboard;
}

void writeLeaderboardToFile(const vector<leaderBoardInfo>& leaderboard, const string& filename) {
	ofstream fout(filename, ios::out | ios::binary);
	if (!fout) {
		cerr << "Error opening file for writing: " << filename << endl;
		return;
	}

	// Write the vector size (number of objects) first
	size_t size = leaderboard.size();
	fout.write(reinterpret_cast<char*>(&size), sizeof(size));

	// Write each leaderBoardInfo object
	for (const auto& entry : leaderboard) {
		fout.write(entry.getName().c_str(), entry.getName().size() + 1); // Include null terminator
		fout.write(entry.getScore().c_str(), entry.getScore().size() + 1);
		fout.write(entry.getDate().c_str(), entry.getDate().size() + 1);
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

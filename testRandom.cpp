#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void test_main() {
    while (true) {
        this_thread::sleep_for(chrono::seconds(1));
        srand(rand());
        int rd = rand()+1000;
        cout << "\nNew Test -------------------" << endl;
        cout << rd << endl;
        cout << rd % 15 << " " << rd %5 << endl;
        cout << rd % 12 << " " << rd % 3 << " " << rd % 4 << endl;
        cout << rd % 20 << endl;
    }
}
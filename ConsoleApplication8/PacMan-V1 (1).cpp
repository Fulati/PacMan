#include <iostream>
#include "windows.h"
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <thread> //this_thread::sleep_for
#include <chrono> //chrono::seconds

using namespace std;

BOOL gotoxy(const WORD x, const WORD y) {
    COORD xy;
    xy.X = x;
    xy.Y = y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

BOOL gotojk(const WORD j, const WORD k) {
    COORD xy;
    xy.X = j;
    xy.Y = k;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}


void gameSetup(vector <string>& map, char pacMan, char pacMan2, char food, char border) {
    string line;
    string userInput;

    //  Select things char
    char input = ' ';

    cout << "Select Map size: " << endl;
    cout << "\t 1. Small" << endl;
    cout << "\t 2. Medium" << endl;
    cout << "\t 3. Large" << endl;
    cout << "\t 4. Xtra Large" << endl;
    cin >> userInput;

    system("cls");


    ifstream infile("map" + userInput + ".txt");
    if (infile) {
        while (getline(infile, line)) {
            for (unsigned int i = 0; i < line.length(); i++) {
                if (line.at(i) == '@') {
                    line.at(i) = pacMan;
                }
                if (line.at(i) == '%') {
                    line.at(i) = pacMan2;
                }
                if (line.at(i) == 'x') {
                    line.at(i) = food;
                }
                if (line.at(i) == '#') {
                    line.at(i) = border;
                }
            }
            map.push_back(line);
        }
        infile.close();
    }
    else {
        cout << "COULD NOT OPEN FILE" << endl;
    }
}

//// Timer
//void timer(int& sec) {
//    while (sec > 0) {
//        this_thread::sleep_for(chrono::seconds(1));
//        sec--;
//    }
//    cout << "Timer: 00::00::" << sec << endl;
//    cout << endl;
//}

void updateScreen(vector <string>& map, int& score, int& score2, int& sec) {

    for (unsigned int i = 0; i < map.size(); i++) {
        cout << map.at(i) << endl;
    }
    cout << "score is " << score << endl;
    cout << "score2 is " << score2 << endl;
}


bool moveTo(vector <string>& map, int x, int y, int& score, char food, char border, char player) {
    if (map.at(y).at(x) == food) {
        score++;
    }
    return (map.at(y).at(x) != border && map.at(y).at(x) != player);
}

bool moveTo2(vector <string>& map, int x, int y, int& score2, char food, char border, char player) {
    if (map.at(y).at(x) == food) {
        score2++;
    }
    return (map.at(y).at(x) != border && map.at(y).at(x) != player);
}


int main(){

    int score = 0;
    int score2 = 0;
    int x = 1;
    int y = 1;
    int j = 2;
    int k = 2;
    bool game_running = true;
    int sec = 5;

    vector <string> map;

    char input;


    // Select Pac1
    cout << "Select Your PacMan (any single character): " << endl;
    cin >> input;
    cout << "Your PacMan is " << input << endl;
    cout << endl;
    const char pacMan = input;

    // Select Pac2
    cout << "Select Your PacMan2 (any single character): " << endl;
    cin >> input;
    cout << "Your PacMan2 is " << input << endl;
    cout << endl;
    const char pacMan2 = input;

    // Select Food
    cout << "Select Your Food (any single character): " << endl;
    cin >> input;
    cout << "Your Food is " << input << endl;
    cout << endl;
    const char food = input;

    // Select Border
    cout << "Select Your Border (any single character): " << endl;
    cin >> input;
    cout << "Your Border is " << input << endl;
    cout << endl;
    const char border = input;


    gameSetup(map, pacMan, pacMan2, food, border);

    do {
        gotoxy(0, 0);
        gotojk(0, 0);

        updateScreen(map, score, score2, sec);  //prints vector on the screen

        system("pause>nul");

        if (GetAsyncKeyState(VK_DOWN) && moveTo(map, x, y + 1, score, food, border, pacMan2)) {
            map.at(y).at(x) = ' ';
            y += 1;
            map.at(y).at(x) = pacMan;
        }


        if (GetAsyncKeyState(VK_UP) && moveTo(map, x, y - 1, score, food, border, pacMan2)) {
            map.at(y).at(x) = ' ';
            y -= 1;
            map.at(y).at(x) = pacMan;

        }

        if (GetAsyncKeyState(VK_RIGHT) && moveTo(map, x + 1, y, score, food, border, pacMan2)) {
            map.at(y).at(x) = ' ';
            x += 1;
            map.at(y).at(x) = pacMan;

        }

        if (GetAsyncKeyState(VK_LEFT) && moveTo(map, x - 1, y, score, food, border, pacMan2)) {
            map.at(y).at(x) = ' ';
            x -= 1;
            map.at(y).at(x) = pacMan;

        }


        // P2 ///////////////////////////////////////////////////////////////////////
        if (GetAsyncKeyState(VK_NUMPAD5) && moveTo(map, j, k + 1, score2, food, border, pacMan)) {
            map.at(k).at(j) = ' ';
            k += 1;
            map.at(k).at(j) = pacMan2;

        }


        if (GetAsyncKeyState(VK_NUMPAD8) && moveTo(map, j, k - 1, score2, food, border, pacMan)) {
            map.at(k).at(j) = ' ';
            k -= 1;
            map.at(k).at(j) = pacMan2;

        }

        if (GetAsyncKeyState(VK_NUMPAD6) && moveTo(map, j+ 1, k, score2, food, border, pacMan)) {
            map.at(k).at(j) = ' ';
            j += 1;
            map.at(k).at(j) = pacMan2;

        }

        if (GetAsyncKeyState(VK_NUMPAD4) && moveTo(map, j - 1, k, score2, food, border, pacMan)) {
            map.at(k).at(j) = ' ';
            j -= 1;
            map.at(k).at(j) = pacMan2;

        }

        if (GetAsyncKeyState(VK_ESCAPE) || sec == 0) {
            game_running = false;
        }
        } while (game_running == true);
        system("cls");
        cout << "Congrats";

        return 0;
   }
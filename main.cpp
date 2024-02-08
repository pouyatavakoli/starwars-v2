// Pouya Tavakoli
// 40212358011

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// struct for saving game data
struct GameData
{
    int ship_x;
    // ship is always in the lowest row so  y = 0
    int score = 0;
    int heal = 3;
};

// struct for saving enemy details
struct Enemy
{
    string type;
    int size;
    int heal;
    int count;
    // Add position here
};

// main menu
void mainMenu(int);
// function to save enemies data in file
void saveEnemies(const vector<Enemy> &enemies);
void gameSaver();
// TODO : struct for saving spaceship types details if needed
// TODO : function to draw the map
// TODO : function to move the spaceship
// TODO : function to shoot
// TODO : scoring system
// TODO : function to refresh game environment
// TODO : menu (pause resume change spaceship etc)
// TODO : saving game data in file (delete the file when game ends)
// TODO : win / lose logic

int main()
{
    return 0;
}

// TODO : make specific menu for each situation or change menu options according to situation
void mainMenu(int input)
{
    cout << "choose what you want to do" << endl
         << "1 - start new game" << endl
         << "2 - resume game" << endl
         << "3 - change game difficulty" << endl
         << "4 - change winning score" << endl;

    if (input == 1)
    {
        // restart game
    }
}

void saveEnemies(const vector<Enemy> &enemies)
{
    ofstream enemyInfo("enemy.txt");
    if (enemyInfo.is_open()) {
        // iterate over vector of enemies and save them into file
        for (const auto& enemy : enemies) {
            enemyInfo << enemy.type << ": size = " << enemy.size << ", heal = " << enemy.heal << ", count = " << enemy.count << endl;
        }
        enemyInfo.close();
    } else {
        cerr << "Error opening enemy.txt" << endl;
    }
}

void gameSaver(){
    // save saveEnemies and other info
}
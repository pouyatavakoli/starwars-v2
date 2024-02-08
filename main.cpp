// Pouya Tavakoli
// 40212358011

#include <iostream>
using namespace std;

// struct for saving game data
struct GameData
{
    int ship_x;
    // ship is always in the lowest row so  y = 0
    int score = 0;
    int heal = 3;
};

// struct for defining enemy type details
// enemy size in map will be size*size

struct Dart
{
    int size = 1;
    int heal = 1;
};

struct Striker
{
    int size = 2;
    int heal = 2;
};

struct Wraith
{
    int size = 3;
    int heal = 4;
};

struct Banshee
{
    int size = 4;
    int heal = 6;
};

// main menu
void mainMenu(int);
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
         << "1 - start new game"         << endl
         << "2 - resume game"            << endl
         << "3 - change game difficulty" << endl
         << "4 - change winning score"   << endl ;

    
    if (input == 1)
    {
        // restart game
    }
}


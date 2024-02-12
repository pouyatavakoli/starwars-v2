// Pouya Tavakoli  40212358011
// Pouya Omidi     40212358002

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <conio.h>
#define up_key 72
#define down_key 80
#define left_key 75
#define right_key 77

using namespace std;

// struct for saving game data
struct GameData
{
    int level = 1;
    int point = 0;
    int killCounter = 0 ;
};

// struct for saving enemy details
struct Dart
{
    int size = 1 * 1;
    int heal = 1;
    int count = 0;
    int D_coordinate[1][2];
    // Add color here
    // Add position here
};

struct Striker
{
    int size = 2 * 2;
    int heal = 2;
    int count = 0;
    int S_coordinate[4][2];
    // Add color here
    // Add position here
};

struct Wraith
{
    int size = 3 * 3;
    int heal = 4;
    int count = 0;
    int W_coordinate[9][2];
    // Add color here
    // Add position here
};

struct Banshee
{
    int size = 4 * 4;
    int heal = 6;
    int count = 0;
    int B_coordinate[16][4];
    // Add color here
    // Add position here
};

// struct for saving spaceship types details
struct SpaceShip
{
    // The shape can be any character, or even the first letter of a player's name
    int ship_y;
    char shape = '@';
    int power;
    int heal = 3;
};

struct Bullet
{
    int coordinate[1][2];
};

// main menu
void mainMenu(int);
// function to save enemies data in file
void saveEnemies();
// checking enemy coordinates.
void coordinates(const int n, vector<Dart> &dart, vector<Striker> &striker,
                 vector<Wraith> &wraith, vector<Banshee> &banshee);
// function to save all game data
void gameSaver();
// function to initialize the game
void initializeGame();
// function to end the game
void endGame();
// function to draw the map
void printMap(int n, SpaceShip &spaceship, vector<Dart> &dart, vector<Striker> &striker,
              vector<Wraith> &wraith, vector<Banshee> &banshee, vector<Bullet> &bullets);

void move_right(SpaceShip &spaceship, int n);
void move_left(SpaceShip &spaceship, int n);

void new_bullet_maker(vector<Bullet> &bullets, SpaceShip &spaceship, int n);

void move_bullets(vector<Bullet> &bullets);
void move_enemies_down(vector<Dart> &dart, vector<Striker> &striker,
                       vector<Wraith> &wraith, vector<Banshee> &banshee);

void enemy_damage_check(GameData &gameData,
                        vector<Dart> &dart, vector<Striker> &striker,
                        vector<Wraith> &wraith, vector<Banshee> &banshee,
                        vector<Bullet> &bullets, int n);
void ship_heal_check(int n, vector<Dart> &dart, vector<Striker> &striker,
                     vector<Wraith> &wraith, vector<Banshee> &banshee, SpaceShip &spaceship);
bool shipStatus(SpaceShip &spaceShip);

/*bool bullet_hit_enemy(vector<Dart> &dart, vector<Striker> &striker,
                      vector<Wraith> &wraith, vector<Banshee> &banshee,
                      vector<Bullet> &bullets);*/

/*
function to check damage of each enemy and remove it if  enemy heal is 0 ,
creat new bullet
move bullets up and
move enemies down
*/
void refresh(GameData &gameData, vector<Dart> &dart, vector<Striker> &striker,
             vector<Wraith> &wraith, vector<Banshee> &banshee,
             vector<Bullet> &bullets, SpaceShip &spaceship, int n);

// TODO : saving game data in file (delete the file when game ends)
// TODO : win / lose logic

int main()
{
    int n;
    int enemyCount;
    SpaceShip spaceship;
    vector<Bullet> bullets;
    vector<Dart> darts;
    vector<Striker> strikers;
    vector<Wraith> wraiths;
    vector<Banshee> banshees;
    GameData gameData;

    cout << "n : ";
    cin >> n;
    cout << "how many enemies you want to kill: ";
    cin >> enemyCount;
    if (n % 2 == 0)
    {
        n++;
        cout << "you entered even number. "
             << "for better visuals map is generated for n = " << n << endl;
        spaceship.ship_y = n / 2;
    }

    else

        spaceship.ship_y = n / 2;

    coordinates(n, darts, strikers, wraiths, banshees);
    printMap(n, spaceship, darts, strikers, wraiths, banshees, bullets);

    int move;
    while (shipStatus(spaceship) && gameData.killCounter != enemyCount)
    {
        cout << "press arrow keys to move left or right : " << endl;
        cout << "point : " << gameData.point << endl;
        cout << "heal  : " << spaceship.heal;
        move = getch();
        if (move == left_key)
        {
            move_left(spaceship, n);
            refresh(gameData, darts, strikers, wraiths, banshees, bullets, spaceship, n);
        }
        else if (move == right_key)
        {
            move_right(spaceship, n);
            refresh(gameData, darts, strikers, wraiths, banshees, bullets, spaceship, n);
        }
        else if (move == up_key)
        {
            refresh(gameData, darts, strikers, wraiths, banshees, bullets, spaceship, n);
        }
        else if (move == 'q' || move == 'Q')
        {
            system("cls") ;
            cout << "you quitted the game";
            return 0;
        }

        printMap(n, spaceship, darts, strikers, wraiths, banshees, bullets);
    }
    system("cls");
    if(gameData.killCounter == enemyCount)
        cout << "we have a winner";
        return 0;
    cout << "looooser";
    return 0;
}

// menu that can be different in each situation
void mainMenu(int situation)
{
    cout << "Choose what you want to do" << endl;

    switch (situation)
    {
    case 1:
        // Start new game menu
        cout << "1 - start new game" << endl
             << "2 - change game mode" << endl
             << "3 - quit game" << endl;
        break;
    case 2:
        // Resume game menu
        cout << "1 - resume game" << endl
             << "2 - save game" << endl
             << "3 - quit game" << endl;
        break;
    case 3:
        // Change game settings menu
        cout << "1 - change game difficulty" << endl
             << "2 - change winning score" << endl;
        break;
    default:
        cout << "Invalid situation" << endl;
        break;
    }
}

void printMap(int n,
              SpaceShip &spaceship,
              vector<Dart> &dart, vector<Striker> &striker,
              vector<Wraith> &wraith,
              vector<Banshee> &banshee, vector<Bullet> &bullets)
{
    system("cls");
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << " ---";

        cout << endl;

        if (i <= n - 1)
        {
            for (int k = 0; k <= n; k++)
            {

                bool isSpaceShip = false;
                bool isEnemy = false;
                bool isBullet = false;
                for (int s = 0; s < n - 1; s++)
                {
                    if (i == n - 1 && k == spaceship.ship_y)
                        isSpaceShip = true;
                }

                for (const auto &enemy : dart)
                {
                    if (i == enemy.D_coordinate[0][0] && k == enemy.D_coordinate[0][1])
                        isEnemy = true;
                }

                for (const auto &enemy : striker)
                {
                    for (int s = 0; s < 4; s++)
                    {
                        if (i == enemy.S_coordinate[s][0] && k == enemy.S_coordinate[s][1])
                            isEnemy = true;
                    }
                }

                for (const auto &enemy : wraith)
                {
                    for (int w = 0; w < 9; w++)
                    {
                        if (i == enemy.W_coordinate[w][0] && k == enemy.W_coordinate[w][1])
                            isEnemy = true;
                    }
                }

                for (const auto &enemy : banshee)
                {
                    for (int b = 0; b < 16; b++)
                    {
                        if (i == enemy.B_coordinate[b][0] && k == enemy.B_coordinate[b][1])
                            isEnemy = true;
                    }
                }

                // Check if the current position is occupied by a bullet
                for (const auto &bullet : bullets)
                {
                    if (i == bullet.coordinate[0][0] && k == bullet.coordinate[0][1])
                        isBullet = true;
                }

                if (isSpaceShip)
                {
                    cout << "| " << spaceship.shape << " ";
                }
                else if (isEnemy)
                {
                    cout << "| * "; // The symbol for Enemy
                }
                else if (isBullet)
                {
                    cout << "| ^ "; // The symbol for Bullet
                }
                else
                {
                    cout << "|   ";
                }
            }
        }

        cout << endl;
    }
}

void coordinates(int n, vector<Dart> &dart, vector<Striker> &striker,
                 vector<Wraith> &wraith, vector<Banshee> &banshee)
{
    // pick a random enemy type between 4 types
    srand(time(0));
    int enemyType = rand() % 4;
    // Depending on the random number, spawn the corresponding enemy
    if (enemyType == 0)
    {
        Dart newDart;

        newDart.D_coordinate[0][0] = 0;
        newDart.D_coordinate[0][1] = rand() % n;

        dart.push_back(newDart);
    }
    else if (enemyType == 1)
    {
        Striker newStriker;

        int y = rand() % (n - 1);
        for (int i = 0; i < 4; i++)
        {
            newStriker.S_coordinate[i][0] = i / 2;
            newStriker.S_coordinate[i][1] = y + (i % 2);
        }

        striker.push_back(newStriker);
    }
    else if (enemyType == 2)
    {
        Wraith newWraith;

        int y = rand() % (n - 2);
        for (int i = 0; i < 9; i++)
        {
            newWraith.W_coordinate[i][0] = i / 3;
            newWraith.W_coordinate[i][1] = y + (i % 3);
        }

        wraith.push_back(newWraith);
    }
    else if (enemyType == 3)
    {
        Banshee newBanshee;

        int y = rand() % (n - 3);
        for (int i = 0; i < 16; i++)
        {
            newBanshee.B_coordinate[i][0] = i / 4;
            newBanshee.B_coordinate[i][1] = y + (i % 4);
        }

        banshee.push_back(newBanshee);
    }
}

void move_left(SpaceShip &spaceship, int n)
{
    if (spaceship.ship_y > 0)
    {
        spaceship.ship_y--;
    }
}

void move_right(SpaceShip &spaceship, int n)
{
    if (spaceship.ship_y < n - 1)
    {
        spaceship.ship_y++;
    }
}

void move_enemies_down(vector<Dart> &dart, vector<Striker> &striker,
                       vector<Wraith> &wraith, vector<Banshee> &banshee)
{
    for (auto &enemy : dart)
    {
        enemy.D_coordinate[0][0]++;
    }

    for (auto &enemy : striker)
    {
        for (int s = 0; s < 4; s++)
        {
            enemy.S_coordinate[s][0]++;
        }
    }

    for (auto &enemy : wraith)
    {
        for (int w = 0; w < 9; w++)
        {
            enemy.W_coordinate[w][0]++;
        }
    }

    for (auto &enemy : banshee)
    {
        for (int b = 0; b < 16; b++)
        {
            enemy.B_coordinate[b][0]++;
        }
    }
}

void new_bullet_maker(vector<Bullet> &bullets, SpaceShip &spaceship, int n)
{
    Bullet newBullet;
    newBullet.coordinate[0][0] = n - 1;            // Spaceship's row position
    newBullet.coordinate[0][1] = spaceship.ship_y; // Spaceship's column position
    bullets.push_back(newBullet);
}

void move_bullets(vector<Bullet> &bullets)
{
    for (auto &bullet : bullets)
    {
        bullet.coordinate[0][0]--;
    }
}
void enemy_heal_check(vector<Dart> &dart, vector<Striker> &striker,
                      vector<Wraith> &wraith, vector<Banshee> &banshee,
                      vector<Bullet> &bullets)
{
    for (auto &bullet : bullets)
    {
        for (auto &enemy : dart)
        {
            if (enemy.D_coordinate[0][0] == bullet.coordinate[0][0] && enemy.D_coordinate[0][1] == bullet.coordinate[0][1])
            {
                enemy.heal--;
            }
        }

        for (auto &enemy : striker)
        {
            for (int s = 0; s < 4; s++)
            {
                if (enemy.S_coordinate[s][0] == bullet.coordinate[0][0] && enemy.S_coordinate[s][1] == bullet.coordinate[0][1])
                {
                    enemy.heal--;
                }
            }
        }

        for (auto &enemy : wraith)
        {
            for (int w = 0; w < 9; w++)
            {
                if (enemy.W_coordinate[w][0] == bullet.coordinate[0][0] && enemy.W_coordinate[w][1] == bullet.coordinate[0][1])
                {
                    enemy.heal--;
                }
            }
        }

        for (auto &enemy : banshee)
        {
            for (int b = 0; b < 16; b++)
            {
                if (enemy.B_coordinate[b][0] == bullet.coordinate[0][0] && enemy.B_coordinate[b][1] == bullet.coordinate[0][1])
                {
                    enemy.heal--;
                }
            }
        }
    }
}

void enemy_damage_check(GameData &gameData,
                        vector<Dart> &dart, vector<Striker> &striker,
                        vector<Wraith> &wraith, vector<Banshee> &banshee,
                        vector<Bullet> &bullets, int n)
{
    for (auto &enemy : dart)
    {
        if (enemy.heal == 0)
        {
            dart.pop_back();
            gameData.point++;
            gameData.killCounter++;
            coordinates(n, dart, striker, wraith, banshee);
        }
    }
    for (auto &enemy : striker)
    {
        if (enemy.heal == 0)
        {
            striker.pop_back();
            gameData.point++;
            gameData.killCounter++;
            coordinates(n, dart, striker, wraith, banshee);
        }
    }
    for (auto &enemy : wraith)
    {
        if (enemy.heal == 0)
        {
            wraith.pop_back();
            gameData.point++;
            gameData.killCounter++;
            coordinates(n, dart, striker, wraith, banshee);
        }
    }
    for (auto &enemy : banshee)
    {
        if (enemy.heal == 0)
        {
            banshee.pop_back();
            gameData.point++;
            gameData.killCounter++;
            coordinates(n, dart, striker, wraith, banshee);
        }
    }
}
void ship_heal_check(int n, vector<Dart> &dart, vector<Striker> &striker,
                     vector<Wraith> &wraith, vector<Banshee> &banshee, SpaceShip &spaceship)
{
    for (auto &enemy : dart)
    {
        if (enemy.D_coordinate[0][0] == n && enemy.D_coordinate[0][1] == spaceship.ship_y)
        {
            spaceship.heal--;
        }
    }

    for (auto &enemy : striker)
    {
        for (int s = 0; s < 4; s++)
        {
            if (enemy.S_coordinate[s][0] == n && enemy.S_coordinate[s][1] == spaceship.ship_y)
            {
                spaceship.heal--;
            }
        }
    }

    for (auto &enemy : wraith)
    {
        for (int w = 0; w < 9; w++)
        {
            if (enemy.W_coordinate[w][0] == n && enemy.W_coordinate[w][1] == spaceship.ship_y)
            {
                spaceship.heal--;
            }
        }
    }

    for (auto &enemy : banshee)
    {
        for (int b = 0; b < 16; b++)
        {
            if (enemy.B_coordinate[b][0] == n && enemy.B_coordinate[b][1] == spaceship.ship_y)
            {
                spaceship.heal--;
            }
        }
    }
}

bool shipStatus(SpaceShip &spaceShip)
{
    if (spaceShip.heal == 0)
        return false; // ship is dead
    return true;
};

void refresh(GameData &gameData, vector<Dart> &dart, vector<Striker> &striker,
             vector<Wraith> &wraith, vector<Banshee> &banshee,
             vector<Bullet> &bullets, SpaceShip &spaceship, int n)
{
    ship_heal_check(n, dart, striker, wraith, banshee, spaceship);
    enemy_heal_check(dart, striker, wraith, banshee, bullets);
    enemy_damage_check(gameData, dart, striker, wraith, banshee, bullets, n);
    new_bullet_maker(bullets, spaceship, n);
    move_enemies_down(dart, striker, wraith, banshee);
    move_bullets(bullets);
}

/*
bool bullet_hit_enemy(vector<Dart> &dart, vector<Striker> &striker,
                      vector<Wraith> &wraith, vector<Banshee> &banshee,
                      vector<Bullet> &bullets)
{
    for (auto &bullet : bullets)
    {
        for (auto &enemy : dart)
        {
            if (enemy.D_coordinate[0][0] == bullet.coordinate[0][0] && enemy.D_coordinate[0][1] == bullet.coordinate[0][1])
            {
                return true;
            }
        }

        for (auto &enemy : striker)
        {
            for (int s = 0; s < 4; s++)
            {
                if (enemy.S_coordinate[s][0] == bullet.coordinate[0][0] && enemy.S_coordinate[s][1] == bullet.coordinate[0][1])
                {
                    return true;
                }
            }
        }

        for (auto &enemy : wraith)
        {
            for (int w = 0; w < 9; w++)
            {
                if (enemy.W_coordinate[w][0] == bullet.coordinate[0][0] && enemy.W_coordinate[w][1] == bullet.coordinate[0][1])
                {
                    return true;
                }
            }
        }

        for (auto &enemy : banshee)
        {
            for (int b = 0; b < 16; b++)
            {
                if (enemy.B_coordinate[b][0] == bullet.coordinate[0][0] && enemy.B_coordinate[b][1] == bullet.coordinate[0][1])
                {
                    return true;
                }
            }
        }

    }
    return false;
}
*/
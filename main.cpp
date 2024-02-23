// Pouya Tavakoli  40212358011
// Pouya Omidi     40212358002

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <conio.h>
#include <algorithm>

#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define CYAN "\033[36m"
#define RESET_TEXT "\033[0m"
#define BRIGHT_WHITE "\033[97m"
#define WHITE "\033[37m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_CYAN "\u001b[36;1m"
#define BRIGHT_RED "\u001b[31;1m"
#define BRIGHT_YELLOW "\u001b[33;1m"
#define BRIGHT_MAGENTA "\u001b[35;1m"
#define BRIGHT_BLACK "\u001b[30;1m"

using namespace std;

// struct for saving game data
struct GameData
{
    int level = 1;
    int point = 0;
    int points_updater = 0;
    int killCounter = 0;
    int targetScore = 0;
    string gameResult = "undefined";
};

// struct for saving enemy details
struct Dart
{
    int size = 1 * 1;
    int heal = 1;
    int count = 0;
    int D_coordinate[1][2];
};

struct Striker
{
    int size = 2 * 2;
    int heal = 2;
    int count = 0;
    int S_coordinate[4][2];
};

struct Wraith
{
    int size = 3 * 3;
    int heal = 4;
    int count = 0;
    int W_coordinate[9][2];
};

struct Banshee
{
    int size = 4 * 4;
    int heal = 6;
    int count = 0;
    int B_coordinate[16][2];
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
int menu(int);
int startGame(int x);
// create new enemy Enemy_coordinate_maker
void Enemy_coordinate_maker(const int n, vector<Dart> &dart, vector<Striker> &striker,
                 vector<Wraith> &wraith, vector<Banshee> &banshee, GameData &gameData);
// function to save all game data
void new_bullet_maker(vector<Bullet> &bullets, SpaceShip &spaceship, int n);

// function to draw the map
void printMap(int n,
              SpaceShip &spaceship,
              vector<Dart> &dart, vector<Striker> &striker, vector<Wraith> &wraith, vector<Banshee> &banshee,
              vector<Bullet> &bullets);

void move_right(SpaceShip &spaceship, int n);
void move_left(SpaceShip &spaceship, int n);

bool bullet_outOfBound(const Bullet &bullet);

void move_bullets(vector<Bullet> &bullets);
void move_enemies_down(vector<Dart> &dart, vector<Striker> &striker,
                       vector<Wraith> &wraith, vector<Banshee> &banshee);
// for each enemy check to see if any enemy is hit by bullet
bool isHit(const Dart &enemy, const Bullet &bullet);
bool isHit(const Striker &enemy, const Bullet &bullet);
bool isHit(const Wraith &enemy, const Bullet &bullet);
bool isHit(const Banshee &enemy, const Bullet &bullet);

// checks if ship hits enemy
bool collision(int n,
               vector<Dart> &dart, vector<Striker> &striker, vector<Wraith> &wraith, vector<Banshee> &banshee,
               SpaceShip &spaceship);

// remove enemy if heal is 0 and update points
void enemy_damage_check(GameData &gameData,
                        vector<Dart> &dart, vector<Striker> &striker, vector<Wraith> &wraith, vector<Banshee> &banshee,
                        vector<Bullet> &bullets,
                        int n);

// check to see if ship is alive
bool shipStatus(SpaceShip &spaceShip);
// score based leveling system
void update_level(GameData &gameData);
// game movements and updates info
void refresh(GameData &gameData,
             vector<Dart> &dart, vector<Striker> &striker, vector<Wraith> &wraith, vector<Banshee> &banshee,
             vector<Bullet> &bullets,
             SpaceShip &spaceship, int n);

// save game to file
void gameSaver(const int n,
               const GameData &gameData,
               vector<Bullet> &bullets,
               const vector<Dart> &dart, const vector<Striker> &striker, const vector<Wraith> &wraith, const vector<Banshee> &banshee,
               const SpaceShip &spaceship);
// read game from file
int gameLoader(int &n,
               GameData &gameData,
               vector<Bullet> &bullets,
               vector<Dart> &dart, vector<Striker> &striker, vector<Wraith> &wraith, vector<Banshee> &banshee,
               SpaceShip &spaceship);

/*
 *       main function
 */
int main()
{
    menu(1);
}

// menu that can be different in each situation
int menu(int situation)
{
    system("cls");
    cout << "Choose what you want to do" << endl;

    switch (situation)
    {
    case 1: // Starting  game menu

        cout << "1 - Start new game" << endl
             << "2 - Continue previous game" << endl
             << "3 - Exit" << endl;
        char userInput;
        userInput = getch();
        if (userInput == '1')
        {
            startGame(1);
        }
        else if (userInput == '2')
        {
            startGame(2);
        }
        else if (userInput == '3')
        {
            cout << "You quitted the game" << endl;
            system("pause");
            exit(0);
        }
        else
        {
            menu(1);
        }
        break;
    case 2: // Pause game menu

        cout << "1 - Resume game" << endl
             << "2 - Quit" << endl;
        userInput = getch();
        if (userInput == '1')
        {
            // Nothing happens.
        }

        // else if (userInput == 2)
        else if (userInput == '2')
        {
            system("cls");
            menu(1);
        }
        else
        {
            menu(2);
        }
        break;

    default:
        cout << "Invalid situation" << endl;
        break;
    }
    return 0;
}

int startGame(int x)
{
    system("cls");

    int n;
    SpaceShip spaceship;
    vector<Bullet> bullets;
    vector<Dart> darts;
    vector<Striker> strikers;
    vector<Wraith> wraiths;
    vector<Banshee> banshees;
    GameData gameData;
    if (x == 1)
    {
        cout << "Size of map : ";
        cin >> n;
        while (n < 16)
        {
            system("cls");
            cout << "The size of map can't be less than 16." << endl;
            cout << "Size of map : ";
            cin >> n;
        }
        cout << "What's your target score : ";
        cin >> gameData.targetScore;
        if (n % 2 == 0)
        {
            n++;
            cout << "you entered even number. "
                 << "for better visuals map is generated for n = " << n << endl;
            spaceship.ship_y = n / 2;
            system("pause");
        }

        else

            spaceship.ship_y = n / 2;

        Enemy_coordinate_maker(n, darts, strikers, wraiths, banshees, gameData);
    }

    else if (x == 2)
    {
        int result = gameLoader(n, gameData, bullets, darts, strikers, wraiths, banshees, spaceship);

        if (result == 1)
        {
            system("cls");
            cout << GREEN_TEXT << "You have WON the last game!" << RESET_TEXT << endl;
            cout << "In order to go to main menu : ";
            system("pause");
            system("cls");
            menu(1);
        }
        else if (result == 0)
        {
            system("cls");
            cout << RED_TEXT << "You have LOST the last game!" << RESET_TEXT << endl;
            cout << "In order to go to main menu : ";
            system("pause");
            system("cls");
            menu(1);
        }
        else if (result == 2)
        {
            cout << "In order to continue : ";
            system("pause");
        }
    }

    printMap(n, spaceship, darts, strikers, wraiths, banshees, bullets);

    bool continue_game = true;
    char move;
    while (shipStatus(spaceship) && continue_game)
    {
        cout << "use 'a' to move left 'd' to move right press 'w' to shoot : " << endl
             << "press 'm' to open menu " << endl;
        cout << "Size of map : " << n << endl;
        cout << CYAN << "Level : " << gameData.level << RESET_TEXT << endl;
        cout << BRIGHT_WHITE << "point : " << WHITE << gameData.point << " / " << gameData.targetScore << RESET_TEXT << endl;
        cout << BRIGHT_GREEN << "heal  : " << GREEN_TEXT << spaceship.heal << RESET_TEXT << endl;
        move = getch();
        if (move == 'a' || move == 'A')
        {
            move_left(spaceship, n);
            refresh(gameData, darts, strikers, wraiths, banshees, bullets, spaceship, n);
        }
        else if (move == 'd' || move == 'D')
        {
            move_right(spaceship, n);
            refresh(gameData, darts, strikers, wraiths, banshees, bullets, spaceship, n);
        }
        else if (move == 'w' || move == 'W')
        {
            refresh(gameData, darts, strikers, wraiths, banshees, bullets, spaceship, n);
        }
        else if (move == 'm' || move == 'M')
        {
            system("cls");
            menu(2);
        }
        else
        {
            cout << "invalid input" << endl;
            system("pause");
        }
        system("cls");
        if (gameData.point >= gameData.targetScore)
        {
            cout << GREEN_TEXT << "we have a WINNER" << RESET_TEXT << endl;
            cout << "Do you want to continue the game ? Y / N ";
            char continue_game;
            continue_game = getch();
            if (continue_game == 'y' || continue_game == 'Y')
            {
                gameData.targetScore += 100;
                continue_game = true;
            }
            else if (continue_game == 'n' || continue_game == 'N')
            {
                continue_game = false;
                gameData.gameResult = "win";
                gameSaver(n, gameData, bullets, darts, strikers, wraiths, banshees, spaceship);
                menu(1);
            }
        }
        printMap(n, spaceship, darts, strikers, wraiths, banshees, bullets);
    }

    system("cls");
    if (shipStatus(spaceship) == false)
    {
        cout << RED_TEXT << "we have a LOOSER" << RESET_TEXT << endl;
        gameData.gameResult = "loose";
        gameSaver(n, gameData, bullets, darts, strikers, wraiths, banshees, spaceship);
        system("pause");
        menu(1);
    }
    return 0;
}

// create new enemy Enemy_coordinate_maker
void Enemy_coordinate_maker(int n, vector<Dart> &dart, vector<Striker> &striker,
                 vector<Wraith> &wraith, vector<Banshee> &banshee, GameData &gameData)
{
    // pick a random enemy type between 4 types
    srand(time(0));
    // Depending on the random number, spawn the corresponding enemy
    bool enemyExist = false;
    do
    {
        int enemyType = rand() % 4;

        if (enemyType == 0 && gameData.point <= 50)
        {
            Dart newDart;

            newDart.D_coordinate[0][0] = 0;
            newDart.D_coordinate[0][1] = rand() % n;

            dart.push_back(newDart);
            enemyExist = true;
        }
        else if (enemyType == 1 && gameData.point <= 400)
        {
            Striker newStriker;

            int y = rand() % (n - 1);
            for (int i = 0; i < 4; i++)
            {
                newStriker.S_coordinate[i][0] = i / 2;
                newStriker.S_coordinate[i][1] = y + (i % 2);
            }

            striker.push_back(newStriker);
            enemyExist = true;
        }
        else if (enemyType == 2 && gameData.point <= 1000)
        {
            Wraith newWraith;

            int y = rand() % (n - 2);
            for (int i = 0; i < 9; i++)
            {
                newWraith.W_coordinate[i][0] = i / 3;
                newWraith.W_coordinate[i][1] = y + (i % 3);
            }

            wraith.push_back(newWraith);
            enemyExist = true;
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
            enemyExist = true;
        }

    } while (!enemyExist);
}
// create new bullet
void new_bullet_maker(vector<Bullet> &bullets, SpaceShip &spaceship, int n)
{
    Bullet newBullet;
    newBullet.coordinate[0][0] = n - 1;            // Spaceship's row position
    newBullet.coordinate[0][1] = spaceship.ship_y; // Spaceship's column position
    bullets.push_back(newBullet);
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
                bool isDart = false;
                bool isStriker = false;
                bool isWraith = false;
                bool isBanshee = false;
                for (int s = 0; s < n - 1; s++)
                {
                    if (i == n - 1 && k == spaceship.ship_y)
                        isSpaceShip = true;
                }

                for (const auto &enemy : dart)
                {
                    if (i == enemy.D_coordinate[0][0] && k == enemy.D_coordinate[0][1])
                        isEnemy = true;
                    isDart = true;
                }

                for (const auto &enemy : striker)
                {
                    for (int s = 0; s < 4; s++)
                    {
                        if (i == enemy.S_coordinate[s][0] && k == enemy.S_coordinate[s][1])
                            isEnemy = true;
                        isStriker = true;
                    }
                }

                for (const auto &enemy : wraith)
                {
                    for (int w = 0; w < 9; w++)
                    {
                        if (i == enemy.W_coordinate[w][0] && k == enemy.W_coordinate[w][1])
                            isEnemy = true;
                        isWraith = true;
                    }
                }

                for (const auto &enemy : banshee)
                {
                    for (int b = 0; b < 16; b++)
                    {
                        if (i == enemy.B_coordinate[b][0] && k == enemy.B_coordinate[b][1])
                            isEnemy = true;
                        isBanshee = true;
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
                    cout << "| " << GREEN_TEXT << spaceship.shape << RESET_TEXT << " ";
                }
                else if (isEnemy)
                {
                    if (isDart == true)
                        cout << "| " << BRIGHT_CYAN << "* " << RESET_TEXT;

                    else if (isStriker == true)
                    {
                        cout << "| " << BRIGHT_YELLOW << "* " << RESET_TEXT;
                    }
                    else if (isWraith == true)
                    {
                        cout << "| " << BRIGHT_RED << "* " << RESET_TEXT;
                    }
                    else if (isBanshee == true)
                    {
                        cout << "| " << BRIGHT_MAGENTA << "* " << RESET_TEXT;
                    }
                }
                else if (isBullet)
                {
                    cout << "| " << BRIGHT_BLACK << "^ " << RESET_TEXT; // The symbol for Bullet
                }
                else
                {
                    cout << BRIGHT_WHITE << "|   " << RESET_TEXT;
                }
            }
        }

        cout << endl;
    }
}

/*
 *     ship movement part
 */
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

/*
 *     enemy movement part
 */

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

/*
 *     map boundary
 */

// checks of bullet is reached top of the map
bool bullet_outOfBound(const Bullet &bullet)
{
    return bullet.coordinate[0][0] < 0;
}
// checks is enemy is reached bottom of the map
bool enemy_outOFBound(const int n, const vector<Dart> &dart, const vector<Striker> &striker,
                      const vector<Wraith> &wraith, const vector<Banshee> &banshee)
{
    for (const auto &enemy : dart)
    {
        if (enemy.D_coordinate[0][0] == n)
        {
            return true;
        }
    }

    for (const auto &enemy : striker)
    {
        if (enemy.S_coordinate[3][0] == n)
        {
            return true;
        }
    }

    for (const auto &enemy : wraith)
    {
        if (enemy.W_coordinate[7][0] == n)
        {
            return true;
        }
    }

    for (const auto &enemy : banshee)
    {
        if (enemy.B_coordinate[15][0] == n)
        {
            return true;
        }
    }

    return false;
}

// removes the enemy and spawns a new enemy only if enemy is not already killed and removed
void removeAndReSpawnEnemy(SpaceShip &spaceship, GameData &gameData, int n, vector<Dart> &dart, vector<Striker> &striker,
                           vector<Wraith> &wraith, vector<Banshee> &banshee)
{
    for (const auto &enemy : dart)
    {
        if (enemy_outOFBound(n, dart, striker, wraith, banshee) || collision(n, dart, striker, wraith, banshee, spaceship))
        {
            if (enemy.heal > 0)
            {
                dart.pop_back();
                spaceship.heal--;
                Enemy_coordinate_maker(n, dart, striker, wraith, banshee, gameData);
            }
        }
    }

    for (const auto &enemy : striker)
    {
        if (enemy_outOFBound(n, dart, striker, wraith, banshee) || collision(n, dart, striker, wraith, banshee, spaceship))
        {
            if (enemy.heal > 0)
            {
                striker.pop_back();
                spaceship.heal--;
                Enemy_coordinate_maker(n, dart, striker, wraith, banshee, gameData);
            }
        }
    }

    for (const auto &enemy : wraith)
    {
        if (enemy_outOFBound(n, dart, striker, wraith, banshee) || collision(n, dart, striker, wraith, banshee, spaceship))
        {
            if (enemy.heal > 0)
            {
                wraith.pop_back();
                spaceship.heal--;
                Enemy_coordinate_maker(n, dart, striker, wraith, banshee, gameData);
            }
        }
    }

    for (const auto &enemy : banshee)
    {
        if (enemy_outOFBound(n, dart, striker, wraith, banshee) || collision(n, dart, striker, wraith, banshee, spaceship))
        {
            if (enemy.heal > 0)
            {
                banshee.pop_back();
                spaceship.heal--;
                Enemy_coordinate_maker(n, dart, striker, wraith, banshee, gameData);
            }
        }
    }
}

void move_bullets(vector<Bullet> &bullets)
{
    for (auto it = bullets.begin(); it != bullets.end();)
    {
        if (bullet_outOfBound(*it))
        {
            it = bullets.erase(it);
        }
        else
        {
            it->coordinate[0][0]--;
            it++;
        }
    }
}

bool isHit(const Dart &enemy, const Bullet &bullet)
{
    return enemy.D_coordinate[0][0] == bullet.coordinate[0][0] &&
           enemy.D_coordinate[0][1] == bullet.coordinate[0][1];
}

bool isHit(const Striker &enemy, const Bullet &bullet)
{
    for (int s = 0; s < 4; s++)
    {
        if (enemy.S_coordinate[s][0] == bullet.coordinate[0][0] &&
            enemy.S_coordinate[s][1] == bullet.coordinate[0][1])
        {
            return true;
        }
    }
    return false;
}

bool isHit(const Wraith &enemy, const Bullet &bullet)
{
    for (int w = 0; w < 9; w++)
    {
        if (enemy.W_coordinate[w][0] == bullet.coordinate[0][0] &&
            enemy.W_coordinate[w][1] == bullet.coordinate[0][1])
        {
            return true;
        }
    }
    return false;
}

bool isHit(const Banshee &enemy, const Bullet &bullet)
{
    for (int b = 0; b < 16; b++)
    {
        if (enemy.B_coordinate[b][0] == bullet.coordinate[0][0] &&
            enemy.B_coordinate[b][1] == bullet.coordinate[0][1])
        {
            return true;
        }
    }
    return false;
}

/*
 *         enemy heal and removal part
 */
void enemy_heal_check(vector<Dart> &dart, vector<Striker> &striker,
                      vector<Wraith> &wraith, vector<Banshee> &banshee,
                      vector<Bullet> &bullets)
{
    for (auto it = bullets.begin(); it != bullets.end();)
    {
        bool bulletHit = false;

        for (auto &enemy : dart)
        {
            if (isHit(enemy, *it))
            {
                enemy.heal--;
                bulletHit = true;
                break;
            }
        }

        if (!bulletHit)
        {
            for (auto &enemy : striker)
            {
                if (isHit(enemy, *it))
                {
                    enemy.heal--;
                    bulletHit = true;
                    break;
                }
            }
        }

        if (!bulletHit)
        {
            for (auto &enemy : wraith)
            {
                if (isHit(enemy, *it))
                {
                    enemy.heal--;
                    bulletHit = true;
                    break;
                }
            }
        }

        if (!bulletHit)
        {
            for (auto &enemy : banshee)
            {
                if (isHit(enemy, *it))
                {
                    enemy.heal--;
                    bulletHit = true;
                    break;
                }
            }
        }

        // Erase the bullet if it hit an enemy
        if (bulletHit)
        {
            it = bullets.erase(it);
        }
        else
        {
            it++;
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
        if (enemy.heal <= 0)
        {
            dart.pop_back();
            gameData.point += 1;
            gameData.points_updater += 1;
            gameData.killCounter++;
            Enemy_coordinate_maker(n, dart, striker, wraith, banshee, gameData);
        }
    }
    for (auto &enemy : striker)
    {
        if (enemy.heal <= 0)
        {
            striker.pop_back();
            gameData.point += 8;
            gameData.points_updater += 8;
            gameData.killCounter++;
            Enemy_coordinate_maker(n, dart, striker, wraith, banshee, gameData);
        }
    }
    for (auto &enemy : wraith)
    {
        if (enemy.heal <= 0)
        {
            wraith.pop_back();
            gameData.point += 18;
            gameData.points_updater += 18;
            gameData.killCounter++;
            Enemy_coordinate_maker(n, dart, striker, wraith, banshee, gameData);
        }
    }
    for (auto &enemy : banshee)
    {
        if (enemy.heal <= 0)
        {
            banshee.pop_back();
            gameData.point += 32;
            gameData.points_updater += 32;
            gameData.killCounter++;
            Enemy_coordinate_maker(n, dart, striker, wraith, banshee, gameData);
        }
    }
}

/*
 *        ship heal and removal part
 */

// checks if any enemy hits the ship
bool collision(int n, vector<Dart> &dart, vector<Striker> &striker,
               vector<Wraith> &wraith, vector<Banshee> &banshee, SpaceShip &spaceship)
{
    for (auto &enemy : dart)
    {
        if (enemy.D_coordinate[0][0] == n - 1 && enemy.D_coordinate[0][1] == spaceship.ship_y)
        {
            return true;
        }
    }

    for (auto &enemy : striker)
    {
        for (int s = 0; s < 4; s++)
        {
            if (enemy.S_coordinate[s][0] == n - 1 && enemy.S_coordinate[s][1] == spaceship.ship_y)
            {
                return true;
            }
        }
    }

    for (auto &enemy : wraith)
    {
        for (int w = 0; w < 9; w++)
        {
            if (enemy.W_coordinate[w][0] == n - 1 && enemy.W_coordinate[w][1] == spaceship.ship_y)
            {
                return true;
            }
        }
    }

    for (auto &enemy : banshee)
    {
        for (int b = 0; b < 16; b++)
        {
            if (enemy.B_coordinate[b][0] == n - 1 && enemy.B_coordinate[b][1] == spaceship.ship_y)
            {
                return true;
            }
        }
    }
    return false;
}

bool shipStatus(SpaceShip &spaceShip)
{
    if (spaceShip.heal == 0)
        return false; // ship is dead
    return true;
};

void update_level(GameData &gameData)
{
    if (gameData.points_updater >= 200)
    {
        gameData.points_updater -= 200;
        gameData.level++;
    }
}

void refresh(GameData &gameData, vector<Dart> &dart, vector<Striker> &striker,
             vector<Wraith> &wraith, vector<Banshee> &banshee,
             vector<Bullet> &bullets, SpaceShip &spaceship, int n)
{
    move_enemies_down(dart, striker, wraith, banshee);
    new_bullet_maker(bullets, spaceship, n);
    move_bullets(bullets);
    // reduce enemy heal when shot
    enemy_heal_check(dart, striker, wraith, banshee, bullets);
    // remove and ReSpawn enemy if heal = 0
    enemy_damage_check(gameData, dart, striker, wraith, banshee, bullets, n);
    removeAndReSpawnEnemy(spaceship, gameData, n, dart, striker, wraith, banshee);
    update_level(gameData);
    gameSaver(n, gameData, bullets, dart, striker, wraith, banshee, spaceship);
}

/*
 *        game saving and reloading part
 */

void gameSaver(const int n, const GameData &gameData, vector<Bullet> &bullets, const vector<Dart> &dart, const vector<Striker> &striker,
               const vector<Wraith> &wraith, const vector<Banshee> &banshee, const SpaceShip &spaceship)
{

    ofstream file("gameData.txt");
    if (file.is_open())
    {
        file << gameData.gameResult << " "; // win / loose / undefined
        file << n << " ";
        file << gameData.level << " ";
        file << gameData.point << " ";
        file << spaceship.ship_y << " ";
        file << spaceship.heal << " ";
        file << gameData.killCounter << " ";
        file << gameData.targetScore << " ";
        file << spaceship.shape << "\n";

        if (!dart.empty())
            file << "dart\n";
        for (const auto &dart : dart)
        {
            file << dart.heal << endl;
            file << dart.D_coordinate[0][0] << " "
                 << dart.D_coordinate[0][1] << " ";
        }

        if (!striker.empty())
            file << "striker\n";

        for (const auto &striker : striker)
        {
            file << striker.heal << endl;
            for (int i = 0; i < 4; i++)
            {
                file << striker.S_coordinate[i][0] << " "
                     << striker.S_coordinate[i][1] << " ";
            }
        }
        if (!wraith.empty())
            file << "wraith\n";
        for (const auto &wraith : wraith)
        {
            file << wraith.heal << endl;
            for (int i = 0; i < 9; i++)
            {
                file << wraith.W_coordinate[i][0] << " "
                     << wraith.W_coordinate[i][1] << " ";
            }
        }
        if (!banshee.empty())
            file << "banshee\n";
        for (const auto &banshee : banshee)
        {
            file << banshee.heal << endl;
            for (int i = 0; i < 16; i++)
            {
                file << banshee.B_coordinate[i][0] << " "
                     << banshee.B_coordinate[i][1] << " ";
            }
        }

        file << endl;

        bullets.shrink_to_fit();
        for (const auto &bullet : bullets)
        {
            file << bullet.coordinate[0][0] << " " << bullet.coordinate[0][1] << " ";
        }
        file.close();
    }
    else
    {
        cerr << "error opening the file";
        return;
    }
}

int gameLoader(int &n, GameData &gameData, vector<Bullet> &bullets,
               vector<Dart> &dart, vector<Striker> &striker, vector<Wraith> &wraith,
               vector<Banshee> &banshee, SpaceShip &spaceship)
{
    ifstream file("gameData.txt");
    if (file.is_open())
    {
        file >> gameData.gameResult; // win / loose / undefined
        if (gameData.gameResult == "win")
        {
            return 1;
        }
        else if (gameData.gameResult == "loose")
        {
            return 0;
        }
        else if (gameData.gameResult == "undefined")
        {
            file >> n >> gameData.level >> gameData.point >> spaceship.ship_y >> spaceship.heal >> gameData.killCounter >> gameData.targetScore >> spaceship.shape;
            string enemyType;
            file >> enemyType;

            if (enemyType == "dart")
            {
                Dart newDart;
                file >> newDart.heal;
                file >> newDart.D_coordinate[0][0] >> newDart.D_coordinate[0][1];
                dart.push_back(newDart);
            }
            else if (enemyType == "striker")
            {
                Striker newStriker;
                file >> newStriker.heal;
                for (int i = 0; i < 4; i++)
                {
                    file >> newStriker.S_coordinate[i][0] >> newStriker.S_coordinate[i][1];
                }
                striker.push_back(newStriker);
            }
            else if (enemyType == "wraith")
            {
                Wraith newWraith;
                file >> newWraith.heal;
                for (int i = 0; i < 9; i++)
                {
                    file >> newWraith.W_coordinate[i][0] >> newWraith.W_coordinate[i][1];
                }
                wraith.push_back(newWraith);
            }
            else if (enemyType == "banshee")
            {
                Banshee newBanshee;
                file >> newBanshee.heal;
                for (int i = 0; i < 16; i++)
                {
                    file >> newBanshee.B_coordinate[i][0] >> newBanshee.B_coordinate[i][1];
                }
                banshee.push_back(newBanshee);
            }


            // Read bullet Enemy_coordinate_maker
            Bullet newBullet;
            while (file >> newBullet.coordinate[0][0] >> newBullet.coordinate[0][1])
            {
                bullets.push_back(newBullet);
            }

            file.close();
        }
        return 2;
    }
    return -1;
}

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

void gotoxy(int x, int y);
void printEnemy1();
void eraseEnemy1();
void moveEnemy1();
void printEnemy2();
void eraseEnemy2();
void moveEnemy2();
void printEnemy3();
void eraseEnemy3();
void moveEnemy3();
void header();
void erasePlayer();
void printPlayer();
void movePlayerLeft();
void movePlayerRight();
void printMaze();
void scrollRoads();
void generateBullet();
void moveBullets();
void printBullet(int x, int y);
void eraseBullet(int x, int y);
void bulletCollisionWithEnemies();
void checkCollisionWithPlayer();
void addScore(int points);
void printScore();
void printLives();
void gameOver();
void dropRewardFromEnemy1();
void dropRewardFromEnemy2();
void dropRewardFromEnemy3();
void moveRewards();
void checkRewardCollection();
void printEnemyBullet(int x, int y);
void eraseEnemyBullet(int x, int y);
void generateEnemyBullet(int ex, int ey);
void moveEnemyBullets();
void enemyBulletCollisionWithPlayer();

const int enemyWidth = 7;
const int enemyHeight = 4;
const int playerWidth = 7;
const int playerHeight = 4;
const int BULLET_MAX = 100;
const int mazeWidth = 54;
const int NUM_ROADS = 6;

int pX = 20 , pY = 21;
int pRoadIndex = 2;
int lives = 3;
int bulletX[BULLET_MAX], bulletY[BULLET_MAX];
bool isBulletActive[BULLET_MAX];
int bulletCount = 0;      
int score = 0;
int roadOffset = 0;
int e1X, e1Y = 2;
int e1RoadIndex;
int e1Health = 30;
int e2X, e2Y = 2;
int e2RoadIndex;
int e2Health = 30;
int e3X, e3Y = 2;
int e3RoadIndex;
int e3Health = 30;
int r1X, r1Y;
bool r1Active = false;
int r2X, r2Y;
bool r2Active = false;
int r3X, r3Y;
bool r3Active = false;
int roadPositions[NUM_ROADS];
int linePositions[NUM_ROADS - 1];

const int E_BULLET_MAX = 50;
int eBulletX[E_BULLET_MAX], eBulletY[E_BULLET_MAX];
bool isEBulletActive[E_BULLET_MAX];
int eBulletCount = 0;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    srand(time(0));
    system("cls");
    header();
    cin.ignore();
    cin.get();
    system("cls");
    printMaze();
    int playableWidth = mazeWidth - 2; 
    int roadWidth = playableWidth / NUM_ROADS;
    for (int i = 0; i < NUM_ROADS; i++) {
        roadPositions[i] = 1 + i * roadWidth + roadWidth / 2 - playerWidth / 2;
    }
    for (int i = 0; i < NUM_ROADS - 1; i++) {
        linePositions[i] = 1 + (i + 1) * roadWidth;
    }
    printPlayer();
    e1RoadIndex = rand() % NUM_ROADS;
    printEnemy1();
    e2RoadIndex = rand() % NUM_ROADS;
    printEnemy2();
    e3RoadIndex = rand() % NUM_ROADS;
    printEnemy3();

    while (true) {
        if (GetAsyncKeyState(VK_LEFT)) {
            movePlayerLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT)) {
            movePlayerRight();
        }
        if (GetAsyncKeyState(VK_SPACE)) {
            generateBullet();
        }
        moveBullets();
        bulletCollisionWithEnemies();
        moveEnemy1();
        moveEnemy2();
        moveEnemy3();
        moveEnemyBullets();
        enemyBulletCollisionWithPlayer();
        checkCollisionWithPlayer();
        moveRewards();
        checkRewardCollection();
        scrollRoads();
        printScore();
        printLives(); 
        Sleep(100);
    }
    return 0;
}

void printPlayer() {
    pX = roadPositions[pRoadIndex];
    gotoxy(pX, pY);
    cout << "   || ";
    gotoxy(pX, pY + 1);
    cout << "  ||||";
    gotoxy(pX, pY + 2);
    cout << "   || ";
    gotoxy(pX, pY + 3);
    cout << "  |||| ";
}

void movePlayerLeft() {
    if (pRoadIndex > 0) {
        erasePlayer();
        pRoadIndex--;
        printPlayer();
    }
}

void movePlayerRight() {
    if (pRoadIndex < NUM_ROADS - 1) {
        erasePlayer();
        pRoadIndex++;
        printPlayer();
    }
}

void erasePlayer() {
    gotoxy(pX, pY);
    cout << "       ";
    gotoxy(pX, pY + 1);
    cout << "       ";
    gotoxy(pX, pY + 2);
    cout << "       ";
    gotoxy(pX, pY + 3);
    cout << "       ";
}

void printEnemy1() {
    e1X = roadPositions[e1RoadIndex];
    gotoxy(e1X, e1Y);
    cout << " ****  ";
    gotoxy(e1X, e1Y + 1);
    cout << "  **   ";
    gotoxy(e1X, e1Y + 2);
    cout << " ****  ";
    gotoxy(e1X, e1Y + 3);
    cout << "  **   ";
}

void eraseEnemy1() {
    gotoxy(e1X, e1Y);
    cout << "       ";
    gotoxy(e1X, e1Y + 1);
    cout << "       ";
    gotoxy(e1X, e1Y + 2);
    cout << "       ";
    gotoxy(e1X, e1Y + 3);
    cout << "       ";
}

void moveEnemy1() {
    eraseEnemy1();
    e1Y++;
    if (e1Y > 21) {
        e1Y = 2;
        e1RoadIndex = rand() % NUM_ROADS;
        e1Health = 30; 
    }
    printEnemy1();
    generateEnemyBullet(e1X, e1Y);
}

void printEnemy2() {
    e2X = roadPositions[e2RoadIndex];
    gotoxy(e2X, e2Y);
    cout << " ****  ";
    gotoxy(e2X, e2Y + 1);
    cout << "  **   ";
    gotoxy(e2X, e2Y + 2);
    cout << " ****  ";
    gotoxy(e2X, e2Y + 3);
    cout << "  **   ";
}

void eraseEnemy2() {
    gotoxy(e2X, e2Y);
    cout << "       ";
    gotoxy(e2X, e2Y + 1);
    cout << "       ";
    gotoxy(e2X, e2Y + 2);
    cout << "       ";
    gotoxy(e2X, e2Y + 3);
    cout << "       ";
}

void moveEnemy2() {
    eraseEnemy2();
    e2Y++;
    if (e2Y > 21) {
        e2Y = 2;
        e2RoadIndex = rand() % NUM_ROADS;
        e2Health = 30;
    }
    printEnemy2();
    generateEnemyBullet(e2X, e2Y);
}

void printEnemy3() {
    e3X = roadPositions[e3RoadIndex];
    gotoxy(e3X, e3Y);
    cout << " ****  ";
    gotoxy(e3X, e3Y + 1);
    cout << "  **   ";
    gotoxy(e3X, e3Y + 2);
    cout << " ****  ";
    gotoxy(e3X, e3Y + 3);
    cout << "  **   ";
}

void eraseEnemy3() {
    gotoxy(e3X, e3Y);
    cout << "       ";
    gotoxy(e3X, e3Y + 1);
    cout << "       ";
    gotoxy(e3X, e3Y + 2);
    cout << "       ";
    gotoxy(e3X, e3Y + 3);
    cout << "       ";
}

void moveEnemy3() {
    eraseEnemy3();
    e3Y++;
    if (e3Y > 21) {
        e3Y = 2;
        e3RoadIndex = rand() % NUM_ROADS;
        e3Health = 30;
    }
    printEnemy3();
    generateEnemyBullet(e3X, e3Y);
}

void header() {
    cout << "______  ___      _____       ________       "   << endl;
    cout << "___   |/  /___  ___  /______ ___  __/       "   << endl;
    cout << "__  /|_/ /_  / / /  __/  __ `/_  /_         "   << endl;
    cout << "_  /  / / / /_/ // /_ / /_/ /_  __/         "   << endl;
    cout << "/_/  /_/  \\__,_/ \\__/ \\__,_/ /_/         "   << endl;
    cout << "                                            "   << endl;
    cout << "________             _____                  "   << endl;
    cout << "___  __ \\_____ _________(_)_____________   " << endl;
    cout << "__  /_/ /  __ `/  ___/_  /__  __ \\_  __ `/ " << endl;
    cout << "_  _, _// /_/ // /__ _  / _  / / /  /_/ /   " << endl;
    cout << "/_/ |_| \\__,_/ \\___/ /_/  /_/ /_/_\\__, / " << endl;
    cout << "                                 /____/     " << endl;
    cout << "                                            " << endl;
    cout << "                                            " << endl;
    cout << " Press any key to continue ...              " << endl;
}

void printMaze() {
    cout << "###################################################" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "#                                                 #" << endl;
    cout << "###################################################" << endl;
}

void scrollRoads() {
    for (int y = 1; y <= 25; y++) {
        for (int i = 0; i < NUM_ROADS - 1; i++) {
            gotoxy(linePositions[i], y);
            cout << " ";
        }
    }
    roadOffset = (roadOffset + 1) % 2;
    for (int y = 2; y <= 24; y++) {
        if ((y + roadOffset) % 2 == 0) {
            for (int i = 0; i < NUM_ROADS - 1; i++) {
                gotoxy(linePositions[i], y);
                cout << "|";
            }
        }
    }
}

void generateBullet() {
    bulletX[bulletCount] = pX + 3;
    bulletY[bulletCount] = pY - 1;
    isBulletActive[bulletCount] = true;
    printBullet(bulletX[bulletCount], bulletY[bulletCount]);
    bulletCount++;
    if (bulletCount >= BULLET_MAX) {
        bulletCount = 0;
    }
}

void moveBullets() {
    for (int i = 0; i < BULLET_MAX; i++) {
        if (isBulletActive[i]) {
            eraseBullet(bulletX[i], bulletY[i]);
            bulletY[i]--;
            if (bulletY[i] <= 1) {
                isBulletActive[i] = false;
            } else {
                printBullet(bulletX[i], bulletY[i]);
            }
        }
    }
}

void printBullet(int x, int y) {
    gotoxy(x, y);
    cout << "*";
}

void eraseBullet(int x, int y) {
    gotoxy(x, y);
    cout << " ";
}

void bulletCollisionWithEnemies() {
    for (int i = 0; i < BULLET_MAX; i++) {
        if (isBulletActive[i]) {
            if ((bulletX[i] >= e1X) && (bulletX[i] <= e1X + enemyWidth) &&
                (bulletY[i] >= e1Y) && (bulletY[i] <= e1Y + enemyHeight)) {
                isBulletActive[i] = false;
                eraseBullet(bulletX[i], bulletY[i]);
                e1Health -= 10;
                if (e1Health <= 0) {
                    dropRewardFromEnemy1();
                    eraseEnemy1();
                    e1Y = 2;
                    e1RoadIndex = rand() % NUM_ROADS;
                    e1Health = 30;
                    addScore(10);
                } else {
                    eraseEnemy1();
                    printEnemy1();
                }
            }
            if ((bulletX[i] >= e2X) && (bulletX[i] <= e2X + enemyWidth) &&
                (bulletY[i] >= e2Y) && (bulletY[i] <= e2Y + enemyHeight)) {
                isBulletActive[i] = false;
                eraseBullet(bulletX[i], bulletY[i]);
                e2Health -= 10;
                if (e2Health <= 0) {
                    dropRewardFromEnemy2();
                    eraseEnemy2();
                    e2Y = 2;
                    e2RoadIndex = rand() % NUM_ROADS;
                    e2Health = 30;
                    addScore(10);
                } else {
                    eraseEnemy2();
                    printEnemy2();
                }
            }
            if ((bulletX[i] >= e3X) && (bulletX[i] <= e3X + enemyWidth) &&
                (bulletY[i] >= e3Y) && (bulletY[i] <= e3Y + enemyHeight)) {
                isBulletActive[i] = false;
                eraseBullet(bulletX[i], bulletY[i]);
                e3Health -= 10;
                if (e3Health <= 0) {
                    dropRewardFromEnemy3();
                    eraseEnemy3();
                    e3Y = 2;
                    e3RoadIndex = rand() % NUM_ROADS;
                    e3Health = 30;
                    addScore(10);
                } else {
                    eraseEnemy3();
                    printEnemy3();
                }
            }
        }
    }
}

void checkCollisionWithPlayer() {
    bool collided = false;
    if (e1RoadIndex == pRoadIndex &&
        e1Y + enemyHeight >= pY && e1Y <= pY + playerHeight) {
        collided = true;
    }
    if (e2RoadIndex == pRoadIndex &&
        e2Y + enemyHeight >= pY && e2Y <= pY + playerHeight) {
        collided = true;
    }
    if (e3RoadIndex == pRoadIndex &&
        e3Y + enemyHeight >= pY && e3Y <= pY + playerHeight) {
        collided = true;
    }
    if (collided) {
        lives = lives - 1;
        if (lives <= 0) {
            gameOver();
        } else {
            eraseEnemy1();
            eraseEnemy2();
            eraseEnemy3();
            e1Y = 2; e1Health = 30; e1RoadIndex = rand() % NUM_ROADS; printEnemy1();
            e2Y = 2; e2Health = 30; e2RoadIndex = rand() % NUM_ROADS; printEnemy2();
            e3Y = 2; e3Health = 30; e3RoadIndex = rand() % NUM_ROADS; printEnemy3();
        }
    }
}

void addScore(int points) {
    score = score + points;
}

void printScore() {
    gotoxy(mazeWidth + 2, 1);
    cout << "Score: " << score << "   ";
}

void printLives() {
    gotoxy(mazeWidth + 2, 2);
    cout << "Lives: " << lives << "   ";
}

void gameOver() {
    system("cls");  
    cout << "   _________                              " << endl;
    cout << "   __  ____/_____ _______ ________        " << endl;
    cout << "   _  / __ _  __ `/_  __ `__ \\  _ \\     " << endl;
    cout << "   / /_/ / / /_/ /_  / / / / /  __/       " << endl;
    cout << "   \\____/  \\__,_/ /_/ /_/ /_/\\___/     " << endl;
    cout << "                                          " << endl;
    cout << "   _______                                " << endl;
    cout << "   __  __ \\__   ______________           " << endl;
    cout << "   _  / / /_ | / /  _ \\_  ___/           " << endl;
    cout << "   / /_/ /__ |/ //  __/  /                " << endl;
    cout << "   \\____/ _____/ \\___//_/               " << endl;
    cout << "                                          " << endl;
    cout << "Your Final Score: " << score << endl;
    cout << "                                          " << endl;
    exit(0);
}

void dropRewardFromEnemy1() {
    r1X = e1X + 3; 
    r1Y = e1Y + enemyHeight;
    r1Active = true;
    gotoxy(r1X, r1Y);
    cout << "$";
}

void dropRewardFromEnemy2() {
    r2X = e2X + 3; 
    r2Y = e2Y + enemyHeight;
    r2Active = true;
    gotoxy(r2X, r2Y);
    cout << "$";
}

void dropRewardFromEnemy3() {
    r3X = e3X + 3; 
    r3Y = e3Y + enemyHeight;
    r3Active = true;
    gotoxy(r3X, r3Y);
    cout << "$";
}

void moveRewards() {
    if (r1Active) {
        gotoxy(r1X, r1Y);
        cout << " ";
        r1Y++; 
        if (r1Y > 24) {
            r1Active = false;
        } else {
            gotoxy(r1X, r1Y);
            cout << "$" ;      
        }
    }
    if (r2Active) {
        gotoxy(r2X, r2Y);
        cout << " ";
        r2Y++;
        if (r2Y > 24) {
            r2Active = false;
        } else {
            gotoxy(r2X, r2Y);
            cout << "$";
        }
    }
    if (r3Active) {
        gotoxy(r3X, r3Y);
        cout << " ";
        r3Y++;
        if (r3Y > 24) {
            r3Active = false;
        } else {
            gotoxy(r3X, r3Y);
            cout << "$";
        }
    }
}

void checkRewardCollection() {
    if (r1Active) {
        if (r1X >= pX && r1X <= pX + playerWidth && r1Y >= pY && r1Y <= pY + playerHeight) {
            r1Active = false;
            addScore(50);
        }
    }
    if (r2Active) {
        if (r2X >= pX && r2X <= pX + playerWidth && r2Y >= pY && r2Y <= pY + playerHeight) {
            r2Active = false;
            addScore(50);
        }
    }
    if (r3Active) {
        if (r3X >= pX && r3X <= pX + playerWidth && r3Y >= pY && r3Y <= pY + playerHeight) {
            r3Active = false;
            addScore(50);
        }
    }
}

void printEnemyBullet(int x, int y) {
    gotoxy(x, y);
    cout << "o";
}

void eraseEnemyBullet(int x, int y) {
    gotoxy(x, y);
    cout << " ";
}

void generateEnemyBullet(int ex, int ey) {
    if (score < 300) return;
    if (rand() % 10 != 0) return; 
    eBulletX[eBulletCount] = ex + 3;
    eBulletY[eBulletCount] = ey + enemyHeight;
    isEBulletActive[eBulletCount] = true;
    printEnemyBullet(eBulletX[eBulletCount], eBulletY[eBulletCount]);
    eBulletCount++;
    if (eBulletCount >= E_BULLET_MAX) {
        eBulletCount = 0;
    }
}

void moveEnemyBullets() {
    for (int i = 0; i < E_BULLET_MAX; i++) {
        if (isEBulletActive[i]) {
            eraseEnemyBullet(eBulletX[i], eBulletY[i]);
            eBulletY[i] = eBulletY[i] + 2;
            if (eBulletY[i] > 24) {
                isEBulletActive[i] = false;
            } else {
                printEnemyBullet(eBulletX[i], eBulletY[i]);
            }

        }
    }
}

void enemyBulletCollisionWithPlayer() {
    for (int i = 0; i < E_BULLET_MAX; i++) {
        if (isEBulletActive[i]) {
            if (eBulletX[i] >= pX && eBulletX[i] <= pX + playerWidth &&
                eBulletY[i] >= pY && eBulletY[i] <= pY + playerHeight) {
                isEBulletActive[i] = false;
                eraseEnemyBullet(eBulletX[i], eBulletY[i]);
                lives--;
                if (lives <= 0) {
                    gameOver();
                } else {
                    eraseEnemy1();
                    eraseEnemy2();
                    eraseEnemy3();
                    e1Y = 2; e1Health = 30; e1RoadIndex = rand() % NUM_ROADS; printEnemy1();
                    e2Y = 2; e2Health = 30; e2RoadIndex = rand() % NUM_ROADS; printEnemy2();
                    e3Y = 2; e3Health = 30; e3RoadIndex = rand() % NUM_ROADS; printEnemy3();
                }
            }
        }
    }
}

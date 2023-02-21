#include <iostream>
#include <windows.h>
using namespace std;
//.......................................................Global Data....................................................

//...............................PrintCharacter

char legs = 193;
char triangleUp = 30;
char triangleRight = 16;
char triangleLeft = 17;
char triangleDown = 31;
char eyes = 248;
char square = 254;
char feet = 220;
char heart = 3;
// NICK
char nick1[4] = {'[', eyes, eyes, ']'};
char nick2[4] = {'/', '|', '|', '\\'};
char nick3[4] = {'-', ' ', '-', ' '};
// Enemy1
char enemyA1[6] = {' ', '_', eyes, eyes, '_', ' '};
char enemyA2[6] = {'<', '|', triangleUp, triangleDown, '|', '>'};
char enemyA3[6] = {' ', '\\', legs, legs, '/', ' '};

// Enemy2
char enemyB1[5] = {' ', triangleUp, triangleUp, triangleUp, ' '};
char enemyB2[5] = {triangleLeft, 'o', '|', 'o', triangleRight};
char enemyB3[5] = {' ', triangleDown, triangleDown, triangleDown, ' '};

// King Grime
char kingGrime1[7] = {' ', ' ', triangleUp, triangleUp, triangleUp, ' ', ' '};
char kingGrime2[7] = {' ', '{', '*', 'v', '*', '}', ' '};
char kingGrime3[7] = {triangleLeft, '|', 'V', ' ', 'V', '|', triangleRight};
char kingGrime4[7] = {triangleLeft, ' ', triangleDown, triangleDown, triangleDown, ' ', triangleRight};

//.........................COORDINATES
// Nick
int nickX = 5;
int nickY = 18;
// Enemy1

int enemy1X = 90;
int enemy1Y = 20;
string enemy1Direction = "UP";

// Enemy2
int enemy2X = 10;
int enemy2Y = 27;
string enemy2Direction = "RIGHT";

// KING GRIME
int kingGrimeX = 70;
int kingGrimeY = 4;
string kingGrimeDirection = "LEFT";

// HEALTH
int nickHealth = 100;
int lives = 3;

int enemy1Health = 100;
int enemy2Health = 100;
int kingGrimeHealth = 100;
// Bullets
int nickBulletX[10000];
int nickBulletY[10000];
int bulletcount = 0;
bool BulletActive[10000];

// Enemy 1 BULLETS
int enemy1BulletX[10000];
int enemy1BulletY[10000];
int enemy1Bulletscount = 0;
bool enemy1BulletActive[10000];

// King Grime Bullets
int kingGrimeBulletX[1000];
int kingGrimeBulletY[1000];
int kingGrimeBulletscount = 0;
bool kingGrimeBulletActive[1000];
// SCORE
int score = 0;

//....................................................... Prototypes....................................................
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);

// Maze
void printMaze();

// Print characters
void printNick();
void printEnemy1();
void printEnemy2();
void printKingGrime();

//...............................Movement
// nick
void nickErase();
void nickUp();
void nickDown();
void nickRight();
void nickLeft();

// enemy1
void eraseEnemy1();
void enemy1Move();

// enemy2
void eraseEnemy2();
void enemy2Move();

// King Grime
void eraseKingGrime();
void moveKingGrime();

//..............................Health
void nickHealthMeter();
void printNickHealth();

void nickLivesMeter();
void printNickLives();
void decreaseLive();

// Enemy1
void enemy1HealthMeter();
void printEnemy1Health();

// Enemy2
void enemy2HealthMeter();
void printEnemy2Health();

// KING GRIME
void kingGrimeHealthMeter();
void printKingGrimeHealth();

//...............................Bullets
// nick
void generateBullets();
void inactiveBullets(int x);
void eraseBullets(int x, int y);
void moveBullets();
void printBullets(int x, int y);
void bulletDetection();

// Enemy1
void generateEnemy1Bullets();
void moveEnemy1Bullets();
void printEnemy1Bullets(int x, int y);
void enemy1BulletDetection();
void inactiveEnemy1Bullets(int x);

// KingGrime
void generateKingGrimeBullets();
void moveKingGrimeBullets();
void printkingGrimeBullets(int x, int y);
void kingGrimeBulletDetection();
void inactiveKingGrimeBullets(int x);

// score
void addScore();
void printScore();

//.....................................................Main Function....................................................
main()
{
    system("cls");
    printMaze();
    printNick();
    bool isPlaying = true;

    while (isPlaying)
    {
        nickHealthMeter();
        printNickHealth();
        nickLivesMeter();
        printNickLives();
        printScore();

        if (enemy1Health == 0 && enemy2Health == 0 && kingGrimeHealth == 0)
        {
            cout << "YOU WIN!!!";
            break;
        }
        if (kingGrimeHealth > 0)
        {
            printKingGrimeHealth();
            printKingGrime();
        }
        if (enemy1Health > 0)
        {
            printEnemy1();
            printEnemy1Health();
        }
        if (enemy2Health > 0)
        {
            printEnemy2Health();
            printEnemy2();
        }
        if (nickHealth <= 0)
        {
            decreaseLive();
            nickHealth = 100;
        }
        if (lives == 0)
        {
            cout << "\n GAME OVER";
            break;
        }
        if (GetAsyncKeyState(VK_UP))
        {
            nickUp();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            nickDown();
        }

        if (GetAsyncKeyState(VK_RIGHT))
        {
            nickRight();
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            nickLeft();
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            generateBullets();
        }
        if (enemy1X - nickX < 60 && (enemy1Y == nickY + 1 || enemy1Y + 1 == nickY + 1) || (enemy1Y + 1 == nickY))
        {
            generateEnemy1Bullets();
        }
        if (kingGrimeX - nickX < 60 && (kingGrimeY == nickY + 1 || kingGrimeY + 1 == nickY + 1) || (kingGrimeY + 1 == nickY))
        {
            generateKingGrimeBullets();
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            isPlaying = false;
        }
        if (enemy1Health > 0)
        {
            enemy1Move();
            moveEnemy1Bullets();
            // enemy1BulletDetection();
        }
        if (enemy2Health > 0)
        {
            enemy2Move();
        }
        if (kingGrimeHealth > 0)
        {
            moveKingGrime();
            moveKingGrimeBullets();
        }

        if (enemy1Health <= 0)
        {
            eraseEnemy1();
            enemy1Health=0;
            enemy1X = 130;
            enemy1Y = 0;
        }
        if (enemy2Health <= 0)
        {
            eraseEnemy2();
            enemy2Health=0;
            enemy2X = 130;
            enemy2Y = 0;
        }
        if (kingGrimeHealth <= 0)
        {
            eraseKingGrime();
            kingGrimeHealth =0;
            kingGrimeX = 130;
            kingGrimeY = 0;
        }
        moveBullets();
        bulletDetection();
        // enemy1BulletDetection();

        Sleep(90);
    }
}

// Nick Movement

void nickUp()
{
    char next = getCharAtxy(nickX, nickY - 1);
    if (next != '#' && next != '*' && next != '<' && '>' && next != '-' && next != '|')
    {
        nickErase();
        nickY--;
        printNick();
    }
}

void nickDown()
{
    char next = getCharAtxy(nickX, nickY + 3);
    char next2 = getCharAtxy(nickX + 2, nickY + 3);
    if (next != '#' && next != '*' && next != '<' && '>' && next != '-' && next != '|' &&
        next2 != '#' && next2 != '*' && next2 != '<' && '>' && next2 != '-' && next2 != '|')
    {
        nickErase();
        nickY++;
        printNick();
    }
}

void nickRight()
{
    char next = getCharAtxy(nickX + 4, nickY);
    char next2 = getCharAtxy(nickX + 4, nickY + 1);
    char next3 = getCharAtxy(nickX + 4, nickY + 2);
    if (next != '#' && next != '*' && next != '<' && next != '>' && next != '-' && next != '|' && next2 != '#' && next2 != '*' && next2 != '<' && next2 != '>' && next2 != '-' && next2 != '|' && next3 != '#' && next3 != '*' && next3 != '<' && next3 != '>' && next3 != '-' && next3 != '|')
    {
        nickErase();
        nickX++;
        printNick();
    }
}

void nickLeft()
{
    char next = getCharAtxy(nickX - 1, nickY);
    char next2 = getCharAtxy(nickX - 1, nickY + 1);

    char next3 = getCharAtxy(nickX - 1, nickY + 2);
    if (next != '#' && next != '*' && next != '<' && next != '>' && next != '-' && next != '|' && next2 != '#' && next2 != '*' && next2 != '<' && next2 != '>' && next2 != '-' && next2 != '|' && next3 != '#' && next3 != '*' && next3 != '<' && next3 != '>' && next3 != '-' && next3 != '|')
    {
        nickErase();
        nickX--;
        printNick();
    }
}

void nickErase()
{
    gotoxy(nickX, nickY);
    for (int i = 0; i < 4; i++)
    {
        cout << " ";
    }
    gotoxy(nickX, nickY + 1);
    for (int i = 0; i < 4; i++)
    {
        cout << " ";
    }
    gotoxy(nickX, nickY + 2);
    for (int i = 0; i < 4; i++)
    {
        cout << " ";
    }
}

void printNick()
{
    gotoxy(nickX, nickY);
    for (int i = 0; i < 4; i++)
    {
        cout << nick1[i];
    }
    gotoxy(nickX, nickY + 1);
    for (int i = 0; i < 4; i++)
    {
        cout << nick2[i];
    }

    gotoxy(nickX, nickY + 2);
    for (int i = 0; i < 4; i++)
    {
        cout << nick3[i];
    }
}

void printMaze()
{
    cout << "#######################################################################################################\n";
    cout << "#                                                                                                     #\n";
    cout << "#                                                                                                     #\n";
    cout << "#                                                                                                     #\n";
    cout << "#                                                                                                     #\n";
    cout << "#                                                                                                     #\n";
    cout << "#                                                                                                     #\n";
    cout << "#                                                                                                     #\n";
    cout << "#                                                                                                     #\n";
    cout << "#        ##############################################################################################\n";
    cout << "#        <<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>#\n";
    cout << "#        ##############################################################################################\n";
    cout << "#                                                                                                     #\n";
    cout << "#                                                                                                     #\n";
    cout << "#                                                                                                     #\n";
    cout << "#  " << heart << "                                                                                                  #\n";
    cout << "#-----------                                                                                          #\n";
    cout << "#          |#######<>                                                                                 #\n";
    cout << "#                  <>                                                                                 #\n";
    cout << "#                  <>###################################################################<>            #\n";
    cout << "#                  <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>             #\n";
    cout << "#                  <>###################################################################<>            #\n";
    cout << "#          |       <>                                                                                 #\n";
    cout << "#          |       <>                                                                                 #\n";
    cout << "#-----------       <>   " << heart << "                                                                             #\n";
    cout << "#                  <>                                                                                 #\n";
    cout << "#                  <>*******************************************************************<>            #\n";
    cout << "#                                                                                                     #\n";
    cout << "#                                                                                                     #\n";
    cout << "#                                                                                                     #\n";
    cout << "#                                                                                                     #\n";
    cout << "#######################################################################################################\n";
}

// Nick Health-Collision detection
void nickHealthMeter()
{
    char next1 = getCharAtxy(nickX + 4, nickY);
    char next2 = getCharAtxy(nickX - 1, nickY);
    char next3 = getCharAtxy(nickX, nickY - 1);
    char next4 = getCharAtxy(nickX + 4, nickY + 2);
    char next5 = getCharAtxy(nickX + 4, nickY + 1);
    char next6 = getCharAtxy(nickX - 1, nickY + 1);
    char next7 = getCharAtxy(nickX - 1, nickY + 2);
    if (next1 == '*' || next2 == '*' || next3 == '*' || next4 == '*' || next5 == '*' || next6 == '*' || next7 == '*' || next1 == '<' || next2 == '<' || next3 == '<' || next4 == '<' || next5 == '<' || next6 == '<' || next7 == '<' || next1 == '>' || next2 == '>' || next3 == '>' || next4 == '>' || next5 == '>' || next6 == '>' || next7 == '>' || next1 == 'o' || next2 == 'o' || next3 == 'o' || next4 == 'o' || next5 == 'o' || next6 == 'o' || next7 == 'o' || next1 == '~' || next2 == '~' || next3 == '~' || next4 == '~' || next5 == '~' || next6 == '~' || next7 == '~')
    {
        nickHealth = nickHealth - 1;
    }
    if (nickX + 3 == enemy1X && (nickY == enemy1Y || nickY == enemy1Y + 1 || nickY == enemy1Y + 2))
    {
        nickHealth -= 10;
    }
    if (nickX == enemy1X + 7 && (nickY == enemy1Y || nickY == enemy1Y + 1 || nickY == enemy1Y + 2))
    {
        nickHealth -= 10;
    }

    //Collision with enemy 2

    if (nickX + 3 == enemy2X && (nickY == enemy2Y || nickY == enemy2Y + 1 || nickY == enemy2Y + 2))
    {
        decreaseLive();
    }
    if (nickX == enemy2X + 6 && (nickY == enemy2Y || nickY == enemy2Y + 1 || nickY == enemy2Y + 2))
    {
        decreaseLive();
    }

    if (nickX == enemy2X && (nickY + 3 == enemy2Y - 1 || nickY -1 == enemy2Y+3 || nickY == enemy2Y))
    {
        decreaseLive();
    }
    
    //KING GRIME

    if (nickX + 3 == kingGrimeX && (nickY == kingGrimeY || nickY == kingGrimeY + 1 || nickY == kingGrimeY + 2))
    {
        decreaseLive();
    }
    if (nickX == kingGrimeX + 7 && (nickY == kingGrimeY || nickY == kingGrimeY + 1 || nickY == kingGrimeY + 2))
    {
        decreaseLive();
    }

    if (nickX == kingGrimeX && (nickY + 3 == kingGrimeY - 1 || nickY -1 == kingGrimeY+3 || nickY == kingGrimeY))
    {
        decreaseLive();
    }
}

void printNickHealth()
{
    gotoxy(110, 10);
    cout << "Health: " << nickHealth;
}

void printNickLives()
{
    gotoxy(110, 11);
    cout << "Lives: " << heart << " " << lives;
}

void nickLivesMeter()
{
    char next1 = getCharAtxy(nickX + 4, nickY);
    char next5 = getCharAtxy(nickX + 4, nickY + 1);
    char next6 = getCharAtxy(nickX + 4, nickY + 2);
    char next2 = getCharAtxy(nickX - 1, nickY);
    char next7 = getCharAtxy(nickX - 1, nickY + 1);
    char next8 = getCharAtxy(nickX - 1, nickY + 2);
    char next3 = getCharAtxy(nickX, nickY + 3);
    char next4 = getCharAtxy(nickX + 4, nickY - 1);
    if (next1 == heart || next2 == heart || next3 == heart || next4 == heart || next5 == heart || next6 == heart || next7 == heart || next8 == heart)
    {
        lives = lives + 1;
    }
}

void decreaseLive()
{
    lives--;
    nickErase();
    nickX = 5;
    nickY = 18;
    nickHealth = 100;
}
// Nick bullets
void generateBullets()
{
    nickBulletX[bulletcount] = nickX + 4;
    nickBulletY[bulletcount] = nickY + 1;
    BulletActive[bulletcount] = true;
    gotoxy(nickX + 4, nickY + 1);
    cout << ">";
    bulletcount++;
}

void moveBullets()
{
    for (int i = 0; i < bulletcount; i++)
    {
        char next = getCharAtxy(nickBulletX[i] + 1, nickBulletY[i]);

        if (next != ' ')
        {
            eraseBullets(nickBulletX[i], nickBulletY[i]);
            inactiveBullets(i);
        }

        else
        {
            eraseBullets(nickBulletX[i], nickBulletY[i]);
            nickBulletX[i]++;
            printBullets(nickBulletX[i], nickBulletY[i]);
        }
    }
}

void printBullets(int x, int y)
{
    gotoxy(x, y);
    cout << ">";
}

void bulletDetection()
{
    for (int i = 0; i < bulletcount; i++)
    {
        if (BulletActive[i] == true)
        {
            if (nickBulletX[i] + 1 == enemy1X && (nickBulletY[i] == enemy1Y || nickBulletY[i] == enemy1Y + 1 || nickBulletY[i] == enemy1Y + 2))
            {
                addScore();
                enemy1HealthMeter();
            }

            if (nickBulletX[i] - 1 == enemy1X && (nickBulletY[i] == enemy1Y || nickBulletY[i] == enemy1Y + 1 || nickBulletY[i] == enemy1Y + 2))
            {
                addScore();
                enemy1HealthMeter();
            }

            if (nickBulletX[i] + 1 == enemy2X && (nickBulletY[i] == enemy2Y || nickBulletY[i] == enemy2Y + 1 || nickBulletY[i] == enemy2Y + 2))
            {
                addScore();
                enemy2HealthMeter();
            }

            if (nickBulletX[i] - 1 == enemy2X && (nickBulletY[i] == enemy2Y || nickBulletY[i] == enemy2Y + 1 || nickBulletY[i] == enemy2Y + 2))
            {
                addScore();
                enemy2HealthMeter();
            }

            if (nickBulletX[i] + 1 == kingGrimeX && (nickBulletY[i] == kingGrimeY || nickBulletY[i] == kingGrimeY + 1 || nickBulletY[i] == kingGrimeY + 2 || nickBulletY[i] == kingGrimeY + 3))
            {
                addScore();
                kingGrimeHealthMeter();
            }

            if (nickBulletX[i] - 1 == kingGrimeX && (nickBulletY[i] == kingGrimeY || nickBulletY[i] == kingGrimeY + 1 || nickBulletY[i] == kingGrimeY + 2 || nickBulletY[i] == kingGrimeY + 3))
            {
                addScore();
                kingGrimeHealthMeter();
            }
        }
    }
}

// SCORE
void addScore()
{
    score++;
}

void printScore()
{
    gotoxy(110, 12);
    cout << "Score: " << score;
}
//..................................... Enemy 1
void printEnemy1()
{
    gotoxy(enemy1X, enemy1Y);

    for (int i = 0; i < 6; i++)
    {
        cout << enemyA1[i];
    }

    gotoxy(enemy1X, enemy1Y + 1);
    for (int i = 0; i < 6; i++)
    {
        cout << enemyA2[i];
    }
    gotoxy(enemy1X, enemy1Y + 2);
    for (int i = 0; i < 6; i++)
    {
        cout << enemyA3[i];
    }
}
// health
void enemy1HealthMeter()
{
    enemy1Health -= 5;
}

void printEnemy1Health()
{
    gotoxy(110, 13);
    cout << "Enemy 1 Health: " << enemy1Health;
}
// Enemy1 Firing
void generateEnemy1Bullets()
{
    enemy1BulletX[enemy1Bulletscount] = enemy1X - 1;
    enemy1BulletY[enemy1Bulletscount] = enemy1Y + 1;
    enemy1BulletActive[enemy1Bulletscount] = true;

    gotoxy(enemy1X - 1, enemy1Y + 1);
    cout << "o";
    enemy1Bulletscount++;
}

void moveEnemy1Bullets()
{
    for (int i = 0; i < enemy1Bulletscount; i++)
    {
        char next = getCharAtxy(enemy1BulletX[i] - 1, enemy1BulletY[i]);
        if (next != ' ')
        {
            eraseBullets(enemy1BulletX[i], enemy1BulletY[i]);
            inactiveEnemy1Bullets(i);
        }
        else
        {
            eraseBullets(enemy1BulletX[i], enemy1BulletY[i]);
            enemy1BulletX[i]--;
            printEnemy1Bullets(enemy1BulletX[i], enemy1BulletY[i]);
        }
    }
}

void printEnemy1Bullets(int x, int y)
{
    gotoxy(x, y);
    cout << 'o';
}

void eraseBullets(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}

void inactiveBullets(int x)
{
    BulletActive[x] = false;
}

void inactiveEnemy1Bullets(int x)
{
    enemy1BulletActive[x] = false;
}

void enemy1BulletDetection()
{
    for (int i = 0; i < enemy1Bulletscount; i++)
    {
        if (enemy1BulletActive[i] == true)
        {

            if (enemy1BulletX[i] + 1 == nickX || (enemy1BulletY[i] == nickY || enemy1BulletY[i] == nickY + 1 || enemy1BulletY[i] == nickY + 2 || enemy1BulletY[i] == nickY + 3))
            {

                nickHealth -= 5;
            }

            if ((enemy1BulletX[i] - 1 == nickX) && (enemy1BulletY[i] == nickY || enemy1BulletY[i] == nickY + 1 || enemy1BulletY[i] == nickY + 2 || enemy1BulletY[i] == nickY + 3))
            {
                nickHealth -= 5;
            }
        }
    }
}

// Enemy 1 Movement

void enemy1Move()
{

    if (enemy1Direction == "UP")
    {
        char next = getCharAtxy(enemy1X, enemy1Y - 1);
        if (next == ' ')
        {
            eraseEnemy1();
            enemy1Y--;
            printEnemy1();
        }
        else
        {
            enemy1Direction = "DOWN";
        }
    }
    else if (enemy1Direction == "DOWN")
    {
        char next = getCharAtxy(enemy1X, enemy1Y + 3);
        if (next == ' ')
        {
            eraseEnemy1();
            enemy1Y++;
            printEnemy1();
        }
        else
        {
            enemy1Direction = "UP";
        }
    }
}

void eraseEnemy1()
{
    gotoxy(enemy1X, enemy1Y);
    for (int i = 0; i < 6; i++)
    {
        cout << " ";
    }
    gotoxy(enemy1X, enemy1Y + 1);
    for (int i = 0; i < 6; i++)
    {
        cout << " ";
    }

    gotoxy(enemy1X, enemy1Y + 2);
    for (int i = 0; i < 6; i++)
    {
        cout << " ";
    }
}

//........................................ Enemy 2

void printEnemy2()
{
    gotoxy(enemy2X, enemy2Y);
    for (int i = 0; i < 5; i++)
    {
        cout << enemyB1[i];
    }

    gotoxy(enemy2X, enemy2Y + 1);
    for (int i = 0; i < 5; i++)
    {
        cout << enemyB2[i];
    }
    gotoxy(enemy2X, enemy2Y + 2);
    for (int i = 0; i < 5; i++)
    {
        cout << enemyB3[i];
    }
}

// Enemy 2 Movement
void enemy2Move()
{

    if (enemy2Direction == "RIGHT")
    {
        char next = getCharAtxy(enemy2X + 5, enemy2Y);
        if (next == ' ')
        {
            eraseEnemy2();
            enemy2X++;
            printEnemy2();
        }
        else
        {
            enemy2Direction = "LEFT";
        }
    }
    else if (enemy2Direction == "DOWN")
    {
        char next = getCharAtxy(enemy2X, enemy2Y + 4);
        if (next == ' ')
        {
            eraseEnemy2();
            enemy2Y++;
            printEnemy2();
        }
        else
        {
            enemy2Direction = "RIGHT";
        }
    }

    else if (enemy2Direction == "UP")
    {
        char next = getCharAtxy(enemy2X, enemy2Y - 1);
        if (next == ' ')
        {
            eraseEnemy2();
            enemy2Y--;
            printEnemy2();
        }
        else
        {
            enemy2Direction = "DOWN";
        }
    }
    if (enemy2Direction == "LEFT")
    {
        char next = getCharAtxy(enemy2X - 1, enemy2Y);
        if (next == ' ')
        {
            eraseEnemy2();
            enemy2X--;
            printEnemy2();
        }
        else
        {
            enemy2Direction = "UP";
        }
    }
}
void eraseEnemy2()
{
    gotoxy(enemy2X, enemy2Y);
    for (int i = 0; i < 5; i++)
    {
        cout << " ";
    }
    gotoxy(enemy2X, enemy2Y + 1);
    for (int i = 0; i < 5; i++)
    {
        cout << " ";
    }
    gotoxy(enemy2X, enemy2Y + 3);
    for (int i = 0; i < 5; i++)
    {
        cout << " ";
    }
}

// Enemy 2 Health
void enemy2HealthMeter()
{
    enemy2Health -= 10;
}
void printEnemy2Health()
{
    if (enemy2Health > 0)
    {
        gotoxy(110, 14);
        cout << "Enemy 2 Health: " << enemy2Health;
    }
}

//.................................... KING GRIME
void printKingGrime()
{
    gotoxy(kingGrimeX, kingGrimeY);
    for (int i = 0; i < 7; i++)
    {
        cout << kingGrime1[i];
    }
    gotoxy(kingGrimeX, kingGrimeY + 1);
    for (int i = 0; i < 7; i++)
    {
        cout << kingGrime2[i];
    }
    gotoxy(kingGrimeX, kingGrimeY + 2);
    for (int i = 0; i < 7; i++)
    {
        cout << kingGrime3[i];
    }
    gotoxy(kingGrimeX, kingGrimeY + 3);
    for (int i = 0; i < 7; i++)
    {
        cout << kingGrime4[i];
    }
}

// Health
void kingGrimeHealthMeter()
{
    kingGrimeHealth -= 4;
}

void printKingGrimeHealth()
{
    gotoxy(110, 15);
    cout << "KING GRIME: " << kingGrimeHealth;
}

// Bullets

void generateKingGrimeBullets()
{
    kingGrimeBulletX[kingGrimeBulletscount] = kingGrimeX - 1;
    kingGrimeBulletY[kingGrimeBulletscount] = kingGrimeY + 2;
    kingGrimeBulletActive[kingGrimeBulletscount] = true;

    gotoxy(kingGrimeX - 1, kingGrimeY + 2);
    cout << "~";
    kingGrimeBulletscount++;
}

void moveKingGrimeBullets()
{
    for (int i = 0; i < kingGrimeBulletscount; i++)
    {
        char next = getCharAtxy(kingGrimeBulletX[i] - 1, kingGrimeBulletY[i]);
        if (next != ' ')
        {
            eraseBullets(kingGrimeBulletX[i], kingGrimeBulletY[i]);
            inactiveKingGrimeBullets(i);
        }
        else
        {
            eraseBullets(kingGrimeBulletX[i], kingGrimeBulletY[i]);
            kingGrimeBulletX[i]--;
            printkingGrimeBullets(kingGrimeBulletX[i], kingGrimeBulletY[i]);
        }
    }
}

void printkingGrimeBullets(int x, int y)
{
    gotoxy(x, y);
    cout << '~';
}

void inactiveKingGrimeBullets(int x)
{
    kingGrimeBulletActive[x] = false;
}

// Movement
void eraseKingGrime()
{
    gotoxy(kingGrimeX, kingGrimeY);
    for (int i = 0; i < 7; i++)
    {
        cout << " ";
    }
    gotoxy(kingGrimeX, kingGrimeY + 1);
    for (int i = 0; i < 7; i++)
    {
        cout << " ";
    }
    gotoxy(kingGrimeX, kingGrimeY + 2);
    for (int i = 0; i < 7; i++)
    {
        cout << " ";
    }
    gotoxy(kingGrimeX, kingGrimeY + 3);
    for (int i = 0; i < 7; i++)
    {
        cout << " ";
    }
}

void moveKingGrime()
{
    if (kingGrimeDirection == "LEFT")
    {
        char next = getCharAtxy(kingGrimeX - 1, kingGrimeY);
        if (next == ' ')
        {
            eraseKingGrime();
            kingGrimeX--;
            printKingGrime();
        }
        else
        {
            kingGrimeDirection = "RIGHT";
        }
    }
    if (kingGrimeDirection == "RIGHT")
    {
        char next = getCharAtxy(kingGrimeX + 7, kingGrimeY);
        if (next == ' ')
        {
            eraseKingGrime();
            kingGrimeX++;
            printKingGrime();
        }
        else
        {
            kingGrimeDirection = "LEFT";
        }
    }
    if (kingGrimeDirection == "UP")
    {
        char next = getCharAtxy(kingGrimeX , kingGrimeY-1);
        if (next == ' ')
        {
            eraseKingGrime();
            kingGrimeY--;
            printKingGrime();
        }
        else
        {
            kingGrimeDirection = "RIGHT";
        }
    }
    if (kingGrimeDirection == "DOWN")
    {
        char next = getCharAtxy(kingGrimeX, kingGrimeY+4);
        if (next == ' ')
        {
            eraseKingGrime();
            kingGrimeY--;
            printKingGrime();
        }
        else
        {
            kingGrimeDirection = "LEFT";
        }
    }
}

// Supporting Functions
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufsize;
    coordBufsize.X = 1;
    coordBufsize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufsize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

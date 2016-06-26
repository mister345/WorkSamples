/******************************************************************************************
* File:           Snake.cpp                                                               *
*                                                                                         *
* Author:         Gregory Weiner                                                          *
* Version:        1.0 3.17.2013                                                           *
* Last Modified:  8.12.2013                                                               *
* Copyright:      Free Software (GNU License)                                             *
* Purpose:        This is a console application written in C++ to demonstrate basic game  *
*                 principles such as drawing with nested for loops, game logic loops,     *
*                 branching, and a crude 'sprite' positioning system with simulated       *
*                 orthagonal coordinates.                                                 *
*                                                                                         *
*                 The snake continues moving until its direction is changed by keyboard   *
*                 input (WASD). Points are accrued by colliding with the fruit,           *
*                 which randomly respawns each time it is eaten. Death occurs when        *
*                 the snake collides with its own tail.                                   *
*                                                                                         *
* Requirements:   Win32 Console Application. Visual Studio 2015 Compiler recommended.     *
*                 Requires a functioning keyboard for input.                              *
*                                                                                         *
* Coding Conventions (Prefixes):  g_   global variable                                    *
*                                                                                         *
******************************************************************************************/

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
using namespace std;

// GLOBAL VARIABLES
bool g_gameOver;
int g_score;
const int g_width = 50; // map width
const int g_height = 20; // map height
int g_snakeX, g_snakeY, g_fruitPosX, g_fruitPosY; // fruit spawn position
int g_tailX[100], g_tailY[100]; // array of tail units (actually just coordinates)
int g_nTail; // number of units in tail
enum g_eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
g_eDirection g_dir;

// GLOBAL FUNCTIONS (no classes used in this program)

// Sets GameOver to false, starts snake out stationary at center of map,
// Spawns fruit at random location w/in bounds and initializes score to 0.
void Setup()
{
    g_gameOver = false;
    g_dir = STOP;
    g_snakeX = g_width / 2;
    g_snakeY = g_height / 2;
    g_fruitPosX = rand() % g_width; 
    g_fruitPosY = rand() % g_height;
    g_score = 0;
}

// Draw map, snake (player), and fruit. Will constantly be run via game loop.
void Draw()
{
    // Flag used to balance out extra spaces taken by fruit if it has been drawn
    bool fruitOffset = false;

    system("cls"); // clear console window

    // DRAW TOP BORDER
    for (int i = 0; i < g_width + 2; i++)
        cout << "#";
        cout << endl;

    // DRAW MAP
        for (int i = 0; i < g_height; i++)
        {
            for (int j = 0; j < g_width; j++)
            {
                // DRAW LEFT BORDER
                if (j == 0)
                    cout << "#";

    // DRAW FRUIT
                if ((i == g_fruitPosY && j == g_fruitPosX) ||
                    (i == g_fruitPosY + 1 && j == g_fruitPosX - 1) ||
                    (i == g_fruitPosY + 2 && j == g_fruitPosX - 1))
                {

                    if (i == g_fruitPosY && j == g_fruitPosX)
                    {
                        cout << "|";
                    }
                    if (i == g_fruitPosY + 1 && j == g_fruitPosX - 1)
                    {
                        cout << "WWW";
                        fruitOffset = true; // warn other objects to take this into account
                    }
                    if (i == g_fruitPosY + 2 && j == g_fruitPosX - 1)
                    {
                        cout << "WWW";
                        fruitOffset = true; // warn other objects to take this into account
                    }
                }

    // DRAW SNAKE HEAD
                else if (fruitOffset && i == g_snakeY && j == g_snakeX - 2)
                    cout << "O";

                else if(!fruitOffset && i == g_snakeY && j == g_snakeX)
                    cout << "O";

    // DRAW TAIL
                else if(fruitOffset)
                {
    // this flag checks for displacement of tail if it was drawn
                    bool print = false; 
                    for (int k = 0; k < g_nTail; k++)
                    {
    // Here, in the case of fruitOffset, we must draw 2 units to the left
    // to accomodate fruit displacement
                        if (g_tailX[k] - 2 == j && g_tailY[k] == i) 
                        {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print)
                        cout << " ";
                }
                else
                {
                    bool print = false; // this flag checks for displacement of tail if it was drawn
                        for (int k = 0; k < g_nTail; k++)
                        {
                            if (g_tailX[k] == j && g_tailY[k] == i)
                            {
                                cout << "o";
                                print = true;
                            }
                        }
                    if (!print)
                        cout << " ";
                }
    // DRAW RIGHT BORDER
                if (!fruitOffset) // this offset is needed if the fruit was drawn, which takes 3 spaces.
                {
                    if (g_width - 1 == j) // Right border
                    {
                        cout << "#";
                    }
                }
                else if (fruitOffset)
                {
                    if (g_width - 3 == j) // Right border
                    {
                        cout << "#";
                        fruitOffset = false; // set false so it will check again on next iteration
                        break; // this break is KEY! - otherwise draws an extra layer to the right 
                               // b/c second expression also evaluates to true.
                    }
                }
            }
            cout << endl;
        }

    // BOTTOM BORDER
    for (int i = 0; i < g_width + 2; i++) 
    cout << "#";
    cout << endl;
    cout << "Score:" << g_score << endl;
}

// Keyboard input (WASD)
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            g_dir = LEFT;
            break;
        case 'd':
            g_dir = RIGHT;
            break;
        case 'w':
            g_dir = UP;
            break;
        case 's':
            g_dir = DOWN;
            break;
        case 'x':
            g_gameOver = true;
            break;
        }
    }
}

// Contains primary game logic for movement, 
// getting fruit, point scoring, and death.
void DoLogic()
{
    int prevX = g_tailX[0];
    int prevY = g_tailY[0];
    int prev2X, prev2Y;
    g_tailX[0] = g_snakeX;
    g_tailY[0] = g_snakeY;

    for (int i = 1; i < g_nTail; i++)
    {
        prev2X = g_tailX[i];
        prev2Y = g_tailY[i];
        g_tailX[i] = prevX;
        g_tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (g_dir)
    {
    case LEFT:
        g_snakeX--;
        break;
    case RIGHT:
        g_snakeX++;
        break;
    case UP:
        g_snakeY--;
        break;
    case DOWN:
        g_snakeY++;
        break;
    default:
        break;
    }

    // If snake hits wall, it is transported to far wall
    if (g_snakeX >= g_width) g_snakeX = 0; else if (g_snakeX < 0) g_snakeX = g_width - 1;
    if (g_snakeY >= g_height) g_snakeY = 0; else if (g_snakeY < 0) g_snakeY = g_height - 1;

    // Enable death by snake crashing into its tail
    for (int i = 0; i < g_nTail; i++)
        if (g_tailX[i] == g_snakeX && g_tailY[i] == g_snakeY)
            g_gameOver = true;

    // Enable collision with entire fruit, which occupies 3 lines
    if ((g_snakeY == g_fruitPosY && g_snakeX == g_fruitPosX) ||
        (g_snakeY == g_fruitPosY + 1 && g_snakeX >= g_fruitPosX - 1 && g_snakeX <= g_fruitPosX + 1) ||
        (g_snakeY == g_fruitPosY + 2 && g_snakeX >= g_fruitPosX - 1 && g_snakeX <= g_fruitPosX + 1))
    {
        g_score += 10; // add to score w/ each fruit eaten
        g_fruitPosX = rand() % g_width; // respawn fruit at random position
        g_fruitPosY = rand() % g_height;
        g_nTail++; // if snake eats fruit, add a unit to its tail array
    }
}

// Same logic as draw function; 
// Just draws empty map w/ "GAME OVER"
void DrawGameOver()
{
    system("cls");
    for (int i = 0; i < g_width + 2; i++)
    cout << "#";
    cout << endl;

    bool gameOverDrawn = false; //  works same as fruitOffset

    for (int i = 0; i < g_height; i++)
    {
        for (int j = 0; j < g_width; j++)
        {
            if (j == 0)
                cout << "#";

            if (j == 20 && i == 9)
            {
                cout << "GAME OVER";
                gameOverDrawn = true;
            }

            else
            cout << " ";

            if (!gameOverDrawn)
            {
                if (j == g_width - 1)
                    cout << "#";
            }

            else if (gameOverDrawn)
            {
                if (j == g_width - 9)
                {
                    cout << "#";
                    gameOverDrawn = false;
                    break;
                }
            }
        }
        cout << endl;
    }

    for (int i = 0; i < g_width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << g_score << endl;
}

int main()
{
    // Set GameOver to false, score to 0, spawn snake and fruit
    Setup();
    // Main game loop. Runs until player collides w/ tail
    while (!g_gameOver)
        {
            Draw();
            Input();
            DoLogic();
            Sleep(50);
        }
        DrawGameOver();
    // Stops console window from closing immediately
        cin.get(); 
    return 0;
}
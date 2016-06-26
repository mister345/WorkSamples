/***************************************************************************************
* File:           Pong.cpp                                                             *
*                                                                                      *
* Author:         Gregory Weiner                                                       *
* Version:        1.0 11.20.2013                                                       *
* Last Modified:  3.22.2014                                                            *
* Copyright:      Free Software (GNU License)                                          *
* Purpose:        This is a console application written in C++ to demonstrate basic    *
*                 programming and game concepts such as pointers, friend functions,    *
*                 drawing with nested for loops, game loops, branching, and a crude    *
*                 'sprite' positioning system with simulated orthagonal coordinates.   *
*                                                                                      *
*                 This is a two player game consisting of two paddles, whose up and    *
*                 down movement is controlled by the 'W' and 'S' keys for player 1,    *
*                 and 'I' and 'K' keys for player 2. Pressing 'Q' quits. Points are    *
*                 scored by sending the ball past the opponent's paddle. Ball spawns   *
*                 stationary in the center of the screen. Pressing any key starts the  *
*                 ball moving. This state is reset each time a point is scored.        *
*                                                                                      *
* Requirements:   Win32 Console Application. Visual Studio 2015 Compiler recommended.  *
*                 Requires a functioning keyboard for input.                           *
*                                                                                      *
* Coding Conventions (Prefixes):                                                       *
*                 m_  member variable                                                  *
*                 p   pointer                                                          *
*                                                                                      *
***************************************************************************************/

#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h> // windows Sleep function, more efficient than std version
using namespace std;

// GLOBAL VARIABLES
enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, 
    RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

// This class contains ball functionality; original and new positions, 
// direction enumeration, allowing basic movement across map.
class Ball
{
private:
    // Stores 2 ball positions to allow dynamic updates to trajectory
    int m_x, m_y;
    int m_originalX, m_originalY;
    eDir m_direction;
public:
    Ball(int posX, int posY)
    {
        m_originalX = posX;
        m_originalY = posY;
        m_x = posX; m_y = posY;
        m_direction = STOP;
    }
    void Reset() // reset and stop ball
    {
        m_x = m_originalX; m_y = m_originalY;
        m_direction = STOP;
    }
    void changeDirection(eDir d)
    {
        m_direction = d;
    }
    void randomDirection() // generate random direction
    {
        m_direction = (eDir)((rand() % 6) + 1);
    }
    inline int getX() { return m_x; }
    inline int getY() { return m_y; }
    inline eDir getDirection() { return m_direction; }
    
    // Increment ball's orthagonal coordinates 
    // each frame to change its position
    void Move()
    {
        switch (m_direction)
        {
        case STOP:
            break;
        case LEFT:
            m_x--;
            break;
        case RIGHT:
            m_x++;
            break;
        case UPLEFT:
            m_x--; m_y--;
            break;
        case DOWNLEFT:
            m_x--; m_y++;
            break;       
        case UPRIGHT:
            m_x++; m_y--;
            break;
        case DOWNRIGHT:
            m_x++; m_y++;
            break;
        default:
            break;
        }
    }
    // prints out ball; accessible from other class b/c friend operator overload
    friend ostream & operator << (ostream & stream, Ball ball)
    {
        stream << "Ball [" << ball.m_x << "," << ball.m_y << "][" << ball.m_direction << "]";
        return stream;
    }
};

// Class contains positioning and movement functions for both paddles;
// can be access via overloaded friend operator
class Paddle
{
private:
    int m_x, m_y;
    int m_originalX, m_originalY;
public:
    Paddle()
    {
        m_x = m_y = 0;
    }
    Paddle(int posX, int posY)
    {
        m_originalX = posX;
        m_originalY = posY;
        m_x = posX;
        m_y = posY;
    }
    inline void Reset() { m_x = m_originalX; m_y = m_originalY; }
    inline int getX() { return m_x; }
    inline int getY() { return m_y; }
    inline void moveUp() { m_y--; }
    inline void moveDown() { m_y++; }
    friend ostream & operator << (ostream & o, Paddle paddle)
    {
        o << "Paddle [" << paddle.m_x << "'" << paddle.m_y << "]";
        return o;
    }
};

// This class keeps track of score, draws the screen, paddles, and ball,
// and handles all game logic and keyboard input
class GameManager
{
private:
    int m_width, m_height; // map size
    int m_score1, m_score2;
    char m_up1, m_down1, m_up2, m_down2; // used for key input
    bool m_quit;
    Ball *pBall;
    Paddle *player1;
    Paddle *player2;
public:
    GameManager(int width, int height)
    {
        srand(time(NULL)); // seed random with current time
        m_quit = false;
        m_up1 = 'w'; m_down1 = 's'; // player 1 key bindings
        m_up2 = 'i'; m_down2 = 'k'; // player 2 key bindings
        m_score1 = m_score2 = 0; // player scores start at 0
        m_width = width; m_height = height; // initializes map size
        pBall = new Ball(width / 2, height / 2);
        player1 = new Paddle(1, height / 2 - 3);
        player2 = new Paddle(width - 2, height / 2 - 3);
    }
    GameManager()
    {
	// cleans up after itself by deleting unused pointers
        delete pBall, player1, player2;
    }
    void ScoreUp(Paddle * player)
    {
        if (player == player1) m_score1++;
        else if(player == player2) m_score2++;

        pBall->Reset(); // resets ball each time a point is scored
        // reset player paddles when point is scored
        player1->Reset();
        player2->Reset();
    }
    void Draw()
    {
        system("cls");

        // draw top border using ASCII characters
        for (int i = 0; i < m_width + 2; i++)
            cout << "\xB2";
        cout << endl;

        for (int i = 0; i < m_height; i++)
        {
            for (int j = 0; j < m_width; j++)
            {
                int ballX = pBall->getX();
                int ballY = pBall->getY();
                int player1X = player1->getX();
                int player2X = player2->getX();
                int player1Y = player1->getY();
                int player2Y = player2->getY();
        // draw left border using ASCII characters
                if (j == 0)
                    cout << "\xB2";

                if (ballX == j && ballY == i)
                    cout << "O"; // ball
                else if (player1X == j && player1Y == i)
                    cout << "\xDB"; // player1 paddle
                else if (player2X == j && player2Y == i)
                    cout << "\xDB"; // player2 paddle
         // player1
                else if (player1X == j && player1Y +1 == i)
                    cout << "\xDB"; // player1 paddle
                else if (player1X == j && player1Y +2 == i)
                    cout << "\xDB"; // player1 paddle
                else if (player1X == j && player1Y + 3 == i)
                    cout << '\xDB'; // player1 paddle
         // player2
                else if (player2X == j && player2Y + 1 == i)
                    cout << "\xDB"; // player1 paddle
                else if (player2X == j && player2Y + 2 == i)
                    cout << "\xDB"; // player1 paddle
                else if (player2X == j && player2Y + 3 == i)
                    cout << "\xDB"; // player1 paddle
        // otherwise fill map with empty spaces
                else
                    cout << " ";
        // draw right border using ASCII characters
                if (j == m_width - 1)
                    cout << '\xB2';
            }                
            cout << endl;
        }
        // draw bottom border using ASCII characters
        for (int i = 0; i < m_width + 2; i++)
            cout << '\xB2';
        cout << endl;

        cout << "Score 1: " << m_score1 << endl << "Score 2: " << m_score2 << endl;
    }

// Keyboard Input
    void DoInput() 
    {
        pBall->Move();

        int ballX = pBall->getX();
        int ballY = pBall->getY();
        int player1X = player1->getX();
        int player2X = player2->getX();
        int player1Y = player1->getY();
        int player2Y = player2->getY();

    // Player 1 Controls: 'W','S'
    // Player 2 Controls: 'I','K'
        if (_kbhit())
        {
            char current = _getch();
            if (current == m_up1)
                if (player1Y > 0)
                    player1->moveUp();
            if (current == m_up2)
                if (player2Y > 0)
                    player2->moveUp();
            if (current == m_down1)
                if (player1Y + 4 < m_height)
                    player1->moveDown();
            if (current == m_down2)
                if (player2Y + 4 < m_height)
                    player2->moveDown();

            if (pBall->getDirection() == STOP)
                pBall->randomDirection();
    // 'Q' to quit
            if (current == 'q')
                m_quit = true;
        }
    }

    void DoLogic()
    {
        int ballX = pBall->getX();
        int ballY = pBall->getY();
        int player1X = player1->getX();
        int player2X = player2->getX();
        int player1Y = player1->getY();
        int player2Y = player2->getY();

        //left paddle
        for (int i = 0; i < 4; i++)
            if (ballX == player1X + 1) // when ball hits paddle...
                if (ballY == player1Y + i) // depending on Y position...
                    // use modulus and random then add 4 to randomly produce 4, 5 or 6,
                    // then cast to eDir; changing direction to RIGHT, UPRIGHT or DOWNRIGHT
                    pBall->changeDirection((eDir)((rand() % 3) + 4));

        //right paddle
        for (int i = 0; i < 4; i++)
            if (ballX == player2X - 1) // when ball hits paddle...
                if (ballY == player2Y + i) // depending on Y position...
                    // use modulus and random then add 1 to randomly produce 1, 2 or 3,
                    // then cast to eDir; changing direction to LEFT, UPLEFT or DOWNLEFT
                    pBall->changeDirection((eDir)((rand() % 3) + 1));

        //bottom wall - simply inverts ball's y-axis velocity component
        if (ballY == m_height - 1)
            pBall->changeDirection(pBall->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        //top wall - simply inverts ball's y-axis velocity component
        if (ballY == 0)
            pBall->changeDirection(pBall->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

        // on collision with right or left wall, corresponding players score a point
        //right wall
        if (ballX == m_width - 1)
            ScoreUp(player1);
        //left wall
        if (ballX == 0)
            ScoreUp(player2);
    }
    void Run()
    {
        while (!m_quit)
        {
            Draw();
            DoInput();
            DoLogic();
            Sleep(20);
        }
    }
};

int main()
{   
    GameManager game(40, 20);
    game.Run();
    return 0;
}
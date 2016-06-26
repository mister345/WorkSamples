/************************************************************************************************
* File:           Game.cpp                                                                        *
*                                                                                               *
* Author:         Gregory Weiner                                                                *
* Version:        1.0 8.21.2014                                                                 *
* Last Modified:  11.17.2014                                                                    *
* License:        Free Software (GNU License Included)                                          *
* Purpose:        This is part of a DirectX 9 framework for powering Win32 graphics             *
*                 for 2D games. Many thanks to Chili and his excellent tutorials in             *
*                 game programming with C++ for making this possible.                           *
*                                                                                               *
* Description:    Main game class responsible for main game loop. Detailed implementation       *
*                 is encapsulated in other classes. This is a simple 2D sidescrolling           *
*                 platformer demo I wrote in c++ for Win32. The camera follows the animated     *
*                 sprite as he jumps around the level.Later, I plan to expand it into more      *
*                 robust applications, with level progression and other full-fledged features.  *
*                                                                                               *
* Input:          Arrow keys for movement, Space key to jump.                                   *
*                                                                                               *
* Requirements:   Latest Visual Studio C++ compiler recommended.                                *
*                 Requires a functioning keyboard for input.                                    *
*                 Runs in windowed mode.                                                        *
*                                                                                               *
*************************************************************************************************/
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

Game::Game( HWND hWnd,KeyboardServer& kServer,const MouseServer& mServer )
:	gfx( hWnd ),
	//audio( hWnd ),
	kbd( kServer ),
	mouse( mServer ),
    t(testMap, MAPWIDTH, MAPHEIGHT, TILESIZE, TILESIZE),
    controller(p,kbd),
    port(gfx,RectI(10,590,10,790)),
    cam(port, t.GetBoundaries())
{
    srand( (unsigned int)time( NULL ) );
}

Game::~Game()
{
}

void Game::Go()
{
    controller.Poll(); // input
    p.GetState().OnUpdate(); // state update

    t.DoCollision(p); // collision
    t.DoSupport(p); // floor support
    p.MoveCameraTo(cam);

	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::ComposeFrame()
{
    t.Draw(cam);
    p.Draw(cam);
    gfx.DrawRect(RectI(10.0f, 590.0f, 10.0f, 790.0f), 0, 0, 128);
}
/************************************************************************************************
* File:           Game.h                                                                        *
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
#pragma once

#include "D3DGraphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Timer.h"
#include "SurfaceSequence.h"
#include "TileMap.h"
#include "TestMapString.h"
#include "PlayerSprite.h"
#include "SpriteController.h"
#include "Camera.h"

class Game
{
public:
	Game( HWND hWnd,KeyboardServer& kServer,const MouseServer& mServer );
	~Game();
	void Go();
private:
	void ComposeFrame();
	/********************************/
	/*  User Functions              */

	/********************************/
private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	MouseClient mouse;
	//DSound audio;
	/********************************/
	/*  User Variables              */

    TileMap t;
    PlayerSprite p;
    SpriteController controller;
    Viewport port;
    Camera cam;
	/********************************/
};
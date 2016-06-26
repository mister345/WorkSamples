/***********************************************************************************************
* File:           Game.h                                                                       *
*                                                                                              *
* Author:         Gregory Weiner                                                               *
* Version:        2.0 6.24.2015                                                                *
* Last Modified:  10.11.2015                                                                   *
* License:        Free Software (GNU License Included)                                         *
* Purpose:        This is part of a DirectX 9 framework for powering Win32 graphics            *
*                   for 2D games. Many thanks to Chili and his excellent tutorials in          *
*                   game programming with C++ for making this possible.                        *
*                                                                                              *
* Description:    Main game class responsible for main game loop. Detailed implementation      *
*                 is encapsulated in other classes. This is a simple 2D overhead free-space    *
*                 racing demo that I wrote in c++ for Win32. It features simple thrust/        *
*                 momentum physics, and circular collision detection physics based on Cohen    *
*                 Sutherland algorithms, as well as raster rotation to rotate and draw the     *
*                 space ship, and vertex triangle mesh based drawing to create the map         *
*                 boundaries, all built from scratch. The camera follows the spaceship around  *
*                 the level. Later, I plan to expand it into more robust applications, with a  *
*                 functioning race track, weapons, split screen support, and other features.   *
*                                                                                              *
* Input:          Arrow keys for turning, Space key for thruster.                              *
*                                                                                              *
* Requirements:   Latest Visual Studio C++ compiler recommended.                               *
*                 Requires a functioning keyboard for input.                                   *
*                 Runs in windowed mode.                                                       *
*                                                                                              *
************************************************************************************************/
#pragma once

#include "D3DGraphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "PolyClosed.h"
#include "Camera.h"
#include "Viewport.h"
#include "Ship.h"
#include "Map.h"

class Game
{
public:
	Game( HWND hWnd,KeyboardServer& kServer,MouseServer& mServer );
	~Game();
	void Go();
private:
	void ComposeFrame();
	/********************************/
	/*  User Functions              */

	void UpdateModel( );
	void HandleInput();

	/********************************/
private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	MouseClient mouse;
	/********************************/
	/*  User Variables              */

	Viewport port;
	Camera cam;
	Ship ship;
	Map map;
    float scale = 1.0f;

	/********************************/
};
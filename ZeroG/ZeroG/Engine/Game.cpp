/***********************************************************************************************
* File:           Game.cpp                                                                     *
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
#include "Game.h"
#include "Mat3.h"
#include "TriangleStrip.h"
#include "Vertex.h"
#include <array>

Game::Game( HWND hWnd,KeyboardServer& kServer,MouseServer& mServer )
:	gfx( hWnd ),
	kbd( kServer ),
	mouse( mServer ),
	ship( "shiptry.dxf",{ -2026.0f,226.0f } ),
	map( "map.dxf" ),
	port( gfx,{0,D3DGraphics::SCREENHEIGHT - 1,0,D3DGraphics::SCREENWIDTH - 1} ),
	cam( port,port.GetWidth(),port.GetHeight() )
{
}

Game::~Game()
{
}

void Game::Go()
{
	HandleInput();
	UpdateModel();

	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}


void Game::HandleInput( )
{
	const KeyEvent key = kbd.ReadKey( );
	switch( key.GetCode( ) )
	{
	case VK_LEFT:
		if( key.IsPress( ) )
		{
			ship.Spin( -1.0f );
		}
		else
		{
			ship.StopSpinning( -1.0f );
		}
		break;
	case VK_RIGHT:
		if( key.IsPress( ) )
		{
			ship.Spin( 1.0f );
		}
		else
		{
			ship.StopSpinning( 1.0f );
		}
		break;
	case VK_SPACE:
		if( key.IsPress( ) )
		{
			ship.Thrust( );
		}
		else
		{
			ship.StopThrusting( );
		}
		break;
	}

	switch( mouse.ReadMouse().GetType() )
	{
	case MouseEvent::WheelUp:
		scale *= 1.13;
		break;
	case MouseEvent::WheelDown:
		scale /= 1.13;
		break;
	}
}

void Game::UpdateModel( )
{
#if NDEBUG
	const float dt = timer.GetTimeSec();
	timer.StartWatch();
#else
	const float dt = 1.0f / 60.0f;
#endif

	ship.Update( dt );
	map.HandleCollision( ship );
}

void Game::ComposeFrame()
{
	ship.FocusOn( cam );
	cam.Draw( ship.GetDrawable() );
	cam.Draw( map.GetDrawable() );

    //const Mat3 tranny =
    //    Mat3::Translation({ 400.0f, 300.0f })*
    //    Mat3::Rotation(2 * PI * float(mouse.GetMouseX()) / 800.0f)*
    //    Mat3::Scaling(scale);

    //std::array<Vertex, 4 > quad;

    //gfx.DrawTriangleTex(
    //    quadTrans[0], quadTrans[1], quadTrans[3],
    //    { 0, D3DGraphics::SCREENHEIGHT - 1,0,D3DGraphics::SCREENWIDTH - 1 }, image);
    //gfx.DrawTriangleTex(
    //    quadTrans[1], quadTrans[2], quadTrans[3],
    //    { 0, D3DGraphics::SCREENHEIGHT - 1,0,D3DGraphics::SCREENWIDTH - 1 }, image);

}
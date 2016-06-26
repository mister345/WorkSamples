/***************************************************************************************
* File:           D3DGraphics.h                                                        *
*                                                                                      *
* Author:         Gregory Weiner                                                       *
* Version:        1.0 8.21.2014                                                        *
* Last Modified:  11.17.2014                                                           *
* License:        Free Software (GNU License Included)                                 *
* Purpose:        This is part of a DirectX 9 framework for powering Win32 graphics    *
*                 for 2D games. Many thanks to Chili and his excellent tutorials in    *
*                 game programming with C++ for making this possible.                  *
*                                                                                      *
* Description:    Main graphics class using D3D API. Includes a simple PutPixel()      *
*                 function that takes int values for rgb and outputs a single pixel    *
*                 to the screen. Several more complex vector art functions are built   *
*                 on top of this using trigonometry, such as DrawCircle, DrawDisc,     *
*                 and DrawLine. DrawChar and DrawString are for in-game font loading.  *
*                 DrawSurface is used for sprites.                                     *
*                                                                                      *
*                 BeginFrame() and EndFrame() are the core functions for interacting   *
*                 with the GPU to draw to the final output by locking and unlocking    *
*                 the backbuffer, presenting to the output device, etc. The D3D Device *
*                 is created, and settings such as Swap Effect type initialized, in    *
*                 the constructor.                                                     *
*                                                                                      *
* Requirements:   Latest Visual Studio C++ compiler recommended.                       *
*                 Runs in windowed mode.                                               *
*                                                                                      *
****************************************************************************************/

#pragma once

#include <d3d9.h>
//#include "Rect.h"
#include "RectF.h"
#include "RectI.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 600
#define FILLVALUE 0x30

struct Font
{
	int charWidth;
	int charHeight;
	int nCharsPerRow;
	D3DCOLOR* surface;
};

void LoadFont( Font* font,D3DCOLOR* surface,const char* filename,
	int charWidth,int charHeight,int nCharsPerRow );

class D3DGraphics
{
public:
	D3DGraphics( HWND hWnd );
	~D3DGraphics();
	void PutPixel( int x,int y,int r,int g,int b );
	void PutPixel( int x,int y,D3DCOLOR c );
	D3DCOLOR GetPixel( int x,int y );
	void DrawLine( int x1,int y1,int x2,int y2,int r,int g,int b );
	void DrawCircle( int cx,int cy,int radius,int r,int g,int b );
	void DrawDisc( int cx,int cy,int r,int rd,int g,int b );
	void DrawChar( char c,int x,int y,Font* font,D3DCOLOR color );
	void DrawString( const char* string,int x,int y,Font* font,D3DCOLOR color );
    void DrawSolidRect(RectI rect, D3DCOLOR color, /*const*/ RectI& clippingBox);
    void DrawRect(RectI rect, int r, int g, int b);
    void DrawSurface(D3DCOLOR* pixels, D3DCOLOR key, int width, int height, int x, int y, /*const*/ RectI& clippingBox);
    void BeginFrame();
	void EndFrame();
private:
	IDirect3D9*			pDirect3D;
	IDirect3DDevice9*	pDevice;
	IDirect3DSurface9*	pBackBuffer;
	D3DLOCKED_RECT		backRect;
	D3DCOLOR*			pSysBuffer;
};
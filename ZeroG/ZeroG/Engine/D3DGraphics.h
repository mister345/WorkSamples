/****************************************************************************************
* File:           D3DGraphics.h                                                         *
*                                                                                       *
* Author:         Gregory Weiner                                                        *
* Version:        2.0 6.24.2015                                                         *
* Last Modified:  10.11.2015                                                            *
* License:        Free Software (GNU License Included)                                  *
* Purpose:        This is part of a DirectX 9 framework for powering Win32 graphics     *
*                 for 2D games. Many thanks to Chili and his excellent tutorials in     *
*                 game programming with C++ for making this possible.                   *
*                                                                                       *
* Description:    Main graphics class using D3D API. Includes a simple PutPixel()       *
*                 function that takes int values for rgb and outputs a single pixel     *
*                 to the screen. Several more complex vector art functions are built    *
*                 on top of this using trigonometry, such as DrawCircle, DrawDisc,      *
*                 and DrawLine. More advanced DrawTriangle functions for creating       *
*                 solid meshe sare the beginnings of 3D rendering.                      *
*                                                                                       *
*                 BeginFrame() and EndFrame() are the core functions for interacting    *
*                 with the GPU to draw to the final output by locking and unlocking     *
*                 the backbuffer, presenting to the output device, etc. The D3D Device  *
*                 is created, and settings such as Swap Effect type initialized, in     *
*                 the constructor.                                                      *
*                                                                                       *
* Requirements:   Latest Visual Studio C++ compiler recommended.                        *
*                 Runs in windowed mode.                                                *
*                                                                                       *
*****************************************************************************************/

#pragma once

#include <d3d9.h>
#include "Vec2.h"
#include "Colors.h"
#include "DrawTarget.h"
#include "Surface.h"
#include "Vertex.h"

class D3DGraphics : public DrawTarget
{
public:
	D3DGraphics( HWND hWnd );
	~D3DGraphics();
	void PutPixel( int x,int y,Color c );
	Color GetPixel( int x,int y ) const;
    void PutPixelAlpha(int x, int y, Color c);
	inline void DrawLine( Vec2 pt1,Vec2 pt2,Color c )
	{
		DrawLine( (int)pt1.x,(int)pt1.y,(int)pt2.x,(int)pt2.y,c );
	}
	void DrawLine( int x1,int y1,int x2,int y2,Color c );
	void DrawLineClip( Vec2 p0,Vec2 p1,Color color,const RectF& clip );
	template< typename T >
	inline void DrawCircle( _Vec2< T > center,int radius,Color c )
	{
		DrawCircle( (int)center.x,(int)center.y,radius,c );
	}
	void DrawCircle( int centerX,int centerY,int radius,Color c );
	void BeginFrame();
	void EndFrame();
	virtual void Draw( Drawable& obj ) override
	{
		obj.Rasterize( *this );
	}
	void DrawTriangle( Vec2 v0,Vec2 v1,Vec2 v2,RectI& clip,Color c );
    void DrawTriangleTex(Vertex v0, Vertex v1, Vertex v2, const RectI& clip, const Surface& tex);
public:
	static const unsigned int	SCREENWIDTH =	800;
	static const unsigned int	SCREENHEIGHT =	600;
private:
    void DrawFlatTopTriangleTex(Vertex v0, Vertex v1, Vertex v2, const RectI& clip, const Surface& tex);
    void DrawFlatBottomTriangleTex(Vertex v0, Vertex v1, Vertex v2, const RectI& clip, const Surface& tex);
    void DrawFlatTriangle(float yStart, float yEnd, float m0, float b0, float m1, float b1, RectI& clip, Color c);
private:
    const Color		FILLVALUE =		BLACK;
	IDirect3D9*			pDirect3D;
	IDirect3DDevice9*	pDevice;
	IDirect3DSurface9*	pBackBuffer;
    Surface             sysBuffer;
};
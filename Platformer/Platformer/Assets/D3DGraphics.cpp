/***************************************************************************************
* File:           D3DGraphics.cpp                                                        *
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
***************************************************************************************/

#include "D3DGraphics.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <GdiPlus.h>
#include "Bitmap.h"
#include "FrameTimer.h"
#pragma comment( lib,"gdiplus.lib" )

void LoadFont( Font* font,D3DCOLOR* surface,const char* filename,
	int charWidth,int charHeight,int nCharsPerRow )
{
	LoadBmp( filename,surface );
	font->charHeight = charHeight;
	font->charWidth = charWidth;
	font->nCharsPerRow = nCharsPerRow;
	font->surface = surface;
}

D3DGraphics::D3DGraphics( HWND hWnd )
	:
pDirect3D( NULL ),
pDevice( NULL ),
pBackBuffer( NULL ),
pSysBuffer( NULL )
{
	HRESULT result;

	backRect.pBits = NULL;
	
	pDirect3D = Direct3DCreate9( D3D_SDK_VERSION );
	assert( pDirect3D != NULL );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp,sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

    result = pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,&d3dpp,&pDevice );
	assert( !FAILED( result ) );

	result = pDevice->GetBackBuffer( 0,0,D3DBACKBUFFER_TYPE_MONO,&pBackBuffer );
	assert( !FAILED( result ) );

	pSysBuffer = new D3DCOLOR[ SCREENWIDTH * SCREENHEIGHT ];
}

D3DGraphics::~D3DGraphics()
{
	if( pDevice )
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if( pDirect3D )
	{
		pDirect3D->Release();
		pDirect3D = NULL;
	}
	if( pBackBuffer )
	{
		pBackBuffer->Release();
		pBackBuffer = NULL;
	}
	if( pSysBuffer )
	{
		delete pSysBuffer;
		pSysBuffer = NULL;
	}
}

void D3DGraphics::PutPixel( int x,int y,int r,int g,int b )
{	
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < SCREENWIDTH );
	assert( y < SCREENHEIGHT );
	pSysBuffer[ x + SCREENWIDTH * y ] = D3DCOLOR_XRGB( r,g,b );
}

void D3DGraphics::PutPixel( int x,int y,D3DCOLOR c )
{	
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < SCREENWIDTH );
	assert( y < SCREENHEIGHT );
	pSysBuffer[ x + SCREENWIDTH * y ] = c;
}

D3DCOLOR D3DGraphics::GetPixel( int x,int y )
{
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < SCREENWIDTH );
	assert( y < SCREENHEIGHT );
	return pSysBuffer[ x + SCREENWIDTH * y ];
}

void D3DGraphics::BeginFrame()
{
	memset( pSysBuffer,FILLVALUE,sizeof( D3DCOLOR ) * SCREENWIDTH * SCREENHEIGHT );
}

void D3DGraphics::EndFrame()
{
	HRESULT result;

	result = pBackBuffer->LockRect( &backRect,NULL,NULL );
	assert( !FAILED( result ) );

	for( int y = 0; y < SCREENHEIGHT; y++ )
	{
		memcpy( &((BYTE*)backRect.pBits)[ backRect.Pitch * y ],&pSysBuffer[ SCREENWIDTH * y ],sizeof( D3DCOLOR ) * SCREENWIDTH );
	}

	result = pBackBuffer->UnlockRect();
	assert( !FAILED( result ) );

	result = pDevice->Present( NULL,NULL,NULL,NULL );
	assert( !FAILED( result ) );
}

void D3DGraphics::DrawDisc( int cx,int cy,int r,int rd,int g,int b )
{
	for( int x = cx - r; x < cx + r; x++ )
	{
		for( int y = cy - r; y < cy + r; y++ )
		{
			if( sqrt( (float)( (x - cx)*(x - cx) + (y - cy)*(y - cy) ) ) < r )
			{
				PutPixel( x,y,rd,g,b );
			}
		}
	}
}

void D3DGraphics::DrawLine( int x1,int y1,int x2,int y2,int r,int g,int blu )
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	if( dy == 0 && dx == 0 )
	{
		PutPixel( x1,y1,r,g,blu );
	}
	else if( abs( dy ) > abs( dx ) )
	{
		if( dy < 0 )
		{
			int temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		float m = (float)dx / (float)dy;
		float b = x1 - m*y1;
		for( int y = y1; y <= y2; y = y + 1 ) 
		{
			int x = (int)(m*y + b + 0.5f);
 			PutPixel( x,y,r,g,blu );
		}
	}
	else
	{
		if( dx < 0 )
		{
			int temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		float m = (float)dy / (float)dx;
		float b = y1 - m*x1;
		for( int x = x1; x <= x2; x = x + 1 )
		{
			int y = (int)(m*x + b + 0.5f);
			PutPixel( x,y,r,g,blu );
		}
	}
}

void D3DGraphics::DrawCircle( int centerX,int centerY,int radius,int r,int g,int b )
{
	int rSquared = radius*radius;
	int xPivot = (int)(radius * 0.707107f + 0.5f);
	for( int x = 0; x <= xPivot; x++ )
	{
		int y = (int)(sqrt( (float)( rSquared - x*x ) ) + 0.5f);
		PutPixel( centerX + x,centerY + y,r,g,b );
		PutPixel( centerX - x,centerY + y,r,g,b );
		PutPixel( centerX + x,centerY - y,r,g,b );
		PutPixel( centerX - x,centerY - y,r,g,b );
		PutPixel( centerX + y,centerY + x,r,g,b );
		PutPixel( centerX - y,centerY + x,r,g,b );
		PutPixel( centerX + y,centerY - x,r,g,b );
		PutPixel( centerX - y,centerY - x,r,g,b );
	}
}

void D3DGraphics::DrawChar( char c,int xoff,int yoff,Font* font,D3DCOLOR color )
{
	if( c < ' ' || c > '~' )
		return;

	const int sheetIndex = c - ' ';
	const int sheetCol = sheetIndex % font->nCharsPerRow;
	const int sheetRow = sheetIndex / font->nCharsPerRow;
	const int xStart = sheetCol * font->charWidth;
	const int yStart = sheetRow * font->charHeight;
	const int xEnd = xStart + font->charWidth;
	const int yEnd = yStart + font->charHeight;
	const int surfWidth = font->charWidth * font->nCharsPerRow;

	for( int y = yStart; y < yEnd; y++ )
	{
		for( int x = xStart; x < xEnd; x++ )
		{
			if( font->surface[ x + y * surfWidth ] == D3DCOLOR_XRGB( 0,0,0 ) )
			{
				PutPixel( x + xoff - xStart,y + yoff - yStart,color );
			}
		}
	}
}

void D3DGraphics::DrawString( const char* string,int xoff,int yoff,Font* font,D3DCOLOR color )
{
	for( int index = 0; string[ index ] != '\0'; index++ )
	{
		DrawChar( string[ index ],xoff + index * font->charWidth,yoff,font,color );
	}
}

void D3DGraphics::DrawSolidRect(RectI rect, D3DCOLOR color, /*const*/ RectI & clippingBox)
{
    rect.ClipTo(clippingBox);

    for (int iy = rect.top; iy < rect.bottom; iy++)
    {
        for (int ix = rect.left; ix < rect.right; ix++)
        {
            PutPixel(ix, iy, color);
        }
    }
}

void D3DGraphics::DrawRect(RectI rect, int r, int g, int b)
{
    DrawLine(rect.left, rect.top, rect.right, rect.top, r, g, b);
    DrawLine(rect.right, rect.top, rect.right, rect.bottom, r, g, b);
    DrawLine(rect.right, rect.bottom, rect.left, rect.bottom, r, g, b);
    DrawLine(rect.left, rect.top, rect.left, rect.bottom, r, g, b);
}

void D3DGraphics::DrawSurface(D3DCOLOR* pixels, D3DCOLOR key, int width, int height, int x, int y, /*const*/ RectI& clippingBox)
{
    RectI rect(y, y + height, x, x + width);
    rect.ClipTo(clippingBox);

    const int yStart = rect.top - y; // get source rectangle back
    const int xStart = rect.left - x;
    const int yEnd = rect.bottom - y;
    const int xEnd = rect.right - x;

    for (int iy = yStart; iy < yEnd; iy++)
    {
        for (int ix = xStart; ix < xEnd; ix++)
        {
            D3DCOLOR srcPixel = pixels[ix + iy * width]; 
            if (srcPixel != key)
            {
                // "The object has type qualifiers that prevent a match"
                PutPixel(ix + x, iy + y, srcPixel);
            }
        }
    }

}

/**************************************************************************************
* File:           Bitmap.h                                                            *
*                                                                                     *
* Author:         Gregory Weiner                                                      *
* Version:        1.0 8.21.2014                                                       *
* Last Modified:  11.17.2014                                                          *
* License:        Free Software (GNU License Included)                                *
* Purpose:        This is part of a DirectX 9 framework for powering Win32 graphics   *
*                 for 2D games. Many thanks to Chili and his excellent tutorials in   *
*                 game programming with C++ for making this possible.                 *
*                                                                                     *
* Description:    Allows loading bitmap image files into game.                        *
*                                                                                     *
* Requirements:   Latest Visual Studio C++ compiler recommended.                      *
*                 Requires a functioning keyboard for input. Runs in windowed mode.   *
*                                                                                     *
***************************************************************************************/

#pragma once
#include <d3d9.h>

struct BitmapFileHeader
{             
   unsigned int fileSize;                   
   unsigned short reserved1, reserved2;
   unsigned int offsetToPixelData;                 
};

struct BitmapInfoHeader
{
   unsigned int headerSize;            
   int width,height;
   unsigned short planes;    
   unsigned short bits;      
   unsigned int compression;     
   unsigned int imageSize;       
   int xResolution,yResolution;  
   unsigned int nColors;        
   unsigned int importantColours;
};

struct Pixel24
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

void LoadBmp( const char* filename,D3DCOLOR* surface );
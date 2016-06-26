/**************************************************************************************
* File:           Bitmap.cpp                                                          *
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
**************************************************************************************/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Bitmap.h"
#include <stdio.h>
#include <assert.h>

void LoadBmp( const char* filename,D3DCOLOR* surface )
{
	FILE* bmpFile = fopen( filename,"rb" );
	
	char signature[ 2 ];
	fread( signature,sizeof( char ),2,bmpFile );
	assert(signature[ 0 ] == 'B' && signature[ 1 ] == 'M');

	BitmapFileHeader fileHeader;
	fread( &fileHeader,sizeof( fileHeader ),1,bmpFile );

	BitmapInfoHeader infoHeader;
	fread( &infoHeader,sizeof( infoHeader ),1,bmpFile );

	fseek( bmpFile,fileHeader.offsetToPixelData,SEEK_SET );

	int nPaddingBytesPerRow = (4 - ((infoHeader.width * 3) % 4)) % 4;
	for( int y = infoHeader.height - 1; y >= 0; y-- )
	{
		for( int x = 0; x < infoHeader.width; x++ )
		{
			Pixel24 pixel;
			fread( &pixel,sizeof( pixel ),1,bmpFile );
			surface[ x + y * infoHeader.width ] = D3DCOLOR_XRGB( pixel.red,pixel.green,pixel.blue );
		}
		fseek( bmpFile,nPaddingBytesPerRow,SEEK_CUR );
	}

	fclose( bmpFile );
}

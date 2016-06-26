#pragma once
#include "Surface.h"
#include "Camera.h"
#include <string>
#include <sstream>
#include <iomanip>

class SurfaceSequence
{
public:
	SurfaceSequence( std::wstring basename,unsigned int nSurfaces,unsigned int nHoldFrames,
        int basex, int basey, D3DCOLOR key = D3DCOLOR_XRGB( 255,255,255 ) )
		:
	nSurfaces( nSurfaces ),
	nHoldFrames( nHoldFrames ),
	iCurSurface( 0 ),
	curHoldCount( 0 ),
    basex(basex),
    basey(basey)
	{
		surfaces = new Surface*[ nSurfaces ];
		for( int index = 0; index < nSurfaces; index++ )
		{
			std::wstringstream s;
			s << std::setw( 4 ) << std::setfill( L'0' ) << index;
			surfaces[ index ] = new KeyedSurface( basename + s.str() + std::wstring( L".bmp" ),key );
		}
	}

    SurfaceSequence(Surface** surfaces, unsigned int nSurfaces, 
        unsigned int nHoldFrames, int basex, int basey)
        :
        surfaces(surfaces),
        nSurfaces(nSurfaces), 
        nHoldFrames(nHoldFrames),
        iCurSurface(0),
        curHoldCount(0),
        basex(basex),
        basey(basey) 
    {}
	~SurfaceSequence()
	{
		for( int index = 0; index < nSurfaces; index++ )
		{
			delete surfaces[ index ];
		}

		delete [] surfaces;
	}
	void Draw( int x,int y,Camera& cam ) /*const*/
	{
		surfaces[ iCurSurface ]->Draw( x-basex,y-basey, cam);
	}
	void Advance()
	{
		curHoldCount++;
		if( curHoldCount >= nHoldFrames )
		{
			iCurSurface++;
			iCurSurface %= nSurfaces;
			curHoldCount = 0;
		}
	}
    SurfaceSequence* CloneMirrored() /*const*/
    {
        Surface** mSurfaces = new Surface*[nSurfaces];
        for (int i = 0;i < nSurfaces; i++)
        { 
            mSurfaces[i] = surfaces[i]->CLoneMirrored();
        }
        return new SurfaceSequence(mSurfaces, nSurfaces, nHoldFrames, basex, basey);
    }

private:
	Surface** surfaces;
	const unsigned int nSurfaces;
	const unsigned int nHoldFrames;
	unsigned int iCurSurface;
	unsigned int curHoldCount;
    int basex, basey;
};
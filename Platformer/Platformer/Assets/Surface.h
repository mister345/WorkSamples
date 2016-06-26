#pragma once
#include "D3DGraphics.h"
#include "Camera.h"
#include <string>
#include <GdiPlus.h>
#pragma comment( lib,"gdiplus.lib" )

class Surface
{
public:
    Surface(std::wstring& filename)
    {
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR gdiplusToken;
        Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        Gdiplus::Bitmap bitmap(filename.c_str());
        Gdiplus::Color pixel;

        height = bitmap.GetHeight();
        width = bitmap.GetWidth();
        surface = new D3DCOLOR[height * width];

        for (unsigned int y = 0; y < bitmap.GetHeight(); y++)
        {
            for (unsigned int x = 0; x < bitmap.GetWidth(); x++)
            {
                bitmap.GetPixel(x, y, &pixel);
                surface[x + y * bitmap.GetWidth()] =
                    D3DCOLOR_ARGB(pixel.GetA(), pixel.GetR(), pixel.GetG(), pixel.GetB());
            }
        }
    }
    ~Surface()
    {
        delete[] surface;
    }
    virtual void Draw(int xoff, int yoff, Camera& cam) const
    {
        // DO NOT use this function.
        cam.DrawSurface(surface, D3DCOLOR_XRGB(255, 0, 255), width, height, xoff, yoff);
    }

    virtual Surface* CLoneMirrored() const
    {
        return new Surface(width, height, GetMirroredPixels());
    }

protected:
    D3DCOLOR* GetMirroredPixels() const
    {

        D3DCOLOR* mSurf = new D3DCOLOR[width * height];

        for (unsigned int y = 0; y < height; y++)
        {
            for (unsigned int x = 0; x < width; x++)
            {
                int mx = width - (x + 1);
                mSurf[mx + y*width] =
                    surface[x + y * width];
            }
        }
        return mSurf;
    }

    Surface(unsigned int width, unsigned int height, D3DCOLOR* surf)
        :
        width(width),
        height(height),
        surface(surf)
    {}
protected:
    unsigned int width;
    unsigned int height;
    D3DCOLOR* surface;
};

class KeyedSurface : public Surface
{
public:
	KeyedSurface( std::wstring& filename,D3DCOLOR key )
		:
	Surface( filename ),
	key( key )
	{}

    virtual void Draw( int xoff,int yoff,Camera& cam ) const
	{		
        cam.DrawSurface(surface, key, width, height, xoff, yoff);
	}

    virtual Surface* CLoneMirrored() const
    {
        return new KeyedSurface(width, height, key, GetMirroredPixels());
    }

protected:
    KeyedSurface(unsigned int width, unsigned int height, D3DCOLOR key, D3DCOLOR* surface)
        :
        Surface(width, height, surface),
        key(key)
    {}

private:
	D3DCOLOR key;
};
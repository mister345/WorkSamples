#pragma once

#include "Camera.h"
#include "Surface.h"
//#include "Rect.h"
#include "RectF.h"
#include "RectI.h"

class Tile
{
public:
    Tile(int x, int y, bool passable, D3DCOLOR color);
    virtual ~Tile();
    void Draw(Camera &cam) const;
    bool IsPassable() const
    {
        return passable;
    }

public:
    static void SetWidthAndHeight(int w, int h){width = w;height = h;}

// functions to get location w/in tilemap
    static int GetIndexXBiasRight(float x) { return x / width; }
    static int GetIndexXBiasLeft(float x) 
    {
        // if it divides perfectly, then it falls exactly between tiles;
        // therefore, must decrement ix by one to avoid collision over
        // detection issue.
        int ix = (int)x / width;
        if ((float)(ix * width) == x)
        {
            ix--;
        }
        return ix;
    }
    static int GetIndexYBiasBottom(float y) { return y / height; }
    static int GetIndexYBiasTop(float y)
    {
        int iy = (int)y / height;
        if ((float)(iy * height) == y)
        {
            iy--;
        }
        return iy;
    }

    // tile doesn't actually spawn collision rect (that would be too costly)
    // so must generate it on the fly:
    static RectF GetCRect(int ix, int iy)
    {
        RectF rect((float)(iy*height), (float)((iy + 1) * height),
            (float)(ix*width), (float)((ix + 1)*width));
        return rect;
    }

    static int GetWidth()
    {
        return width;
    }
    static int GetHeight()
    {
        return height;
    }

private:
    int x, y;
    D3DCOLOR color;
    static int width, height;     // these must be also defined in cpp file bc they're static:
    bool passable;
};

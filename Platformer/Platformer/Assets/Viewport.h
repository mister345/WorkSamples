#pragma once

//#include "Rect.h"
#include "RectF.h"
#include "RectI.h"
#include "D3DGraphics.h"

// directly ACCESSES graphics and is ACCESSED BY Camera
class Viewport
{
public:
    Viewport(D3DGraphics& gfx, /*const*/ RectI & port)
        :
        gfx(gfx),
        port(port)
    {}
    void DrawSolidRect(RectI rect, D3DCOLOR color) /*const*/ // bc not changing actual camera here
    {
        rect.Translate(port.left, port.top); 
        gfx.DrawSolidRect(rect, color, port);
    }
    void DrawSurface(D3DCOLOR* pixels, D3DCOLOR key, int width, int height, int x, int y) /*const*/
    {
        gfx.DrawSurface(pixels, key, width, height, x + port.left, y + port.top, port);
    }
    float GetWidth() /*const*/
    {
        return (float)(port.right - port.left);
    }
    float GetHeight() /*const*/
    {
        return (float)(port.bottom - port.top);
    }
private:
    D3DGraphics& gfx;
    RectI port;
};

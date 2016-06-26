#pragma once

//#include "Rect.h"
#include "RectF.h"
#include "RectI.h"
#include "Viewport.h"

// Must transform from World Space > ViewPort Space > Screen Space

class Camera
{
public:
    Camera(/*const*/ Viewport& port, const RectF& boundaries)
        :
        port(port),
        boundaries(boundaries)
    {
        SetPosition(0.0f, 0.0f);
    }
    void DrawSolidRect(RectF rect, D3DCOLOR color) /*const*/ // bc not changing actual camera here
    {
        rect.Translate(-x, -y);
        port.DrawSolidRect(rect, color);
    }
    void DrawSurface(D3DCOLOR* pixels, D3DCOLOR key, int width, int height, float x, float y) const
    {
        port.DrawSurface(pixels, key, width, height, (int)(x - this->x), (int)(y - this->y));
    }
    // transforms from top left to center
    void SetPosition(float nx, float ny)
    {
        x = nx - port.GetWidth() / 2.0f;
        y = ny - port.GetHeight() / 2.0f;
        x = max(x, boundaries.left);
        y = max(y, boundaries.top);
        x = min(x, boundaries.right - port.GetWidth()); // subtract bc x is TOP LEFT corner of camera
        y = min(y, boundaries.bottom - port.GetHeight());
    }

private:
    const RectF boundaries; // must constrain camera to tilemap
    /*const*/ Viewport& port;
    // refer to TOP LEFT CORNER of camera
    float x;
    float y;
};
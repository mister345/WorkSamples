#pragma once

//#include "Rect.h"
#include "RectF.h"
#include "RectI.h"

class CollisionRectF : public RectF
{
public:

    CollisionRectF() {}
    CollisionRectF(/*const*/ CollisionRectF& r)
        :
        RectF(r.top, r.bottom, r.left, r.right),
        vx(r.vx),
        vy(r.vy)
    {}
    CollisionRectF(float top, float bottom, float left, float right, float vx, float vy)
        :
        vx(vx),
        vy(vy)
    {}
    CollisionRectF(/*const*/ RectF& r, float vx = 0.0f, float vy = 0.0f)
        :
        RectF(r.top, r.bottom, r.left, r.right),
        vx(vx),
        vy(vy)
    {}

public:
    float vx;
    float vy;
};
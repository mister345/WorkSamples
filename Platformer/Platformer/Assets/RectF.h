#pragma once

#include "D3DGraphics.h"
#include <list>
#include "RectI.h"
 
class RectF
{
public:
    RectF() {} 
    RectF(float top, float bottom, float left, float right)
        :
        top(top),
        bottom(bottom),
        left(left),
        right(right)
    {}
    RectF(const RectF& rect) //copy constructor
        :
        top(rect.top),
        bottom(rect.bottom),
        left(rect.left),
        right(rect.right)
    {}
    void Translate(float dx, float dy)
    {
        top += dy;
        bottom += dy;
        left += dx;
        right += dx;
    }

    //template<class T2>     // template function
    //operator Rect <T2>()     // user defined conversion
    //{
    //    return Rect<int>((T2)top, (T2)bottom, (T2)left, (T2)right);
    //}

    operator RectI()     // user defined conversion
    {
        RectI rectI((int)top, (int)bottom, (int)left, (int)right);
        return rectI;
    }

    void ClipTo(/*const*/ RectF& rect)
    {
        top = max(top, rect.top);
        bottom = min(bottom, rect.bottom);
        left = max(left, rect.left);
        right = min(right, rect.right);
    }

public:
    float top;
    float bottom;
    float left;
    float right;
};

typedef std::list<RectF> RectFList;

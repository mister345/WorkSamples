#pragma once

#include "D3DGraphics.h"
#include <list>
#include "RectF.h"

class RectI
{
public:
    RectI() {}
    RectI(int top, int bottom, int left, int right)
        :
        top(top),
        bottom(bottom),
        left(left),
        right(right)
    {}
    RectI(const RectI& rect) //copy constructor
        :
        top(rect.top),
        bottom(rect.bottom),
        left(rect.left),
        right(rect.right)
    {}
    void Translate(int dx, int dy)
    {
        top += dy;
        bottom += dy;
        left += dx;
        right += dx;
    }

    //template<class T1>     // template function
    //operator Rect <T1>()     // user defined conversion
    //{
    //    return Rect<int>((T1)top, (T1)bottom, (T1)left, (T1)right);
    //}

    operator RectI()     // user defined conversion
    {
        return RectI((int)top, (int)bottom, (int)left, (int)right);
    }

    void ClipTo(/*const*/ RectI& rect)
    {
        top = max(top, rect.top);
        bottom = min(bottom, rect.bottom);
        left = max(left, rect.left);
        right = min(right, rect.right);
    }

public:
    int top;
    int bottom;
    int left;
    int right;
};

typedef std::list<RectI> RectIList;

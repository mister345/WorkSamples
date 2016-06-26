#pragma once

#include <float.h>

class BiDirection
{
public:
    // copy constructor
    BiDirection(const BiDirection& d)
    {
        dir = d.dir;
    }
    BiDirection()
    {
        dir = Invalid;
    }

    // allows you to create a new Bidirection and feed it to above constructor
    static BiDirection MakeRight()
    {
        BiDirection d;
        d.SetRight();
        return d;
    }
    static BiDirection MakeLeft()
    {
        BiDirection d;
        d.SetLeft();
        return d;
    }

    void SetLeft()
    {
        dir = Left;
    }
    void SetRight()
    {
        dir = Right;
    }

    bool IsLeft()const
    {
        return dir == Left;
    }
    bool IsRight()const
    {
        return dir == Right;
    }
    bool IsValid() const
    {
        return dir != Invalid;
    }
    // overload operators:
    // * reroute the dir enum instances to specific member of rhs object:
    bool operator == (const BiDirection& rhs) const
    {
        return dir == rhs.dir;
    }
    bool operator != (const BiDirection& rhs) const
    {
        return dir != rhs.dir;
    }
    BiDirection& operator = (const BiDirection& rhs)
    {
        dir = rhs.dir;
        return *this;
    }
    BiDirection GetOpposite() const
    {
        BiDirection o;
        if (dir == Left)
        {
            o.SetRight();
        }
        else if (dir == Right)
        {
            o.SetLeft();
        }
        return o;
    }

    void Reverse()
    {
        if (dir == Left)
        {
            SetRight();
        }
        else if (dir == Right)
        {
            SetLeft();
        }
    }
    float Transform(float val) const
    {
        if (dir == Left)
        {
            return val*-1.0f;
        }
        else if (dir == Right)
        {
            return val;
        }
        else
        {
            return _FPCLASS_SNAN;
        }
    }


private:
    enum BiDir
    {
        Left,
        Right,
        Invalid
    } dir;
};
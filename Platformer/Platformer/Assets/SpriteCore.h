#pragma once
#include "BiSurfaceSequence.h"
#include "CollisionRectF.h"

class SpriteCore
{
public:
    CollisionRectF GetCRect() /*const*/
    {
        CollisionRectF rect(cRect, vx, vy);
        rect.Translate(x, y);
        return rect;
    }

public:
    float x, y;     // player position
    float vx, vy;   // player velocity
    BiSurfaceSequence* currentSeq;
    BiSurfaceSequence** seqs;
    // fwd dec
    class SpriteState* state;
    BiDirection dir;
    RectF cRect;
};

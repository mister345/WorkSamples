#pragma once

#include "SpriteState.h"

class PlayerMovingHorizontally : public SpriteState
{
public:
    PlayerMovingHorizontally(SpriteCore& core)
        :
        SpriteState(core)
    {}
    virtual void OnCollision(/*const*/ CollisionRectF& rect);
};

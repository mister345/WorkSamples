#pragma once

#include "SpriteState.h"

class PlayerJumping : public SpriteState
{
public:
    PlayerJumping(SpriteCore& core, bool isMoving, bool hasJumped = true)
        :
        SpriteState(core),
        isMoving(isMoving),
        ay(0.60f),
        sax(0.4f),
        sdx(0.97f), 
        maxsx(7.5f),
        isBoosting(true),
        sdy(0.4f)
    {
        if (hasJumped)
        {
            core.vy = -12.0f; // enables player to fall off ledge
        }
        core.currentSeq = core.seqs[2];
    }
    virtual void OnUpdate();
    virtual void OnCtrlDirPress(BiDirection d);
    virtual void OnCtrlDirRelease(BiDirection d);
    virtual void OnCtrlJumpRelease();
    virtual void OnCollision(/*const*/ CollisionRectF& rect);

protected:
    const float sax; // speed acceleration of x (scalar)
    const float sdx; // speed decay coefficient
    // this is ONLY magnitude, not velocity (does not include direction)
    const float ay;
    const float maxsx;
    bool isMoving;
    bool isBoosting; // Mario style jump physics
    const float sdy; // upwards velocity decay coefficient
};
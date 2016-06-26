#pragma once

#include "SpriteState.h"
#include "PlayerMovingHorizontally.h"

class PlayerStanding :public PlayerMovingHorizontally
{
public:
    PlayerStanding(SpriteCore& core) 
        :
        PlayerMovingHorizontally(core),
        sdx(0.92f)
    {
        core.currentSeq = core.seqs[0];
    }
    virtual void OnCtrlDirPress(BiDirection d);
    virtual void OnCtrlJumpPress();
    virtual void OnUpdate();
    virtual void OnUnsupported();
protected:
    const float sdx; // speed decay coefficient

};

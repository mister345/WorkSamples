#pragma once

#include "SpriteState.h"
#include "PlayerMovingHorizontally.h"

class PlayerRunning : public PlayerMovingHorizontally
{
public:
    PlayerRunning(SpriteCore& core) 
        : 
        PlayerMovingHorizontally(core),
        sax(0.4f),
        maxsx(6.0f)
    {
        core.currentSeq = core.seqs[1];
    }
    virtual void OnUpdate();
    virtual void OnCtrlDirPress(BiDirection d);
    virtual void OnCtrlDirRelease(BiDirection d);
    virtual void OnCtrlJumpPress();
    virtual void OnUnsupported();

protected:
    const float sax;
    const float maxsx;
};

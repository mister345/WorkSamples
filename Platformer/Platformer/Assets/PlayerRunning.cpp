#include "PlayerRunning.h"
#include "PlayerStanding.h"
#include "PlayerJumping.h"

void PlayerRunning::OnUpdate()
{
    core.vx += core.dir.Transform(sax);
    core.vx = min(core.vx, maxsx);
    core.vx = max(core.vx, -maxsx);

    // update position AFTER update velocity
    // otherwise, slide thru wall issue
    core.x += core.vx; 
    
    core.currentSeq->Advance(core.dir);
}

void PlayerRunning::OnCtrlDirPress(BiDirection d)
{
    core.dir = d;
}

void PlayerRunning::OnCtrlDirRelease(BiDirection d)
{
    if (core.dir == d)
    {
        Transition(new PlayerStanding(core));
    }
}

void PlayerRunning::OnCtrlJumpPress()
{
    Transition(new PlayerJumping(core, true));
}

void PlayerRunning::OnUnsupported()
{
    // if player is in a PlayerJumping state, but has NOT jumped,
    // it means he must have fallen off ledge:
    Transition(new PlayerJumping(core, true, false));
}

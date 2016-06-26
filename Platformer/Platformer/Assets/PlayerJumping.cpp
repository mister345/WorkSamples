#include "PlayerJumping.h"
#include "PlayerStanding.h"
#include "PlayerRunning.h"

void PlayerJumping::OnUpdate()
{
    core.vy += ay;
    if (isMoving)
    {
        // constrain vx between maxsx and -maxsx
        core.vx += core.dir.Transform(sax);
        core.vx = min(core.vx, maxsx);
        core.vx = max(core.vx, -maxsx);
    } 
    else   // if not moving
    {
        core.vx *= sdx;
    }
    if (!isBoosting && core.vy < 0.0f)
    {
        core.vy *= sdy;
    }

    // had to move this down BELOW velocity to stop from getting stuck in tiles
    core.x += core.vx;
    core.y += core.vy;

    if (core.vy >= 0.0f)
    {
        core.currentSeq = core.seqs[3];
    }
}

// must be adjusted to floorY value

void PlayerJumping::OnCtrlDirRelease(BiDirection d)
{
    if (core.dir == d)
    {
        isMoving = false;
    }
}

void PlayerJumping::OnCtrlDirPress(BiDirection d)
{
        core.dir = d;
        isMoving = true;
}

void PlayerJumping::OnCtrlJumpRelease()
{
    isBoosting = false;
}

void PlayerJumping::OnCollision(/*const*/ CollisionRectF & rect)
{
    CollisionRectF sRect = core.GetCRect();
    if (core.vx > 0.0f)
    {
        if (core.vy > 0.0f)
        {
            float px = sRect.right - rect.left;
            float py = sRect.bottom - rect.top;
            // this formula determines whether side or top collision
            if (core.vy*px > core.vx*py)
            {
                //top collision
                core.vy = 0.0f;
                core.y -= py;
                if (isMoving)
                {
                    Transition(new PlayerRunning(core));
                }
                else
                {
                    Transition(new PlayerStanding(core));
                }
            }
            else // core.vy * px > core.vx * py
            {
                // side collision
                core.vx = 0.0f;
                core.x -= px;
            }
        }
        else  // core.vy > 0.0f
        {
            float px = sRect.right - rect.left;
            float py = sRect.bottom - sRect.top;
            if ((-core.vy)*px > core.vx*py)
            {
                //top collision
                core.vy = 0.0f;
                core.y += py;
            }
            else // core.vy * px > core.vx * py
            {
                // side collision
                core.vx = 0.0f;
                core.x -= px;
            }
        }
    }
    else // core.vx < 0.0f
    {
        if (core.vy > 0.0f)
        {
            float px = rect.right - sRect.left;
            float py = sRect.bottom - rect.top;
            if (core.vy*px > (-core.vx)*py)
            {
                //top collision
                core.vy = 0.0f;
                core.y -= py;
                if (isMoving)
                {
                    Transition(new PlayerRunning(core));
                }
                else
                {
                    Transition(new PlayerStanding(core));
                }
            }
            else // core.vy * px > core.vx * py
            {
                // side collision
                core.vx = 0.0f;
                core.x += px;
            }
        }
        else  // core.vy > 0.0f
        {
            float px = rect.right - sRect.left;
            float py = rect.bottom - sRect.top;
            if ((-core.vy)*px > (-core.vx)*py)
            {
                //top collision
                core.vy = 0.0f;
                core.y += py;
            }
            else // core.vy * px > core.vx * py
            {
                // side collision
                core.vx = 0.0f;
                core.x += px;
            }
        }
    }
}

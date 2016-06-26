#include "PlayerMovingHorizontally.h"

void PlayerMovingHorizontally::OnCollision(/*const*/ CollisionRectF& rect)
{
    if (core.vx > 0)
    {
        core.x -= core.GetCRect().right - rect.left;
        core.vx = 0.0f;
    }
    else
    {
        core.x += rect.right - core.GetCRect().left,
            core.vx = 0.0f;
    }
}

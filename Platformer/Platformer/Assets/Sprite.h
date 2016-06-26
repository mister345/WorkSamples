#pragma once
#include "SpriteCore.h"
#include "Camera.h"

class Sprite
{
public:
    void Draw(Camera& cam) /*const*/;
       virtual ~Sprite() {}
       SpriteState& GetState() { return *(core.state); }
       CollisionRectF GetCRect() /*const*/
       {
           return core.GetCRect(); // allow top level access to collision rectangle
       }
       void MoveCameraTo(Camera& cam)
       {
           cam.SetPosition(core.x, core.y - 80.0f);
       }

protected:
    SpriteCore core;
};

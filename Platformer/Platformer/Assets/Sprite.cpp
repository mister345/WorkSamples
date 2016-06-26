#include "Sprite.h"

void Sprite::Draw(Camera& cam) /*const*/
{
    core.currentSeq->Draw(core.x, core.y, core.dir, cam);
} 
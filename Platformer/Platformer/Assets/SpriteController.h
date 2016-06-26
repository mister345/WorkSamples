#pragma once

#include "Sprite.h"
#include "SpriteState.h"
#include "Keyboard.h"

class SpriteController
{
public:
    SpriteController(Sprite& sprite, KeyboardClient& kbd)
        :
        sprite(sprite),
        kbd(kbd)
    {}
    void Poll();

protected:
    Sprite& sprite;
    KeyboardClient& kbd;
};

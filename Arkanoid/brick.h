#pragma once
#include "actor.h"

class Brick :
    public Actor
{
public:
    Brick(int x, int y);

    Brick(Sprite* sprite, int x, int y);
};


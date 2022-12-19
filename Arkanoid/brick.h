#pragma once
#include "actor.h"

class Brick :
    public Actor
{
public:
    Brick(int x, int y);

    Brick(const char* sprite, int x, int y);

    virtual void tick();
};


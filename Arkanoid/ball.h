#pragma once
#include "actor.h"

class Ball :
    public Actor
{
    void bounce();

    void bounceFromBricks();

    void bounceFromPlatform();

    void bounceFromBarrier();
public:

    bool isOut();

    Ball(int x, int y);

    void tick();

    void launch(int xdir, int ydir);
};


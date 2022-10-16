#pragma once
#include "actor.h"

class Ball :
    public Actor
{
    bool bounce();

    void bounceFromBricks();

    bool bounceFromPlatform();

    void bounceFromBarrier();
public:

    bool isOut();

    Ball(int x, int y);

    bool tick();

    void launch(int xdir, int ydir);
};


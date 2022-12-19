//work in progress
#pragma once
#include "brick.h"
class MovingBrick :
    public Brick
{
    //orientation: 0 - horisontal, 1 - vertical
    //value of an end is always bigger then start. Yes, it means that a brick can spawn at the end
    //of their trajectory if it moves towards decreasing coordinates at spawn
    int start, end, orientation;

public:
    MovingBrick(int startx, int starty, int orient, int distance);

    void tick();
};


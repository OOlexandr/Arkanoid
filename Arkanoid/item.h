#pragma once
#include "actor.h"
class Item :
    public Actor
{
public:
    Item(int type, int x, int y);

    bool isCaught();

    bool isOut();

    int powerup;
};


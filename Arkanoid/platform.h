#pragma once
#include "actor.h"
class Platform :
    public Actor
{
    vector<Sprite*> spritesList{};
    int spritei;
    float spriteFrame;

public:
    Platform();

    void setSpeed(int speed);

    void tick();
};


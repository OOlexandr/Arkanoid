#include <time.h>
#include "actor.h"

Actor::Actor(const char* spritePath, int x, int y, int width, int height)
{
    sprite = createSprite(spritePath);
    setSpriteSize(sprite, width, height);
    xpos = x;
    ypos = y;
    timeFrame = getTickCount() / 1000.0;
}

void Actor::move()
{
    float newFrame = getTickCount() / 1000.0;
    float timePassed = newFrame - timeFrame;
    xpos += xspeed * timePassed;
    ypos += yspeed * timePassed;
    timeFrame = newFrame;
}

void Actor::tick()
{
    move();
    drawSprite(sprite, int(xpos), int(ypos));
}

Actor::~Actor()
{
    destroySprite(sprite);
}

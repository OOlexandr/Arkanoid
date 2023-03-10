#pragma once
#define _WINDOWS
#include "Framework.h"
#include "gamestate.h"

class Actor
{
public:

	Actor(const char* spritePath, int x, int y, int width, int height);

	virtual void move();

	virtual void tick();

	~Actor();

//private:
	Sprite* sprite;
	float xpos, ypos, xspeed, yspeed, width, height;
	float timeFrame;
};


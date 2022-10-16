#include "brick.h"

Brick::Brick(int x, int y) :Actor(BrickSprite, x, y, BrickWidth, BrickHeight)
{
	coordinates coord;
	coord.x = xpos; coord.y = ypos;
	bricksList.push_back(coord);
}

Brick::Brick(Sprite* sprite, int x, int y) :Actor(sprite, x, y, BrickWidth, BrickHeight)
{
	coordinates coord;
	coord.x = xpos; coord.y = ypos;
	bricksList.push_back(coord);
}

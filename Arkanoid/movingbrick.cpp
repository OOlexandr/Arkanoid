#include "movingbrick.h"

MovingBrick::MovingBrick(int startx, int starty, int orient, int distance) 
			:Brick(MovingBrickSprite, startx, starty)
{
	orientation = orient;
	if (orientation == 0)
	{
		start = startx;
		xspeed = MovingBrickSpeed;
	}
	else
	{
		start = starty;
		yspeed = MovingBrickSpeed;
	}
	end = start + distance;
	if (end < start)
	{
		int temp = end;
		end = start;
		start = temp;
		
		xspeed *= -1;
		yspeed *= -1;
	}
}

void MovingBrick::tick()
{
	__super::tick();
	if (orientation == 0)
	{
		if (xpos<=start)
		{
			xspeed *= -1;
			xpos = start + 1;
		}
		else if (xpos >= end)
		{
			xspeed *= -1;
			xpos = end - 1;
		}
	}
	else
	{
		if (ypos<=start)
		{
			yspeed *= -1;
			ypos = start + 1;
		}
		else if (ypos >= end)
		{
			yspeed *= -1;
			ypos = end - 1;
		}
	}
}

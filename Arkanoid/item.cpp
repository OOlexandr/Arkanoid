#include "item.h"

Item::Item(int type, int x, int y) :Actor::Actor(ItemsSprites[type], x, y, BrickWidth, BrickHeight)
{
	powerup = type;
	yspeed = ItemFallSpeed;
}

bool Item::isCaught()
{
	return (ypos + BrickHeight >= Height - PlatformHeight) &&
		((xpos>=platformPosition && xpos<=platformPosition+PlatformWidth)|| 
			(xpos + BrickWidth >= platformPosition && xpos + BrickWidth <= platformPosition + PlatformWidth));
}

bool Item::isOut()
{
	return ypos >= Height;
}

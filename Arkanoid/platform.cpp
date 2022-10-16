#include "platform.h"

Platform::Platform():Actor(PlatformSprites[0], (Width - PlatformWidth) / 2,
		Height - PlatformHeight, PlatformWidth, PlatformHeight)
{
	for (int i = 0; i < PlatformSprites.size(); i++)
	{
		spritesList.push_back(createSprite(PlatformSprites[i]));
		setSpriteSize(spritesList[i], PlatformWidth, PlatformHeight);
	}
	spritei = 0;
	spriteFrame = getTickCount();
}

void Platform::setSpeed(int speed)
{
	xspeed = speed;
}

void Platform::tick()
{
	if (getTickCount() - spriteFrame > 0.1)
	{
		spritei = (spritei == PlatformSprites.size() - 1) ? 0 : spritei + 1;
		sprite = spritesList[spritei];
		spriteFrame = getTickCount();
	}

	Actor::tick();
	if (xpos < 0)
	{
		xpos = 0;
	}
	if (xpos + PlatformWidth > Width)
	{
		xpos = Width - PlatformWidth;
	}
	platformPosition = xpos;
}

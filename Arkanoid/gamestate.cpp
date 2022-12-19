#include "gamestate.h"

int Width = 407;
int Height = 400;
int BallDiameter = 15;
int BallSpeed = 200;
int BallsAmount = 1;
float TimeBetweenLaunches = 1;
int BrickWidth = 34;
int BrickHeight = 17;
int PlatformWidth = 70;
int PlatformHeight = 17;
int PlatformSpeed = 200;
int ItemFallSpeed = 50;
int BallStartX = (Width - BallDiameter) / 2;
int BallStartY = Height - PlatformHeight - 1.5 * BallDiameter;
int MovingBrickSpeed = 100;

const char* BallSprite = "data/63-Breakout-Tiles.png";
const char* BrickSprite = "data/01-Breakout-Tiles.png";
vector<const char*> PlatformSprites{ "data/50-Breakout-Tiles.png", "data/51-Breakout-Tiles.png",
									"data/52-Breakout-Tiles.png" };
vector<const char*> ItemsSprites{ "data/48-Breakout-Tiles.png", "data/45-Breakout-Tiles.png" };
const char* BackgroundSprite = "data/background.jpeg";
const char* BarrierSprite = "data/barrier.png";
const char* MovingBrickSprite = "data/05-Breakout-Tiles.png";

vector<coordinates> bricksList = vector<coordinates>();

int platformPosition = (Width - PlatformWidth) / 2;

bool barrierUp = false;

bool ballOnPlatform = false;

bool ballLineIntersection(coordinates ball, int r, coordinates end1, coordinates end2)
{
	if (end1.x == end2.x)
	{
		int dist = abs(ball.x - end1.x);
		if (dist > r)
			return false;
		if (dist == r)
			return ball.y >= end1.y && ball.y <= end2.y;
		else
		{
			int y1 = ball.y + sqrt(r * r - dist * dist);
			int y2 = ball.y - sqrt(r * r - dist * dist);
			return (y1 >= end1.y && y1 <= end2.y) || (y2 >= end1.y && y2 <= end2.y);
		}
	}
	else
	{
		int dist = abs(ball.y - end1.y);
		if (dist > r)
			return false;
		if (dist == r)
			return ball.x >= end1.x && ball.x <= end2.x;
		else
		{
			int x1 = ball.x + sqrt(r * r - dist * dist);
			int x2 = ball.x - sqrt(r * r - dist * dist);
			return (x1 >= end1.x && x1 <= end2.x) || (x2 >= end1.x && x2 <= end2.x);
		}
	}
}

void scale(int w, int h)
{
	float wscale = float(w) / Width;
	float hscale = float(h) / Height;
	Width *= wscale;
	Height *= hscale;
	BallDiameter *= min(wscale,hscale);
	BallSpeed *= min(wscale, hscale);
	BrickWidth *= wscale;
	BrickHeight *= hscale;
	PlatformWidth *= wscale;
	PlatformHeight *= hscale;
	PlatformSpeed *= wscale;
	ItemFallSpeed *= hscale;
	BallStartX = (Width - BallDiameter) / 2;
	BallStartY = Height - PlatformHeight - BallDiameter;
	platformPosition = (Width - PlatformWidth) / 2;
}
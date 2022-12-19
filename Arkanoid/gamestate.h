#pragma once
#include <vector>

using namespace std;

extern int Width;
extern int Height;
extern int BallDiameter;
extern int BallSpeed;
extern int BallStartX;
extern int BallStartY;
extern int BallsAmount;
extern float TimeBetweenLaunches;
extern int BrickWidth;
extern int BrickHeight;
extern int PlatformWidth;
extern int PlatformHeight;
extern int PlatformStartPosition;
extern int PlatformSpeed;
extern int ItemFallSpeed;
extern int MovingBrickSpeed;

extern const char* BallSprite;
extern const char* BrickSprite;
extern vector<const char*> PlatformSprites;
extern vector<const char*> ItemsSprites;
extern const char* BackgroundSprite;
extern const char* BarrierSprite;
extern const char* MovingBrickSprite;

struct coordinates
{
	int x;
	int y;
};

extern vector<coordinates> bricksList;

extern int platformPosition;

extern bool barrierUp;

extern bool ballOnPlatform;

bool ballLineIntersection(coordinates ball, int r, coordinates end1, coordinates end2);

void scale(int w, int h);
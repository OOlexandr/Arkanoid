#include "gamerules.h"
#include <random>
#include <ctime>

void MyFramework::powerUpBarrier()
{
	if (!barrierUp)
	{
		barrier = new Barrier();
		barrierUp = true;
	}
}

void MyFramework::powerUpDamage()
{
	delete platform;
	platform = 0;
	platformPosition = Width;
}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	width = Width;
	height = Height;
	fullscreen = false;
}

bool MyFramework::Init()
{
	srand(time(0));
	background = createSprite(BackgroundSprite);
	setSpriteSize(background, Width, Height);

	for (int i = 0; i < BallsAmount; i++)
	{
		balls.push_back(new Ball(BallStartX, BallStartY));
	}

	bricks.push_back(new Brick(0, 0));
	bricks.push_back(new Brick(BrickWidth, 0));
	bricks.push_back(new Brick(BrickWidth * 2, 0));

	platform = new Platform();
	return true;
}

void MyFramework::Close()
{
	delete platform;
	for (int i = 0; i < bricks.size(); i++)
	{
		delete bricks[i];
	}
	bricks.clear();
	bricksList.clear();

	for (int i = 0; i < balls.size(); i++)
	{
		delete balls[i];
	}
	balls.clear();

	for (int i = 0; i < itemBoxes.size(); i++)
	{
		delete itemBoxes[i];
	}
	itemBoxes.clear();

	gameStarted = false;
	ballsLaunched = 0;
	platformMovementDirection = 0;
	delete barrier;
	barrierUp = false;
}

bool MyFramework::Tick()
{
	drawSprite(background, 0, 0);

	for (int i = 0; i < bricks.size(); i++)
	{
		while (i < bricks.size() && bricksList[i].x < 0)
		{
			bricksList.erase(bricksList.begin() + i);
			delete bricks[i];
			bricks.erase(bricks.begin() + i);
		}
		if (i < bricks.size())
		{
			bricks[i]->tick();
		}
	}

	if (ballsLaunched > 0 && ballsLaunched < BallsAmount)
	{
		if (getTickCount() / 1000.0 - LastLaunch >= TimeBetweenLaunches)
		{
			balls[ballsLaunched]->launch(launchDirectionx, launchDirectiony);
			ballsLaunched += 1;
			LastLaunch = getTickCount() / 1000.0;
		}
	}

	if (barrier != 0)
	{
		barrier->tick();
		if (!barrierUp)
		{
			delete barrier;
			barrier = 0;
		}
	}

	bool onPlatform = false;
	for (int i = 0; i < balls.size(); i++)
	{
		onPlatform = (balls[i]->tick()) ? true : onPlatform;
		if (balls[i]->isOut())
		{
			delete balls[i];
			balls.erase(balls.begin() + i);
			i--;
		}
	}

	if (platform)
	{
		platform->tick();
	}


	if (gameStarted)
	{
		if (rand() % 10000 == 0)
		{
			itemBoxes.push_back(new Item(rand() % 2, rand() % (Width - BrickWidth), rand() % (Height / 2)));
		}
	}

	for (int i = 0; i < itemBoxes.size(); i++)
	{
		while (i < itemBoxes.size() && (itemBoxes[i]->isCaught() || itemBoxes[i]->isOut()))
		{
			if (!itemBoxes[i]->isOut())
			{
				if (itemBoxes[i]->powerup == 0)
				{
					powerUpBarrier();
				}
				else
				{
					powerUpDamage();
				}
			}
			delete itemBoxes[i];
			itemBoxes.erase(itemBoxes.begin() + i);
		}
		if (i < itemBoxes.size())
		{
			itemBoxes[i]->tick();
		}
	}

	if ((onPlatform && bricks.empty()) || balls.empty())
	{
		restart();
	}

	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	showCursor(true);
	coursorx = x;
	coursory = y;
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
	if (!gameStarted)
	{
		launchDirectionx = coursorx;
		launchDirectiony = coursory;
		balls[0]->launch(launchDirectionx, launchDirectiony);
		LastLaunch = getTickCount() / 1000.0;
		gameStarted = true;
		ballsLaunched = 1;
	}
}

void MyFramework::onKeyPressed(FRKey k)
{
	if (gameStarted && platform)
	{
		if (k == FRKey::RIGHT)
		{
			platformMovementDirection++;
		}
		else if (k == FRKey::LEFT)
		{
			platformMovementDirection--;
		}
		platform->setSpeed(PlatformSpeed * platformMovementDirection);
	}
}

void MyFramework::onKeyReleased(FRKey k)
{
	if (gameStarted && platform)
	{
		if (k == FRKey::RIGHT)
		{
			platformMovementDirection--;
		}
		else if (k == FRKey::LEFT)
		{
			platformMovementDirection++;
		}
		platform->setSpeed(PlatformSpeed * platformMovementDirection);
	}
}

const char* MyFramework::GetTitle()
{
	return "Arcanoid";
}

void MyFramework::restart()
{
	Close();
	Init();
}

void MyFramework::loadLevel()
{
	//It is not in the task, but i want it. It's pretty.
}

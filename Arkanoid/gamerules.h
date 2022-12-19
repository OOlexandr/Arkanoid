#pragma once
#include "ball.h"
#include "brick.h"
#include "movingbrick.h"
#include "platform.h"
#include "item.h"
#include "barrier.h"
#include "Framework.h"

class MyFramework : public Framework {

public:
	Sprite* background;
	vector<Brick*> bricks{};
	vector<Ball*> balls{};
	Platform* platform;
	vector<Item*> itemBoxes{};
	Barrier* barrier = 0;

	bool gameStarted = false;
	int ballsLaunched = 0;
	float LastLaunch = 0;
	int launchDirectionx, launchDirectiony;
	int platformMovementDirection = 0;

	int coursorx = 0, coursory = 0;

	void powerUpBarrier();

	void powerUpDamage();

	virtual void PreInit(int& width, int& height, bool& fullscreen);

	virtual bool Init();

	virtual void Close();

	virtual bool Tick();

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);

	virtual void onKeyPressed(FRKey k);

	virtual void onKeyReleased(FRKey k);

	virtual const char* GetTitle() override;

	void restart();

	void loadLevel();
};
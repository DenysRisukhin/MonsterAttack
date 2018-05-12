#pragma once

#include "Global.h"

struct Time
{
	u32 lastTime;
	u32 now;
	u32 lastFire;
	u32 lastStep;
	u32 lastEnemyFire;
	f32 delta;
	u32 totalTime;
	u32 pauseTime;
	u32 lastFrame;

	void zeroTimes()
	{
		lastTime = 0;
		now = 0;
		lastFire = 0;
		lastStep = 0;
		lastEnemyFire = 0;
		totalTime = 0;
		pauseTime = 0;
		lastFrame = 0;
	}

	void addDelta(u32 delta)
	{
		lastTime += delta;
		lastFire += delta;
		lastStep += delta;
		lastEnemyFire += delta;
		totalTime += delta;
		lastFrame += delta;
	}
};

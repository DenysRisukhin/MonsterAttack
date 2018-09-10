#pragma once

#include "IrrLicht.h"
#include "GameObject.h"

#define PLAYER_CANON_MARGIN		8

#define PLAYER_SPEED			200
#define PLAYER_FIRE_TIME		400
#define PLAYER_DAMAGE			10

#define PLAYER_ROTATION		{ 0, 270, 180 }

enum playerState
{
	IDLE,
	ATTACK,
	RUNNING
};

class Player : public GameObject
{

private:
	playerState pState;

public:

	Player();

	bool move(f32 delta);
	vector3df fire();

	void setIdleAnimation();
	void setRunningAnimation();
	void setAttackAnimation();

};

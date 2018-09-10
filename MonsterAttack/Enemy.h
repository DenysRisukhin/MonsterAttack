#pragma once

#include "IrrLicht.h"
#include "GameObject.h"
#include "TextureManager.h"

enum EnemyType
{
	ENEMY0 = 0,
	ENEMY1,
	ENEMY2,
	ENEMY3,
	ENEMY4
};

enum Damage
{
	DAMAGE0 = 30,
	DAMAGE1 = 40,
	DAMAGE2 = 60,
	DAMAGE3 = 100,
	DAMAGE4 = 70
};

#define NINJA_ROTATION	{ 0, 180, 180 }
#define NINJA_SCALE		{ 6, 6, 6 }

#define ENEMY_TYPE_COUNT		5     
#define ENEMY_STEP_TIME			1500
#define ENEMY_FIRE_TIME			1000
#define ENEMY_STEP_SIZE			5
#define ENEMY_SPEED				50
#define ENEMY_ROTATION			{0.f, 90.f, 180.f}
#define ENEMY_ROTATION_SPEED	{ 0.f, 0.f, 0.f }

// Destroyed enemy move behind the screen
#define ENEMY_OUT_OF_FIELD		{ 0.f, 0.f, -500.f }

class Enemy : public GameObject
{

private:

	EnemyType type;
	Damage ownDamage;

	// Rectangle with float values
	rectf limits;
	Direction direction;

public:

	Enemy();
	Enemy(ISceneManager *manager, TextureManager *&texManager, u32 curType, Direction dir, vector3df position, rectf newLimits);

	EnemyType getType() const;
	Damage getDamage() const;
	rectf getLimits() const;
	Direction getDirection() const;

	void setType(const EnemyType newType);
	void setDamage(const Damage newDamage);
	void setLimits(const rectf newPath);
	void setDirection(const Direction newDirection);

	void moveFromField();
	void deathAnimation();
	bool move(f32 delta);
};
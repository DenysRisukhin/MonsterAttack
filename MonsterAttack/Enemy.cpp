#include "Enemy.h"

Enemy::Enemy() : GameObject(), type(ENEMY0), ownDamage(DAMAGE0), limits({}), direction(RIGHT)
{
}

Enemy::Enemy(ISceneManager *manager, TextureManager *&texManager, u32 curType, Direction dir, vector3df position, rectf newLimits) : GameObject()
{
	path name = "models/";
	u32 index = 0;
	switch (curType)
	{
	case ENEMY0:
		name += "faerie.md2";
		type = ENEMY0;
		ownDamage = DAMAGE0;
		index = 0;
		break;
	case ENEMY1:
		name += "faerie.md2";
		type = ENEMY1;
		ownDamage = DAMAGE1;
		index = 1;
		break;
	case ENEMY2:
		name += "ninja.b3d";
		type = ENEMY2;
		ownDamage = DAMAGE2;
		index = 2;
		break;
	case ENEMY3:
		name += "ninja.b3d";
		type = ENEMY3;
		ownDamage = DAMAGE3;
		index = 3;
		break;
	case ENEMY4:
		name += "lostsoul1.md2";
		type = ENEMY4;
		ownDamage = DAMAGE4;
		index = 4;
		break;
	}

	this->name = name;
	if (!createNode(manager))
		return;

	limits = newLimits;
	direction = dir;
	node->setPosition(position);
	node->setRotation(ENEMY_ROTATION);
	node->setMD2Animation(EMAT_ATTACK);
	node->setAnimationSpeed(20);
	//node->addAnimator(manager->createRotationAnimator(ENEMY_ROTATION_SPEED));
	node->setMaterialTexture(0, texManager->getEnemyTexture()[index]);

	if (curType == ENEMY2 || curType == ENEMY3) {
		node->setScale(NINJA_SCALE);
		node->setRotation(NINJA_ROTATION);
		node->setFrameLoop(1, 13);
		node->setAnimationSpeed(5);
	}
}

void Enemy::deathAnimation() {
	node->setMD2Animation(EMAT_DEATH_FALLFORWARD);
	node->setAnimationSpeed(20);
}

EnemyType Enemy::getType() const
{
	return type;
}

Damage Enemy::getDamage() const
{
	return ownDamage;
}

rectf Enemy::getLimits() const
{
	return limits;
}

Direction Enemy::getDirection() const
{
	return direction;
}


void Enemy::setType(const EnemyType newType)
{
	type = newType;
}

void Enemy::setDamage(const Damage newDamage)
{
	ownDamage = newDamage;
}

void Enemy::setLimits(rectf newLimits)
{
	limits = newLimits;
}

void Enemy::setDirection(Direction newDirection)
{
	direction = newDirection;
}

void Enemy::moveFromField()
{
	node->removeAnimators();
	animators.clear();
	collisions.clear();
	node->setPosition(ENEMY_OUT_OF_FIELD);
}

bool Enemy::move(f32 delta)
{
	vector3df pos = node->getPosition();
	if (direction != LEFT)
	{
		switch (direction)
		{
		case DOWN:
			pos.X -= delta * ENEMY_SPEED;
			break;
		case UP:
			pos.X += delta * ENEMY_SPEED;
			break;
		}

		if (pos.X < -200)
		{
			pos.X = -200;
			direction = UP;
		}
		else if (pos.X > 200)
		{
			pos.X = 200;
			direction = DOWN;
		}

	}
	else
	{
		pos.Z -= ENEMY_STEP_SIZE;
		if (pos.Z < -300) {
			
			return true;
		}
	}
	node->setPosition(pos);
	return false;
}
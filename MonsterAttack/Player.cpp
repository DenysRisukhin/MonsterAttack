#include "Player.h"

Player::Player() : GameObject()
{
}

bool Player::move(f32 delta)
{
	vector3df pos = node->getPosition();
	f32 path = PLAYER_SPEED * delta;
	pos.X += path;

	node->setPosition(pos);
	return false;
}

vector3df Player::fire()
{
	vector3df pos = node->getPosition();

	return pos;
}

void Player::setIdleAnimation()
{
	if (pState != playerState::IDLE)
	{
		node->setMD2Animation(EMAT_STAND);
		node->setAnimationSpeed(30);
		pState = playerState::IDLE;
	}
}

void Player::setRunningAnimation()
{
	if (pState != playerState::RUNNING)
	{
		node->setMD2Animation(EMAT_RUN);
		node->setAnimationSpeed(30);
		pState = playerState::RUNNING;
	}
}

void Player::setAttackAnimation()
{
	if (pState != playerState::ATTACK)
	{
		node->setMD2Animation(EMAT_ATTACK);
		node->setAnimationSpeed(20);
		pState = playerState::ATTACK;
	}
}
#pragma once

#include "Global.h"

#define EFFECT_DEATH_TIME	1500

class Effect
{
public:
	Effect();

	void addDeath(ISceneManager *manager, vector3df position, IVideoDriver *video);

	void drop();

private:
	scene::IParticleSystemSceneNode* deathEffect;
};
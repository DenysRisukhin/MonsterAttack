#include "Effect.h"

Effect::Effect() : deathEffect(NULL) {}

// rendered when bullets kill something
void Effect::addDeath(ISceneManager *manager, vector3df position, IVideoDriver *video)
{
	if (!deathEffect)
	{
		deathEffect = manager->addParticleSystemSceneNode(false);

		scene::IParticleEmitter* em = deathEffect->createBoxEmitter(
			core::aabbox3d<f32>(-7, 0, -7, 7, 1, 7), // emitter size
			core::vector3df(0.0f, 0.06f, 0.0f),   // initial direction
			80, 100,                             // emit rate
			video::SColor(0, 255, 255, 255),       // darkest color
			video::SColor(0, 255, 255, 255),       // brightest color
			800, 2000, 0,                         // min and max age, angle
			core::dimension2df(10.f, 10.f),         // min size
			core::dimension2df(20.f, 20.f));        // max size

		deathEffect->setEmitter(em); // this grabs the emitter
		em->drop(); // so we can drop it here without deleting it

		scene::IParticleAffector* paf = deathEffect->createFadeOutParticleAffector();

		deathEffect->addAffector(paf); // same goes for the affector
		paf->drop();

		deathEffect->setPosition(position);
		deathEffect->setScale(core::vector3df(4, 4, 4));
		deathEffect->setMaterialFlag(video::EMF_LIGHTING, false);
		deathEffect->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		deathEffect->setMaterialTexture(0, video->getTexture("textures/smoke2.jpg"));
		deathEffect->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	}
}


void Effect::drop()
{
	if (deathEffect)
	{
		deathEffect->remove();
		deathEffect = NULL;
	}
}
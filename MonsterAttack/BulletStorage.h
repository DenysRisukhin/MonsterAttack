#pragma once


#include "Global.h"
#include "Bullet.h"
#include "TextureManager.h"

#define BULLET_PLAYER_SPEED		800
#define BULLET_ENEMY_SPEED		400

#define BULLET_ELIPSE_BOUND { 5.f, 5.f, 5.f }

class BulletStorage
{
private:

	list<Bullet> pBullets;
	list<Bullet> eBullets;

public:

	list<Bullet>		getPBullets() const;
	list<Bullet>		getEBullets() const;

	void				setPBullets(list<Bullet> rockets);
	void				setEBullets(list<Bullet> rockets);

	void				addPlayerBullet(ISceneManager *manager, IVideoDriver *video, TextureManager *&texManager, IMetaTriangleSelector *world, vector3df position);
	void				addEnemyBullet(ISceneManager *manager, IVideoDriver *video, TextureManager *&texManager, ITriangleSelector *world, vector3df position);

	// The method checkBullets() returns an array of nodes with which the bullet cuts off
	array<ISceneNode *>	checkBullets(array<u32> *Pindecies, array<u32> *Eindecies);
	void				move(f32 delta);
	void				drop();
};
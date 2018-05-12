#include "BulletStorage.h"

list<Bullet> BulletStorage::getPBullets() const
{
	return pBullets;
}

list<Bullet> BulletStorage::getEBullets() const
{
	return eBullets;
}

void BulletStorage::setPBullets(list<Bullet> bullets)
{
	pBullets = bullets;
}

void BulletStorage::setEBullets(list<Bullet> bullets)
{
	eBullets = bullets;
}

//! Creates a special scene node animator for doing automatic collision detection and response.
/** See ISceneNodeAnimatorCollisionResponse for details.
\param world: Triangle selector holding all triangles of the world with which
the scene node may collide. You can create a triangle selector with
ISceneManager::createTriangleSelector();
\param sceneNode: SceneNode which should be manipulated. After you added this animator
to the scene node, the scene node will not be able to move through walls and is
affected by gravity. If you need to teleport the scene node to a new position without
it being effected by the collision geometry, then call sceneNode->setPosition(); then
animator->setTargetNode(sceneNode);
\param ellipsoidRadius: Radius of the ellipsoid with which collision detection and
response is done. If you have got a scene node, and you are unsure about
how big the radius should be, you could use the following code to determine
it:
\code
const core::aabbox3d<f32>& box = yourSceneNode->getBoundingBox();
core::vector3df radius = box.MaxEdge - box.getCenter();
\endcode
\param gravityPerSecond: Sets the gravity of the environment, as an acceleration in
units per second per second. If your units are equivalent to metres, then
core::vector3df(0,-10.0f,0) would give an approximately realistic gravity.
You can disable gravity by setting it to core::vector3df(0,0,0).
\param ellipsoidTranslation: By default, the ellipsoid for collision detection is created around
the center of the scene node, which means that the ellipsoid surrounds
it completely. If this is not what you want, you may specify a translation
for the ellipsoid.
\param slidingValue: DOCUMENTATION NEEDED.
\return The animator. Attach it to a scene node with ISceneNode::addAnimator()
and the animator will cause it to do collision detection and response.
If you no longer need the animator, you should call ISceneNodeAnimator::drop().
See IReferenceCounted::drop() for more information. */
void BulletStorage::addPlayerBullet(ISceneManager *manager, IVideoDriver *video, TextureManager *&texManager, IMetaTriangleSelector *world, vector3df position)
{
	Bullet bullet;
	if (bullet.createBullet (manager, video, position, UP))
	{
		// Anim contains list of all tringleselectors for enemy 
		ISceneNodeAnimatorCollisionResponse *anim = manager->createCollisionResponseAnimator(world, bullet.getNode(), BULLET_ELIPSE_BOUND, IDLE_VECTOR);
		
		// Add Collisions with enemys for each bullet (we add anim to collisions lists from GameObject class).
		if (anim)
			bullet.addCollision(anim);
		pBullets.push_back(bullet);
	}
}

void BulletStorage::addEnemyBullet(ISceneManager *manager, IVideoDriver *video, TextureManager *&texManager, ITriangleSelector *world, vector3df position)
{
	Bullet bullet;
	if (bullet.createBullet(manager, video, position, DOWN))
	{
		ISceneNodeAnimatorCollisionResponse *anim = manager->createCollisionResponseAnimator(world, bullet.getNode(), BULLET_ELIPSE_BOUND, IDLE_VECTOR);
		if (anim)
			bullet.addCollision(anim);
		eBullets.push_back(bullet);
	}
}

array<ISceneNode *> BulletStorage::checkBullets(array<u32> *Pindecies, array<u32> *Eindecies)
{
	array<ISceneNode *> nodes;

	u32 count = 0;
	for (auto &i : pBullets)
	{
		if (!i.isDead())
		{
			// If the bullet is outside the established path, then delete it and put the number to Findecies
			if (i.checkEnd())
			{
				i.drop();
				i.setHealth(0);
				Pindecies->push_back(count);
				continue;
			}

			// If the method checkCollision() returns the node that was collided with bullet -
			// put this node to "nodes", then delete the bullet and put its number in Findecies
			ISceneNode *buff = i.checkCollision();
			if (buff)
			{
				nodes.push_back(buff);
				i.drop();
				i.setHealth(0);
				Pindecies->push_back(count);
			}
		}
		count++;
	}

	count = 0;
	for (auto &i : eBullets)
	{
		if (!i.isDead())
		{
			if (i.checkEnd())
			{
				i.drop();
				i.setHealth(0);
				Eindecies->push_back(count);
				continue;
			}

			ISceneNode *buff = i.checkCollision();
			if (buff)
			{
				nodes.push_back(buff);
				i.drop();
				i.setHealth(0);
				Eindecies->push_back(count);
			}
		}
		count++;
	}

	return nodes;
}

void BulletStorage::move(f32 delta)
{
	for (auto &i : pBullets)
	{
		if (!i.isDead())
		{
			vector3df pos = i.getPosition();
			pos.Z += delta * BULLET_PLAYER_SPEED;
			i.setPosition(pos);
		}
	}

	for (auto &i : eBullets)
	{
		if (!i.isDead())
		{
			vector3df pos = i.getPosition();
			pos.Z -= delta * BULLET_ENEMY_SPEED;
			i.setPosition(pos);
		}
	}
}

void BulletStorage::drop()
{
	for (auto &i : pBullets)
		i.drop();

	for (auto &i : eBullets)
		i.drop();

	pBullets.clear();
	eBullets.clear();
}
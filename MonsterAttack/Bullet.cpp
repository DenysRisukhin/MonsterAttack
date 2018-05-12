#include "Bullet.h"

Bullet::Bullet() : GameObject(), path()
{
}

line3df Bullet::getPath() const
{
	return path;
}

void Bullet::setPath(const line3df newPath)
{
	path = newPath;
}

bool Bullet::createBullet(ISceneManager *manager, IVideoDriver *video, vector3df position, Direction direction)
{
	vector3df end = position;
	switch (direction)
	{
	case UP:
		end.X = BULLET_END_PATH;
		break;
	case DOWN:
		end.X = -BULLET_END_PATH;
		break;
	}
	path = line3df(position, end);

	name = "models/cube.x";
	createNode(manager);

	node->setPosition(position);
	node->setScale({1.5, 1.5, 1.5});
	health = MAX_HEALTH;

	return true;
}

ISceneNode *Bullet::checkCollision()
{
	vector3df pos = node->getPosition();

	// Check the bullet for the limit of the installed path(If the bullet is outside the path : health = 0 & return NULL)
	if (pos.X > path.start.X && pos.X >= path.end.X)
		health = 0;

	else if (pos.X < path.start.X && pos.X <= path.end.X)
		health = 0;

	// If health <= 0
	if (isDead())
		return NULL;

	// Check the collision of the current bullet with the list of collisions (class GameObject 
	// Special scene node animator for doing automatic collision detection and response.
	// list<ISceneNodeAnimatorCollisionResponse *>	collisions;)
	for (auto i : collisions)
	{
		
		// The method collisionOccurred() returns true if a collision occurred during the last animateNode()
		if (i->collisionOccurred()) 
		{
			// If true, then return the node with a collision
			health = 0;
			return (i->getCollisionNode()); // Returns the node that was collided with.
		}
	}

	return NULL;
}

// Check the bullet for the limit of the installed path
bool Bullet::checkEnd() const
{
	if (node->getPosition().X > path.start.X && node->getPosition().X >= path.end.X)
		return true;
	if (node->getPosition().X < path.start.X && node->getPosition().X <= path.end.X)
		return true;
	return false;
}
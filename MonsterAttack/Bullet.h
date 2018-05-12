#pragma once

#include "Global.h"
#include "GameObject.h"

#define BULLET_END_PATH					250

class Bullet : public GameObject
{

private:

	line3df						path;

public:

	Bullet();

	line3df						getPath() const;

	void						setPath(const line3df newPath);

	bool						createBullet(ISceneManager *manager, IVideoDriver *video, vector3df position, Direction direction);


	// The method checkCollision() returns the node that was collided with bullet or NULL
	// 1. If the collision occurred: health = 0 and Returns the node that was collided with.
	// 2. Check the bullet for the limit of the installed path (If the bullet is outside the path: health = 0 & return NULL)
	ISceneNode					*checkCollision();

	// Check the bullet for the limit of the installed path
	bool						checkEnd() const;

};
#pragma once

#include "Global.h"

#define MAX_HEALTH 100

class GameObject
{

protected:

	IAnimatedMeshSceneNode *node;
	list<ISceneNodeAnimator *> animators;

	// Special scene node animator for doing automatic collision detection and response.
	list<ISceneNodeAnimatorCollisionResponse *>	collisions;
	path name;

	//s32 -> int
	s32	health;
private:

	void addAllAnimators();

public:

	GameObject();
	GameObject(IAnimatedMeshSceneNode *node, list<ISceneNodeAnimator *> animators, list<ISceneNodeAnimatorCollisionResponse *> collisions, path name);
	GameObject(const GameObject &object);
	~GameObject();

	/** A scene node is a node in the hierarchical scene graph. Every scene
	node may have children, which are also scene nodes. Children move
	relative to their parent's position. If the parent of a node is not
	visible, its children won't be visible either. In this way, it is for
	example easily possible to attach a light to a moving car, or to place
	a walking character on a moving platform on a moving ship.
	*/
	ISceneNode	*getNode() const;

	list<ISceneNodeAnimator *>	getAnimators() const;

	//! Animates a scene node. Can animate position, rotation, material, and so on.
	/** A scene node animator is able to animate a scene node in a very simple way. It may
	change its position, rotation, scale and/or material. There are lots of animators
	to choose from. You can create scene node animators with the ISceneManager interface.
	*/
	ISceneNodeAnimator	*getAnimatorByIndex(u32 index) const;

	list<ISceneNodeAnimatorCollisionResponse *>	getCollisions() const;
	ISceneNodeAnimatorCollisionResponse	*getCollisionByIndex(u32 index) const;

	path getName() const;
	s32	getHealth() const;

	vector3df getPosition() const;
	vector3df getRotation() const;
	vector3df getScale() const;

	void setPosition(const vector3df position);
	void setRotation(const vector3df rotation);
	void setScale(const vector3df scale);

	void setNode(IAnimatedMeshSceneNode *newNode);
	void setAnimators(list<ISceneNodeAnimator *> newAnimators);
	void setCollisions(list<ISceneNodeAnimatorCollisionResponse *>	newCollisions);
	void setName(const path newName);
	void setHealth(const s32 newHealth);

	bool createNode(ISceneManager *manager);

	ITriangleSelector *createTriangleSelector(ISceneManager *manager) const;

	void addAnimator(ISceneNodeAnimator *animator);
	void addCollision(ISceneNodeAnimatorCollisionResponse *collision);

	virtual	bool move(f32 delta);
	void damage(u32 dmg);
	bool isDead() const;

	virtual void drop();
};

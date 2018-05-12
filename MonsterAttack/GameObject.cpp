#include "GameObject.h"

/////////////////////////////////////////
// Constructors and Distructors
/////////////////////////////////////////

GameObject::GameObject() : node(NULL), animators({}), collisions({}), name(""), health(MAX_HEALTH)
{
}

GameObject::GameObject(IAnimatedMeshSceneNode *node, list<ISceneNodeAnimator *> animators, list<ISceneNodeAnimatorCollisionResponse *> collisions, path name) : node(node), animators(animators), collisions(collisions), name(name), health(MAX_HEALTH)
{
	if (node)
	{
		for (auto &i : animators)
			node->addAnimator(i);
		for (auto &i : collisions)
			node->addAnimator(i);
	}
}

GameObject::GameObject(const GameObject &object)
{
	node = object.node;

	for (auto &i : object.animators)
		animators.push_back(i);

	for (auto &i : object.collisions)
		collisions.push_back(i);

	name = object.name;
	health = object.health;
}

GameObject::~GameObject()
{
	if (node)
		node = NULL;

	animators.clear();
	collisions.clear();
}

/////////////////////////////////////////
// Getters
/////////////////////////////////////////

ISceneNode *GameObject::getNode() const
{
	return node;
}

list<ISceneNodeAnimator *> GameObject::getAnimators() const
{
	return animators;
}

ISceneNodeAnimator *GameObject::getAnimatorByIndex(u32 index) const
{
	if (index >= animators.getSize())
		return NULL;

	else
	{
		auto iter = animators.begin();
		for (u32 i = 0; i < index; i++)
			iter++;
		return *iter;
	}
}

list<ISceneNodeAnimatorCollisionResponse *> GameObject::getCollisions() const
{
	return collisions;
}

ISceneNodeAnimatorCollisionResponse *GameObject::getCollisionByIndex(u32 index) const
{
	if (index >= collisions.getSize())
		return NULL;

	else
	{
		auto iter = collisions.begin();
		for (u32 i = 0; i < index; i++)
			iter++;
		return *iter;
	}
}

path GameObject::getName() const
{
	return name;
}

s32 GameObject::getHealth() const
{
	return health;
}

vector3df GameObject::getPosition() const
{
	return node->getPosition();
}

vector3df GameObject::getRotation() const
{
	return node->getRotation();
}

vector3df GameObject::getScale() const
{
	return node->getScale();
}

/////////////////////////////////////////
// Setters
/////////////////////////////////////////

void GameObject::setPosition(const vector3df position)
{
	node->setPosition(position);
}

void GameObject::setRotation(const vector3df rotation)
{
	node->setRotation(rotation);
}

void GameObject::setScale(const vector3df scale)
{
	node->setScale(scale);
}

void GameObject::setNode(IAnimatedMeshSceneNode *newNode)
{
	node->removeAnimators();
	node->remove();
	node = newNode;
	addAllAnimators();
}

void GameObject::setAnimators(list<ISceneNodeAnimator *> newAnimators)
{
	animators.clear();
	for (auto &i : newAnimators)
		animators.push_back(i);

	if (node)
	{
		for (auto &i : animators)
			node->addAnimator(i);
	}
}

void GameObject::setCollisions(list<ISceneNodeAnimatorCollisionResponse* > newCollisions)
{
	collisions.clear();
	for (auto &i : newCollisions)
		collisions.push_back(i);

	if (node)
	{
		for (auto &i : collisions)
			node->addAnimator(i);
	}
}

void GameObject::setName(const path newName)
{
	name = newName;
}

void GameObject::setHealth(const s32 newHealth)
{
	health = newHealth;
}

/////////////////////////////////////////
// Additional functions
/////////////////////////////////////////

void GameObject::addAllAnimators()
{
	for (auto &i : animators)
		node->addAnimator(i);

	for (auto &i : collisions)
		node->addAnimator(i);
}

bool GameObject::createNode(ISceneManager *manager)
{
	IAnimatedMesh *mesh = manager->getMesh(name);
	if (!mesh)
		return false;

	node = manager->addAnimatedMeshSceneNode(mesh);
	if (!node)
		return false;

	addAllAnimators();

	return true;
}

ITriangleSelector *GameObject::createTriangleSelector(ISceneManager *manager) const
{
	return manager->createTriangleSelectorFromBoundingBox(node);
}

void GameObject::addAnimator(ISceneNodeAnimator *animator)
{
	animators.push_back(animator);
	node->addAnimator(animator);
}

void GameObject::addCollision(ISceneNodeAnimatorCollisionResponse *collision)
{
	collisions.push_back(collision);
	node->addAnimator(collision);
}

bool GameObject::move(f32 delta)
{
	return false;
}

void GameObject::damage(u32 dmg)
{
	health -= dmg;
}

bool GameObject::isDead() const
{
	return health <= 0;
}

void GameObject::drop()
{
	if (node)
	{
		node->removeAnimators();
		node->remove();
		node = NULL;
		animators.clear();
		collisions.clear();
	}
}
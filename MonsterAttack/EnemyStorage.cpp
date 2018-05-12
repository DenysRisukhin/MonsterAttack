#include "EnemyStorage.h"

list<Enemy> EnemyStorage::getEnemyList() const
{
	return enemyList;
}


void EnemyStorage::setEnemyList(list<Enemy> newList)
{
	enemyList = newList;
}


vector3df EnemyStorage::getRandomEnemyPosition() const
{
	vector3df result = IDLE_VECTOR;
	while (result == vector3df(IDLE_VECTOR))
	{
		u32 index = rand() % enemyList.size();
		u32 count = 0;
		for (auto &i : enemyList)
		{
			if (count == index && !i.isDead())
			{
				result = i.getPosition();
				return result;
			}
			count++;
		}
	}
	return result;
}

bool EnemyStorage::createEnemies(ISceneManager *manager, TextureManager *&texManager, rectf limits)
{
	Direction direction = DOWN;
	for (u32 i = 0; i < 10; i++)
	{
		u32 type = rand() % ENEMY_TYPE_COUNT;
		if (i % ENEMY_LINE_COUNT == 0 && i)
			direction = (direction == DOWN ? UP : DOWN);

		f32 yStep = i % ENEMY_LINE_COUNT;
		if (direction == UP)
			yStep++;

		vector3df position = { limits.UpperLeftCorner.X + yStep * ENEMY_HOTIZONTAL_MARGIN, 0.f, limits.UpperLeftCorner.Y - (i / ENEMY_LINE_COUNT) * ENEMY_VERTICAL_MARGIN };
		//vector3df position = { limits.UpperLeftCorner.Y - (i / ENEMY_LINE_COUNT) * ENEMY_VERTICAL_MARGIN, 0.f, limits.UpperLeftCorner.X + yStep * ENEMY_HOTIZONTAL_MARGIN };

		vector3df end = position;
		vector3df start = position;

		switch (direction)
		{
		case UP:
			end.X += ENEMY_VERTICAL_MARGIN;
			break;
		case DOWN:
			start.X -= ENEMY_VERTICAL_MARGIN;
			break;
		}
		end.X = limits.LowerRightCorner.Y;
		rectf path = { start.Z, start.X, end.Z, end.X };

		enemyList.push_back({ manager, texManager, type, direction, position, path });
	}

	return true;
}

IMetaTriangleSelector *EnemyStorage::createSelectors(ISceneManager *manager)
{
	IMetaTriangleSelector *result = manager->createMetaTriangleSelector();
	for (auto &i : enemyList)
		result->addTriangleSelector(i.createTriangleSelector(manager));
	return result;
}

bool EnemyStorage::checkNode(ISceneNode *check, ISceneManager *manager, u32 *score, ISoundEngine *sound, bool soundPlay, vector3df *position)
{
	for (auto &i : enemyList)
	{
		if (check == i.getNode())
		{
			i.damage(i.getDamage());
			(*score) += i.getDamage();

			if (i.isDead())
			{
				if (soundPlay)
				{
					ISound *bang = sound->play2D("sounds/crash.wav", false, true);
					bang->setVolume(10.0f);
					bang->setIsPaused(false);
					bang->drop();
				}
				i.deathAnimation();
				(*score) += i.getDamage() * 2;
				(*position) = i.getPosition();

				// Move the object behind the screen & delete collisions and animators from node
				i.moveFromField();
				break;
			}
		}
	}

	for (auto &i : enemyList)
		if (!i.isDead())
			return false;

	return true;
}

void EnemyStorage::move(f32 delta)
{
	for (auto &i : enemyList)
		if (!i.isDead())
			i.move(delta);
}

bool EnemyStorage::step()
{
	for (auto &i : enemyList)
	{
		if (!i.isDead())
		{
			Direction temp = i.getDirection();
			i.setDirection(LEFT);
			if (i.move(0))
				return true;
			i.setDirection(temp);
		}
	}
	return false;
}

void EnemyStorage::drop()
{
	for (auto &i : enemyList)
		i.drop();

	enemyList.clear();
}
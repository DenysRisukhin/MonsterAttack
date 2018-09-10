#include "Global.h"
#include "Enemy.h"
#include "TextureManager.h"

#define ENEMY_COUNT				8 
#define ENEMY_LINE_COUNT		5
#define ENEMY_VERTICAL_MARGIN	50
#define ENEMY_HOTIZONTAL_MARGIN	100

class EnemyStorage
{
private:

	list<Enemy>	enemyList;

public:

	list<Enemy>	getEnemyList() const;

	void setEnemyList(list<Enemy> newList);

	vector3df getRandomEnemyPosition() const;

	bool createEnemies(ISceneManager *manager, TextureManager *&texManager, rectf limits);

	// IMetaTriangleSelector - Interface for making multiple triangle selectors work as one big selector.

	/** This is nothing more than a collection of one or more triangle selectors
	providing together the interface of one triangle selector. In this way,
	collision tests can be done with different triangle soups in one pass.
	*/

	// The method creates triangleselector for each enemy from enemyList & add it to the IMetaTriangleSelector.
	IMetaTriangleSelector *createSelectors(ISceneManager *manager);

	// The method checks for enemies damage and death
	bool checkNode(ISceneNode *check, ISceneManager *manager, u32 *score, ISoundEngine *sound, bool soundPlay, vector3df *position);
	void move(f32 delta);
	bool step();
	void drop();
};
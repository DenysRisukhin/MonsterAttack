#pragma once

#include "IrrLicht.h"
#include "Irrklang.h"
#include "Player.h"
#include "EnemyStorage.h"
#include "BulletStorage.h"
#include "Timer.h"
#include "Gui.h"
#include "Effect.h"
#include "TextureManager.h"
#include <time.h>

enum State
{
	MENU,
	OPTIONS,
	INGAME,
	PAUSE,
	OVER,
	EXIT
};

#define ENEMY_FIELD_SIZE	{ -250.f, 180.f, 250.f, -160.f }
#define PLAYER_LINE_SIZE	{ -200, 0.f, -500,  200, 0.f, 0 }


#define SCENE_SKYBOX_ROTATION	{ 0.f, 270.f, 0.f }
#define SCENE_SKYBOX_SCALE		{ 1.1f, 1.f, 0.75f }

class Game
{
private:

	Irrlicht		*engine;
	ISoundEngine	*sound;

	Player			*player;
	EnemyStorage	*enemies;
	BulletStorage	*bullets;
	GUI				*gui;
	Effect			*effects;
	ISound			*gameMusic;
	TextureManager	*texManager;

	rectf			enemyField;

	// 3D line between two points with intersection methods.
	line3df			playerLine;

	State			state;
	Time			timer;

	u32				score;
	bool			soundPlay;

	void toLevel(bool pause);

	void menu();
	void game();

	bool addPlayer();
	bool addEnemies();

	void applyEnemiesMoves();
	void applyPlayerMoves();
	void applyBulletsMoves();
	void applyEffects();

	void drop();

public:

	Game();
	void loop();

};
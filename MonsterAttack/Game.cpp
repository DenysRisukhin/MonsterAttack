#include "Game.h"

Game::Game() :
	enemyField(ENEMY_FIELD_SIZE),
	playerLine(line3df(PLAYER_LINE_SIZE)),
	enemies(new EnemyStorage()),
	player(new Player()),
	bullets(new BulletStorage()),
	gui(new GUI()),
	effects(new Effect()),
	texManager(new TextureManager()),
	engine(new Irrlicht(L"Monster Attack", dimension2du(WINDOW_WIDTH, WINDOW_HEIGHT))),
	state(MENU),
	sound(createIrrKlangDevice()),
	score(0),
	soundPlay(true)
{
	srand(time(NULL));
}

void Game::toLevel(bool pause)
{
	engine->hideCursor(true);
	engine->setCursorToCenter();
	engine->resetInput();

	if (!pause)
	{
		drop();
		if (!addPlayer())
			exit(1);
		if (!addEnemies())
			exit(1);

		timer.zeroTimes();
		engine->setTime(0);
	}

	gui->game(engine->getGUI(), texManager, engine->getVideo());
}

void Game::menu()
{
	switch (state)
	{
	case MENU:
		if (gui->isButtonPressed(START_BUTTON))
		{
			state = INGAME;
			toLevel(false);
		}
		else if (gui->isButtonPressed(OPTIONS_BUTTON))
		{
			state = OPTIONS;
			gui->options(engine->getGUI(), texManager);
		}
		else if (gui->isButtonPressed(QUIT_BUTTON))
			state = EXIT;
		break;

	case OPTIONS:
		if (gui->isButtonPressed(BACK_BUTTON))
		{
			state = MENU;
			gui->menu(engine->getGUI(), texManager, engine->getVideo());
		}

		else if (gui->getMusicSelection() == MUSIC_ENABLE)
		{
			if (gameMusic->getIsPaused())
				gameMusic = sound->play2D("sounds/soundtrack.mp3", true, false, true);
		}

		else if (gui->getMusicSelection() == MUSIC_DISABLE)
			gameMusic->setIsPaused(true);

		if (gui->getSoundSelection() == SOUND_ENABLE)
			soundPlay = true;

		else if (gui->getSoundSelection() == SOUND_DISABLE)
			soundPlay = false;
		break;

	case PAUSE:
		if (gui->isButtonPressed(BACK_BUTTON))
		{
			score = 0; 
			state = MENU;
			drop();
			engine->hideCursor(false);
			gui->menu(engine->getGUI(), texManager, engine->getVideo());
		}

		else if (gui->isButtonPressed(RESUME_BUTTON))
		{
			state = INGAME;
			u32 delta = engine->getNow() - timer.pauseTime;
			timer.addDelta(delta);
			toLevel(true);
		}

		else if (gui->isButtonPressed(QUIT_BUTTON))
			state = EXIT;
		break;

	case OVER:
		score = 0; 

		if (gui->isButtonPressed(START_BUTTON))
		{
			state = INGAME;
			toLevel(false);
		}
		else if (gui->isButtonPressed(BACK_BUTTON))
		{
			state = MENU;
			drop();
			engine->hideCursor(false);
			gui->menu(engine->getGUI(), texManager, engine->getVideo());
		}
		else if (gui->isButtonPressed(QUIT_BUTTON))
			state = EXIT;
		break;
	}
}

void Game::game()
{
	// Counting time since last frame
	timer.now = engine->getNow();
	timer.delta = (f32)(timer.now - timer.lastTime) / 1000.f;
	timer.lastTime = timer.now;

	// Apply game objects moves
	applyPlayerMoves();
	applyEnemiesMoves();
	applyBulletsMoves();
	applyEffects();

	if (engine->isKeyPressed(KEY_ESCAPE))
	{
		state = PAUSE;
		timer.pauseTime = engine->getNow();
		gui->pause(engine->getGUI(), texManager);
		engine->hideCursor(false);

	}
}

void Game::loop()
{
	// Creating background
	ISceneNode *skybox = engine->getSkyBox("textures/background1.jpg");
	skybox->setRotation(SCENE_SKYBOX_ROTATION);
	skybox->setScale(SCENE_SKYBOX_SCALE);

	// Textures
	texManager->loadTextures(engine->getVideo());

	// Light
	ILightSceneNode *light = engine->getManager()->addLightSceneNode(0, LIGHT_POSITION, WHITE_COLOR, LIGHT_RADIUS);

	// Menu
	gui->menu(engine->getGUI(), texManager, engine->getVideo());

	// Music
	gameMusic = sound->play2D("sounds/soundtrack.mp3", true, false, true);

	bool exitFlag = false;

	while (engine->run())
	{
		switch (state)
		{
		case MENU:
		case OPTIONS:
		case PAUSE:
		case OVER:
			menu();
			break;

		case INGAME:
			game();
			break;

		case EXIT:
			exitFlag = true;
			break;
		}

		if (exitFlag)
			break;

		engine->drawAll();
	}

	texManager->drop();
	engine->drop();
	sound->drop();
}

void Game::drop()
{
	player->drop();
	enemies->drop();
	bullets->drop();
	effects->drop();
}

bool Game::addPlayer()
{
	player->setName("models/sydney.md2");
	engine->resetMouseMove();
	bool result = player->createNode(engine->getManager());
	if (result)
	{
		player->setPosition(playerLine.getMiddle());
		player->setRotation(PLAYER_ROTATION);
		player->setHealth(MAX_HEALTH);
	}
	player->getNode()->setMaterialTexture(0, texManager->getPlayerTexture()[0]);

	player->setIdleAnimation();

	return result;
}

void Game::applyPlayerMoves()
{
	vector3df initPos = player->getPosition();

	// Keyboard moves
	if (engine->isKeyPressed(KEY_KEY_S)) {
		player->move(-timer.delta);
		player->setRunningAnimation();
		engine->resetMouseMove();
	}
	else if (engine->isKeyPressed(KEY_KEY_W)) {
		player->move(timer.delta);
		player->setRunningAnimation();
		engine->resetMouseMove();
	}
	else if( (!engine->isKeyPressed(KEY_KEY_S) || !engine->isKeyPressed(KEY_KEY_W)) && !engine->isKeyPressed(KEY_SPACE))
		player->setIdleAnimation();
	
	// Mouse moves
	dimension2du center = engine->getCenter();
	vector2di mouse = engine->getCursorPosition();
	if (center.Width != mouse.X)
	{
		f32 move = (f32)(mouse.X - (s32)center.Width);
		player->move(timer.delta * move);
		engine->setCursorPosition(center);
	} 
	
	// checking player move border
	vector3df pos = player->getPosition();
	if (pos != initPos)
	{
		// Checking for bound.
		if (pos.X < playerLine.start.X)
			pos.X = playerLine.start.X;
		else if (pos.X > playerLine.end.X)
			pos.X = playerLine.end.X;

		player->setPosition(pos);
	} 


	// Fire
	if ((engine->isKeyPressed(KEY_SPACE) || engine->isLeftMouseButtonPressed()) && (timer.now - timer.lastFire) >= PLAYER_FIRE_TIME)
	{
		player->setAttackAnimation();

		ISound *bang = sound->play2D("sounds/lazer.wav", false, true);
		bang->setVolume(0.5f);
		bang->setIsPaused(false);
		bang->drop();

		vector3df rPos = player->fire();
		
		bullets->addPlayerBullet(engine->getManager(), engine->getVideo(), texManager, enemies->createSelectors(engine->getManager()), rPos);
		timer.lastFire = timer.now;
	}
}

bool Game::addEnemies()
{
	return enemies->createEnemies(engine->getManager(), texManager, enemyField);
}

void Game::applyEnemiesMoves()
{
	// Move up/down
	enemies->move(timer.delta);

	// Check left movement
	if ((timer.now - timer.lastStep) >= ENEMY_STEP_TIME)
	{
		// If the enemies were on the left side of the screen
		if (enemies->step())
		{
			state = OVER;
			engine->hideCursor(false);
			gui->lose(engine->getGUI(), texManager);
			player->setHealth(0);
		}

		timer.lastStep = timer.now;
	}

	// Random enemy fires
	if ((timer.now - timer.lastEnemyFire) >= ENEMY_FIRE_TIME)
	{
		ISound *bang = sound->play2D("sounds/lazer.wav", false, true);
		bang->setVolume(0.5f);
		bang->setIsPaused(false);
		bang->drop();

		vector3df rPos = enemies->getRandomEnemyPosition();

		// function createTriangleSelector from class GameObject
		bullets->addEnemyBullet(engine->getManager(), engine->getVideo(), texManager, player->createTriangleSelector(engine->getManager()), rPos);
		timer.lastEnemyFire = timer.now;
	}
}

void Game::applyBulletsMoves()
{
	// Move thier ways
	bullets->move(timer.delta);
	
	// Getting all nodes bullets hited & indecies for bullets
	array<u32> *Pindecies, *Eindecies;
	Pindecies = new array<u32>();
	Eindecies = new array<u32>();
	array<ISceneNode *> nodes = bullets->checkBullets(Pindecies, Eindecies);
	
	for (u32 i = 0; i < nodes.size(); i++)
	{
		vector3df pos = IDLE_VECTOR;

		// Checking for player damage and death
		if (nodes[i] == player->getNode())
		{
			player->damage(PLAYER_DAMAGE);
			if (player->isDead())
			{
				if (soundPlay)
				{
					ISound *bang = sound->play2D("sounds/crash.wav", false, true);
					bang->setVolume(0.1f);
					bang->setIsPaused(false);
					bang->drop();
				}
				state = OVER;
				engine->hideCursor(false);
				drop();
				gui->lose(engine->getGUI(), texManager);
				gui->setScore(score);

				return;
			}
		}

		// Checking for enemies damage and death
		else if (enemies->checkNode(nodes[i], engine->getManager(), &score, sound, soundPlay, &pos))
		{
			state = OVER;
			engine->hideCursor(false);
			drop();
			gui->win(engine->getGUI(), texManager);
			return;
		}

		if (pos != vector3df(IDLE_VECTOR)) 
  			effects->addDeath(engine->getManager(), pos, engine->getVideo());
	}

	gui->setScore(score);

	if (!player->isDead()) 
		gui->setHealth(player->getHealth());
}

void Game::applyEffects()
{
	if (timer.now - timer.lastFrame >= EFFECT_DEATH_TIME)
	{
		effects->drop();
		timer.lastFrame = timer.now;
	}
}
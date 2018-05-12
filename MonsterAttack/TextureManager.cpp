#include "TextureManager.h"

TextureManager::TextureManager() : playerTex(NULL), enemyTex(NULL), buttonsTex(NULL)
{
}

ITexture **TextureManager::getPlayerTexture() const
{
	return playerTex;
}

ITexture **TextureManager::getEnemyTexture() const
{
	return enemyTex;
}


ITexture **TextureManager::getButtonsTexture() const
{
	return buttonsTex;
}


void TextureManager::setPlayerTexture(ITexture **texture)
{
	playerTex = texture;
}

void TextureManager::setEnemyTexture(ITexture **texture)
{
	enemyTex = texture;
}


void TextureManager::setButtonsTexture(ITexture **texture)
{
	buttonsTex = texture;
}

void TextureManager::loadTextures(IVideoDriver *video)
{
	path name = TEXTURE_PATH;
	playerTex = new ITexture *;
	playerTex[0] = video->getTexture(name + PLAYER_NAME);

	enemyTex = new ITexture *[ENEMY_TEXTURES_COUNT];
	enemyTex[0] = video->getTexture(name + ENEMY01_NAME);
	enemyTex[1] = video->getTexture(name + ENEMY02_NAME);
	enemyTex[2] = video->getTexture(name + ENEMY03_NAME);
	enemyTex[3] = video->getTexture(name + ENEMY04_NAME);
	enemyTex[4] = video->getTexture(name + ENEMY05_NAME);

	buttonsTex = new ITexture *[BUTTON_TEXTURES_COUNT];
	buttonsTex[0] = video->getTexture(name + BUTTON_START_NAME);
	buttonsTex[1] = video->getTexture(name + BUTTON_OPTIONS_NAME);
	buttonsTex[2] = video->getTexture(name + BUTTON_BACK_NAME);
	buttonsTex[3] = video->getTexture(name + BUTTON_QUIT_NAME);
}

void TextureManager::drop()
{
	if (playerTex)
	{
		if (playerTex[0])
			playerTex[0] = NULL;
		delete playerTex;
	}

	if (enemyTex)
	{
		for (u32 i = 0; i < ENEMY_TEXTURES_COUNT; i++)
		{
			if (enemyTex[i])
				enemyTex[i] = NULL;
		}
		delete enemyTex;
	}

	if (buttonsTex)
	{
		for (u32 i = 0; i < BUTTON_TEXTURES_COUNT; i++)
		{
			if (buttonsTex[i])
				buttonsTex[i] = NULL;
		}
		delete buttonsTex;
	}
}
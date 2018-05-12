#pragma once

#include "Global.h"

#define TEXTURE_PATH			"textures/"
#define PLAYER_NAME			"sydney.bmp"
#define ENEMY01_NAME			"faerie2.bmp"
#define ENEMY02_NAME			"Faerie5.bmp"
#define ENEMY03_NAME			"nskinbl.jpg"
#define ENEMY04_NAME			"nskinrd.jpg"
#define ENEMY05_NAME			"lostsoul.bmp"
#define BUTTON_START_NAME		"Start1.png"
#define BUTTON_OPTIONS_NAME		"Start1.png"
#define BUTTON_BACK_NAME		"Start1.png"
#define BUTTON_QUIT_NAME		"Start1.png"

#define ENEMY_TEXTURES_COUNT	5
#define BUTTON_TEXTURES_COUNT	4

class TextureManager
{

private:

	ITexture **playerTex;
	ITexture **enemyTex;
	ITexture **buttonTex;
	ITexture **buttonsTex;

public:


	TextureManager();

	ITexture **getPlayerTexture() const;
	ITexture **getEnemyTexture() const;
	ITexture **getButtonsTexture() const;

	void setPlayerTexture(ITexture **texture);
	void setEnemyTexture(ITexture **texture);
	void setButtonsTexture(ITexture **texture);

	void loadTextures(IVideoDriver *video);

	void drop();

};
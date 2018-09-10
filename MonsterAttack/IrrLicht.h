#pragma once

#include "Global.h"
#include "GameEvents.h"

#define WINDOW_COLOR_DEPTH		32
#define WINDOW_BACKGROUND_COLOR	{0, 0, 0, 0}

#define CAMERA_POSITION			{ 0.f, -300.f, 0.f }
#define LIGHT_POSITION			{ 0.f, -500.f, 0.f }
#define LIGHT_RADIUS			5000

class Irrlicht {
private:

	GameEvents *reciever;
	IrrlichtDevice *device;
	IVideoDriver *video;
	ISceneManager *manager;
	IGUIEnvironment *gui;
	dimension2du windowSize;
	ICameraSceneNode *camera;

public:

	Irrlicht();
	Irrlicht(wchar_t *name, dimension2du size);

	ISceneManager *getManager() const;
	IGUIEnvironment	*getGUI() const;
	IVideoDriver *getVideo() const;
	ISceneNode *getSkyBox(path fileName) const;

	dimension2du getCenter() const;
	u32	getNow() const;
	void setTime(u32 newTime);
	bool isKeyPressed(EKEY_CODE key) const;
	void hideCursor(const bool flag);
	void setCursorPosition(const dimension2du position);
	void setCursorToCenter();
	vector2di getCursorPosition() const;
	bool isLeftMouseButtonPressed() const;
	void resetInput();
	void resetMouseMove();
	bool isMouseActive();
	bool run();
	void drawAll();
	bool drop();
};

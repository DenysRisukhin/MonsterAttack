#include "Irrlicht.h"

Irrlicht::Irrlicht() : reciever(NULL), device(NULL), video(NULL), manager(NULL), gui(NULL), windowSize(dimension2du(0, 0)), camera(NULL)
{
}

Irrlicht::Irrlicht(wchar_t *name, dimension2du size) : windowSize(size)
{
	reciever = new GameEvents();
	device = createDevice(EDT_OPENGL, windowSize, WINDOW_COLOR_DEPTH, false, false, false, reciever);
	if (!device)
		return;

	device->setWindowCaption(name);
	video = device->getVideoDriver();
	manager = device->getSceneManager();
	gui = device->getGUIEnvironment();
	camera = manager->addCameraSceneNode(NULL, CAMERA_POSITION, IDLE_VECTOR);
}

ISceneManager *Irrlicht::getManager() const
{
	return manager;
}

IGUIEnvironment *Irrlicht::getGUI() const
{
	return gui;
}

IVideoDriver *Irrlicht::getVideo() const
{
	return video;
}

ISceneNode *Irrlicht::getSkyBox(path fileName) const
{
	ISceneNode *box = manager->addSkyBoxSceneNode(video->getTexture(fileName), NULL, NULL, NULL, NULL, NULL);
	return box;
}

dimension2du Irrlicht::getCenter() const
{
	return dimension2du(windowSize.Width / 2, windowSize.Height / 2);
}

u32 Irrlicht::getNow() const
{
	return device->getTimer()->getTime();
}

void Irrlicht::setTime(u32 newTime)
{
	device->getTimer()->setTime(newTime);
}

bool Irrlicht::isKeyPressed(EKEY_CODE key) const
{
	return reciever->isKeyDown(key);
}

void Irrlicht::hideCursor(const bool flag)
{
	device->getCursorControl()->setVisible(!flag);
}

void Irrlicht::setCursorPosition(const dimension2du position)
{
	s32 x = position.Width;
	s32 y = position.Height;
	device->getCursorControl()->setPosition(x, y);
}

void Irrlicht::setCursorToCenter()
{
	s32 x = windowSize.Width / 2;
	s32 y = windowSize.Height / 2;
	device->getCursorControl()->setPosition(x, y);
}

vector2di Irrlicht::getCursorPosition() const
{
	return device->getCursorControl()->getPosition();
}

bool Irrlicht::isLeftMouseButtonPressed() const
{
	return reciever->isLeftButtonPressed();
}

void Irrlicht::resetInput()
{
	reciever->zeroMouse();
	//reciever->zeroMouseMove();
}

bool Irrlicht::isMouseActive() {
	return reciever->isMouseMoveActive();
}

void Irrlicht::resetMouseMove()
{
	reciever->zeroMouseMove();
}

bool Irrlicht::run()
{
	return device->run();
}

void Irrlicht::drawAll()
{
	video->beginScene(true, true, WINDOW_BACKGROUND_COLOR);
	manager->drawAll();
	gui->drawAll();
	video->endScene();
}

bool Irrlicht::drop()
{
	return device->drop();
}
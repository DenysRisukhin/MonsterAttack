#pragma once

#include "irrLicht\irrlicht.h"
#include "IrrKlang\irrKlang.h"
#include <iostream>

#pragma comment(lib, "libs/Irrlicht.lib")

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

using namespace irrklang;

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

#define IDLE_VECTOR		{0.f, 0.f, 0.f}

#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	768
#pragma once

#include "Global.h"


class GameEvents : public IEventReceiver
{
private:
	// Boolean array to store the state of the keys
	bool keys[KEY_KEY_CODES_COUNT];
	position2di	mousePosition;
	bool leftButtonPressed;
	bool mouseMove;

public:

	GameEvents();

	bool OnEvent(const SEvent &event);
	bool isKeyDown(EKEY_CODE key) const;
	position2di	getMousePosition() const;
	bool isLeftButtonPressed() const;
	bool isMouseMoveActive() const;
	void setMousePosition(vector3df position);
	void zeroMouse();
	void zeroMouseMove();
};

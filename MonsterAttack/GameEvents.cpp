#include "GameEvents.h"

GameEvents::GameEvents() : leftButtonPressed(false)
{
	for (bool &i : keys)
		i = false;
}

bool GameEvents::OnEvent(const SEvent &event)
{
	if (event.EventType == EET_KEY_INPUT_EVENT)
		keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
	else
	{
		switch (event.MouseInput.Event)
		{
		case EMIE_LMOUSE_PRESSED_DOWN:
			leftButtonPressed = true;
			break;

		case EMIE_LMOUSE_LEFT_UP:
			leftButtonPressed = false;
			break;

		case EMIE_MOUSE_MOVED:
			mousePosition.X = event.MouseInput.X;
			mousePosition.Y = event.MouseInput.Y;
			break;

		default:
			
			break;
		}
		
	}

	return false;
}

bool GameEvents::isKeyDown(EKEY_CODE key) const
{
	return keys[key];
}

position2di GameEvents::getMousePosition() const
{
	return mousePosition;
}

bool GameEvents::isLeftButtonPressed() const
{
	return leftButtonPressed;
}

void GameEvents::setMousePosition(const vector3df position)
{
	mousePosition.Y = position.X;
	mousePosition.X = position.Z;
}

void GameEvents::zeroMouse()
{
	leftButtonPressed = false;
}

bool GameEvents::isMouseMoveActive() const {
	return mouseMove;
}

void GameEvents::zeroMouseMove()
{
	mouseMove = false;
}
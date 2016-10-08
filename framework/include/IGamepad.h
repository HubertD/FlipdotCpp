#pragma once

#include <FlipdotTypes.h>

class IGamepad
{
	public:
		virtual ~IGamepad() {};
		virtual void init() = 0;
		virtual void update(unsigned ticks) = 0;
		virtual bool isKeyPressed(GamepadKey key) = 0;
		virtual bool wasKeyPressed(GamepadKey key) = 0;
		virtual bool wasKeyReleased(GamepadKey key) = 0;
		virtual void resetEvents() = 0;

};

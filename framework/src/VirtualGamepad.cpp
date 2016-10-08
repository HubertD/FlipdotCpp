#include "VirtualGamepad.h"

void VirtualGamepad::update(unsigned ticks)
{
	(void) ticks;
}

bool VirtualGamepad::isKeyPressed(GamepadKey key)
{
	return keyStatus(key, _currentStatus);
}

bool VirtualGamepad::wasKeyPressed(GamepadKey key)
{
	return isKeyPressed(key) && !keyStatus(key, _lastStatus);
}

bool VirtualGamepad::wasKeyReleased(GamepadKey key)
{
	return !isKeyPressed(key) && keyStatus(key, _lastStatus);
}

void VirtualGamepad::resetEvents()
{
	_lastStatus = _currentStatus;
}

void VirtualGamepad::injectKeyPress(GamepadKey key)
{
	_currentStatus |= (1<<(unsigned)key);
}

void VirtualGamepad::injectKeyRelease(GamepadKey key)
{
	_currentStatus &= ~(1<<(unsigned)key);
}

bool VirtualGamepad::keyStatus(GamepadKey key, uint32_t status)
{
	return (status & (1 << (unsigned)key)) != 0;
}

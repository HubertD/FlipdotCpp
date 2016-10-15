#include <GamepadKey.h>

void GamepadKey::update(unsigned ticks, bool isPressed)
{
	if (isPressed)
	{

		if (_tNextRepeat == 0)
		{
			_tNextRepeat = ticks + T_FIRST_REPEAT;
			setEvent(Event::DOWN);
			setEvent(Event::PRESS);
		} else {
			if (ticks >= _tNextRepeat)
			{
				_tNextRepeat = ticks + T_REPEAT;
				setEvent(Event::REPEAT);
				setEvent(Event::PRESS);
			}
		}

	} else {

		if (_tNextRepeat != 0)
		{
			_tNextRepeat = 0;
			setEvent(Event::UP);
		}

	}
}

void GamepadKey::update(unsigned ticks)
{
	update(ticks, isPressed());
}

void GamepadKey::resetEvents()
{
	_events = 0;
}

bool GamepadKey::isPressed()
{
	return _tNextRepeat != 0;
}

bool GamepadKey::hasDownEvent()
{
	return hasEvent(Event::DOWN);
}

bool GamepadKey::hasUpEvent()
{
	return hasEvent(Event::UP);
}

bool GamepadKey::hasPressEvent()
{
	return hasEvent(Event::PRESS);
}

bool GamepadKey::hasRepeatEvent()
{
	return hasEvent(Event::REPEAT);
}

void GamepadKey::setEvent(Event event)
{
	_events |= (1<< (unsigned)event);
}

bool GamepadKey::hasEvent(Event event)
{
	return (_events & (1<< (unsigned)event)) != 0;
}

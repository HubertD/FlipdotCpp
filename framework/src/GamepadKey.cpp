#include <GamepadKey.h>

void GamepadKey::update(unsigned ticks, bool isPressed)
{
	if (isPressed)
	{

		if (_tNextRepeat == 0)
		{
			_tNextRepeat = ticks + T_FIRST_REPEAT;
			_events |= (unsigned) Event::DOWN;
			_events |= (unsigned) Event::PRESS;
		} else {
			if (ticks >= _tNextRepeat)
			{
				_tNextRepeat = ticks + T_REPEAT;
				_events |= (unsigned) Event::REPEAT;
				_events |= (unsigned) Event::PRESS;
			}
		}

	} else {

		if (_tNextRepeat != 0)
		{
			_tNextRepeat = 0;
			_events |= (unsigned) Event::UP;
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
	return (_events & (unsigned)Event::DOWN) != 0;
}

bool GamepadKey::hasUpEvent()
{
	return (_events & (unsigned)Event::UP) != 0;
}

bool GamepadKey::hasPressEvent()
{
	return (_events & (unsigned)Event::PRESS) != 0;
}

bool GamepadKey::hasRepeatEvent()
{
	return (_events & (unsigned)Event::REPEAT) != 0;
}

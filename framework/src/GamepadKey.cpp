#include <GamepadKey.h>

void GamepadKey::update(unsigned ticks, bool isPressed)
{
	updateDebounce(ticks, isPressed);

	if (hasEvent(Event::DEBOUNCED_DOWN))
	{
		if (_tNextRepeat == 0)
		{
			_tNextRepeat = ticks + T_FIRST_REPEAT;
			setEvent(Event::DOWN, true);
			setEvent(Event::PRESS, true);
		} else {
			if (ticks >= _tNextRepeat)
			{
				_tNextRepeat = ticks + T_REPEAT;
				setEvent(Event::REPEAT, true);
				setEvent(Event::PRESS, true);
			}
		}

	} else {

		if (_tNextRepeat != 0)
		{
			_tNextRepeat = 0;
			setEvent(Event::UP, true);
		}

	}
}

void GamepadKey::update(unsigned ticks)
{
	update(ticks, hasEvent(Event::RAW_DOWN));
}

void GamepadKey::resetEvents()
{
	_status &= ~RESET_EVENT_MASK;
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

void GamepadKey::setEvent(Event event, bool isSet)
{
	if (isSet == hasEvent(event)) { return; }
	if (isSet)
	{
		_status |= (1<< (unsigned)event);
	} else {
		_status &= ~(1<< (unsigned)event);
	}
}

bool GamepadKey::hasEvent(Event event)
{
	return (_status & (1<< (unsigned)event)) != 0;
}

void GamepadKey::updateDebounce(unsigned ticks, bool isPressed)
{
	bool wasPressedBefore = hasEvent(Event::RAW_DOWN);
	setEvent(Event::RAW_DOWN, isPressed);

	if (isPressed != wasPressedBefore)
	{
		_tLastStateChange = ticks;
	}

	if ( (ticks - _tLastStateChange) >= T_DEBOUNCE )
	{
		setEvent(Event::DEBOUNCED_DOWN, isPressed);
	}
}

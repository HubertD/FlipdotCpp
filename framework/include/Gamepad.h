#pragma once

#include <GamepadKey.h>

class Gamepad
{
	public:
		GamepadKey North, South, West, East;
		GamepadKey A, B, Start, Select;

		void update(unsigned ticks)
		{
			North.update(ticks);
			South.update(ticks);
			West.update(ticks);
			East.update(ticks);
			A.update(ticks);
			B.update(ticks);
			Start.update(ticks);
			Select.update(ticks);
		}

		void resetEvents()
		{
			North.resetEvents();
			South.resetEvents();
			West.resetEvents();
			East.resetEvents();
			A.resetEvents();
			B.resetEvents();
			Start.resetEvents();
			Select.resetEvents();
		}
};

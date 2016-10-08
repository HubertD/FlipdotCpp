#pragma once

#include <stdint.h>

enum class FlipdotColor
{
	BLACK,
	WHITE
};

enum class PanelOrientation
{
	DEG_0,
	DEG_180
};

class PanelConfig
{
	public:
		const unsigned x;
		const unsigned y;
		const PanelOrientation orientation;
};

enum class GamepadKey
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_A,
	KEY_B,
	KEY_START,
	KEY_SELECT,
	KEY_NONE
};


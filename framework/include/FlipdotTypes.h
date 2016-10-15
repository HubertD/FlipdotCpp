#pragma once

#include <stdint.h>

enum class Color
{
	BLACK,
	WHITE
};

enum class Orientation
{
	DEG_0,
	DEG_90,
	DEG_180,
	DEG_270
};

class PanelConfig
{
	public:
		const unsigned x;
		const unsigned y;
		const Orientation orientation;
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


#pragma once

#include <FlipdotTypes.h>

constexpr unsigned NUM_PANELS = 4;
constexpr unsigned SCREEN_WIDTH = 32;
constexpr unsigned SCREEN_HEIGHT = 40;

constexpr PanelConfig PANEL_CONFG[] = {
		{ 0, 20, Orientation::DEG_180},
		{ 0,  0, Orientation::DEG_180},
		{16,  0, Orientation::DEG_0},
		{16, 20, Orientation::DEG_0}
};


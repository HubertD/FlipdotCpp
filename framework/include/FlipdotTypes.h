#pragma once

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

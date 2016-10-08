#pragma once

#include "ScreenBuffer.h"

class FlipdotPanel
{
	public:

		enum class Orientation
		{
			DEG_0,
			DEG_180
		};

		static constexpr unsigned ACTIVE_ROWS = 20;
		static constexpr unsigned ACTIVE_COLUMNS = 16;

		void configure(unsigned x, unsigned y, Orientation orientation);
		static uint8_t reverseByte(uint8_t b);
		void fillColumnRegister(ScreenBuffer &screen, unsigned column, uint8_t *buf);

	private:
		unsigned _x = 0;
		unsigned _y = 0;
		Orientation _orientation = Orientation::DEG_0;

};

inline void FlipdotPanel::configure(unsigned x, unsigned y, Orientation orientation)
{
	_x = x;
	_y = y;
	_orientation = orientation;
}

inline void FlipdotPanel::fillColumnRegister(ScreenBuffer &screen, unsigned column, uint8_t *buf)
{
	unsigned x = _x + column;
	unsigned data;

	switch (_orientation)
	{

		case Orientation::DEG_0:
			x = _x + column;
			data = (reverseByte(screen.get8Pixels(x, _y   )) << 24)
			     | (reverseByte(screen.get8Pixels(x, _y+8 )) << 16)
			     | (reverseByte(screen.get8Pixels(x, _y+16)) <<  8)
		     	 | (reverseByte(screen.get8Pixels(x, _y+24)) <<  0);
			data <<= (_y % 8);
			buf[0] = (data >> 8) & 0xF0;
			buf[1] = (data >> 16) & 0xFF;
			buf[2] = (data >> 24) & 0xFF;
			break;

		case Orientation::DEG_180:
			x = _x + (ACTIVE_COLUMNS-1) - column;
			data = (screen.get8Pixels(x, _y)    << 4)
			     | (screen.get8Pixels(x, _y+8)  << 12)
				 | (screen.get8Pixels(x, _y+16) << 20)
				 | (screen.get8Pixels(x, _y+24) << 28);
			data >>= (_y % 8);
			buf[0] = (data >> 0) & 0xF0;
			buf[1] = (data >> 8) & 0xFF;
			buf[2] = (data >> 16) & 0xFF;
			break;

	}
}

inline uint8_t FlipdotPanel::reverseByte(uint8_t b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

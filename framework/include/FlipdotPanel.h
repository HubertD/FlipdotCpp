#pragma once

#include <FlipdotTypes.h>
#include "ScreenBuffer.h"

class FlipdotPanel
{
	public:

		static constexpr unsigned ACTIVE_ROWS = 20;
		static constexpr unsigned ACTIVE_COLUMNS = 16;

		void configure(const PanelConfig &config);
		static uint8_t reverseByte(uint8_t b);
		void fillColumnRegister(ScreenBuffer &screen, unsigned column, uint8_t *buf);

		bool columnNeedsUpdate(unsigned column, FlipdotColor color, ScreenBuffer& onScreenBuffer, ScreenBuffer& offScreenBuffer);
		void updateOnScreenBuffer(unsigned column, FlipdotColor color, ScreenBuffer& onScreenBuffer, ScreenBuffer& offScreenBuffer);

	private:
		unsigned _x = 0;
		unsigned _y = 0;
		PanelOrientation _orientation = PanelOrientation::DEG_0;

		unsigned getRotatedColumn(unsigned column);
		unsigned getScreenX(unsigned column);
		bool columnNeedsUpdateHelper(FlipdotColor color, unsigned screenX, unsigned screenY, ScreenBuffer& onScreenBuffer, ScreenBuffer& offScreenBuffer);
};

inline void FlipdotPanel::configure(const PanelConfig &config)
{
	_x = config.x;
	_y = config.y;
	_orientation = config.orientation;
}

inline unsigned FlipdotPanel::getRotatedColumn(unsigned column)
{
	return (_orientation == PanelOrientation::DEG_0) ? column : (ACTIVE_COLUMNS-1) - column;
}

inline unsigned FlipdotPanel::getScreenX(unsigned column)
{
	return _x + getRotatedColumn(column);
}

inline void FlipdotPanel::fillColumnRegister(ScreenBuffer &screen, unsigned column, uint8_t *buf)
{
	unsigned data;
	unsigned screenX = getScreenX(column);

	switch (_orientation)
	{

		case PanelOrientation::DEG_0:
			data = (reverseByte(screen.get8Pixels(screenX, _y   )) << 24)
			     | (reverseByte(screen.get8Pixels(screenX, _y+8 )) << 16)
			     | (reverseByte(screen.get8Pixels(screenX, _y+16)) <<  8)
		     	 | (reverseByte(screen.get8Pixels(screenX, _y+24)) <<  0);
			data <<= (_y % 8);
			buf[0] = (data >> 8) & 0xF0;
			buf[1] = (data >> 16) & 0xFF;
			buf[2] = (data >> 24) & 0xFF;
			break;

		case PanelOrientation::DEG_180:
			data = (screen.get8Pixels(screenX, _y)    << 4)
			     | (screen.get8Pixels(screenX, _y+8)  << 12)
				 | (screen.get8Pixels(screenX, _y+16) << 20)
				 | (screen.get8Pixels(screenX, _y+24) << 28);
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

inline bool FlipdotPanel::columnNeedsUpdate(
	unsigned column,
	FlipdotColor color,
	ScreenBuffer& onScreenBuffer,
	ScreenBuffer& offScreenBuffer
)
{
	unsigned screenX = getScreenX(column);

	// FIXME screenbuffer y overflow at last panel, offset=16?
	return columnNeedsUpdateHelper(color, screenX, _y,    onScreenBuffer, offScreenBuffer)
		 | columnNeedsUpdateHelper(color, screenX, _y+8,  onScreenBuffer, offScreenBuffer)
		 | columnNeedsUpdateHelper(color, screenX, _y+16, onScreenBuffer, offScreenBuffer);
}

inline bool FlipdotPanel::columnNeedsUpdateHelper(
	FlipdotColor color,
	unsigned screenX,
	unsigned screenY,
	ScreenBuffer& onScreenBuffer,
	ScreenBuffer& offScreenBuffer
)
{
	auto on  = onScreenBuffer.get8Pixels(screenX, screenY);
	auto off = offScreenBuffer.get8Pixels(screenX, screenY);

	if (color==FlipdotColor::BLACK)
	{
		return (on | off) != on;
	} else {
		return (on & off) != on;
	}
}

inline void FlipdotPanel::updateOnScreenBuffer(
	unsigned column,
	FlipdotColor color,
	ScreenBuffer& onScreenBuffer,
	ScreenBuffer& offScreenBuffer
)
{
	unsigned screenX = getScreenX(column);
	if (color==FlipdotColor::BLACK)
	{
		onScreenBuffer.or8Pixels(screenX, _y+0,  offScreenBuffer.get8Pixels(screenX, _y+0));
		onScreenBuffer.or8Pixels(screenX, _y+8,  offScreenBuffer.get8Pixels(screenX, _y+8));
		onScreenBuffer.or8Pixels(screenX, _y+16, offScreenBuffer.get8Pixels(screenX, _y+16));
	} else {
		onScreenBuffer.and8Pixels(screenX, _y+0,  offScreenBuffer.get8Pixels(screenX, _y+0));
		onScreenBuffer.and8Pixels(screenX, _y+8,  offScreenBuffer.get8Pixels(screenX, _y+8));
		onScreenBuffer.and8Pixels(screenX, _y+16, offScreenBuffer.get8Pixels(screenX, _y+16));
	}
}


#pragma once

#include <FlipdotTypes.h>
#include "ScreenBuffer.h"

class FlipdotPanel
{
	public:

		static constexpr unsigned ACTIVE_ROWS = 20;
		static constexpr unsigned ACTIVE_COLUMNS = 16;

		void configure(const PanelConfig &config);
		void fillColumnRegister(ScreenBuffer &screen, unsigned column, uint8_t *buf);

		bool columnNeedsUpdate(unsigned column, FlipdotColor color, ScreenBuffer& onScreenBuffer, ScreenBuffer& offScreenBuffer);
		void updateOnScreenBuffer(unsigned column, FlipdotColor color, ScreenBuffer& onScreenBuffer, ScreenBuffer& offScreenBuffer);

	private:
		unsigned _x = 0;
		unsigned _y = 0;
		PanelOrientation _orientation = PanelOrientation::DEG_0;

		uint8_t reverseByte(uint8_t b);
		unsigned getRotatedColumn(unsigned column);
		unsigned getScreenX(unsigned column);
		bool columnNeedsUpdateHelper(FlipdotColor color, unsigned screenX, unsigned screenY, ScreenBuffer& onScreenBuffer, ScreenBuffer& offScreenBuffer);
};

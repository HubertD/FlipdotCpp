#pragma once

#include <stdint.h>

#include <FlipdotConfig.h>
#include "IFlipdotDriver.h"
#include "FlipdotPanel.h"

class FlipdotFramebuffer
{
	public:
		FlipdotFramebuffer(IFlipdotDriver &driver);

		void configurePanels();
		void init();
		void update(unsigned ticks);

		void flush();

		void clear();
		void setPixel(unsigned x, unsigned y, bool value);
		bool getPixel(unsigned x, unsigned y);

		ScreenBuffer &getOnScreenBuffer();
		ScreenBuffer &getOffScreenBuffer();

	private:
		static const unsigned DOT_FLIP_TIME_MS = 15;

		IFlipdotDriver &_driver;
		FlipdotPanel _panels[NUM_PANELS];
		ScreenBuffer _offScreenBuffer;
		ScreenBuffer _onScreenBuffer;

		uint32_t _updateCounter = 0;
		uint32_t _tWaitDotsFlip = 0;

		void selectColumn(unsigned column);
		void updateColumn(unsigned column, FlipdotColor color);
		void flushColor(FlipdotColor color);

		bool columnNeedsUpdate(unsigned column, FlipdotColor color);

};


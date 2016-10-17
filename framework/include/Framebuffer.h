#pragma once

#include <stdint.h>

#include <FlipdotConfig.h>
#include "IFlipdotDriver.h"
#include "FlipdotPanel.h"
#include <IDrawable.h>

struct Rect
{
	int x, y, width, height;
};

class Framebuffer
{
	public:
		Framebuffer(IFlipdotDriver &driver);

		void configurePanels();
		void init();
		void update(unsigned ticks);

		void flush();

		void clear();
		void setPixel(int x, int y, bool value);
		bool getPixel(int x, int y);

		void drawRect(int x, int y, int dx, int dy, bool value);
		void drawRect(Rect rect, bool value);
		void draw(int x, int y, const IDrawable &drawable, bool doInvert=false);

		ScreenBuffer &getOnScreenBuffer();
		ScreenBuffer &getOffScreenBuffer();

	private:
		static const unsigned DOT_FLIP_TIME_MS = 6;

		IFlipdotDriver &_driver;
		FlipdotPanel _panels[NUM_PANELS];
		ScreenBuffer _offScreenBuffer;
		ScreenBuffer _onScreenBuffer;

		uint32_t _updateCounter = 0;
		uint32_t _tWaitDotsFlip = 0;

		void selectColumn(unsigned column);
		void updateColumn(unsigned column, Color color);
		void flushColor(Color color);

		bool columnNeedsUpdate(unsigned column, Color color);

};


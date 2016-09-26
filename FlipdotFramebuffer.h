#pragma once

#include <stdint.h>
#include "IFlipdotFramebuffer.h"
#include "IFlipdotDriver.h"

class FlipdotFramebuffer : public IFlipdotFramebuffer
{

	public:
		FlipdotFramebuffer(IFlipdotDriver &driver, unsigned numPanelsX, unsigned numPanelsY, uint8_t *buffer, unsigned bufferSize);
		~FlipdotFramebuffer() override;

		void init() override;
		void flush() override;
		void update() override;

		void clear() override;
		void setPixel(unsigned x, unsigned y, bool value) override;

	private:
		static const unsigned COLUMNS = 16;
		static const unsigned ROWS_PER_PANEL = 24;
		static const unsigned ACTIVE_ROWS_PER_PANEL = 20;

		typedef enum {
			COLOR_WHITE,
			COLOR_BLACK
		} color_t;

		IFlipdotDriver &_driver;
		unsigned _numPanelsX;
		unsigned _numPanelsY;
		unsigned _bytesPerColumn;
		uint8_t *_buffer;
		unsigned _bufferSize;

		uint32_t _dirty;
		uint32_t _currentColumn;
		color_t _currentColor;

		void flipCurrentColor();

		void updateColumn(color_t color, unsigned column);
		void flushColor(color_t color);

		bool isColumnDirty(color_t color, unsigned column);
		bool hasDirtyColumns();
		void setColumnDirty(unsigned column);
		void setColumnClean(color_t color, unsigned column);

};

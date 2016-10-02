#pragma once

#include <stdint.h>
#include "IFlipdotFramebuffer.h"
#include "IFlipdotDriver.h"

class FlipdotFramebufferBase : public IFlipdotFramebuffer
{

	public:
		~FlipdotFramebufferBase() override;

		void init() override;
		void flush() override;
		void update() override;

		void clear() override;
		void setPixel(unsigned x, unsigned y, bool value) override;

	protected:
		FlipdotFramebufferBase(IFlipdotDriver &driver, unsigned numPanelsX, unsigned numPanelsY, uint8_t *buffer, unsigned bufferSize);

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

template <unsigned NUM_PANELS_X, unsigned NUM_PANELS_Y> class FlipdotFramebuffer : public FlipdotFramebufferBase
{
	private:
		static const unsigned BYTES_PER_COLUMN = (ROWS_PER_PANEL * (NUM_PANELS_X * NUM_PANELS_Y)) / 8;
		uint8_t _implBuffer[COLUMNS*BYTES_PER_COLUMN];

	public:
		FlipdotFramebuffer(IFlipdotDriver &driver)
			: FlipdotFramebufferBase(driver, NUM_PANELS_X, NUM_PANELS_Y, _implBuffer, sizeof(_implBuffer))
		{
		}

};

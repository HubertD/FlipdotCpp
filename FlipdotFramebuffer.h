#pragma once

#include <stdint.h>

#include "../gfx/driver/IFlipdotDriver.h"
#include "../gfx/IFlipdotFramebuffer.h"

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
		FlipdotFramebufferBase(IFlipdotDriver &driver, unsigned numPanelsX, unsigned numPanelsY, uint8_t *onScreenBuffer, uint8_t *offScreenBuffer, unsigned bufferSize);

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
		uint8_t *_offScreenBuffer;
		uint8_t *_onScreenBuffer;
		unsigned _bufferSize;

		uint32_t _currentColumn;

		void flipCurrentColor();

		void selectColumn(unsigned column);
		void updateColumn(color_t color, unsigned column);
		void flushColor(color_t color);

		void copyColumnToOnScreenBuffer(color_t color, unsigned column);

		bool mustUpdateBlack(unsigned column);
		bool mustUpdateWhite(unsigned column);

		unsigned getPhysicalX(unsigned x);
		unsigned getPhysicalY_ignoringInactiveRows(unsigned x, unsigned y);
		unsigned getPhysicalY(unsigned x, unsigned y);

};

template <unsigned NUM_PANELS_X, unsigned NUM_PANELS_Y> class FlipdotFramebuffer : public FlipdotFramebufferBase
{
	private:
		static const unsigned BYTES_PER_COLUMN = (ROWS_PER_PANEL * (NUM_PANELS_X * NUM_PANELS_Y)) / 8;
		uint8_t _implOnScreenBuffer[COLUMNS*BYTES_PER_COLUMN];
		uint8_t _implOffScreenBuffer[COLUMNS*BYTES_PER_COLUMN];

	public:
		FlipdotFramebuffer(IFlipdotDriver &driver)
		  : FlipdotFramebufferBase(
			    driver,
				NUM_PANELS_X,
				NUM_PANELS_Y,
				_implOnScreenBuffer,
				_implOffScreenBuffer,
				sizeof(_implOnScreenBuffer)
		    ),
			_implOnScreenBuffer{0},
			_implOffScreenBuffer{0}
		{
		}

};

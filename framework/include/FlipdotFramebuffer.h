#pragma once

#include <stdint.h>

#include "IFlipdotDriver.h"
#include "IFlipdotFramebuffer.h"

class FlipdotFramebufferBase : public IFlipdotFramebuffer
{

	public:
		~FlipdotFramebufferBase() override;

		void init() override;
		void update(unsigned ticks) override;

		void flush() override;

		void clear() override;
		void setPixel(unsigned x, unsigned y, bool value) override;
		bool getPixel(unsigned x, unsigned y) override;

		unsigned getScreenWidth() override;
		unsigned getScreenHeight() override;

	protected:
		FlipdotFramebufferBase(IFlipdotDriver &driver, unsigned numPanelsX, unsigned numPanelsY, uint8_t *onScreenBuffer, uint8_t *offScreenBuffer, unsigned bufferSize);

	private:
		static const unsigned COLUMNS = 16;
		static const unsigned ROWS_PER_PANEL = 24;
		static const unsigned ACTIVE_ROWS_PER_PANEL = 20;
		static const unsigned DOT_FLIP_TIME_MS = 15;

		enum class Color {
			WHITE,
			BLACK
		};

		IFlipdotDriver &_driver;
		unsigned _numPanelsX;
		unsigned _numPanelsY;
		unsigned _bytesPerColumn;
		uint8_t *_offScreenBuffer;
		uint8_t *_onScreenBuffer;
		unsigned _bufferSize;

		uint32_t _currentColumn = 0;
		uint32_t _tWaitDotsFlip = 0;

		void selectColumn(unsigned column);
		void updateColumn(Color color, unsigned column);
		void flushColor(Color color);

		void copyColumnToOnScreenBuffer(Color color, unsigned column);

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

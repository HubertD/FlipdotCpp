#pragma once

#include "IFlipdotFramebuffer.h"

class FlipdotFramebuffer : public IFlipdotFramebuffer
{

	public:
		FlipdotFramebuffer(IFlipdotDriver &driver);

		void init() override;
		void flush() override;
		void update() override;

		void clear() override;
		void setPixel(unsigned x, unsigned y, bool value) override;

	private:
		static const unsigned COLUMNS = 16;
		static const unsigned ROWS_PER_PANEL = 24;
		static const unsigned ACTIVE_ROWS_PER_PANEL = 20;
		static const unsigned NUM_PANELS_X = 2;
		static const unsigned NUM_PANELS_Y = 2;
		static const unsigned NUM_PANELS = (NUM_PANELS_X * NUM_PANELS_Y);
		static const unsigned BITS_PER_COLUMN = ROWS_PER_PANEL * NUM_PANELS;
		static const unsigned BYTES_PER_COLUMN = BITS_PER_COLUMN / 8;

		typedef enum {
			COLOR_WHITE,
			COLOR_BLACK
		} color_t;

		IFlipdotDriver &_driver;

		uint8_t _buffer[COLUMNS * BYTES_PER_COLUMN];
		uint32_t _dirty;
		uint32_t _currentColumn;
		color_t _currentColor;

		void flipCurrentColor();

		void selectColumn(unsigned column);
		void writeColumnByte(uint8_t data);
		void writeColumnData(uint8_t *data);
		void updateColumn(color_t color, unsigned column);
		void flushColor(color_t color);

		bool isColumnDirty(color_t color, unsigned column);
		bool hasDirtyColumns();
		void setColumnDirty(unsigned column);
		void setColumnClean(color_t color, unsigned column);
};
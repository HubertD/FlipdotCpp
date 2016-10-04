#pragma once

#include <stdint.h>

class VirtualFlipdotPanel
{
	public:
		static const unsigned COLUMNS = 16;
		static const unsigned ACTIVE_ROWS = 20;
		static const unsigned VIRTUAL_ROWS = 24;

		VirtualFlipdotPanel();
		virtual ~VirtualFlipdotPanel();

		void selectColumn(uint8_t column);
		void shiftInputColumnByte(uint8_t data);
		uint8_t getOutputColumnByte();
		void strobe();

		void setOutputEnableBlack();
		void setOutputEnableWhite();

		bool getDotColor(unsigned x, unsigned y);

	private:
		static const unsigned BYTES_PER_COLUMN = VIRTUAL_ROWS/8;
		static const unsigned COLUMN_OUTPUT_BYTE = BYTES_PER_COLUMN;

		typedef bool buffer_t[COLUMNS * VIRTUAL_ROWS];

		buffer_t _offScreenBuffer;
		buffer_t _onScreenBuffer;
		uint8_t _columnShiftRegister[BYTES_PER_COLUMN+1];
		uint8_t _selectedColumn;

		void setBufferBit(buffer_t &buffer, unsigned x, unsigned y, bool value);
		bool getBufferBit(buffer_t &buffer, unsigned x, unsigned y);
};


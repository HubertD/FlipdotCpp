#include "CubeMxFlipdotFramebuffer.h"
#include "stm32f0xx_hal.h"

CubeMxFlipdotFramebuffer::CubeMxFlipdotFramebuffer()
{
}

void CubeMxFlipdotFramebuffer::init()
{
	clear();
	flush();
}

void CubeMxFlipdotFramebuffer::update()
{
	for (unsigned i=0; i<COLUMNS; i++)
	{
		if (_dirty & (1<<i))
		{
			selectColumn(i);

			writeColumn(&_buffer[i*BYTES_PER_COLUMN]);

			setOutputEnableBlack();
			delayFlipDots();

			setOutputEnableWhite();
			delayFlipDots();

			setOutputEnableNone();

			break; /* always update max one column per update() call */
		}
	}
}

void CubeMxFlipdotFramebuffer::flush()
{
	shiftColumnRegister(1);

	for (int i=0; i<COLUMNS; i++)
	{
		writeColumn(&_buffer[i*BYTES_PER_COLUMN]);

		setOutputEnableBlack();
		delayFlipDots();

		setOutputEnableWhite();
		delayFlipDots();

		setOutputEnableNone();

		shiftColumnRegister(0);
	}
}

void CubeMxFlipdotFramebuffer::clear()
{
	for (unsigned i=0; i<sizeof(_buffer); i++) {
		_buffer[i] = 0;
	}

	for (unsigned i=0; i<COLUMNS; i++) {
		_dirty |= (1<<i);
	}
}

void CubeMxFlipdotFramebuffer::setPixel(unsigned x, unsigned y, bool value)
{
	unsigned column = x % COLUMNS;
	unsigned panel = ((x/COLUMNS) * NUM_PANELS_Y) + (y / ACTIVE_ROWS_PER_PANEL);
	unsigned row = (panel * ROWS_PER_PANEL) + (y % ACTIVE_ROWS_PER_PANEL);
	unsigned bytePos = (column * BYTES_PER_COLUMN) + (row/8);
	unsigned bitMask = 1<<(row % 8);

	if (value) {
		_buffer[bytePos] |= bitMask;
	} else {
		_buffer[bytePos] &= ~bitMask;
	}

	_dirty |= (1<<column);
}

void CubeMxFlipdotFramebuffer::setOutputEnableBlack()
{
	HAL_GPIO_WritePin(FD_COL_OE_GPIO_Port, FD_COL_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(FD_ROW_OE_GPIO_Port, FD_ROW_OE_Pin, GPIO_PIN_SET);
}

void CubeMxFlipdotFramebuffer::setOutputEnableWhite()
{
	HAL_GPIO_WritePin(FD_ROW_OE_GPIO_Port, FD_ROW_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(FD_COL_OE_GPIO_Port, FD_COL_OE_Pin, GPIO_PIN_SET);
}

void CubeMxFlipdotFramebuffer::setOutputEnableNone()
{
	HAL_GPIO_WritePin(FD_ROW_OE_GPIO_Port, FD_ROW_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(FD_COL_OE_GPIO_Port, FD_COL_OE_Pin, GPIO_PIN_RESET);
}

void CubeMxFlipdotFramebuffer::strobe()
{
	HAL_GPIO_WritePin(FD_STROBE_GPIO_Port, FD_STROBE_Pin, GPIO_PIN_SET);
	delayClock();
	HAL_GPIO_WritePin(FD_STROBE_GPIO_Port, FD_STROBE_Pin, GPIO_PIN_RESET);
}

void CubeMxFlipdotFramebuffer::shiftColumnRegister(bool in)
{
	HAL_GPIO_WritePin(FD_COL_DATA_GPIO_Port, FD_COL_DATA_Pin, in ? GPIO_PIN_SET : GPIO_PIN_RESET);
	delayClock();
	HAL_GPIO_WritePin(FD_COL_CLK_GPIO_Port, FD_COL_CLK_Pin, GPIO_PIN_SET);
	delayClock();
	HAL_GPIO_WritePin(FD_COL_CLK_GPIO_Port, FD_COL_CLK_Pin, GPIO_PIN_RESET);
}

void CubeMxFlipdotFramebuffer::selectColumn(unsigned column)
{
	uint32_t sr = (1<<column);
	for (unsigned i=0; i<COLUMNS; i++)
	{
		shiftColumnRegister(sr & (1<<i));
	}
}

void CubeMxFlipdotFramebuffer::shiftRowRegister(bool in)
{
	HAL_GPIO_WritePin(FD_ROW_DATA_GPIO_Port, FD_ROW_DATA_Pin, in ? GPIO_PIN_SET : GPIO_PIN_RESET);
	delayClock();
    HAL_GPIO_WritePin(FD_ROW_CLK_GPIO_Port, FD_ROW_CLK_Pin, GPIO_PIN_SET);
	delayClock();
    HAL_GPIO_WritePin(FD_ROW_CLK_GPIO_Port, FD_ROW_CLK_Pin, GPIO_PIN_RESET);
}

void CubeMxFlipdotFramebuffer::writeColumnByte(uint8_t data)
{
	for (int i=0; i<8; i++) {
		shiftRowRegister(data & (1<<i));
	}
}

void CubeMxFlipdotFramebuffer::writeColumn(uint8_t* data)
{
	for (int i=0; i<BYTES_PER_COLUMN; i++) {
		writeColumnByte(data[i]);
	}
	strobe();
}

void CubeMxFlipdotFramebuffer::delayClock()
{
}

void CubeMxFlipdotFramebuffer::delayFlipDots()
{
}

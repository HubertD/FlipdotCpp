#include "CubeMxFlipdotFramebuffer.h"
#include "stm32f0xx_hal.h"

CubeMxFlipdotFramebuffer::CubeMxFlipdotFramebuffer()
  : _dirty(0), _currentColumn(0), _currentColor(COLOR_BLACK)
{
}

void CubeMxFlipdotFramebuffer::init()
{
	clear();
	flush();
}

void CubeMxFlipdotFramebuffer::updateColumn(color_t color, unsigned column)
{
	selectColumn(column);
	writeColumnData(&_buffer[column*BYTES_PER_COLUMN]);

	setOutputEnable(color);
	delayFlipDots();
	setOutputEnableNone();

	setColumnClean(color, column);
}

void CubeMxFlipdotFramebuffer::flipCurrentColor()
{
	_currentColor = (_currentColor==COLOR_BLACK) ? COLOR_WHITE : COLOR_BLACK;
}

void CubeMxFlipdotFramebuffer::update()
{
	while (hasDirtyColumns())
	{
		if (++_currentColumn >= COLUMNS)
		{
			flipCurrentColor();
			_currentColumn = 0;
		}

		if (isColumnDirty(_currentColor, _currentColumn))
		{
			updateColumn(_currentColor, _currentColumn);
			return; /* always update max one column per update() call */
		}
	}

}

void CubeMxFlipdotFramebuffer::flushColor(color_t color)
{
	for (unsigned i=0; i<COLUMNS; i++)
	{
		updateColumn(color, i);
	}
}


void CubeMxFlipdotFramebuffer::flush()
{
	flushColor(COLOR_BLACK);
	flushColor(COLOR_WHITE);
}

void CubeMxFlipdotFramebuffer::clear()
{
	for (unsigned i=0; i<sizeof(_buffer); i++) {
		_buffer[i] = 0;
	}

	for (unsigned i=0; i<COLUMNS; i++) {
		setColumnDirty(i);
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

	setColumnDirty(column);
}

void CubeMxFlipdotFramebuffer::setOutputEnable(color_t color)
{
	if (color==COLOR_BLACK) {
		HAL_GPIO_WritePin(FD_WHITE_OE_GPIO_Port, FD_WHITE_OE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(FD_BLACK_OE_GPIO_Port, FD_BLACK_OE_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(FD_BLACK_OE_GPIO_Port, FD_BLACK_OE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(FD_WHITE_OE_GPIO_Port, FD_WHITE_OE_Pin, GPIO_PIN_SET);
	}
}

void CubeMxFlipdotFramebuffer::setOutputEnableNone()
{
	HAL_GPIO_WritePin(FD_WHITE_OE_GPIO_Port, FD_WHITE_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(FD_BLACK_OE_GPIO_Port, FD_BLACK_OE_Pin, GPIO_PIN_RESET);
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

void CubeMxFlipdotFramebuffer::writeColumnData(uint8_t* data)
{
	for (int i=0; i<BYTES_PER_COLUMN; i++) {
		writeColumnByte(data[i]);
	}
	strobe();
}

void CubeMxFlipdotFramebuffer::setColumnDirty(unsigned column)
{
	_dirty |= (1<<column) | (1<<COLUMNS+column);
}

void CubeMxFlipdotFramebuffer::setColumnClean(color_t color, unsigned column)
{
	if (color==COLOR_BLACK) {
		_dirty &= ~(1<<column);
	} else {
		_dirty &= ~(1<<(COLUMNS+column));
	}
}

bool CubeMxFlipdotFramebuffer::isColumnDirty(color_t color, unsigned column)
{
	if (color==COLOR_BLACK) {
		return _dirty & (1<<column);
	} else {
		return _dirty & (1<<(COLUMNS+column));
	}
}

bool CubeMxFlipdotFramebuffer::hasDirtyColumns()
{
	return _dirty != 0;
}

void CubeMxFlipdotFramebuffer::delayClock()
{
}

void CubeMxFlipdotFramebuffer::delayFlipDots()
{
}


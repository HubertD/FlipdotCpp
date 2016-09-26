#include "FlipdotFramebuffer.h"

FlipdotFramebuffer::FlipdotFramebuffer(IFlipdotDriver &driver)
  : _driver(driver), _dirty(0), _currentColumn(0), _currentColor(COLOR_BLACK)
{
}

void FlipdotFramebuffer::init()
{
	clear();
	flush();
}

void FlipdotFramebuffer::updateColumn(color_t color, unsigned column)
{
	selectColumn(column);
	writeColumnData(&_buffer[column*BYTES_PER_COLUMN]);

	if (color==COLOR_BLACK) {
		_driver.setOutputEnableBlack();
	} else {
		_driver.setOutputEnableWhite();
	}
	_driver.delayFlipDots();
	_driver.setOutputEnableNone();

	setColumnClean(color, column);
}

void FlipdotFramebuffer::flipCurrentColor()
{
	_currentColor = (_currentColor==COLOR_BLACK) ? COLOR_WHITE : COLOR_BLACK;
}

void FlipdotFramebuffer::update()
{
	while (hasDirtyColumns())
	{
		if (++_currentColumn >= COLUMNS) {
			flipCurrentColor();
			_currentColumn = 0;
		}

		if (isColumnDirty(_currentColor, _currentColumn)) {
			updateColumn(_currentColor, _currentColumn);
			return; /* always update max one column per update() call */
		}
	}

}

void FlipdotFramebuffer::flushColor(color_t color)
{
	for (unsigned i=0; i<COLUMNS; i++)
	{
		updateColumn(color, i);
	}
}


void FlipdotFramebuffer::flush()
{
	flushColor(COLOR_BLACK);
	flushColor(COLOR_WHITE);
}

void FlipdotFramebuffer::clear()
{
	for (unsigned i=0; i<sizeof(_buffer); i++)
	{
		_buffer[i] = 0;
	}

	for (unsigned i=0; i<COLUMNS; i++)
	{
		setColumnDirty(i);
	}
}

void FlipdotFramebuffer::setPixel(unsigned x, unsigned y, bool value)
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

void FlipdotFramebuffer::selectColumn(unsigned column)
{
	uint32_t sr = (1<<column);
	for (unsigned i=0; i<COLUMNS; i++)
	{
		_driver.shiftColumnRegister(sr & (1<<i));
	}
}

void FlipdotFramebuffer::writeColumnByte(uint8_t data)
{
	for (int i=0; i<8; i++)
	{
		_driver.shiftRowRegister(data & (1<<i));
	}
}

void FlipdotFramebuffer::writeColumnData(uint8_t* data)
{
	for (int i=0; i<BYTES_PER_COLUMN; i++)
	{
		writeColumnByte(data[i]);
	}
	_driver.strobe();
}

void FlipdotFramebuffer::setColumnDirty(unsigned column)
{
	_dirty |= (1<<column) | (1<<COLUMNS+column);
}

void FlipdotFramebuffer::setColumnClean(color_t color, unsigned column)
{
	if (color==COLOR_WHITE) {
		column += COLUMNS;
	}
	_dirty &= ~(1<<column);
}

bool FlipdotFramebuffer::isColumnDirty(color_t color, unsigned column)
{
	if (color==COLOR_WHITE) {
		column += COLUMNS;
	}
	return _dirty & (1<<column);
}

bool FlipdotFramebuffer::hasDirtyColumns()
{
	return _dirty != 0;
}


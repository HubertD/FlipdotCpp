#include "../gfx/FlipdotFramebuffer.h"

FlipdotFramebufferBase::FlipdotFramebufferBase(IFlipdotDriver &driver, unsigned numPanelsX, unsigned numPanelsY, uint8_t *buffer, unsigned bufferSize)
  : _driver(driver),
	_numPanelsX(numPanelsX),
	_numPanelsY(numPanelsY),
	_bytesPerColumn((ROWS_PER_PANEL * (numPanelsX * numPanelsY)) / 8),
	_buffer(buffer),
	_bufferSize(bufferSize),
	_dirty(0),
	_currentColumn(0),
	_currentColor(COLOR_BLACK)
{
}

FlipdotFramebufferBase::~FlipdotFramebufferBase()
{
}

void FlipdotFramebufferBase::init()
{
	clear();
	flush();
}

void FlipdotFramebufferBase::update()
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

void FlipdotFramebufferBase::flush()
{
	flushColor(COLOR_BLACK);
	flushColor(COLOR_WHITE);
}

void FlipdotFramebufferBase::flushColor(color_t color)
{
	for (unsigned i=0; i<COLUMNS; i++)
	{
		updateColumn(color, i);
	}
}

void FlipdotFramebufferBase::clear()
{
	for (unsigned y=0; y<_numPanelsY*ACTIVE_ROWS_PER_PANEL; y++)
	{
		for (unsigned x=0; x<_numPanelsX*COLUMNS; x++)
		{
			setPixel(x, y, false);
		}
	}
}

void FlipdotFramebufferBase::setPixel(unsigned x, unsigned y, bool value)
{
	auto column = getPhysicalX(x);
	auto row = getPhysicalY(x, y);

	unsigned bytePos = (column * _bytesPerColumn) + 11 - (row / 8);
	unsigned bitMask = 1<<(row % 8);

	if (value)
	{
		if ((_buffer[bytePos] & bitMask) == 0)
		{
			_buffer[bytePos] |= bitMask;
			setColumnDirty(column);
		}
	} else {
		if ((_buffer[bytePos] & bitMask) != 0)
		{
			_buffer[bytePos] &= ~bitMask;
			setColumnDirty(column);
		}
	}

}

void FlipdotFramebufferBase::selectColumn(unsigned column)
{
	uint8_t row_data[] = {
		((1<<column) >> 8) & 0xFF,
		(1<<column) & 0xFF
	};
	_driver.writeRowData(row_data, sizeof(row_data));
}

void FlipdotFramebufferBase::updateColumn(color_t color, unsigned column)
{
	selectColumn(column);
	_driver.writeColumnData(&_buffer[column*_bytesPerColumn], _bytesPerColumn);
	_driver.strobe();

	if (color==COLOR_BLACK) {
		_driver.setOutputEnableBlack();
	} else {
		_driver.setOutputEnableWhite();
	}
	_driver.delayFlipDots();
	_driver.setOutputEnableNone();

	setColumnClean(color, column);
}

void FlipdotFramebufferBase::flipCurrentColor()
{
	_currentColor = (_currentColor==COLOR_BLACK) ? COLOR_WHITE : COLOR_BLACK;
}

void FlipdotFramebufferBase::setColumnDirty(unsigned column)
{
	_dirty |= ((1<<column) | (1<<(COLUMNS+column)));
}

void FlipdotFramebufferBase::setColumnClean(color_t color, unsigned column)
{
	if (color==COLOR_WHITE) {
		column += COLUMNS;
	}
	_dirty &= ~(1<<column);
}

bool FlipdotFramebufferBase::isColumnDirty(color_t color, unsigned column)
{
	if (color==COLOR_WHITE) {
		column += COLUMNS;
	}
	return _dirty & (1<<column);
}

bool FlipdotFramebufferBase::hasDirtyColumns()
{
	return _dirty != 0;
}

unsigned FlipdotFramebufferBase::getPhysicalX(unsigned x)
{
	/*
	 *                                         /---\
	 * 0, 1, 2, ..., 14, 15, | 15, 14, ..., 1, 0, | 0, 1, ....
	 *                     \___/
	 */

	bool doFlip = ((x / COLUMNS) % 2) != 0;
	unsigned logicalX = x % COLUMNS;
	return doFlip ? (COLUMNS-1 - logicalX) : logicalX;
}

unsigned FlipdotFramebufferBase::getPhysicalY_ignoringInactiveRows(unsigned x, unsigned y)
{
	/*
	 *          /------\
	 * 0,    | 79,   | 80,
	 * 1,    | 78,   | 81,
	 * ...,  | ...,  | ...,
	 * 38,   | 41,   | 118,
	 * 39,   | 40,   | 119,
	 *   \_____/
	 */

	const unsigned DOTS_PER_ROW = _numPanelsY * ACTIVE_ROWS_PER_PANEL;

	unsigned panel_x = x / COLUMNS;

	return ( (panel_x % 2) == 0)
		   ? (panel_x * DOTS_PER_ROW) + y
		   : (panel_x * DOTS_PER_ROW) + (DOTS_PER_ROW-1 - y);
}


unsigned FlipdotFramebufferBase::getPhysicalY(unsigned x, unsigned y)
{
	/*
	 *          /------\
	 * 0,    | [d3], | 80,
	 * 1,    | [d2], | 81,
	 * ...,  | [d1], | ...,
	 * 19,   | [d0],
	 * [d0], | 79,
	 * [d1], | 78,
	 * [d2], | ...,
	 * [d3], |
	 * 20,   |
	 * 21,   |
	 * ...,  | ...,  | ...,
	 * 38,   | 45,   | 118,
	 * 39,   | 44,   | 119,
	 * [d0], | 43,
	 * [d1], | 42,
	 * [d2], | 41,
	 * [d3]  | 40,
	 *   \_____/
	 */

	unsigned py = getPhysicalY_ignoringInactiveRows(x, y);
	return py + (4 * (py/ACTIVE_ROWS_PER_PANEL));
}

#include "../gfx/FlipdotFramebuffer.h"

FlipdotFramebufferBase::FlipdotFramebufferBase(IFlipdotDriver &driver, unsigned numPanelsX, unsigned numPanelsY, uint8_t *onScreenBuffer, uint8_t *offScreenBuffer, unsigned bufferSize)
  : _driver(driver),
	_numPanelsX(numPanelsX),
	_numPanelsY(numPanelsY),
	_bytesPerColumn((ROWS_PER_PANEL * (numPanelsX * numPanelsY)) / 8),
	_offScreenBuffer(offScreenBuffer),
	_onScreenBuffer(onScreenBuffer),
	_bufferSize(bufferSize),
	_currentColumn(0)
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
	unsigned startColumn = _currentColumn;

	do {
		_currentColumn = (_currentColumn + 1) % (2*COLUMNS);

		if (_currentColumn < COLUMNS) {
			if (mustUpdateBlack(_currentColumn)) {
				updateColumn(COLOR_BLACK, _currentColumn);
				return; /* always update max one column per update() call */
			}
		} else {
			if (mustUpdateWhite(_currentColumn-COLUMNS)) {
				updateColumn(COLOR_WHITE, _currentColumn-COLUMNS);
				return; /* always update max one column per update() call */
			}
		}
	} while (_currentColumn != startColumn);
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
		_offScreenBuffer[bytePos] |= bitMask;
	} else {
		_offScreenBuffer[bytePos] &= ~bitMask;
	}

}

bool FlipdotFramebufferBase::getPixel(unsigned x, unsigned y)
{
	auto column = getPhysicalX(x);
	auto row = getPhysicalY(x, y);
	unsigned bytePos = (column * _bytesPerColumn) + 11 - (row / 8);
	unsigned bitMask = 1<<(row % 8);
	return _offScreenBuffer[bytePos] & bitMask;
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
	_driver.writeColumnData(&_offScreenBuffer[column*_bytesPerColumn], _bytesPerColumn);
	_driver.strobe();

	if (color==COLOR_BLACK) {
		_driver.setOutputEnableBlack();
	} else {
		_driver.setOutputEnableWhite();
	}
	copyColumnToOnScreenBuffer(color, column);

	_driver.delayFlipDots();
	_driver.setOutputEnableNone();
}

void FlipdotFramebufferBase::copyColumnToOnScreenBuffer(color_t color, unsigned column)
{
	unsigned offset = column*_bytesPerColumn;
	for (unsigned i=offset; i<offset+_bytesPerColumn; i++)
	{
		if (color==COLOR_BLACK)
		{
			_onScreenBuffer[i] |= _offScreenBuffer[i];
		} else {
			_onScreenBuffer[i] &= _offScreenBuffer[i];
		}
	}

}

bool FlipdotFramebufferBase::mustUpdateBlack(unsigned column)
{
	unsigned offset = column*_bytesPerColumn;
	for (unsigned i=0; i<_bytesPerColumn; i++)
	{
		uint8_t onScreen = _onScreenBuffer[offset+i];
		uint8_t offScreen = _offScreenBuffer[offset+i];

		if ( (onScreen & offScreen) != offScreen)
		{ /* there are set bits in the offscreen buffer which are cleared onscreen */
			return true;
		}
	}
	return false;
}

bool FlipdotFramebufferBase::mustUpdateWhite(unsigned column)
{
	unsigned offset = column*_bytesPerColumn;
	for (unsigned i=0; i<_bytesPerColumn; i++)
	{
		uint8_t onScreen = _onScreenBuffer[offset+i];
		uint8_t offScreen = _offScreenBuffer[offset+i];

		if ( (onScreen & offScreen) != onScreen)
		{ /* there are cleared bits in the offscreen buffer which are set onscreen */
			return true;
		}
	}
	return false;
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

unsigned FlipdotFramebufferBase::getScreenWidth()
{
	return _numPanelsX * COLUMNS;
}

unsigned FlipdotFramebufferBase::getScreenHeight()
{
	return _numPanelsY * ACTIVE_ROWS_PER_PANEL;
}

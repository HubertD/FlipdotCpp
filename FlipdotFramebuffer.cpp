#include "FlipdotFramebuffer.h"

FlipdotFramebuffer::FlipdotFramebuffer(IFlipdotDriver &driver, unsigned numPanelsX, unsigned numPanelsY, uint8_t *buffer, unsigned bufferSize)
  : _driver(driver),
	_numPanelsX(numPanelsX),
	_numPanelsY(numPanelsY),
	_buffer(buffer),
	_bufferSize(buffer),
	_dirty(0),
	_currentColumn(0),
	_currentColor(COLOR_BLACK)
{
	_bytesPerColumn = (ROWS_PER_PANEL * (_numPanelsX * _numPanelsY)) / 8;
	if (_bufferSize < _bytesPerColumn*COLUMNS) {
		// screen buffer to small, should better not continue
		while (1);
	}
}

FlipdotFramebuffer::~FlipdotFramebuffer()
{
}

void FlipdotFramebuffer::init()
{
	clear();
	flush();
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

void FlipdotFramebuffer::flush()
{
	flushColor(COLOR_BLACK);
	flushColor(COLOR_WHITE);
}

void FlipdotFramebuffer::flushColor(color_t color)
{
	for (unsigned i=0; i<COLUMNS; i++)
	{
		updateColumn(color, i);
	}
}

void FlipdotFramebuffer::clear()
{
	for (unsigned i=0; i<_bufferSize; i++)
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
	unsigned panel = ((x/COLUMNS) * _numPanelsY) + (y / ACTIVE_ROWS_PER_PANEL);
	unsigned row = (panel * ROWS_PER_PANEL) + (y % ACTIVE_ROWS_PER_PANEL);
	unsigned bytePos = (column * _bytesPerColumn) + (row/8);
	unsigned bitMask = 1<<(row % 8);

	if (value) {
		_buffer[bytePos] |= bitMask;
	} else {
		_buffer[bytePos] &= ~bitMask;
	}

	setColumnDirty(column);
}

void FlipdotFramebuffer::updateColumn(color_t color, unsigned column)
{
	uint16_t column_register = (1<<column);
	_driver.writeRowData((uint8_t*)&column_register, 2);
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

void FlipdotFramebuffer::flipCurrentColor()
{
	_currentColor = (_currentColor==COLOR_BLACK) ? COLOR_WHITE : COLOR_BLACK;
}

void FlipdotFramebuffer::setColumnDirty(unsigned column)
{
	_dirty |= ((1<<column) | (1<<(COLUMNS+column)));
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


#include "FlipdotFramebuffer.h"

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
	for (unsigned i=0; i<sizeof(_buffer); i++)
	{
		_buffer[i] = 0;
	}
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
	for (unsigned i=0; i<_bufferSize; i++)
	{
		_buffer[i] = 0;
	}

	for (unsigned i=0; i<COLUMNS; i++)
	{
		setColumnDirty(i);
	}
}

void FlipdotFramebufferBase::setPixel(unsigned x, unsigned y, bool value)
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

void FlipdotFramebufferBase::updateColumn(color_t color, unsigned column)
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


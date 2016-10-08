#include "FlipdotFramebuffer.h"

FlipdotFramebuffer::FlipdotFramebuffer(IFlipdotDriver &driver)
  : _driver(driver)
{
}

void FlipdotFramebuffer::init()
{
	configurePanels();
	clear();
	flush();
}

void FlipdotFramebuffer::configurePanels()
{
	for (unsigned i=0; i<NUM_PANELS; i++) {
		_panels[i].configure(PANEL_CONFG[i]);
	}
}

void FlipdotFramebuffer::update(unsigned ticks)
{
	/* TODO refactor this method */

	_driver.update(ticks);

	if (ticks < _tWaitDotsFlip)
	{
		/* wait untils magnets have done their work */
		return;
	}

	unsigned startColumn = _currentColumn;

	_driver.setOutputEnableNone();
	do
	{
		_currentColumn = (_currentColumn + 1) % (2*FlipdotPanel::ACTIVE_COLUMNS);

		if (_currentColumn < FlipdotPanel::ACTIVE_COLUMNS) {
			if (_onScreenBuffer.otherHasSetBitsWeHaveNot(_offScreenBuffer, _currentColumn)) {
				updateColumn(Color::BLACK, _currentColumn);
				_tWaitDotsFlip = ticks + DOT_FLIP_TIME_MS;
				break; /* always update max one column per update() call */
			}
		} else {
			if (_offScreenBuffer.otherHasSetBitsWeHaveNot(_onScreenBuffer, _currentColumn)) {
				updateColumn(Color::WHITE, _currentColumn-FlipdotPanel::ACTIVE_COLUMNS);
				_tWaitDotsFlip = ticks + DOT_FLIP_TIME_MS;
				break; /* always update max one column per update() call */
			}
		}

	} while (_currentColumn != startColumn);
}

void FlipdotFramebuffer::flush()
{
	flushColor(Color::BLACK);
	flushColor(Color::WHITE);
}

void FlipdotFramebuffer::flushColor(Color color)
{
	for (unsigned i=0; i<FlipdotPanel::ACTIVE_COLUMNS; i++)
	{
		updateColumn(color, i);
	}
}

void FlipdotFramebuffer::clear()
{
	for (unsigned y=0; y<SCREEN_HEIGHT; y++)
	{
		for (unsigned x=0; x<SCREEN_WIDTH; x++)
		{
			setPixel(x, y, false);
		}
	}
}

void FlipdotFramebuffer::setPixel(unsigned x, unsigned y, bool value)
{
	_offScreenBuffer.setPixel(x, y, value);
}

bool FlipdotFramebuffer::getPixel(unsigned x, unsigned y)
{
	return _offScreenBuffer.getPixel(x, y);
}

void FlipdotFramebuffer::selectColumn(unsigned column)
{
	uint8_t row_data[] = {
		(uint8_t)((1<<column) & 0xFF),
		(uint8_t)(((1<<column) >> 8) & 0xFF),
	};
	_driver.writeRowData(row_data, sizeof(row_data));
}

void FlipdotFramebuffer::updateColumn(Color color, unsigned column)
{
	selectColumn(column);

	uint8_t colbuf[3];
	for (int i=NUM_PANELS-1; i>=0; i--)
	{
		_panels[i].fillColumnRegister(_offScreenBuffer, column, &colbuf[0]);
		_driver.writeColumnData(colbuf, sizeof(colbuf));
	}
	_driver.strobe();

	if (color==Color::BLACK) {
		_driver.setOutputEnableBlack();
		_onScreenBuffer.copyColumnFromOther(_offScreenBuffer, column, true, false);
	} else {
		_driver.setOutputEnableWhite();
		_onScreenBuffer.copyColumnFromOther(_offScreenBuffer, column, false, true);
	}

}


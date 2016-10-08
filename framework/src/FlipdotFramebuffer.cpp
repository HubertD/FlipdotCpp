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
	_driver.update(ticks);

	if (ticks < _tWaitDotsFlip)
	{
		/* wait untils magnets have done their work */
		return;
	}

	unsigned startCounter = _updateCounter;

	_driver.setOutputEnableNone();
	do
	{
		_updateCounter = (_updateCounter + 1) % (2*FlipdotPanel::ACTIVE_COLUMNS);

		FlipdotColor color = (_updateCounter < FlipdotPanel::ACTIVE_COLUMNS) ? FlipdotColor::BLACK : FlipdotColor::WHITE;
		unsigned column = _updateCounter % FlipdotPanel::ACTIVE_COLUMNS;

		if (columnNeedsUpdate(column, color))
		{
			updateColumn(column, color);
			_tWaitDotsFlip = ticks + DOT_FLIP_TIME_MS;
			break; /* always update max one column per update() call */
		}

	} while (_updateCounter != startCounter);
}

void FlipdotFramebuffer::flush()
{
	flushColor(FlipdotColor::BLACK);
	flushColor(FlipdotColor::WHITE);
}

ScreenBuffer& FlipdotFramebuffer::getOnScreenBuffer()
{
	return _onScreenBuffer;
}

ScreenBuffer& FlipdotFramebuffer::getOffScreenBuffer()
{
	return _offScreenBuffer;
}

void FlipdotFramebuffer::flushColor(FlipdotColor color)
{
	for (unsigned i=0; i<FlipdotPanel::ACTIVE_COLUMNS; i++)
	{
		updateColumn(i, color);
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

void FlipdotFramebuffer::updateColumn(unsigned column, FlipdotColor color)
{
	selectColumn(column);

	uint8_t colbuf[3];
	for (int i=NUM_PANELS-1; i>=0; i--)
	{
		_panels[i].fillShiftRegister(_offScreenBuffer, column, &colbuf[0]);
		_driver.writeColumnData(colbuf, sizeof(colbuf));
		_panels[i].updateOnScreenBuffer(column, color, _onScreenBuffer, _offScreenBuffer);
	}
	_driver.strobe();

	if (color==FlipdotColor::BLACK)
	{
		_driver.setOutputEnableBlack();
	} else {
		_driver.setOutputEnableWhite();
	}

}

bool FlipdotFramebuffer::columnNeedsUpdate(unsigned column, FlipdotColor color)
{
	for (auto panel: _panels)
	{
		if (panel.columnNeedsUpdate(column, color, _onScreenBuffer, _offScreenBuffer))
		{
			return true;
		}
	}
	return false;
}

#include <Framebuffer.h>

Framebuffer::Framebuffer(IFlipdotDriver &driver)
  : _driver(driver)
{
}

void Framebuffer::init()
{
	configurePanels();
	clear();
	flush();
}

void Framebuffer::configurePanels()
{
	for (unsigned i=0; i<NUM_PANELS; i++) {
		_panels[i].configure(PANEL_CONFG[i]);
	}
}

void Framebuffer::update(unsigned ticks)
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

		Color color = (_updateCounter < FlipdotPanel::ACTIVE_COLUMNS) ? Color::BLACK : Color::WHITE;
		unsigned column = _updateCounter % FlipdotPanel::ACTIVE_COLUMNS;

		if (columnNeedsUpdate(column, color))
		{
			updateColumn(column, color);
			_tWaitDotsFlip = ticks + DOT_FLIP_TIME_MS;
			break; /* always update max one column per update() call */
		}

	} while (_updateCounter != startCounter);
}

void Framebuffer::flush()
{
	flushColor(Color::BLACK);
	flushColor(Color::WHITE);
}

ScreenBuffer& Framebuffer::getOnScreenBuffer()
{
	return _onScreenBuffer;
}

ScreenBuffer& Framebuffer::getOffScreenBuffer()
{
	return _offScreenBuffer;
}

void Framebuffer::flushColor(Color color)
{
	for (unsigned i=0; i<FlipdotPanel::ACTIVE_COLUMNS; i++)
	{
		updateColumn(i, color);
	}
}

void Framebuffer::clear()
{
	for (unsigned y=0; y<SCREEN_HEIGHT; y++)
	{
		for (unsigned x=0; x<SCREEN_WIDTH; x++)
		{
			setPixel(x, y, false);
		}
	}
}

void Framebuffer::setPixel(int x, int y, bool value)
{
	_offScreenBuffer.setPixel(x, y, value);
}

bool Framebuffer::getPixel(int x, int y)
{
	return _offScreenBuffer.getPixel(x, y);
}


void Framebuffer::drawRect(int x, int y, int dx, int dy, bool value)
{
	for (int px=x; px<(x+dx); px++)
	{
		for (int py=y; py<(y+dy); py++)
		{
			setPixel(px, py, value);
		}
	}
}

void Framebuffer::draw(int x, int y, const IDrawable& drawable, bool doInvert)
{
	drawable.draw(*this, x, y, doInvert);
}

void Framebuffer::selectColumn(unsigned column)
{
	uint8_t row_data[] = {
		(uint8_t)((1<<column) & 0xFF),
		(uint8_t)(((1<<column) >> 8) & 0xFF),
	};
	_driver.writeRowData(row_data, sizeof(row_data));
}

void Framebuffer::updateColumn(unsigned column, Color color)
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

	if (color==Color::BLACK)
	{
		_driver.setOutputEnableBlack();
	} else {
		_driver.setOutputEnableWhite();
	}

}

bool Framebuffer::columnNeedsUpdate(unsigned column, Color color)
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

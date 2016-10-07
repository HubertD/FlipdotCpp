#include "VirtualFlipdotDriver.h"
#include "VirtualFlipdotPanel.h"

VirtualFlipdotDriver::VirtualFlipdotDriver(unsigned numPanelsX, unsigned numPanelsY)
  : _numPanelsX(numPanelsX),
	_numPanelsY(numPanelsY),
	_numPanels(numPanelsX * numPanelsY),
	_columnShiftReg(0)
{
	_panels = new VirtualFlipdotPanel[_numPanels];
}

VirtualFlipdotDriver::~VirtualFlipdotDriver()
{
	delete[] _panels;
}

void VirtualFlipdotDriver::update(unsigned ticks)
{
	(void) ticks;
}

unsigned VirtualFlipdotDriver::getPhysicalX(unsigned x)
{
	/*
	 *                                         /---\
	 * 0, 1, 2, ..., 14, 15, | 15, 14, ..., 1, 0, | 0, 1, ....
	 *                     \___/
	 */

	bool doFlip = ((x / VirtualFlipdotPanel::COLUMNS) % 2) != 0;
	unsigned logicalX = x % VirtualFlipdotPanel::COLUMNS;
	return doFlip ? (VirtualFlipdotPanel::COLUMNS-1 - logicalX) : logicalX;
}

unsigned VirtualFlipdotDriver::getPhysicalY(unsigned x, unsigned y)
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

	const unsigned DOTS_PER_ROW = _numPanelsY * VirtualFlipdotPanel::ACTIVE_ROWS;

	unsigned panel_x = x / VirtualFlipdotPanel::COLUMNS;

	return ( (panel_x % 2) == 0)
		   ? (panel_x * DOTS_PER_ROW) + y
		   : (panel_x * DOTS_PER_ROW) + (DOTS_PER_ROW-1 - y);

}


bool VirtualFlipdotDriver::getDotColor(unsigned x, unsigned y)
{
	static uint8_t xmap[] = { 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8 };

	unsigned panel_x = 0;
	unsigned panel_y = 0;
	unsigned panelNumber = 0;

	if (x<16) {
		panelNumber = (y<20) ? 1 : 0;
		panel_x = xmap[x % 16];
		panel_y = y;
	} else {
		panelNumber = (y<20) ? 2 : 3;
		panel_x = 15-xmap[x % 16];
		panel_y = 39-y;
	}

	return _panels[panelNumber].getDotColor(panel_x, panel_y % VirtualFlipdotPanel::ACTIVE_ROWS);
}

void VirtualFlipdotDriver::writeColumnData(uint8_t* data, unsigned length)
{
	for (unsigned i=0; i<length; i++)
	{
		_panels[0].shiftInputColumnByte(data[i]);
		for (unsigned panel_num=1; panel_num<_numPanels; panel_num++)
		{
			_panels[panel_num].shiftInputColumnByte(_panels[panel_num-1].getOutputColumnByte());
		}
	}
}

void VirtualFlipdotDriver::writeRowData(uint8_t* data, unsigned length)
{
	for (unsigned i=0; i<length; i++)
	{
		_columnShiftReg <<= 8;
		_columnShiftReg |= data[i];
	}
	for (unsigned i=0; i<_numPanels; i++)
	{
		_panels[i].selectColumn(getSelectedColumn());
	}
}

unsigned VirtualFlipdotDriver::getSelectedColumn()
{
	for (unsigned i=0; i<COLUMNS; i++)
	{
		if ( (_columnShiftReg & (1<<i)) != 0)
		{
			return i;
		}
	}
	return 0;
}

void VirtualFlipdotDriver::setOutputEnableBlack()
{
	for (unsigned i=0; i<_numPanels; i++)
	{
		_panels[i].setOutputEnableBlack();
	}
	onUpdateColumn(getSelectedColumn());
}

void VirtualFlipdotDriver::setOutputEnableWhite()
{
	for (unsigned i=0; i<_numPanels; i++)
	{
		_panels[i].setOutputEnableWhite();
	}
	onUpdateColumn(getSelectedColumn());
}

void VirtualFlipdotDriver::setOutputEnableNone()
{
}

void VirtualFlipdotDriver::strobe()
{
	for (unsigned i=0; i<_numPanels; i++)
	{
		_panels[i].strobe();
	}
}

void VirtualFlipdotDriver::onUpdateScreen()
{
}

void VirtualFlipdotDriver::onUpdateColumn(unsigned column)
{
	onUpdateScreen();
}

unsigned VirtualFlipdotDriver::getWidth()
{
	return _numPanelsX * VirtualFlipdotPanel::COLUMNS;
}

unsigned VirtualFlipdotDriver::getHeight()
{
	return _numPanelsY * VirtualFlipdotPanel::ACTIVE_ROWS;
}


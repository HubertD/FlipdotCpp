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
	auto phys_x = getPhysicalX(x);
	auto phys_y = getPhysicalY(x, y);

	unsigned panel_x = x / VirtualFlipdotPanel::COLUMNS;
	unsigned panel_y = (phys_y / VirtualFlipdotPanel::ACTIVE_ROWS) % _numPanelsY;

	return _panels[_numPanelsY*panel_x + panel_y].getDotColor(
			phys_x % VirtualFlipdotPanel::COLUMNS,
			phys_y % VirtualFlipdotPanel::ACTIVE_ROWS
	);
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


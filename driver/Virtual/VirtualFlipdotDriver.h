#pragma once

#include "../../../gfx/driver/IFlipdotDriver.h"

class VirtualFlipdotPanel;

class VirtualFlipdotDriver: public IFlipdotDriver
{
	public:
		static unsigned const COLUMNS = 16;

		VirtualFlipdotDriver(unsigned numPanelsX, unsigned numPanelsY);
		~VirtualFlipdotDriver();
		bool getDotColor(unsigned x, unsigned y);

		void writeColumnData(uint8_t* data, unsigned length) override;
		void writeRowData(uint8_t* data, unsigned length) override;

		void setOutputEnableBlack() override;
		void setOutputEnableWhite() override;
		void setOutputEnableNone() override;
		void strobe() override;
		void delayFlipDots() override;

		unsigned getWidth();
		unsigned getHeight();

	protected:
		virtual void onUpdateColumn(unsigned column);
		virtual void onUpdateScreen();

	private:

		unsigned _numPanelsX;
		unsigned _numPanelsY;
		unsigned _numPanels;
		uint16_t _columnShiftReg;
		VirtualFlipdotPanel *_panels;

		unsigned getSelectedColumn();

		unsigned getPhysicalX(unsigned x);
		unsigned getPhysicalY(unsigned x, unsigned y);

};

#pragma once

#include "IFlipdotDriver.h"

class CubeMxFlipdotDriver : public IFlipdotDriver
{
	public:
		CubeMxFlipdotDriver();
		~CubeMxFlipdotDriver() override;
		void setOutputEnableBlack() override;
		void setOutputEnableWhite() override;
		void setOutputEnableNone() override;
		void strobe() override;
		void writeColumnData(uint8_t* data, unsigned length) override;
		void writeRowData(uint8_t* data, unsigned length) override;
		void delayFlipDots() override;

	private:
		void shiftColumnRegister(bool in);
		void shiftRowRegister(bool in);
		void delayClock();

};

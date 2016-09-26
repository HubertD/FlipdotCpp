#pragma once

#include "IFlipdotDriver.h"

class CubeMxFlipdotDriver : public IFlipdotDriver
{
	public:
		CubeMxFlipdotDriver();
		~CubeMxFlipdotDriver();
		void setOutputEnableBlack() override;
		void setOutputEnableWhite() override;
		void setOutputEnableNone() override;
		void strobe() override;
		void shiftColumnRegister(bool in) override;
		void shiftRowRegister(bool in) override;
		void delayClock() override;
		void delayFlipDots() override;

};

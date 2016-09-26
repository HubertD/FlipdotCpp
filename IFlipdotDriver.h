#pragma once

class IFlipdotDriver
{
	public:
		virtual ~IFlipdotDriver();
		virtual void setOutputEnableBlack() = 0;
		virtual void setOutputEnableWhite() = 0;
		virtual void setOutputEnableNone() = 0;
		virtual void strobe() = 0;
		virtual void shiftColumnRegister(bool in) = 0;
		virtual void shiftRowRegister(bool in) = 0;
		virtual void delayClock() = 0;
		virtual void delayFlipDots() = 0;
};

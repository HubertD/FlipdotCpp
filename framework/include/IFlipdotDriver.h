#pragma once

#include <stdint.h>

class IFlipdotDriver
{
	public:
		IFlipdotDriver() {};
		virtual ~IFlipdotDriver() {};

		virtual void update(unsigned ticks) = 0;

		virtual void setOutputEnableBlack() = 0;
		virtual void setOutputEnableWhite() = 0;
		virtual void setOutputEnableNone() = 0;
		virtual void strobe() = 0;
		virtual void writeColumnData(uint8_t* data, unsigned length) = 0;
		virtual void writeRowData(uint8_t* data, unsigned length) = 0;
};

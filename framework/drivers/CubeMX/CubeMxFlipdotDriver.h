#pragma once

#include <IFlipdotDriver.h>
#include <stdint.h>

class CubeMxFlipdotDriver : public IFlipdotDriver
{
	public:
		CubeMxFlipdotDriver();
		~CubeMxFlipdotDriver() override;

		void update(unsigned ticks) override;

		void setOutputEnableBlack() override;
		void setOutputEnableWhite() override;
		void setOutputEnableNone() override;
		void strobe() override;
		void writeColumnData(uint8_t* data, unsigned length) override;
		void writeRowData(uint8_t* data, unsigned length) override;
		void delayFlipDots() override;

	private:
		inline void shiftColumnRegister(bool in);
		inline void shiftRowRegister(bool in);
		inline void delayClock();

};

#pragma once

#include <IFlipdotDriver.h>
#include <stdint.h>

class STM32F4FlipdotDriver : public IFlipdotDriver
{
	public:
		STM32F4FlipdotDriver();
		~STM32F4FlipdotDriver() override;

		void update(unsigned ticks) override;

		void setOutputEnableBlack() override;
		void setOutputEnableWhite() override;
		void setOutputEnableNone() override;
		void strobe() override;
		void writeColumnData(uint8_t* data, unsigned length) override;
		void writeRowData(uint8_t* data, unsigned length) override;

	private:
		inline void shiftColumnRegister(bool in);
		inline void shiftRowRegister(bool in);
		inline void delayClock();

};

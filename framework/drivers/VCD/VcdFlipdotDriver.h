#pragma once

#include <IFlipdotDriver.h>
#include <stdint.h>

class VcdFlipdotDriver : public IFlipdotDriver
{
	public:
		VcdFlipdotDriver();
		~VcdFlipdotDriver() override;
		void update(unsigned ticks) override;

		void setOutputEnableBlack() override;
		void setOutputEnableWhite() override;
		void setOutputEnableNone() override;
		void strobe() override;
		void writeColumnData(uint8_t* data, unsigned length) override;
		void writeRowData(uint8_t* data, unsigned length) override;

	private:
		unsigned _time;

		enum class Signal {
			ROW_DATA, ROW_CLK,
			COL_DATA, COL_CLK,
			STROBE, BLACK_OE,
			WHITE_OE, _COUNT
		};

		bool _signals[(unsigned)Signal::_COUNT];

		void shiftColumnRegister(bool in);
		void shiftRowRegister(bool in);
		void delayClock();
		void printSignals();
		void setSignal(Signal signal, bool value);

};

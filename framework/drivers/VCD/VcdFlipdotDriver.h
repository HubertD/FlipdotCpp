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
		void delayFlipDots() override;

	private:
		unsigned _time;

		typedef enum {
			signal_row_data, signal_row_clk,
			signal_col_data, signal_col_clk,
			signal_strobe, signal_black_oe,
			signal_white_oe, signal_COUNT
		} signal_t;

		bool _signals[signal_COUNT];

		void shiftColumnRegister(bool in);
		void shiftRowRegister(bool in);
		void delayClock();
		void printSignals();
		void setSignal(signal_t signal, bool value);

};

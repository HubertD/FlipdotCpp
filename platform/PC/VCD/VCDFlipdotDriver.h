#pragma once

#include <IFlipdotDriver.h>
#include <stdint.h>

class VCDPlatform;

class VCDFlipdotDriver : public IFlipdotDriver
{
	public:
		VCDFlipdotDriver(VCDPlatform &platforms);
		~VCDFlipdotDriver() override;
		void update(unsigned ticks) override;

		void setOutputEnableBlack() override;
		void setOutputEnableWhite() override;
		void setOutputEnableNone() override;
		void strobe() override;
		void writeColumnData(uint8_t* data, unsigned length) override;
		void writeRowData(uint8_t* data, unsigned length) override;

	private:
		VCDPlatform &_platform;

		enum class Signal {
			ROW_DATA, ROW_CLK,
			COL_DATA, COL_CLK,
			STROBE, BLACK_OE,
			WHITE_OE, _COUNT
		};

		static constexpr unsigned SET_SIGNAL_DELAY_US = 1;
		static constexpr unsigned CLOCK_DELAY_US = 10;

		unsigned _signals = 0;
		unsigned _lastSignals = -1;

		void shiftColumnRegister(bool in);
		void shiftRowRegister(bool in);
		void delayClock();
		void printHeader();
		void printSignals();
		void printSignalsIfChanged();
		void setSignal(Signal signal, bool value);
		bool getSignal(Signal signal);
		int  getSignalInt(Signal signal);

};

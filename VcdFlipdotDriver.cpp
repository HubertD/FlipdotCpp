#include "VcdFlipdotDriver.h"
#include <stdio.h>

VcdFlipdotDriver::VcdFlipdotDriver()
  : _time(0), _signals{false,false,false,false,false,false,false}
{
	printf("$date $end\n");
	printf("$version VcdFlipdotDriver 0.1.0 $end\n");
	printf("$comment flipdot driver simulation $end\n");
	printf("$timescale 100 ns $end\n");
	printf("$scope module flipdot $end\n");
	printf("$var wire 1 RD RowData $end\n");
	printf("$var wire 1 RC RowClock $end\n");
	printf("$var wire 1 CD ColData $end\n");
	printf("$var wire 1 CC ColClock $end\n");
	printf("$var wire 1 ST Strobe $end\n");
	printf("$var wire 1 BE Black_OE $end\n");
	printf("$var wire 1 WE White_OE $end\n");
	printf("$upscope $end\n");
	printf("$enddefinitions $end\n");
	printSignals();
}

VcdFlipdotDriver::~VcdFlipdotDriver() {
}

inline void VcdFlipdotDriver::delayClock()
{
	_time += 10;
}

void VcdFlipdotDriver::delayFlipDots()
{
	_time += 100000;
}

void VcdFlipdotDriver::setSignal(signal_t signal, bool value)
{
	_time += 1;
	_signals[signal] = value;
	printSignals();
}

void VcdFlipdotDriver::printSignals()
{
	printf(
		"#%d %dRD %dRC %dCD %dCC %dST %dBE %dWE\n",
		_time,
		_signals[signal_row_data] ? 1 : 0,
		_signals[signal_row_clk] ? 1 : 0,
		_signals[signal_col_data] ? 1 : 0,
		_signals[signal_col_clk] ? 1 : 0,
		_signals[signal_strobe] ? 1 : 0,
		_signals[signal_black_oe] ? 1 : 0,
		_signals[signal_white_oe] ? 1 : 0
	);
}

void VcdFlipdotDriver::writeColumnData(uint8_t* data, unsigned length)
{
	for (unsigned i=0; i<length; i++)
	{
		for (int j=0; j<8; j++)
		{
			shiftColumnRegister(data[i] & (1<<j));
		}
	}
}

void VcdFlipdotDriver::writeRowData(uint8_t* data, unsigned length)
{
	for (unsigned i=0; i<length; i++)
	{
		for (int j=0; j<8; j++)
		{
			shiftRowRegister(data[i] & (1<<j));
		}
	}
}

void VcdFlipdotDriver::setOutputEnableBlack()
{
	setSignal(signal_white_oe, false);
	setSignal(signal_black_oe, true);
}

void VcdFlipdotDriver::setOutputEnableWhite()
{
	setSignal(signal_black_oe, false);
	setSignal(signal_white_oe, true);
}

void VcdFlipdotDriver::setOutputEnableNone()
{
	setSignal(signal_black_oe, false);
	setSignal(signal_white_oe, false);
}

void VcdFlipdotDriver::strobe()
{
	setSignal(signal_strobe, true);
	delayClock();
	setSignal(signal_strobe, false);
}

void VcdFlipdotDriver::shiftColumnRegister(bool in)
{
	setSignal(signal_col_data, in);
	delayClock();
	setSignal(signal_col_clk, true);
	delayClock();
	setSignal(signal_col_clk, false);
}

void VcdFlipdotDriver::shiftRowRegister(bool in)
{
	setSignal(signal_row_data, in);
	delayClock();
	setSignal(signal_row_clk, true);
	delayClock();
	setSignal(signal_row_clk, false);
}

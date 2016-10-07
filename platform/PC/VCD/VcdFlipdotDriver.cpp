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

void VcdFlipdotDriver::update(unsigned ticks)
{
	(void) ticks;
}

inline void VcdFlipdotDriver::delayClock()
{
	_time += 10;
}

void VcdFlipdotDriver::setSignal(Signal signal, bool value)
{
	_time += 1;
	_signals[(unsigned)signal] = value;
	printSignals();
}

void VcdFlipdotDriver::printSignals()
{
	printf(
		"#%d %dRD %dRC %dCD %dCC %dST %dBE %dWE\n",
		_time,
		_signals[(unsigned)Signal::ROW_DATA] ? 1 : 0,
		_signals[(unsigned)Signal::ROW_CLK] ? 1 : 0,
		_signals[(unsigned)Signal::COL_DATA] ? 1 : 0,
		_signals[(unsigned)Signal::COL_CLK] ? 1 : 0,
		_signals[(unsigned)Signal::STROBE] ? 1 : 0,
		_signals[(unsigned)Signal::BLACK_OE] ? 1 : 0,
		_signals[(unsigned)Signal::WHITE_OE] ? 1 : 0
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
	setSignal(Signal::WHITE_OE, false);
	setSignal(Signal::BLACK_OE, true);
}

void VcdFlipdotDriver::setOutputEnableWhite()
{
	setSignal(Signal::BLACK_OE, false);
	setSignal(Signal::WHITE_OE, true);
}

void VcdFlipdotDriver::setOutputEnableNone()
{
	setSignal(Signal::BLACK_OE, false);
	setSignal(Signal::WHITE_OE, false);
}

void VcdFlipdotDriver::strobe()
{
	setSignal(Signal::STROBE, true);
	delayClock();
	setSignal(Signal::STROBE, false);
}

void VcdFlipdotDriver::shiftColumnRegister(bool in)
{
	setSignal(Signal::COL_DATA, in);
	delayClock();
	setSignal(Signal::COL_CLK, true);
	delayClock();
	setSignal(Signal::COL_CLK, false);
}

void VcdFlipdotDriver::shiftRowRegister(bool in)
{
	setSignal(Signal::ROW_DATA, in);
	delayClock();
	setSignal(Signal::ROW_CLK, true);
	delayClock();
	setSignal(Signal::ROW_CLK, false);
}

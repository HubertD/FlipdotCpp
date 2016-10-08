#include "VCDFlipdotDriver.h"
#include "VCDPlatform.h"
#include <stdio.h>

VCDFlipdotDriver::VCDFlipdotDriver(VCDPlatform &platform)
  : _platform(platform)
{
	printHeader();
}

VCDFlipdotDriver::~VCDFlipdotDriver() {
}

void VCDFlipdotDriver::update(unsigned ticks)
{
	(void) ticks;
}

inline void VCDFlipdotDriver::delayClock()
{
	_platform.incrementUTicks(CLOCK_DELAY_US);
}

bool VCDFlipdotDriver::getSignal(Signal signal)
{
	unsigned bitmask = (1<<(unsigned)signal);
	return (_signals & bitmask) != 0;
}

int VCDFlipdotDriver::getSignalInt(Signal signal)
{
	return getSignal(signal) ? 1 : 0;
}

void VCDFlipdotDriver::setSignal(Signal signal, bool value)
{
	_platform.incrementUTicks(SET_SIGNAL_DELAY_US);
	unsigned bitmask = (1<<(unsigned)signal);
	if (value) {
		_signals |= bitmask;
	} else {
		_signals &= ~bitmask;
	}
	printSignalsIfChanged();
}

void VCDFlipdotDriver::printSignalsIfChanged()
{
	if (_lastSignals != _signals)
	{
		printSignals();
	}
}

void VCDFlipdotDriver::printHeader()
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
}

void VCDFlipdotDriver::printSignals()
{
	printf(
		"#%d %dRD %dRC %dCD %dCC %dST %dBE %dWE\n",
		_platform.getUTicks(),
		getSignalInt(Signal::ROW_DATA),
		getSignalInt(Signal::ROW_CLK),
		getSignalInt(Signal::COL_DATA),
		getSignalInt(Signal::COL_CLK),
		getSignalInt(Signal::STROBE),
		getSignalInt(Signal::BLACK_OE),
		getSignalInt(Signal::WHITE_OE)
	);
	_lastSignals = _signals;
}

void VCDFlipdotDriver::writeColumnData(uint8_t* data, unsigned length)
{
	for (unsigned i=0; i<length; i++)
	{
		for (int j=0; j<8; j++)
		{
			shiftColumnRegister(data[i] & (1<<j));
		}
	}
}

void VCDFlipdotDriver::writeRowData(uint8_t* data, unsigned length)
{
	for (unsigned i=0; i<length; i++)
	{
		for (int j=0; j<8; j++)
		{
			shiftRowRegister(data[i] & (1<<j));
		}
	}
}

void VCDFlipdotDriver::setOutputEnableBlack()
{
	setSignal(Signal::BLACK_OE, false);
	setSignal(Signal::WHITE_OE, true);
}

void VCDFlipdotDriver::setOutputEnableWhite()
{
	setSignal(Signal::WHITE_OE, false);
	setSignal(Signal::BLACK_OE, true);
}

void VCDFlipdotDriver::setOutputEnableNone()
{
	setSignal(Signal::BLACK_OE, false);
	setSignal(Signal::WHITE_OE, false);
}

void VCDFlipdotDriver::strobe()
{
	setSignal(Signal::STROBE, true);
	delayClock();
	setSignal(Signal::STROBE, false);
	delayClock();
	setSignal(Signal::STROBE, true);
}

void VCDFlipdotDriver::shiftColumnRegister(bool in)
{
	setSignal(Signal::COL_DATA, in);
	delayClock();
	setSignal(Signal::COL_CLK, true);
	delayClock();
	setSignal(Signal::COL_CLK, false);
}

void VCDFlipdotDriver::shiftRowRegister(bool in)
{
	setSignal(Signal::ROW_DATA, in);
	delayClock();
	setSignal(Signal::ROW_CLK, true);
	delayClock();
	setSignal(Signal::ROW_CLK, false);
}


#include "CubeMxFlipdotDriver.h"
#include "stm32f0xx_hal.h"

CubeMxFlipdotDriver::CubeMxFlipdotDriver()
{
}

CubeMxFlipdotDriver::~CubeMxFlipdotDriver()
{
}

void CubeMxFlipdotDriver::writeColumnData(uint8_t* data, unsigned length)
{
	for (unsigned i=0; i<length; i++)
	{
		for (int j=0; j<8; j++)
		{
			shiftColumnRegister(data[i] & (1<<j));
		}
	}
}

void CubeMxFlipdotDriver::writeRowData(uint8_t* data, unsigned length)
{
	for (unsigned i=0; i<length; i++)
	{
		for (int j=0; j<8; j++)
		{
			shiftRowRegister(data[i] & (1<<j));
		}
	}
}

void CubeMxFlipdotDriver::setOutputEnableBlack()
{
	WHITE_OE_GPIO_Port->BRR = (uint32_t)WHITE_OE_Pin;
	BLACK_OE_GPIO_Port->BSRR = (uint32_t)BLACK_OE_Pin;
}

void CubeMxFlipdotDriver::setOutputEnableWhite()
{
	BLACK_OE_GPIO_Port->BRR = (uint32_t)BLACK_OE_Pin;
	WHITE_OE_GPIO_Port->BSRR = (uint32_t)WHITE_OE_Pin;
}

void CubeMxFlipdotDriver::setOutputEnableNone()
{
	BLACK_OE_GPIO_Port->BRR = (uint32_t)BLACK_OE_Pin;
	WHITE_OE_GPIO_Port->BRR = (uint32_t)WHITE_OE_Pin;
}

void CubeMxFlipdotDriver::strobe()
{
	STROBE_GPIO_Port->BSRR = (uint32_t)STROBE_Pin;
	delayClock();
	STROBE_GPIO_Port->BRR = (uint32_t)STROBE_Pin;
}

void CubeMxFlipdotDriver::shiftColumnRegister(bool in)
{
	if (in) {
		COL_DATA_GPIO_Port->BSRR = (uint32_t)COL_DATA_Pin;
	} else {
		COL_DATA_GPIO_Port->BRR = (uint32_t)COL_DATA_Pin;
	}

	delayClock();
	COL_CLK_GPIO_Port->BSRR = (uint32_t)COL_CLK_Pin;
	delayClock();
	COL_CLK_GPIO_Port->BRR = (uint32_t)COL_CLK_Pin;
}

void CubeMxFlipdotDriver::shiftRowRegister(bool in)
{
	if (in) {
		ROW_DATA_GPIO_Port->BSRR = (uint32_t)ROW_DATA_Pin;
	} else {
		ROW_DATA_GPIO_Port->BRR = (uint32_t)ROW_DATA_Pin;
	}
	delayClock();
	ROW_CLK_GPIO_Port->BSRR = (uint32_t)ROW_CLK_Pin;
	delayClock();
	ROW_CLK_GPIO_Port->BRR = (uint32_t)ROW_CLK_Pin;
}

void CubeMxFlipdotDriver::delayClock()
{
	asm("nop");
}

void CubeMxFlipdotDriver::delayFlipDots()
{
	HAL_Delay(10);
}

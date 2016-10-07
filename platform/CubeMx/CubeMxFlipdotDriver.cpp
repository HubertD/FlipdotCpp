#include "CubeMxFlipdotDriver.h"
#include "stm32f0xx_hal.h"

CubeMxFlipdotDriver::CubeMxFlipdotDriver()
{
}

CubeMxFlipdotDriver::~CubeMxFlipdotDriver()
{
}

void CubeMxFlipdotDriver::update(unsigned ticks)
{
	(void) ticks;
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
	HAL_GPIO_WritePin(BLACK_OE_GPIO_Port, BLACK_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(WHITE_OE_GPIO_Port, WHITE_OE_Pin, GPIO_PIN_SET);
}

void CubeMxFlipdotDriver::setOutputEnableWhite()
{
	HAL_GPIO_WritePin(WHITE_OE_GPIO_Port, WHITE_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BLACK_OE_GPIO_Port, BLACK_OE_Pin, GPIO_PIN_SET);
}

void CubeMxFlipdotDriver::setOutputEnableNone()
{
	HAL_GPIO_WritePin(BLACK_OE_GPIO_Port, BLACK_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(WHITE_OE_GPIO_Port, WHITE_OE_Pin, GPIO_PIN_RESET);
}

void CubeMxFlipdotDriver::strobe()
{
	HAL_GPIO_WritePin(STROBE_GPIO_Port, STROBE_Pin, GPIO_PIN_SET);
	delayClock();
	HAL_GPIO_WritePin(STROBE_GPIO_Port, STROBE_Pin, GPIO_PIN_RESET);
	delayClock();
	HAL_GPIO_WritePin(STROBE_GPIO_Port, STROBE_Pin, GPIO_PIN_SET);
}

void CubeMxFlipdotDriver::shiftColumnRegister(bool in)
{

	if (in) {
		HAL_GPIO_WritePin(COL_DATA_GPIO_Port, COL_DATA_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(COL_DATA_GPIO_Port, COL_DATA_Pin, GPIO_PIN_RESET);
	}
	delayClock();
	HAL_GPIO_WritePin(COL_CLK_GPIO_Port, COL_CLK_Pin, GPIO_PIN_SET);
	delayClock();
	HAL_GPIO_WritePin(COL_CLK_GPIO_Port, COL_CLK_Pin, GPIO_PIN_RESET);
}

void CubeMxFlipdotDriver::shiftRowRegister(bool in)
{
	if (in) {
		HAL_GPIO_WritePin(ROW_DATA_GPIO_Port, ROW_DATA_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(ROW_DATA_GPIO_Port, ROW_DATA_Pin, GPIO_PIN_RESET);
	}

	delayClock();
	HAL_GPIO_WritePin(ROW_CLK_GPIO_Port, ROW_CLK_Pin, GPIO_PIN_SET);
	delayClock();
	HAL_GPIO_WritePin(ROW_CLK_GPIO_Port, ROW_CLK_Pin, GPIO_PIN_RESET);
}

void CubeMxFlipdotDriver::delayClock()
{
	asm("nop");
}

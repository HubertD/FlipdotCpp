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
	for (int i=0; i<length; i++)
	{
		for (int j=0; j<8; j++)
		{
			shiftColumnRegister(data[i] & (1<<j));
		}
	}
}

void CubeMxFlipdotDriver::writeRowData(uint8_t* data, unsigned length)
{
	for (int i=0; i<length; i++)
	{
		for (int j=0; j<8; j++)
		{
			shiftRowRegister(data[i] & (1<<j));
		}
	}
}

void CubeMxFlipdotDriver::setOutputEnableBlack()
{
	HAL_GPIO_WritePin(FD_WHITE_OE_GPIO_Port, FD_WHITE_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(FD_BLACK_OE_GPIO_Port, FD_BLACK_OE_Pin, GPIO_PIN_SET);
}

void CubeMxFlipdotDriver::setOutputEnableWhite()
{
	HAL_GPIO_WritePin(FD_BLACK_OE_GPIO_Port, FD_BLACK_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(FD_WHITE_OE_GPIO_Port, FD_WHITE_OE_Pin, GPIO_PIN_SET);
}

void CubeMxFlipdotDriver::setOutputEnableNone()
{
	HAL_GPIO_WritePin(FD_BLACK_OE_GPIO_Port, FD_BLACK_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(FD_WHITE_OE_GPIO_Port, FD_WHITE_OE_Pin, GPIO_PIN_RESET);
}

void CubeMxFlipdotDriver::strobe()
{
	HAL_GPIO_WritePin(FD_STROBE_GPIO_Port, FD_STROBE_Pin, GPIO_PIN_SET);
	delayClock();
	HAL_GPIO_WritePin(FD_STROBE_GPIO_Port, FD_STROBE_Pin, GPIO_PIN_RESET);
}

void CubeMxFlipdotDriver::shiftColumnRegister(bool in)
{
	HAL_GPIO_WritePin(FD_COL_DATA_GPIO_Port, FD_COL_DATA_Pin, in ? GPIO_PIN_SET : GPIO_PIN_RESET);
	delayClock();
	HAL_GPIO_WritePin(FD_COL_CLK_GPIO_Port, FD_COL_CLK_Pin, GPIO_PIN_SET);
	delayClock();
	HAL_GPIO_WritePin(FD_COL_CLK_GPIO_Port, FD_COL_CLK_Pin, GPIO_PIN_RESET);
}

void CubeMxFlipdotDriver::shiftRowRegister(bool in)
{
	HAL_GPIO_WritePin(FD_ROW_DATA_GPIO_Port, FD_ROW_DATA_Pin, in ? GPIO_PIN_SET : GPIO_PIN_RESET);
	delayClock();
	HAL_GPIO_WritePin(FD_ROW_CLK_GPIO_Port, FD_ROW_CLK_Pin, GPIO_PIN_SET);
	delayClock();
	HAL_GPIO_WritePin(FD_ROW_CLK_GPIO_Port, FD_ROW_CLK_Pin, GPIO_PIN_RESET);
}

void CubeMxFlipdotDriver::delayClock()
{
}

void CubeMxFlipdotDriver::delayFlipDots()
{
}


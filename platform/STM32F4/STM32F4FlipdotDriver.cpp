#include "STM32F4FlipdotDriver.h"
#include "stm32f4xx_hal.h"

STM32F4FlipdotDriver::STM32F4FlipdotDriver()
{
}

STM32F4FlipdotDriver::~STM32F4FlipdotDriver()
{
}

void STM32F4FlipdotDriver::update(unsigned ticks)
{
	(void) ticks;
}

void STM32F4FlipdotDriver::writeColumnData(uint8_t* data, unsigned length)
{
	for (unsigned i=0; i<length; i++)
	{
		for (int j=0; j<8; j++)
		{
			shiftColumnRegister(data[i] & (1<<j));
		}
	}
}

void STM32F4FlipdotDriver::writeRowData(uint8_t* data, unsigned length)
{
	for (unsigned i=0; i<length; i++)
	{
		for (int j=0; j<8; j++)
		{
			shiftRowRegister(data[i] & (1<<j));
		}
	}
}

void STM32F4FlipdotDriver::setOutputEnableBlack()
{
	HAL_GPIO_WritePin(BLACK_OE_GPIO_Port, BLACK_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(WHITE_OE_GPIO_Port, WHITE_OE_Pin, GPIO_PIN_SET);
}

void STM32F4FlipdotDriver::setOutputEnableWhite()
{
	HAL_GPIO_WritePin(WHITE_OE_GPIO_Port, WHITE_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BLACK_OE_GPIO_Port, BLACK_OE_Pin, GPIO_PIN_SET);
}

void STM32F4FlipdotDriver::setOutputEnableNone()
{
	HAL_GPIO_WritePin(BLACK_OE_GPIO_Port, BLACK_OE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(WHITE_OE_GPIO_Port, WHITE_OE_Pin, GPIO_PIN_RESET);
}

void STM32F4FlipdotDriver::strobe()
{
	HAL_GPIO_WritePin(STROBE_GPIO_Port, STROBE_Pin, GPIO_PIN_SET);
	delayClock();
	HAL_GPIO_WritePin(STROBE_GPIO_Port, STROBE_Pin, GPIO_PIN_RESET);
	delayClock();
	HAL_GPIO_WritePin(STROBE_GPIO_Port, STROBE_Pin, GPIO_PIN_SET);
}

void STM32F4FlipdotDriver::shiftColumnRegister(bool in)
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

void STM32F4FlipdotDriver::shiftRowRegister(bool in)
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

void STM32F4FlipdotDriver::delayClock()
{
	asm("nop");
}

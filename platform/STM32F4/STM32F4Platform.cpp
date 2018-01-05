#include <STM32F4Platform.h>

#include "stm32f4xx_hal.h"

static void MX_GPIO_Init(void);
static void SystemClock_Config(void);


STM32F4Platform::STM32F4Platform()
	: _framebuffer(_driver)
{
}

void STM32F4Platform::init()
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
}

uint32_t STM32F4Platform::getTicks()
{
	return HAL_GetTick();
}

bool STM32F4Platform::doQuit()
{
	return false;
}


void STM32F4Platform::update()
{
	uint8_t nes = getNESbyte();
	auto now = getTicks();
	_gamepad.A.update(now, (nes & 0x80) != 0);
	_gamepad.B.update(now, (nes & 0x40) != 0);
	_gamepad.Select.update(now, (nes & 0x20) != 0);
	_gamepad.Start.update(now, (nes & 0x10) != 0);
	_gamepad.North.update(now, (nes & 0x08) != 0);
	_gamepad.South.update(now, (nes & 0x04) != 0);
	_gamepad.West.update(now, (nes & 0x02) != 0);
	_gamepad.East.update(now, (nes & 0x01) != 0);
}

void STM32F4Platform::done()
{
}

uint8_t STM32F4Platform::getNESbyte()
{
	uint8_t value = 0;

	sendNESlatch();
	for (int i=0; i<8; i++)
	{
		value <<= 1;
		if (getNESbit())
		{
			value |= 0x01;
		}

		sendNESclock();
	}

	return value;
}

bool STM32F4Platform::getNESbit()
{
	return HAL_GPIO_ReadPin(NES_DATA_GPIO_Port, NES_DATA_Pin) == 0;
}

void STM32F4Platform::sendNESlatch()
{
	HAL_GPIO_WritePin(NES_LATCH_GPIO_Port, NES_LATCH_Pin, GPIO_PIN_SET);
	for (int i=0; i<100; i++) { asm("nop"); }
	HAL_GPIO_WritePin(NES_LATCH_GPIO_Port, NES_LATCH_Pin, GPIO_PIN_RESET);
	for (int i=0; i<10; i++) { asm("nop"); }
}

void STM32F4Platform::sendNESclock()
{
	for (int i=0; i<10; i++) { asm("nop"); }
	HAL_GPIO_WritePin(NES_CLK_GPIO_Port, NES_CLK_Pin, GPIO_PIN_SET);
	for (int i=0; i<10; i++) { asm("nop"); }
	HAL_GPIO_WritePin(NES_CLK_GPIO_Port, NES_CLK_Pin, GPIO_PIN_RESET);
}



Framebuffer& STM32F4Platform::getFramebuffer()
{
	return _framebuffer;
}

Gamepad& STM32F4Platform::getGamepad()
{
	return _gamepad;
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

	  RCC_OscInitTypeDef RCC_OscInitStruct;
	  RCC_ClkInitTypeDef RCC_ClkInitStruct;

	    /**Configure the main internal regulator output voltage
	    */
	  __HAL_RCC_PWR_CLK_ENABLE();

	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	    /**Initializes the CPU, AHB and APB busses clocks
	    */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	  RCC_OscInitStruct.PLL.PLLM = 4;
	  RCC_OscInitStruct.PLL.PLLN = 96;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	  RCC_OscInitStruct.PLL.PLLQ = 7;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	  {
	    while(1);
	  }

	    /**Initializes the CPU, AHB and APB busses clocks
	    */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	  {
		    while(1);
	  }

	    /**Configure the Systick interrupt time
	    */
	  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	    /**Configure the Systick
	    */
	  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	  /* SysTick_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

static void MX_GPIO_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOE_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|NES_LATCH_Pin|NES_CLK_Pin|B1_Pin
	                          |COL_DATA_Pin|COL_CLK_Pin|ROW_DATA_Pin|ROW_CLK_Pin
	                          |STROBE_Pin|BLACK_OE_Pin|WHITE_OE_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
	                          |Audio_RST_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pins : CS_I2C_SPI_Pin NES_LATCH_Pin NES_CLK_Pin B1_Pin
	                           COL_DATA_Pin COL_CLK_Pin ROW_DATA_Pin ROW_CLK_Pin
	                           STROBE_Pin BLACK_OE_Pin WHITE_OE_Pin */
	  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|NES_LATCH_Pin|NES_CLK_Pin|B1_Pin
	                          |COL_DATA_Pin|COL_CLK_Pin|ROW_DATA_Pin|ROW_CLK_Pin
	                          |STROBE_Pin|BLACK_OE_Pin|WHITE_OE_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	  /*Configure GPIO pin : NES_DATA_Pin */
	  GPIO_InitStruct.Pin = NES_DATA_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(NES_DATA_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
	  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : PDM_OUT_Pin */
	  GPIO_InitStruct.Pin = PDM_OUT_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : PUSH_BTN_Pin */
	  GPIO_InitStruct.Pin = PUSH_BTN_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(PUSH_BTN_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : I2S3_WS_Pin */
	  GPIO_InitStruct.Pin = I2S3_WS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
	  HAL_GPIO_Init(I2S3_WS_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : SPI1_SCK_Pin SPI1_MISO_Pin SPI1_MOSI_Pin */
	  GPIO_InitStruct.Pin = SPI1_SCK_Pin|SPI1_MISO_Pin|SPI1_MOSI_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pin : BOOT1_Pin */
	  GPIO_InitStruct.Pin = BOOT1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : CLK_IN_Pin */
	  GPIO_InitStruct.Pin = CLK_IN_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
	                           Audio_RST_Pin */
	  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
	                          |Audio_RST_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	  /*Configure GPIO pins : I2S3_MCK_Pin I2S3_SCK_Pin I2S3_SD_Pin */
	  GPIO_InitStruct.Pin = I2S3_MCK_Pin|I2S3_SCK_Pin|I2S3_SD_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pin : VBUS_FS_Pin */
	  GPIO_InitStruct.Pin = VBUS_FS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(VBUS_FS_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : OTG_FS_ID_Pin OTG_FS_DM_Pin OTG_FS_DP_Pin */
	  GPIO_InitStruct.Pin = OTG_FS_ID_Pin|OTG_FS_DM_Pin|OTG_FS_DP_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
	  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : Audio_SCL_Pin Audio_SDA_Pin */
	  GPIO_InitStruct.Pin = Audio_SCL_Pin|Audio_SDA_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*Configure GPIO pin : MEMS_INT2_Pin */
	  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);
}


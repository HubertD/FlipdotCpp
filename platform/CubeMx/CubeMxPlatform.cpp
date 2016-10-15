#include <CubeMxPlatform.h>

#include "stm32f0xx_hal.h"

void Error_Handler(void);
static void MX_GPIO_Init(void);
static void SystemClock_Config(void);


CubeMxPlatform::CubeMxPlatform()
	: _framebuffer(_driver)
{
}

void CubeMxPlatform::init()
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
}

uint32_t CubeMxPlatform::getTicks()
{
	return HAL_GetTick();
}

bool CubeMxPlatform::doQuit()
{
	return false;
}


void CubeMxPlatform::update()
{
	uint8_t nes = getNESbyte();
	_gamepad.setKeyStatus(GamepadKey::KEY_A,      (nes & 0x80) != 0);
	_gamepad.setKeyStatus(GamepadKey::KEY_B,      (nes & 0x40) != 0);
	_gamepad.setKeyStatus(GamepadKey::KEY_SELECT, (nes & 0x20) != 0);
	_gamepad.setKeyStatus(GamepadKey::KEY_START,  (nes & 0x10) != 0);
	_gamepad.setKeyStatus(GamepadKey::KEY_UP,     (nes & 0x08) != 0);
	_gamepad.setKeyStatus(GamepadKey::KEY_DOWN,   (nes & 0x04) != 0);
	_gamepad.setKeyStatus(GamepadKey::KEY_LEFT,   (nes & 0x02) != 0);
	_gamepad.setKeyStatus(GamepadKey::KEY_RIGHT,  (nes & 0x01) != 0);
}

void CubeMxPlatform::done()
{
}

uint8_t CubeMxPlatform::getNESbyte()
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

bool CubeMxPlatform::getNESbit()
{
	return HAL_GPIO_ReadPin(NES_DATA_GPIO_Port, NES_DATA_Pin) == 0;
}

void CubeMxPlatform::sendNESlatch()
{
	HAL_GPIO_WritePin(NES_LATCH_GPIO_Port, NES_LATCH_Pin, GPIO_PIN_SET);
	for (int i=0; i<100; i++) { asm("nop"); }
	HAL_GPIO_WritePin(NES_LATCH_GPIO_Port, NES_LATCH_Pin, GPIO_PIN_RESET);
	for (int i=0; i<10; i++) { asm("nop"); }
}

void CubeMxPlatform::sendNESclock()
{
	for (int i=0; i<10; i++) { asm("nop"); }
	HAL_GPIO_WritePin(NES_CLK_GPIO_Port, NES_CLK_Pin, GPIO_PIN_SET);
	for (int i=0; i<10; i++) { asm("nop"); }
	HAL_GPIO_WritePin(NES_CLK_GPIO_Port, NES_CLK_Pin, GPIO_PIN_RESET);
}



Framebuffer& CubeMxPlatform::getFramebuffer()
{
	return _framebuffer;
}

IGamepad& CubeMxPlatform::getGamepad()
{
	return _gamepad;
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : NES_DATA */
  GPIO_InitStruct.Pin = NES_DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(NES_DATA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ROW_DATA_Pin ROW_CLK_Pin COL_DATA_Pin COL_CLK_Pin
                           STROBE_Pin BLACK_OE_Pin WHITE_OE_Pin */
  GPIO_InitStruct.Pin = ROW_DATA_Pin|ROW_CLK_Pin|COL_DATA_Pin|COL_CLK_Pin
                          |STROBE_Pin|BLACK_OE_Pin|WHITE_OE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure NES GPIO output pins : NES_CLK, NES_LATCH */
  GPIO_InitStruct.Pin = NES_CLK_Pin|NES_LATCH_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ROW_DATA_Pin|ROW_CLK_Pin|COL_DATA_Pin|COL_CLK_Pin
                          |STROBE_Pin|BLACK_OE_Pin|WHITE_OE_Pin, GPIO_PIN_RESET);


  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LD4_Pin|LD3_Pin, GPIO_PIN_RESET);

}

void Error_Handler(void)
{
  while(1)
  {
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
}

#endif


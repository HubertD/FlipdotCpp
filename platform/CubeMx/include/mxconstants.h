/**
  ******************************************************************************
  * File Name          : mxconstants.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MXCONSTANT_H
#define __MXCONSTANT_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
/*
#define ROW_DATA_Pin GPIO_PIN_1
#define ROW_DATA_GPIO_Port GPIOA
#define ROW_CLK_Pin GPIO_PIN_2
#define ROW_CLK_GPIO_Port GPIOA
#define COL_DATA_Pin GPIO_PIN_3
#define COL_DATA_GPIO_Port GPIOA
#define COL_CLK_Pin GPIO_PIN_4
#define COL_CLK_GPIO_Port GPIOA
*/

#define ROW_DATA_Pin GPIO_PIN_3
#define ROW_DATA_GPIO_Port GPIOA
#define ROW_CLK_Pin GPIO_PIN_4
#define ROW_CLK_GPIO_Port GPIOA
#define COL_DATA_Pin GPIO_PIN_1
#define COL_DATA_GPIO_Port GPIOA
#define COL_CLK_Pin GPIO_PIN_2
#define COL_CLK_GPIO_Port GPIOA
#define STROBE_Pin GPIO_PIN_5
#define STROBE_GPIO_Port GPIOA
#define BLACK_OE_Pin GPIO_PIN_6
#define BLACK_OE_GPIO_Port GPIOA
#define WHITE_OE_Pin GPIO_PIN_7
#define WHITE_OE_GPIO_Port GPIOA
#define LD4_Pin GPIO_PIN_8
#define LD4_GPIO_Port GPIOC
#define LD3_Pin GPIO_PIN_9
#define LD3_GPIO_Port GPIOC
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA

#define NES_CLK_Pin GPIO_PIN_2
#define NES_CLK_GPIO_Port GPIOC
#define NES_DATA_Pin GPIO_PIN_1
#define NES_DATA_GPIO_Port GPIOC
#define NES_LATCH_Pin GPIO_PIN_0
#define NES_LATCH_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MXCONSTANT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "uart.h"
#include "key.h"
//#include "lcd12864.h"
//#include "string.h"
//#include "stdio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CS_Pin GPIO_PIN_0
#define CS_GPIO_Port GPIOF
#define REST_Pin GPIO_PIN_1
#define REST_GPIO_Port GPIOF
#define RS_Pin GPIO_PIN_2
#define RS_GPIO_Port GPIOF
#define SDA_Pin GPIO_PIN_3
#define SDA_GPIO_Port GPIOF
#define SCLK_Pin GPIO_PIN_4
#define SCLK_GPIO_Port GPIOF
#define ROM_CS_Pin GPIO_PIN_0
#define ROM_CS_GPIO_Port GPIOA
#define ROM_SCK_Pin GPIO_PIN_1
#define ROM_SCK_GPIO_Port GPIOA
#define ROM_OUT_Pin GPIO_PIN_2
#define ROM_OUT_GPIO_Port GPIOA
#define ROM_IN_Pin GPIO_PIN_3
#define ROM_IN_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */



void main_page_init(void);

/* USER CODE END Private defines */
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

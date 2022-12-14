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
#define ROM_CS_Pin GPIO_PIN_12
#define ROM_CS_GPIO_Port GPIOC
#define ROM_SCK_Pin GPIO_PIN_13
#define ROM_SCK_GPIO_Port GPIOC
#define ROM_OUT_Pin GPIO_PIN_14	
#define ROM_OUT_GPIO_Port GPIOC
#define ROM_IN_Pin GPIO_PIN_15
#define ROM_IN_GPIO_Port GPIOC
#define CS_Pin GPIO_PIN_4
#define CS_GPIO_Port GPIOC
#define REST_Pin GPIO_PIN_5
#define REST_GPIO_Port GPIOC
#define RS_Pin GPIO_PIN_6
#define RS_GPIO_Port GPIOC
#define SDA_Pin GPIO_PIN_7
#define SDA_GPIO_Port GPIOC
#define SCLK_Pin GPIO_PIN_8
#define SCLK_GPIO_Port GPIOC
//#define UP_Pin_Pin GPIO_PIN_6
//#define UP_Pin_GPIO_Port GPIOB
//#define DOWN_Pin_Pin GPIO_PIN_7
//#define DOWN_Pin_GPIO_Port GPIOB
//#define BACK_Pin_Pin GPIO_PIN_8
//#define BACK_Pin_GPIO_Port GPIOB
//#define OK_Pin_Pin GPIO_PIN_9
//#define OK_Pin_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
void main_page_init(void);
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

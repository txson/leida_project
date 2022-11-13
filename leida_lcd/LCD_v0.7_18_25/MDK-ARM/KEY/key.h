#ifndef _KEY_H
#define _KEY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f103xe.h"
#include "stm32f1xx_hal.h"

#define KEY_MAX_NUM 20

/* Private defines -----------------------------------------------------------*/
#define UP_Pin GPIO_PIN_6
#define UP_GPIO_Port GPIOB
#define DOWN_Pin GPIO_PIN_7
#define DOWN_GPIO_Port GPIOB
#define BACK_Pin GPIO_PIN_8
#define BACK_GPIO_Port GPIOB
#define OK_Pin GPIO_PIN_9
#define OK_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

//操作HAL库函数读取IO口状态
#define KEY_UP		HAL_GPIO_ReadPin(UP_GPIO_Port,UP_Pin)
#define KEY_DOWN    HAL_GPIO_ReadPin(DOWN_GPIO_Port,DOWN_Pin)
#define KEY_BACK  HAL_GPIO_ReadPin(BACK_GPIO_Port,BACK_Pin)
#define KEY_OK      HAL_GPIO_ReadPin(OK_GPIO_Port,OK_Pin)

#define UP_KEY 	1
#define DOWN_KEY	2
#define BACK_KEY	3
#define OK_KEY   	4 

void Key_Init(void);


uint8_t KEY_Scan(uint8_t mode);

#ifdef __cplusplus
}
#endif

#endif


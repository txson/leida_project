/*
 * @Author: YourName
 * @Date: 2022-11-16 22:46:45
 * @LastEditTime: 2022-11-21 21:08:11
 * @LastEditors: YourName
 * @Description: 
 * @FilePath: \MDK-ARM\user\KEY\key.c
 * 版权声明
 */
#include "lcd12864.h"
#include "key.h"


uint8_t g_key_buf[KEY_MAX_NUM] = {0}; //记录20个按键缓存

void Key_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : up_Pin dwon_Pin select_Pin OK_Pin */
  GPIO_InitStruct.Pin = UP_Pin|DOWN_Pin|BACK_Pin|OK_Pin;	/*初始化按键*/
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//  /* EXTI interrupt init*/
//  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);	/*初始化按键中断*/
//  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);  		/*按键中断使能*/

}
/*
	按键扫描函数
*/
uint8_t key_val = 0;
uint8_t KEY_Scan(uint8_t mode)   /*按键扫描*/
{
	uint8_t tmp_key_val = 0;
	if(((KEY_UP == 0)||(KEY_DOWN == 0)||(KEY_BACK == 0)||(KEY_OK == 0)) )/*有一个出发就进入扫描*/
	{		
		HAL_Delay(10);			//按键消抖
		if(KEY_UP==0)
		{
			key_val = UP_KEY;
		}
		else if(KEY_DOWN==0)
		{			
			key_val = DOWN_KEY;
		}
		else if(KEY_BACK==0)	
		{
			key_val = BACK_KEY;
		}
		else if(KEY_OK==0)		
		{
			key_val = OK_KEY;
		}

	}
	else
	{
		tmp_key_val = key_val;
		key_val = 0;
	}
	return tmp_key_val;
}

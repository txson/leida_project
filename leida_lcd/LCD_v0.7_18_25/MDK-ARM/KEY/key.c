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
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);	/*初始化按键中断*/
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);  		/*按键中断使能*/

}
/*
	按键扫描函数
*/
uint8_t key_val = 0;
uint8_t KEY_Scan(uint8_t mode)   /*按键扫描*/
{
	uint8_t tmp_sta = 0;
	if(((KEY_UP == 0)||(KEY_DOWN == 0)||(KEY_BACK == 0)||(KEY_OK == 0)) )/*有一个出发就进入扫描*/
	{		
		HAL_Delay(10);			//按键消抖
		//key = 0;
		if(KEY_UP==0)
		{
			key_val = UP_KEY;
			//while(!HAL_GPIO_ReadPin(UP_GPIO_Port,UP_Pin));			//这里后面需要优化成超时
		}
		else if(KEY_DOWN==0)
		{			
			key_val = DOWN_KEY;
			//while(!HAL_GPIO_ReadPin(DOWN_GPIO_Port,DOWN_Pin));
		}
		else if(KEY_BACK==0)	
		{
			key_val = BACK_KEY;
			//while(!HAL_GPIO_ReadPin(BACK_GPIO_Port,BACK_Pin));
		}
		else if(KEY_OK==0)		
		{
			key_val = OK_KEY;
			//while(!HAL_GPIO_ReadPin(OK_GPIO_Port,OK_Pin));
		}
		else
		{
			
			tmp_sta = key_val;
			key_val = 0;
		}
	}
	return tmp_sta;
}

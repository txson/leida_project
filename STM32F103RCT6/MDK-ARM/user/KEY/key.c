/*
 * @Author: YourName
 * @Date: 2022-11-16 22:46:45
 * @LastEditTime: 2022-11-24 10:55:48
 * @LastEditors: herod
 * @Description: 
 * @FilePath: \MDK-ARM\user\KEY\key.c
 * ��Ȩ����
 */
#include "lcd12864.h"
#include "key.h"


uint8_t g_key_buf[KEY_MAX_NUM] = {0}; //��¼20����������



/**
 * @Date: 2022-11-24 10:55:35
 * @LastEditors: herod
 * @Description: 按键初始化
 */
void Key_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : up_Pin dwon_Pin select_Pin OK_Pin */
  GPIO_InitStruct.Pin = UP_Pin|DOWN_Pin|BACK_Pin|OK_Pin;	/*��ʼ������*/
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//  /* EXTI interrupt init*/
//  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);	/*��ʼ�������ж�*/
//  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);  		/*�����ж�ʹ��*/

}
/*
	����ɨ�躯��
*/
uint8_t key_val = 0;
/**
 * @Date: 2022-11-24 10:55:44
 * @LastEditors: herod
 * @param {uint8_t} mode
 * @Description: 按键扫描
 */
uint8_t KEY_Scan(uint8_t mode)   /*����ɨ��*/
{
	uint8_t tmp_key_val = 0;
	if(((KEY_UP == 0)||(KEY_DOWN == 0)||(KEY_BACK == 0)||(KEY_OK == 0)) )/*��һ�������ͽ���ɨ��*/
	{		
		HAL_Delay(10);			//��������
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
		tmp_key_val = key_val;	/*�ȴ�����ȫ���ſ�,�������һ���ſ��İ���*/
		if(tmp_key_val != 0)
		{
			printf("key up key val = %d\r\n",key_val);
		}
		key_val = 0;
	}
	return tmp_key_val;
}

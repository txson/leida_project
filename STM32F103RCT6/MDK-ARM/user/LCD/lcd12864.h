#ifndef _LCD12864_H
#define _LCD12864_H
#include "stm32f103xe.h"
#include "stm32f1xx_hal.h"
#include "main.h"
#define lcd_cs1_h HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
#define lcd_cs1_l HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);

#define lcd_reset_h HAL_GPIO_WritePin(REST_GPIO_Port, REST_Pin, GPIO_PIN_SET);
#define lcd_reset_l HAL_GPIO_WritePin(REST_GPIO_Port, REST_Pin, GPIO_PIN_RESET);

#define lcd_rs_h HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
#define lcd_rs_l HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);

#define lcd_sid_h HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET);
#define lcd_sid_l HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_RESET);

#define lcd_sclk_h HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);
#define lcd_sclk_l HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);

#define Rom_CS_h HAL_GPIO_WritePin(ROM_CS_GPIO_Port, ROM_CS_Pin, GPIO_PIN_SET);
#define Rom_CS_l HAL_GPIO_WritePin(ROM_CS_GPIO_Port, ROM_CS_Pin, GPIO_PIN_RESET);

#define Rom_SCK_h HAL_GPIO_WritePin(ROM_SCK_GPIO_Port, ROM_SCK_Pin, GPIO_PIN_SET);
#define Rom_SCK_l HAL_GPIO_WritePin(ROM_SCK_GPIO_Port, ROM_SCK_Pin, GPIO_PIN_RESET);

#define Rom_OUT_h HAL_GPIO_WritePin(ROM_OUT_GPIO_Port, ROM_OUT_Pin, GPIO_PIN_SET);
#define Rom_OUT_l HAL_GPIO_WritePin(ROM_OUT_GPIO_Port, ROM_OUT_Pin, GPIO_PIN_RESET);

#define Rom_IN_h HAL_GPIO_WritePin(ROM_IN_GPIO_Port, ROM_IN_Pin, GPIO_PIN_SET);
#define Rom_IN_l HAL_GPIO_WritePin(ROM_IN_GPIO_Port, ROM_IN_Pin, GPIO_PIN_RESET);

#define Rom_OUT HAL_GPIO_ReadPin(ROM_OUT_GPIO_Port, ROM_OUT_Pin)


void display_string_5x8(uchar page,uchar column,uchar *text);

/***********************************************************************************************
*������ ��		delay
*������������ ��ms������ʱ����
*�������� ��	n_ms : ��Ҫ��ʱ��msʱ��
*��������ֵ ��	��
*���� ��		
*������������ ��2022-08-06
*�����޸����� ��
*�޸��� ��
*�޸�ԭ�� ��	
*�汾 ��		v0.1
*��ʷ�汾 ��
***********************************************************************************************/
void delay(int n_ms);

/***********************************************************************************************
*������ ��		delay_us
*������������ ��us������ʱ����
*�������� ��	n_us : ��Ҫ��ʱ��usʱ��
*��������ֵ ��	��
*���� ��		
*������������ ��2022-08-06
*�����޸����� ��
*�޸��� ��
*�޸�ԭ�� ��	
*�汾 ��		v0.1
*��ʷ�汾 ��
***********************************************************************************************/
void delay_us(int n_us);

/***********************************************************************************************
*������ ��		transfer_command_lcd
*������������ ����lcd����ָ��
*�������� ��	data1 : ���͵�ָ��
*��������ֵ ��	��
*���� ��		
*������������ ��2022-08-06
*�����޸����� ��
*�޸��� ��
*�޸�ԭ�� ��	
*�汾 ��		v0.1
*��ʷ�汾 ��
***********************************************************************************************/
void transfer_command_lcd(int data1);

/***********************************************************************************************
*������ ��		transfer_data_lcd
*������������ ����lcd��������
*�������� ��	data1 : ���͵�����
*��������ֵ ��	��
*���� ��		
*������������ ��2022-08-06
*�����޸����� ��
*�޸��� ��
*�޸�ԭ�� ��	
*�汾 ��		v0.1
*��ʷ�汾 ��
***********************************************************************************************/
void transfer_data_lcd(int data1);

/***********************************************************************************************
*������ ��		initial_lcd
*������������ ����ʼ��lcd  ��ָ��Ĵ�������ָ��  ����lcd
*�������� ��	��
*��������ֵ ��	��
*���� ��		
*������������ ��2022-08-06
*�����޸����� ��
*�޸��� ��
*�޸�ԭ�� ��	
*�汾 ��		v0.1
*��ʷ�汾 ��
***********************************************************************************************/
void initial_lcd(void);

/***********************************************************************************************
*������ ��		lcd_address
*������������ ������lcd���ʵ�ַ  ����ָ�������Ǹ�ɫ��
*�������� ��	��
*��������ֵ ��	��
*���� ��		
*������������ ��2022-08-06
*�����޸����� ��
*�޸��� ��
*�޸�ԭ�� ��	
*�汾 ��		v0.1
*��ʷ�汾 ��
***********************************************************************************************/
void lcd_address(uint page,uint column);

/***********************************************************************************************
*������ ��		clear_screen
*������������ ������
*�������� ��	��
*��������ֵ ��	��
*���� ��		
*������������ ��2022-08-06
*�����޸����� ��
*�޸��� ��
*�޸�ԭ�� ��	
*�汾 ��		v0.1
*��ʷ�汾 ��
***********************************************************************************************/
void clear_screen(void);

/***********************************************************************************************
*������ ��		send_command_to_ROM
*������������ ���������ݵ��ֿ�ȡ��
*�������� ��	datu : ȡ�ֵ�ָ��
*��������ֵ ��	��
*���� ��		
*������������ ��2022-08-06
*�����޸����� ��
*�޸��� ��
*�޸�ԭ�� ��	
*�汾 ��		v0.1
*��ʷ�汾 ��
***********************************************************************************************/
void send_command_to_ROM( uchar datu );
//static uchar get_data_from_ROM(void);

/***********************************************************************************************
*������ ��		display_GB2312_string
*������������ ��������ʾ�������
*�������� ��	fontaddr : ȡ�ֵ�ַ
				page	 : �к�
				column   : �к�
				reverse  : ��ɫ��ת  	0:��ɫ����ת   	��0:��ɫ��ת
				under    : �Ƿ��»���  	0:���»���   	1:û���»���
*��������ֵ ��	��
*���� ��		
*������������ ��2022-08-06
*�����޸����� ��
*�޸��� ��
*�޸�ԭ�� ��	
*�汾 ��		v0.1
*��ʷ�汾 ��
***********************************************************************************************/
void display_GB2312_string(uchar page,uchar column,uchar *text,uint8_t reverse,uchar under);

/***********************************************************************************************
*������ ��		display_Signle_GB2312_string
*������������ ����ʾ��������
*�������� ��	fontaddr : ȡ�ֵ�ַ
				page	 : �к�
				column   : �к�
				reverse  : �Ƿ���ɫ��ת    	0:��ɫ����ת   ��0:��ɫ��ת
				under    : �Ƿ��»���  		0:���»���   	1:û���»���
*��������ֵ ��	��
*���� ��		
*������������ ��2022-08-06
*�����޸����� ��
*�޸��� ��
*�޸�ԭ�� ��	
*�汾 ��		v0.1
*��ʷ�汾 ��
***********************************************************************************************/
void display_Signle_GB2312_string(uchar page,uchar column,uchar *text,uint8_t reverse,uchar under);


void transfer_data(int data1);
#endif

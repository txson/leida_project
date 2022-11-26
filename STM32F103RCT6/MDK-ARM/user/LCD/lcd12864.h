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
*函数名 ：		delay
*函数功能描述 ：ms级粗延时函数
*函数参数 ：	n_ms : 需要延时的ms时间
*函数返回值 ：	无
*作者 ：		
*函数创建日期 ：2022-08-06
*函数修改日期 ：
*修改人 ：
*修改原因 ：	
*版本 ：		v0.1
*历史版本 ：
***********************************************************************************************/
void delay(int n_ms);

/***********************************************************************************************
*函数名 ：		delay_us
*函数功能描述 ：us级粗延时函数
*函数参数 ：	n_us : 需要延时的us时间
*函数返回值 ：	无
*作者 ：		
*函数创建日期 ：2022-08-06
*函数修改日期 ：
*修改人 ：
*修改原因 ：	
*版本 ：		v0.1
*历史版本 ：
***********************************************************************************************/
void delay_us(int n_us);

/***********************************************************************************************
*函数名 ：		transfer_command_lcd
*函数功能描述 ：向lcd发送指令
*函数参数 ：	data1 : 发送的指令
*函数返回值 ：	无
*作者 ：		
*函数创建日期 ：2022-08-06
*函数修改日期 ：
*修改人 ：
*修改原因 ：	
*版本 ：		v0.1
*历史版本 ：
***********************************************************************************************/
void transfer_command_lcd(int data1);

/***********************************************************************************************
*函数名 ：		transfer_data_lcd
*函数功能描述 ：向lcd发送数据
*函数参数 ：	data1 : 发送的数据
*函数返回值 ：	无
*作者 ：		
*函数创建日期 ：2022-08-06
*函数修改日期 ：
*修改人 ：
*修改原因 ：	
*版本 ：		v0.1
*历史版本 ：
***********************************************************************************************/
void transfer_data_lcd(int data1);

/***********************************************************************************************
*函数名 ：		initial_lcd
*函数功能描述 ：初始化lcd  向指令寄存器发送指令  配置lcd
*函数参数 ：	无
*函数返回值 ：	无
*作者 ：		
*函数创建日期 ：2022-08-06
*函数修改日期 ：
*修改人 ：
*修改原因 ：	
*版本 ：		v0.1
*历史版本 ：
***********************************************************************************************/
void initial_lcd(void);

/***********************************************************************************************
*函数名 ：		lcd_address
*函数功能描述 ：发送lcd访问地址  用于指定控制那个色块
*函数参数 ：	无
*函数返回值 ：	无
*作者 ：		
*函数创建日期 ：2022-08-06
*函数修改日期 ：
*修改人 ：
*修改原因 ：	
*版本 ：		v0.1
*历史版本 ：
***********************************************************************************************/
void lcd_address(uint page,uint column);

/***********************************************************************************************
*函数名 ：		clear_screen
*函数功能描述 ：清屏
*函数参数 ：	无
*函数返回值 ：	无
*作者 ：		
*函数创建日期 ：2022-08-06
*函数修改日期 ：
*修改人 ：
*修改原因 ：	
*版本 ：		v0.1
*历史版本 ：
***********************************************************************************************/
void clear_screen(void);

/***********************************************************************************************
*函数名 ：		send_command_to_ROM
*函数功能描述 ：发送数据到字库取字
*函数参数 ：	datu : 取字的指令
*函数返回值 ：	无
*作者 ：		
*函数创建日期 ：2022-08-06
*函数修改日期 ：
*修改人 ：
*修改原因 ：	
*版本 ：		v0.1
*历史版本 ：
***********************************************************************************************/
void send_command_to_ROM( uchar datu );
//static uchar get_data_from_ROM(void);

/***********************************************************************************************
*函数名 ：		display_GB2312_string
*函数功能描述 ：连续显示多个汉字
*函数参数 ：	fontaddr : 取字地址
				page	 : 行号
				column   : 列号
				reverse  : 颜色反转  	0:颜色不反转   	非0:颜色反转
				under    : 是否下划线  	0:有下划线   	1:没有下划线
*函数返回值 ：	无
*作者 ：		
*函数创建日期 ：2022-08-06
*函数修改日期 ：
*修改人 ：
*修改原因 ：	
*版本 ：		v0.1
*历史版本 ：
***********************************************************************************************/
void display_GB2312_string(uchar page,uchar column,uchar *text,uint8_t reverse,uchar under);

/***********************************************************************************************
*函数名 ：		display_Signle_GB2312_string
*函数功能描述 ：显示单个汉字
*函数参数 ：	fontaddr : 取字地址
				page	 : 行号
				column   : 列号
				reverse  : 是否颜色翻转    	0:颜色不反转   非0:颜色反转
				under    : 是否下划线  		0:有下划线   	1:没有下划线
*函数返回值 ：	无
*作者 ：		
*函数创建日期 ：2022-08-06
*函数修改日期 ：
*修改人 ：
*修改原因 ：	
*版本 ：		v0.1
*历史版本 ：
***********************************************************************************************/
void display_Signle_GB2312_string(uchar page,uchar column,uchar *text,uint8_t reverse,uchar under);


void transfer_data(int data1);
#endif

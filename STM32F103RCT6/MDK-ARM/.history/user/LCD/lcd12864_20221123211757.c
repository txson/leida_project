#include "lcd12864.h"




/**
 * @Date: 2022-11-23 21:15:26
 * @LastEditors: herod
 * @param {int} n_ms
 * @Description:  粗延时
 */
void delay(int n_ms) //延时
{
	int j,k;
	for(j=0;j<n_ms;j++)
	for(k=0;k<990;k++);
}

/**
 * @Date: 2022-11-23 21:14:22
 * @LastEditors: herod
 * @param {int} data1	项lcd模块写入的指令
 * @Description: 
 */
void transfer_command_lcd(int data1) //写指令到LCD   使用的模拟SPI
{
	char i;
	lcd_cs1_l;				//片选拉低
	lcd_rs_l;				//rs拉低
	for(i=0;i<8;i++)
	{
		lcd_sclk_l;			//时钟拉低
//		delay_us(10); 
		if(data1&0x80) 
		{
			lcd_sid_h; 
		}
		else 
		{
			lcd_sid_l;
		}
		lcd_sclk_h;
//		delay_us(10); 
		data1=data1 <<= 1;
	}
	lcd_cs1_h;
}

/**
 * @Date: 2022-11-23 21:16:03
 * @LastEditors: herod
 * @param {int} data1
 * @Description: 向lcd写入数据
 */
void transfer_data_lcd(int data1) //写数据到LCD
{
	char i;
	lcd_cs1_l;
	lcd_rs_h;				//RS拉高
	for(i=0;i<8;i++)
	{
		lcd_sclk_l;
		if(data1&0x80) 
		{
			lcd_sid_h;
		}
		else 
		{
			lcd_sid_l;
		}
		lcd_sclk_h;
		data1=data1 <<= 1;
	}
	lcd_cs1_h;
}

/**
 * @Date: 2022-11-23 21:16:21
 * @LastEditors: herod
 * @Description: 初始化lcd
 */
void initial_lcd() //LCD初始化
{
	lcd_reset_l; 
	delay(100);
	lcd_reset_h; 
	delay(100);
	transfer_command_lcd(0xe2);    /*软复位*/
	delay(5);
	transfer_command_lcd(0x2c);    /*升压步骤1*/
	delay(50);
	transfer_command_lcd(0x2e);    /*升压步骤2*/
	delay(50);
	transfer_command_lcd(0x2f);    /*升压步骤3*/
	delay(5);
	transfer_command_lcd(0x23);     /*粗调对比度，可设置范围0x20~0x27*/
	transfer_command_lcd(0x81);     /*微调对比度*/
	transfer_command_lcd(0x22);     /*0x1a,微调对比度的值,可设置范围0x00~0x3f*/
	transfer_command_lcd(0xa2);     /*1/9偏压比(bias)*/
	transfer_command_lcd(0xc8);     /*行扫描顺序:从上到下*/
	transfer_command_lcd(0xa0);     /*行扫描顺序:从左到右*/
	transfer_command_lcd(0x40);     /*起始行:第一行开始*/
	transfer_command_lcd(0xb7);
	transfer_command_lcd(0xa6);     /*设置页颜色翻转*/
	
	transfer_command_lcd(0xaf);      /*开显示*/
	transfer_command_lcd(0xa4); 
}

/**
 * @Date: 2022-11-23 21:16:49
 * @LastEditors: herod
 * @param {uint} page	页面 每8行为一个页面
 * @param {uint} column	列
 * @Description: 向lcd发送需要显示地址
 */
void lcd_address(uint page,uint column)
{
	column=column-0x01;								/*行-1*/
	transfer_command_lcd(0xb0+page-1);              /*设置页地址。每页8行。一个画面分为64行被分成8页。我们平常所说的第一页，在LCD驱动里是第0页
	所以要减去1*/
	transfer_command_lcd(0x10+(column>>4&0x0f));    /*设置列地址的高4位*/
	transfer_command_lcd(column&0x0f);				/*设置列地址的低4位*/
}



void clear_screen() //全屏清屏
{
	uchar i,j;
 	for(i=0;i<9;i++)
	{
		lcd_address(1+i,1);
		for(j=0;j<132;j++)
		{
			transfer_data_lcd(0x00);
		}
	}
}

void send_command_to_ROM( uchar datu ) //送指令到字库
{
	uchar i;
	for(i=0;i<8;i++ )
	{
		Rom_SCK_l;
//		delay_us(10);
		if(datu&0x80)
		{
			Rom_IN_h;
		}
		else 
		{
			Rom_IN_l;
		}
		datu = datu<<1;
		Rom_SCK_h;
//		delay_us(10);
	}
}

static uchar get_data_from_ROM( ) //从字库中取汉字或字符
{
	uchar i;
	uchar ret_data=0;
	for(i=0;i<8;i++)
	{
		Rom_OUT_h;
		Rom_SCK_l;
//		delay_us(1);
		ret_data=ret_data<<1;
		if(Rom_OUT)  //
		ret_data=ret_data+1;
		else
		ret_data=ret_data+0;
		Rom_SCK_h;
//		delay_us(1);
	}
	return(ret_data);
}

static void get_and_write_16x16(ulong fontaddr,uchar page,uchar column,uint8_t reverse,uchar under)
{
	uchar i,j,disp_data;
	Rom_CS_l;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);
	send_command_to_ROM((fontaddr&0xff00)>>8);
	send_command_to_ROM(fontaddr&0xff);
 
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for(i=0; i<16; i++ )
		{
			if(under == 1 && j == 1 )
			{
				disp_data=get_data_from_ROM()|0x80;
			}
			else
			{
				disp_data=get_data_from_ROM();
			}

			if(reverse == 1)
				transfer_data_lcd(~disp_data);
			else
				transfer_data_lcd(disp_data);
		}
	}
	
		

	Rom_CS_h;
}

void get_and_write_8x16(ulong fontaddr,uchar page,uchar column,uchar reverse,uchar under)
{
	uchar i,j,disp_data;
	Rom_CS_l;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);
	send_command_to_ROM((fontaddr&0xff00)>>8); 
	send_command_to_ROM(fontaddr&0xff); 

	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for(i=0; i<8; i++ )
		{
			if(under == 1 && j == 1 )
			{
				disp_data=get_data_from_ROM()|0x80;
			}
			else
			{
				disp_data=get_data_from_ROM();
			}
			if(reverse == 0)
			{
				transfer_data_lcd(disp_data);
			}
			else
			{
				transfer_data_lcd(~disp_data);
			}
		}
	}
	
	Rom_CS_h;
}

void get_and_write_5x8(ulong fontaddr,uchar page,uchar column)
{
	uchar i,disp_data;
	Rom_CS_l;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);
	send_command_to_ROM((fontaddr&0xff00)>>8);
	send_command_to_ROM(fontaddr&0xff);
	lcd_address(page,column);
	for(i=0; i<5; i++ )
	{
		disp_data=get_data_from_ROM();
		transfer_data_lcd(disp_data);
	}
	Rom_CS_h;
}

ulong fontaddr=0;
void display_GB2312_string(uchar page,uchar column,uint8_t *text,uint8_t reverse,uchar under)
{
	uchar i= 0;
	while((text[i]>0x00))
	{
		if(((text[i]>=0xb0) &&(text[i]<=0xf7))&&(text[i+1]>=0xa1))
		{
			fontaddr = (text[i]- 0xb0)*94;
			fontaddr += (text[i+1]-0xa1)+846;
			fontaddr = (ulong)(fontaddr*32);
			get_and_write_16x16(fontaddr,page,column,reverse, under);
			i+=2;
			column+=16;
		}
		else if(((text[i]>=0xa1) &&(text[i]<=0xa3))&&(text[i+1]>=0xa1))
		{
			fontaddr = (text[i]- 0xa1)*94;
			fontaddr += (text[i+1]-0xa1);
			fontaddr = (ulong)(fontaddr*32);
			get_and_write_16x16(fontaddr,page,column,reverse, under);
			i+=2;
			column+=16;
		}
		else if((text[i]>=0x20) &&(text[i]<=0x7e))
		{
			fontaddr = (text[i]- 0x20);
			fontaddr = (unsigned long)(fontaddr*16);
			fontaddr = (unsigned long)(fontaddr+0x3cf80);
			get_and_write_8x16(fontaddr,page,column,reverse,under);
			i+=1;
			column+=8;
		}
		else
		i++;
	}
}

void display_Signle_GB2312_string(uchar page,uchar column,uchar *text,uint8_t reverse,uchar under)
{
		if(((text[0]>=0xb0) &&(text[0]<=0xf7))&&(text[0+1]>=0xa1))
		{
			fontaddr = (text[0]- 0xb0)*94;
			fontaddr += (text[0+1]-0xa1)+846;
			fontaddr = (ulong)(fontaddr*32);
			get_and_write_16x16(fontaddr,page,column,reverse,under);
			//i+=2;
			column+=16;
		}
		else if(((text[0]>=0xa1) &&(text[0]<=0xa3))&&(text[0+1]>=0xa1))
		{
			fontaddr = (text[0]- 0xa1)*94;
			fontaddr += (text[0+1]-0xa1);
			fontaddr = (ulong)(fontaddr*32);
			get_and_write_16x16(fontaddr,page,column,reverse,under);
			//i+=2;
			column+=16;
		}
		else if((text[0]>=0x20) &&(text[0]<=0x7e))
		{
			fontaddr = (text[0]- 0x20);
			fontaddr = (unsigned long)(fontaddr*16);
			fontaddr = (unsigned long)(fontaddr+0x3cf80);
			get_and_write_8x16(fontaddr,page,column,reverse,under);
			//i+=1;
			column+=8;
		}
}



void display_string_5x8(uchar page,uchar column,uchar *text)
{
	unsigned char i= 0;
	while((text[i]>0x00))
	{
		if((text[i]>=0x20) &&(text[i]<=0x7e))
		{
			fontaddr = (text[i]- 0x20);
			fontaddr = (unsigned long)(fontaddr*8);
			fontaddr = (unsigned long)(fontaddr+0x3bfc0);
			get_and_write_5x8(fontaddr,page,column);
			i+=1;
			column+=6;
		}
		else
		i++;
	}
}

/*写数据到LCD模块*/
void transfer_data(int data1)
{
	char i;
	lcd_cs1_l;
	lcd_rs_h;
	for(i=0;i<8;i++)
	{
		lcd_sclk_l;
		if(data1&0x80) 
		{
			lcd_sid_h;
		}
		else 
		{
			lcd_sid_l;
		}
		lcd_sclk_h;
		data1<<=1;
	}
	lcd_cs1_h;
}



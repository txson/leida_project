#include "lcd12864.h"




/**
 * @Date: 2022-11-23 21:15:26
 * @LastEditors: herod
 * @param {int} n_ms
 * @Description:  ����ʱ
 */
void delay(int n_ms) //��ʱ
{
	int j,k;
	for(j=0;j<n_ms;j++)
	for(k=0;k<990;k++);
}

/**
 * @Date: 2022-11-23 21:14:22
 * @LastEditors: herod
 * @param {int} data1	��lcdģ��д���ָ��
 * @Description: 
 */
void transfer_command_lcd(int data1) //дָ�LCD   ʹ�õ�ģ��SPI
{
	char i;
	lcd_cs1_l;				//Ƭѡ����
	lcd_rs_l;				//rs����
	for(i=0;i<8;i++)
	{
		lcd_sclk_l;			//ʱ������
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
 * @Description: ��lcdд������
 */
void transfer_data_lcd(int data1) //д���ݵ�LCD
{
	char i;
	lcd_cs1_l;
	lcd_rs_h;				//RS����
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
 * @Description: ��ʼ��lcd
 */
void initial_lcd() //LCD��ʼ��
{
	lcd_reset_l; 
	delay(100);
	lcd_reset_h; 
	delay(100);
	transfer_command_lcd(0xe2);    /*��λ*/
	delay(5);
	transfer_command_lcd(0x2c);    /*��ѹ����1*/
	delay(50);
	transfer_command_lcd(0x2e);    /*��ѹ����2*/
	delay(50);
	transfer_command_lcd(0x2f);    /*��ѹ����3*/
	delay(5);
	transfer_command_lcd(0x23);     /*�ֵ��Աȶȣ������÷�Χ0x20~0x27*/
	transfer_command_lcd(0x81);     /*΢���Աȶ�*/
	transfer_command_lcd(0x22);     /*0x1a,΢���Աȶȵ�ֵ,�����÷�Χ0x00~0x3f*/
	transfer_command_lcd(0xa2);     /*1/9ƫѹ��(bias)*/
	transfer_command_lcd(0xc8);     /*��ɨ��˳��:���ϵ���*/
	transfer_command_lcd(0xa0);     /*��ɨ��˳��:������*/
	transfer_command_lcd(0x40);     /*��ʼ��:��һ�п�ʼ*/
	transfer_command_lcd(0xb7);
	transfer_command_lcd(0xa6);     /*����ҳ��ɫ��ת*/
	
	transfer_command_lcd(0xaf);      /*����ʾ*/
	transfer_command_lcd(0xa4); 
}

/**
 * @Date: 2022-11-23 21:16:49
 * @LastEditors: herod
 * @param {uint} page	ҳ�� ÿ8��Ϊһ��ҳ��
 * @param {uint} column	��
 * @Description: ��lcd������Ҫ��ʾ��ַ
 */
void lcd_address(uint page,uint column)
{
	column=column-0x01;								/*��-1*/
	transfer_command_lcd(0xb0+page-1);              /*����ҳ��ַ��ÿҳ8�С�һ�������Ϊ64�б��ֳ�8ҳ������ƽ����˵�ĵ�һҳ����LCD�������ǵ�0ҳ
	����Ҫ��ȥ1*/
	transfer_command_lcd(0x10+(column>>4&0x0f));    /*�����е�ַ�ĸ�4λ*/
	transfer_command_lcd(column&0x0f);				/*�����е�ַ�ĵ�4λ*/
}



void clear_screen() //ȫ������
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

void send_command_to_ROM( uchar datu ) //��ָ��ֿ�
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

static uchar get_data_from_ROM( ) //���ֿ���ȡ���ֻ��ַ�
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

/*д���ݵ�LCDģ��*/
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



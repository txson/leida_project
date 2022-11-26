#include "view_mgr.h"
#include "MainMenu.h"
#include "stdlib.h"

extern UART_HandleTypeDef huart1;
extern uint8_t receive_buff[255];
extern uint8_t uart1_stat;
uint16_t  amplitude = 120;
//extern Menu BasicSetMenu

Menu WaveMenu = { 
	"波形界面\0",						//界面名
	0,0,0,0,2,							//默认显示0-3项，总共4项，当前选择0项，为显示界面
}; 

Menu MainMenu = { 
	"主界面\0",						//界面名
	0,0,0,0,2,						//默认显示0-3项，总共4项，当前选择0项，为显示界面
}; 

Menu ListMenu = { 
	"列表界面\0",						//界面名
	0,2,3,0,0,						//默认显示0-3项，总共4项，当前选择0项，为列表界面
}; 


Menu AdvancedSetting = { 
	"高级设置\0",
	0,3,4,0,0,						//默认显示0-3项，总共5项，当前选择0项，为列表界面
}; 

Menu BasicSetMenu = { 
	"设置\0",
	0,3,8,0,0,						//默认显示0-3项，总共8项，当前选择0项，
}; 

Menu ShowMenu = { 
	"显示\0",
	0,3,5,0,0,						//默认显示0-3项，总共5项，当前选择0项，为列表界面
}; 

Menu Service = { 
	"服务\0",
	0,3,5,0,0,						//默认显示0-3项，总共5项，当前选择0项，为列表界面
}; 

Menu Info = { 
	"信息\0",
	0,3,3,0,0,						//默认显示0-3项，总共3项，当前选择0项，为列表界面
}; 





uchar disp_cursor_16x40[11][64] = 
{
{0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x40,0x40,0x40,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xF0,0xFE,0x0F,0x01,0x00,0x00,0x00,0x00,0x01,0x07,0xFE,0xF0,0x00,0x00,
0x00,0x00,0x3F,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0x3F,0x00,0x00,
0x00,0x00,0x00,0x01,0x03,0x06,0x0C,0x08,0x08,0x08,0x06,0x03,0x01,0x00,0x00,0x00},/*"0",0*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x01,0x01,0x01,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x08,0x08,0x08,0x0C,0x0F,0x0F,0x0C,0x08,0x08,0x08,0x00,0x00,0x00},/*"1",1*/
{0x00,0x00,0x00,0x00,0x80,0x40,0x40,0x40,0x40,0x40,0xC0,0x80,0x80,0x00,0x00,0x00,
0x00,0x00,0x1E,0x19,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC1,0xFF,0x3E,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0x40,0x30,0x18,0x0C,0x06,0x03,0x01,0x00,0xC0,0x00,0x00,
0x00,0x00,0x0E,0x0D,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0E,0x03,0x00,0x00},/*"2",2*/
{0x00,0x00,0x00,0x80,0x80,0x40,0x40,0x40,0x40,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x80,0xC1,0x7F,0x3E,0x00,0x00,0x00,
0x00,0x00,0xC0,0xC0,0x00,0x00,0x01,0x01,0x01,0x03,0x02,0x06,0xFC,0xF0,0x00,0x00,
0x00,0x00,0x03,0x07,0x04,0x08,0x08,0x08,0x08,0x08,0x04,0x06,0x03,0x00,0x00,0x00},/*"3",3*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0x60,0x10,0x0C,0x03,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x30,0x2C,0x26,0x21,0x20,0x20,0x20,0x20,0xFF,0xFF,0x20,0x20,0x20,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x0F,0x0F,0x08,0x08,0x08,0x00,0x00},/*"4",4*/
{0x00,0x00,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,
0x00,0x00,0x00,0xFF,0x00,0x80,0x40,0x40,0x40,0x40,0xC0,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0xC0,0xC3,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFC,0x00,0x00,
0x00,0x00,0x03,0x04,0x04,0x08,0x08,0x08,0x08,0x08,0x04,0x07,0x03,0x00,0x00,0x00},/*"5",5*/
{0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x40,0x40,0x40,0x40,0x80,0x80,0x00,0x00,0x00,
0x00,0x00,0xE0,0xFC,0x07,0x81,0xC0,0x40,0x40,0x40,0xC0,0x83,0x03,0x00,0x00,0x00,
0x00,0x00,0x7F,0xFF,0x83,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFC,0x00,0x00,
0x00,0x00,0x00,0x01,0x07,0x06,0x0C,0x08,0x08,0x08,0x0C,0x06,0x03,0x00,0x00,0x00},/*"6",6*/
{0x00,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,
0x00,0x00,0x0E,0x03,0x00,0x00,0x00,0x00,0x00,0xE0,0x18,0x06,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFC,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"7",7*/
{0x00,0x00,0x00,0x00,0x80,0xC0,0x40,0x40,0x40,0x40,0xC0,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x3E,0x7F,0xF1,0xC0,0xC0,0x80,0x00,0x00,0x80,0x41,0x7F,0x1E,0x00,0x00,
0x00,0xF0,0xFC,0x0E,0x02,0x01,0x01,0x01,0x03,0x07,0x0E,0x1E,0xFC,0xF0,0x00,0x00,
0x00,0x01,0x03,0x06,0x04,0x08,0x08,0x08,0x08,0x08,0x04,0x06,0x03,0x01,0x00,0x00},/*"8",8*/
{0x00,0x00,0x00,0x80,0x80,0x40,0x40,0x40,0x40,0x40,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0xFC,0xFF,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFE,0xF8,0x00,0x00,
0x00,0x01,0x03,0x07,0x0C,0x08,0x08,0x08,0x08,0x04,0x06,0xE1,0x7F,0x1F,0x00,0x00,
0x00,0x00,0x07,0x07,0x08,0x08,0x08,0x08,0x0C,0x06,0x03,0x01,0x00,0x00,0x00,0x00},/*"9",9*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x06,0x0F,0x0F,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}/*".",10*/



};

uchar clear[80] = 
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


uchar baifenhao[8] = 	{0x00,0x66,0x16,0x68,0x66,0x00,0x00,0x00};/*"%",0*/

uchar triangle_sign[8] = {0x40,0x70,0x48,0x44,0x44,0x48,0x70,0x40};/*"△",0*/

uchar unit[4][8] = {
	{0x30,0x48,0x48,0x48,0x48,0x7E,0x40,0x00},/*"d",0*/
	{0x00,0x00,0x00,0x18,0x24,0x42,0x80,0x00},/*"(",1*/
	{0x08,0x78,0x08,0x08,0x70,0x08,0x78,0x00},/*"m",2*/
	{0x00,0x80,0x42,0x3C,0x00,0x00,0x00,0x00},/*")",3*/
};
uchar disp_cursor_16x8[11][8] = 
{
{0x00,0x3E,0x41,0x41,0x3E,0x00,0x00,0x00},/*"0",0*/
{0x00,0x42,0x7F,0x40,0x00,0x00,0x00,0x00},/*"1",1*/
{0x00,0x62,0x51,0x49,0x46,0x00,0x00,0x00},/*"2",2*/
{0x00,0x22,0x49,0x49,0x36,0x00,0x00,0x00},/*"3",3*/
{0x00,0x38,0x26,0x7F,0x20,0x00,0x00,0x00},/*"4",4*/
{0x00,0x4F,0x49,0x49,0x31,0x00,0x00,0x00},/*"5",5*/
{0x00,0x3E,0x49,0x49,0x32,0x00,0x00,0x00},/*"6",6*/
{0x00,0x03,0x71,0x09,0x07,0x00,0x00,0x00},/*"7",7*/
{0x00,0x36,0x49,0x49,0x36,0x00,0x00,0x00},/*"8",8*/
{0x00,0x26,0x49,0x49,0x3E,0x00,0x00,0x00},/*"9",9*/
{0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00},/*".",10*/

};

uint8_t  Progress_box[80]={
/*--  进度框  --*/
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF};

uint8_t  data_temp[80]={
/*进度条显示的临时变量*/
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF};

uchar  jindu[14] = {
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
};
uchar  thermometer[105]={
/*--  温度计图片显示点阵  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xF8,0xFC,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,
0xFC,0xFC,0xFC,0xF0,0x00,0x00,0x00,0x1C,0x14,0x1C,0x00,0xF0,0xF0,0x18,0x08,0x08,
0x08,0x10,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xFF,0x7F,0x3F,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x3F,0x7F,0xFF,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x01,0x03,
0x06,0x04,0x04,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x1F,0x3F,0x3F,0x70,0xE0,0xE0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0x60,0x30,0x3F,0x3F,0x1F,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};




  

void jindutiao(uchar page,uchar column,uchar *dp)
{
	uchar i,j,*data_temp;
	data_temp=dp;
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<16;i++)
		{	
//			if(reverse==1)
//			{
//				transfer_data_lcd(~*data_temp);	/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
//			}
//			else
//			{
				transfer_data_lcd(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
//			}
			data_temp++;
		}
	}
}


void line(uint16_t line_num,uint16_t lie,uint16_t line_numlen,uint16_t lielen)
{
	uint8_t i = 0;
	uint16_t j = 0;
		//uint8_t i = 0, j = 0;
	uint8_t remainder = 0;   //余数部分
	uint8_t integer = 0;	 //整数部分
	
	integer = line_num / 8;
	remainder = line_num % 8;
	i = 1 << remainder;
	for(j = lie ; j < lielen + lie +1 ; j++)   //画第i行
	{
		jindutiao(integer + 1,j,&i);
	}
}


/*写指令到LCD模块*/
void transfer_command(int data1)   
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





void clear_jindutiao(uchar page,uchar column)
{
	uchar i = 0,l = 0;
		for(l=0;l<5;l++)
		{
			/*k是显示每一个页面的*/

			
			lcd_address(page+l,column);
			for (i=0;i<16;i++)
			{	

				transfer_data(0X00);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
			}
		}
}

void progress_bar_show(uchar page,uchar column,uchar *dp,uchar jindu)
{
    volatile uchar i = 0,j = 0,k = 0,l = 0,m = 0;   /*临时变量*/

	volatile uchar integer = 0,decimal = 0;
	volatile char jindu_to_line = jindu /2.5;  /*将百分比进行转化为进度条 100 / 40 = 2.5*/
	integer = jindu_to_line / 8;  /*整数部分按照page显示*/
	decimal = jindu_to_line % 8;  /*小数部分按照每一条显示*/

	/*将当前进度条数组进行初始化*/
	for(m = 0;m<80;m++)
	{
		data_temp[m] = Progress_box[m];
	}
	
	
		/*按照页面去初始化进度条*/
		for(l = 0;l<integer +1;l++)
		{
			if(l == (integer ))
			{
				for(k = 0 ; k < decimal ; k++)
				{					
					for(j = (65 - l*16) ; j < (14 + 65 - l*16) ; j++)
					{
						data_temp[j] |=  0x80 >> k;  /*当前page按条显示*/
					}					
				}
			}
			else
			{
				for(j = (65 - l*16) ; j < (14 + 65 - l*16) ; j++)
					{
						data_temp[j] =  0XFF;      /*按page显示*/
					}
			}
		}
		for(l=0;l<5;l++)
		{
			/*k是显示每一个页面的*/

			
			lcd_address(page+l,column);
			for (i=0;i<16;i++)
			{	

				transfer_data(data_temp[l*16+i]);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				//data_temp;
			}
		}
	
}


void disp_blink_16x40_clean(uchar page,uchar column,uchar *dp)
{
	uchar i,j,*data_temp;
	
		data_temp=dp;
		for(j=0;j<5;j++)
		{
			lcd_address(page+j,column);
			for (i=0;i<16 * 5;i++)
			{	

				transfer_data(0x00);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				//data_temp++;
			}
		}
	
}

void disp_blink_16x40(uchar page,uchar column,uchar *dp)
{
	uchar i,j,*data_temp;
	
		data_temp=dp;
		for(j=0;j<4;j++)
		{
			lcd_address(page+j,column);
			for (i=0;i<16;i++)
			{	

				transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				data_temp++;
			}
		}
	
}

/*
lcd显示 参数1:显示的页面
		   
*/
void display_lcd(uchar page,uchar column,uchar width,uchar height,uchar *dp,uchar ctrl_flag)
{
	uchar i,j,*data_temp;
	uchar tmp_width = width;
	uchar tmp_height = height / 8;
		data_temp=dp;
		/*高度显示*/
		for(j=0;j<tmp_height;j++)
		{
			lcd_address(page+j,column);
			/*宽度显示*/
			for (i=0;i<tmp_width;i++)
			{	
				if(ctrl_flag & 0x00)				/*正常模式*/
				{
					transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				}
				else if(ctrl_flag & 0x01)			/*清0模式*/
				{
					transfer_data(0x00);
				}
				data_temp++;
			}
		}
	
}


void disp_blink_16x8(uchar page,uchar column,uchar *dp)
{
	uchar i,j,*data_temp;
	
		data_temp=dp;
		for(j=0;j<1;j++)
		{
			lcd_address(page+j,column);
			for (i=0;i<8;i++)
			{	

				transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				data_temp++;
			}
		}
	
}

void clear_16x8(uchar page,uchar column)
{
	uchar i,j;
	for(j=0;j<1;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<16;i++)
		{	

			transfer_data(0x00);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
		}
	}
	
}


/*温度计显示使用*/
void disp_blink_35x24(uchar page,uchar column,uchar *dp)
{
	uchar i,j,*data_temp;
	
		data_temp=dp;
		for(j=0;j<3;j++)
		{
			lcd_address(page+j,column);
			for (i=0;i<35;i++)
			{	

				transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				data_temp++;
			}
		}
}

/*纵坐标显示*/

void lcd_disp_blink(uchar page,uchar column,uchar *dp,uint16_t row_num,uint16_t col_num)
{
	uchar i = 0;
	uchar j = 0;
	uchar *data_temp = NULL;	
	data_temp=dp;
	lcd_address(page,column);
	for(j=0;j<(row_num/4);j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<col_num;i++)
		{	

			transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
			data_temp++;
		}
	}

}

void disp_blink_8x120(uchar page,uchar column,uchar *dp)
{
	uchar i,j,*data_temp;
	
		data_temp=dp;
		for(j=0;j<1;j++)
		{
			lcd_address(page+j,column);
			for (i=0;i<121;i++)
			{	

				transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				data_temp++;
			}
		}
}

extern volatile int cnt;
extern volatile int start_cnt;
extern uint32_t cnt_start;
extern uint32_t cnt_end;
extern ADC_HandleTypeDef hadc1;
extern __IO uint16_t Current_Temperature; 


extern MenuMgr MenuManager;

/*主界面显示*/
void main_menu_func(uint8_t key_value)
{
	switch(key_value)
	{
		case OK_KEY:		/*OK键进入列表界面*/
		{
			MenuManager.cur_menu = MenuManager.cur_menu->subMenus[0];	/*切换到子界面*/
			MenuManager.menu_status  = 1;								/*设置状态  表示状态为刚切换界面的状态*/
			break;
		}
		case UP_KEY:
		{
			break;
		}
		case DOWN_KEY:
		{
			MenuManager.cur_menu->selected = 0;							/*初始化选中标记*/
			MenuManager.menu_status  = 1;								/*设置状态为刚切换状态*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;		/*切换到波形界面*/
			break;
		}
		case BACK_KEY:
		{
			MenuManager.cur_menu->selected = 0;		//这里有两个数据界面
			break;
		}
		default://按键A（确认按键）
		{
			cnt = HAL_GetTick();
			//MenuManager.cur_menu->func();	/*默认选择*/
			if(MenuManager.menu_status == 1)	/*第一次切换进来进行初始化*/
			{
				main_page_init();
				MenuManager.cur_menu->selected = 1;
				MenuManager.menu_status = 0;
			}
			else if (!((cnt - cnt_start) %5000))		/*1s刷新一次温度*/
			{
					main_page_init();

			////			/*更新传感器的值*/
			////			update_sensor_val(current_sr_val,current_len);
			////			
			////			/*更新进度显示*/
			////			update_sensor_progress(current_sr_val,current_len);
			}
			else if (!(cnt%1000))		/*1s刷新一次温度*/
			{
				//HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&ADC_ConvertedValue,sizeof(ADC_ConvertedValue));  
				/*更新温度显示*/
				//Current_Temperature = (0x6EE - ((uint32_t)  hadc1.Instance->DR)) / 0x05 + 25;
				//update_sensor_temp(33);
			}
			else
			{
				start_cnt = HAL_GetTick();
			}
			/*串口进程*/
//			uart_process_data();
			
			
			break;
		}
	}
}



uint8_t Ordinate[8] = 
{
0xff,0xff,0xff,0xff
};/*"未命名文件",0*/
uint8_t Abscissa[121] = 
{0xff,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x03,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x03,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x03,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xff};

uint8_t Abscissa_under[121] = 
{0xff,0x81,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xc0,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xc0,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xc0,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x81,0xff};

uint8_t val[4] = 
{
	0x80,0x00,0x00,0x00
};

void point(uchar page,uchar column,uchar *dp)
{
	uchar i,j,*data_temp;
	
		data_temp=dp;
		for(j=0;j<6;j++)
		{
			lcd_address(page+j,column);
			for (i=0;i<1;i++)
			{	

				transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				data_temp++;
			}
		}
}

char boxin_dm[8] = "0.00";
char boxin_Adb[8] = "0.00";
/*波形显示*/
extern volatile float g_new_dis;
extern volatile int g_max_db;
#define Y_MAX_VAL 	128//(0x8FF)		/*Y轴显示最大数值32*/
#define Y_POINT_MAX  48				/*Y轴最大48个点位*/
 char test_buf[1024] =
 {
 	0x0,0x0,0x00,0x00,0x50,0x00,0x01,0x00,0x02,0x00,0x17,0x00,0x04,0x00,0x05,0x00,0x1d,0x00,0x1c,0x00,0x1b,0x00
 	,0x1a,0x00,0x19,0x00,0x18,0x00,0x17,0x00,0x18,0x00,0x19,0x00,0x20,0x00,0x21,0x00,0x22,0x00,0x23,0x00,0x24,0x00,0x25,0x00,0x26,0x00,0x27,0x00,0x28,0x00
 	,0x29,0x00,0x30,0x00,0x31,0x00,0x32,0x00,0x32,0x00,0x32,0x00,0x32,0x00,0x32,0x00,0x32,0x00,0x32,0x00,0x32,0x00,0x32,0x00,0x32,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00
 	,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00
 	,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x50,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00
 	,0x1f,0x00,0x1f,0x00,0x50,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x50,0x00,0x51,0x00,0x52,0x00,0x59,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00
 	,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00
 	,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00
 	,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x1f,0x00,0x2f,0x00,0x00,0x00
 };

 static uchar jiantou[7] = {0x10,0x30,0x7F,0xFF,0x7F,0x30,0x10};
 static uchar daosanjiao_bai[7] = {0x0F,0x19,0x31,0x61,0x31,0x19,0x0F};
 static uchar daosanjiao_hei[7] = {0x0F,0x1F,0x3F,0x7F,0x3F,0x1F,0x0F};

void show_boxin_page(char* val_data,int len)
{
	volatile uint8_t show_x = 0;	/*用于遍历横坐标，并将每一个横坐标的数值显示*/
	uint8_t x_start = 6;			/*x轴开始的坐标*/
	uchar show_led_val[6] = {0};	/*用于记录每个横坐标显示的数据*/

	short  previous_data = 0;		/*之前的数据*/
	short  current_data = 0;		/*当前的数据*/

	volatile int show_cy_val = 0;	/*用于记录当前坐标需要显示的y轴点位  val_data[(current x)] y*/
	volatile int show_py_val = 0;	/*用于记录前一个x轴坐标的数据val_data[(current x) -1]*/
	volatile int tmp_y_val = 0;		/*临时变量 show_py_val 逼近 show_cy_val 画线*/



	/*表头显示*/
	display_string_5x8(1,2,"d(m):");
	display_string_5x8(1,30,boxin_dm);
	display_string_5x8(1,60,"A(dB):");
	display_string_5x8(1,96,boxin_Adb);

	/*表尾显示*/
	display_string_5x8(8,1,"0");
	display_string_5x8(8,112,"20");
	
	/*	1.竖坐标数值显示			*/
	lcd_disp_blink(3,x_start,Ordinate,32,1);
	lcd_disp_blink(3,120 + x_start,Ordinate,32,1);
	
	/*	2.横坐标数值显示			*/
	disp_blink_8x120(7,x_start,Abscissa_under);
	disp_blink_8x120(2,x_start,Abscissa);
	/*	3.显示↓						*/

	/*	4.显示数值					*/
	if(val_data != NULL)
	{
		for(show_x = 1;show_x <= 119 ; show_x++)
		{
			if(show_x == 1)
			{
				memset(show_led_val,0x01,6);
			}
			else
			{
				memset(show_led_val,0x00,6);
			}
			if(show_x % 30 == 0 )
			{
					memset(show_led_val,0xaa,6);
			}
			memcpy((void*)&previous_data,(void*)&val_data[(show_x - 1) * 2],2);		/*上一次的数据*/
			show_py_val = Y_POINT_MAX - (previous_data * Y_POINT_MAX / (g_max_db / 0.9f)) ;
			
			memcpy((void*)&current_data,(void*)&val_data[(show_x) * 2],2);			/*这一次的数据*/
			show_cy_val = Y_POINT_MAX - (current_data * Y_POINT_MAX / (g_max_db / 0.9f)) ;//  -  ( (tmp_i) * Y_POINT_MAX / (g_max_db / 0.9f) ) ;
			
			tmp_y_val = show_py_val;		/*记录前一个x轴的数据*/
			while(1){

				for(volatile uint8_t page = 0 ; page < 6 ; page++)		/*用于记录y轴上需要画的点*/
				{
					if(tmp_y_val / 8 == page)
					{
						show_led_val[page] |= 1 << (tmp_y_val % 8);
					}
				}
				if(tmp_y_val == show_cy_val)
				{
					break;
				}
				else if(tmp_y_val < show_cy_val )		/*比当前数据小  正方向逼近*/
				{
					tmp_y_val++;
				}
				else									/*比当前数据大  反方向逼近*/
				{
					tmp_y_val--;
				}
			}
			show_led_val[0] |= 0x01;
			show_led_val[5] |= 0x80;
			point(2 ,x_start + show_x,show_led_val);
			
		}
	}
}

/*波形显示函数*/
void wave_show(uint8_t key_value)
{
	uint32_t cnt = 0;
	switch(key_value)
	{
		case OK_KEY:
		{
			break;
		}
		case UP_KEY:
		{
			break;
		}
		case DOWN_KEY:
		{
			MenuManager.cur_menu = MenuManager.cur_menu->parent;
			MenuManager.menu_status  = 1;
			break;
		}
		case BACK_KEY:
		{
			break;
		}
		default://按键A（确认按键）
		{
			cnt = HAL_GetTick();
			if (MenuManager.menu_status == 1)		/*第一次切换带页面进行一次刷新*/
			{
				clear_screen(); 
				show_boxin_page(test_buf,sizeof(test_buf));
				MenuManager.menu_status = 0;
				
			}
			else if(!((cnt) %5000))					//5s中刷新一次屏幕
			{
				clear_screen(); 
				show_boxin_page(test_buf,sizeof(test_buf));
			}
				
			break;
		}
	}
	
}


void MainMeunuInit(void)
{
	MainMenu.func = main_menu_func;
	MainMenu.parent = &WaveMenu;			/*主界面的夫界面是波形界面*/
	MainMenu.subMenus[0] = &ListMenu;		/*主界面的子界面为列表界面*/
	
	WaveMenu.parent = &MainMenu;			/*波形界面父界面为主界面*/
	WaveMenu.func = wave_show;
	
	
	/*主界面初始化*/
	ListMenu.subMenus[0] = &BasicSetMenu;
	ListMenu.subMenus[1] = &ShowMenu;
	ListMenu.subMenus[2] = &AdvancedSetting;
//	ListMenu.subMenus[3] = &Service;
//	ListMenu.subMenus[4] = &Info;
	ListMenu.parent = &MainMenu;			/*列表界面上级目录为主界面*/
	ListMenu.func = ListMenuFunc;
	


	
	
	MenuManager.cur_menu = &MainMenu;
	MenuManager.DataSelectionStatus = 0;
}


/*主界面显示*/
void ListMenuFunc(uint8_t key_value)
{
		switch(key_value)
		{
			case OK_KEY://按键A（确认按键）
			{
				clear_screen(); 
				if( MenuManager.cur_menu->subMenus[MenuManager.cur_menu->selected] != NULL)
				{
					MenuManager.cur_menu = MenuManager.cur_menu->subMenus[MenuManager.cur_menu->selected];
				}
				displaymenu();
				break;
			}
			case UP_KEY://按键B（上一行菜单）
			{
				if(MenuManager.cur_menu->selected == 0)
				{
					/*当前选项已经为第一项 返回不进行处理*/
					break;
				}
				else
				{
					clear_screen(); 
					if(MenuManager.cur_menu->selected != 0)
					{
						/*列表选项上翻*/
						MenuManager.cur_menu->selected--;
					}
					if(MenuManager.cur_menu->selected < MenuManager.cur_menu->range_from)
					{
						/*已经翻到当前页面第一项 则更新页面显示的选项*/
						MenuManager.cur_menu->range_from = MenuManager.cur_menu->selected;
						MenuManager.cur_menu->range_to = MenuManager.cur_menu->range_from+3;
					}

					displaymenu();
				}
				break;
			}
			case DOWN_KEY://按键C（下一行菜单 ）
			{
				if(MenuManager.cur_menu->selected == MenuManager.cur_menu->itemCount-1)
				{
					break;
				}
				clear_screen(); 
				if(MenuManager.cur_menu->selected <= MenuManager.cur_menu->itemCount)
				{
					MenuManager.cur_menu->selected++;
				}
				if(MenuManager.cur_menu->selected > MenuManager.cur_menu->range_to)
				{
					MenuManager.cur_menu->range_to = MenuManager.cur_menu->selected;
					MenuManager.cur_menu->range_from = MenuManager.cur_menu->range_to-3;
				}
				displaymenu();
				break;
			}	
			case BACK_KEY://按键D（返回）
			{
				if(MenuManager.cur_menu->parent != NULL)
				{
					MenuManager.cur_menu = MenuManager.cur_menu->parent;
				}
				MenuManager.menu_status = 1;
				break;
			}
			default:   //界面刷新
			{
				//displaymenu(MenuManager.cur_menu->selected);
			//闪烁 ，根据select
				

			//距离更新
				if(MenuManager.menu_status  == 1)	//第一次进入页面  进行刷新
				{
					clear_screen(); 
					displaymenu();
					MenuManager.menu_status  = 0;
				}
				break;
			}
		}
}
float g_test_val = 10.2;
char current_sr_val[128] = "00.00";
int current_len = 4;
uint8_t time_out_cnt = 0;
/*界面初始化*/
void main_page_init(void)
{
	clear_screen(); 
	update_sensor_temp(33);
	
	/*温度计图形显示*/
	disp_blink_35x24(6,0,thermometer);

	/*进度条单位显示*/
	disp_blink_16x8(1,24,unit[0]);
	disp_blink_16x8(1,24 + 1*8,unit[1]);
	disp_blink_16x8(1,24 + 2*8,unit[2]);
	disp_blink_16x8(1,24 +  3*8,unit[3]);

	/*温度计错误码显示*/
	time_out_cnt++;
	if(time_out_cnt > 5)
	{
		display_GB2312_string(7,58,"Sensor E1",0,0);
	}
	else
	{
		display_GB2312_string(7,58,"Sensor OK",0,0);
	}

	/*显示三角形标志*/
	clear_16x8(1,64);
	disp_blink_16x8(1,70,triangle_sign);

	/*显示百分号*/
	disp_blink_16x8(1,120,baifenhao);
	
	/*增加一步高低位调整的运算*/
	update_sensor_val(current_sr_val,current_len);
	
	/*更新进度显示*/
	update_sensor_progress(current_sr_val,current_len);
}



/*字符串转浮点数*/
float charTofloat( char *str) {
	uint16_t star_cnt = 0,cur_cnt = 0;
	const char*p = str;
	float i = 0;
	float j = 0;
	char flag = 1;
	if(*p == '-')
	{
		
		++p;
	}
	star_cnt = HAL_GetTick();
	while(*p)
	{
		cur_cnt = HAL_GetTick();
		if((cur_cnt - star_cnt) > 500 )   /*超时退出*/
		{
			return 0;
		}
		if(*p == '.')
		{
			flag = 0;
			++p;
			continue;
		}
		if(flag)
		{
			if(*p >= '0' && *p <= '9')
			{
				i = i * 10 + ((*p) - '0');
			}
			else
			{
				break;
			}
		}
		else
		{
			if(*p >= '0' && *p <= '9')
			{
				i += ((*p) - '0') * j;
				j = j * 0.1;
			}
			else
			{
				break;
			}
		}
		++p;
	}
	if(*str == '-')
	{
		return -i;
	}
	return i;
}

/*浮点数和整数转字符串*/
void FToStr1(float fl , char *str, uint8_t d)  // fl:浮点数    d:小数位数
{
    int     integer = 0;     //整数部分
    float   decimal  = 0;    //小数部分
    int     temp;
	uint16_t star_cnt = 0,cur_cnt = 0;
    uint8_t i, n;
    //整数部分
    integer = (int)(fl);
    temp = integer;
    n = 0;
	star_cnt = HAL_GetTick();
    do
    {
        n++;
        temp = (int)(temp / 10);  //计算有几位整数位 n
		cur_cnt = HAL_GetTick();
		if((cur_cnt - star_cnt) > 500 )   /*超时退出*/
		{
			return;
		}
    }
    while(temp != 0);
 
    temp = integer;
    for( i = 0; i < n ; i++)
    {
        *(str + n - 1 - i) = (uint8_t)(temp % 10) + '0'; //此处跳出
        temp = (int)(temp / 10);
    }
    if( d == 0 )
    {
        *(str + i) = '\0';
    }
    else
    {
        *(str + i) = '.';
    }
    //小数部分
    decimal = fl - integer;
    for(i = n + 1; i < d + n + 1 ; i++)
    {
        decimal = decimal * 10;
        *(str + i) = (uint8_t)(decimal) + '0';
        decimal = decimal - (uint8_t)(decimal);
    }
    *(str + i) = '\0';
}

/*显示传感器的值*/
void update_sensor_val(char* buf,int len)
{
	volatile uint8_t tmp_i = 0;
	/*显示字符*/
	for(tmp_i = 0 ; tmp_i < 7 ; tmp_i++)
	{
		if(tmp_i > (len -1))   /*长度为6下标要-1*/
		{
			disp_blink_16x40(2,18 + tmp_i * 16,clear);
			//ontinue;
		}
		
		else if(buf[tmp_i] == '.')
		{
			/*显示传感器数值*/
			disp_blink_16x40(2,18 + tmp_i * 16,clear);
			disp_blink_16x40(2,18+ tmp_i * 16,disp_cursor_16x40[10]);
		}
		else 
		{
			/*显示传感器数值*/
			disp_blink_16x40(2,18 + tmp_i * 16,clear);
			disp_blink_16x40(2,18+ tmp_i * 16,disp_cursor_16x40[buf[tmp_i] - '0']);
		}
	}

}

/*更新进度条和百分比显示
输入参数:out_data : 输入的百分比的值
		 len	  : 输入百分比的值的数据长度
*/
extern F_VAL HighlowAdjetMenu_Val[2];
void update_sensor_progress(char* data,int len)
{
	volatile uint8_t tmp_i = 0;
	float sensor_val = 0;
	float tmp_val = 0.0;
	uchar sensor_per_val = 0;
	char baifenbi[6] = {0};
	
	/*计算全量*/
	amplitude = HighlowAdjetMenu_Val[0].float_val - HighlowAdjetMenu_Val[1].float_val;
	if(amplitude > 0 )
	{
		if(atof(data) < HighlowAdjetMenu_Val[1].float_val)			/*如果小于高位调整*/
		{
			sensor_val = 0;
		}
		else if(atof(data) > HighlowAdjetMenu_Val[0].float_val)	/*如果大于低位调整,传感器值为低位调整的值*/
		{
			sensor_val = amplitude;
		}
		else
		{
			sensor_val = atof(data);//传感器值为传入值
		}
		tmp_val = ((sensor_val * 100) / (amplitude / 0.9f));

		sensor_per_val = ((sensor_val * 100) / (amplitude / 0.9f)) ;
		clear_jindutiao(1,1);

//		/*进度条显示*/
		progress_bar_show(1, 1,Progress_box,sensor_per_val);
//		
		memset(baifenbi,0,6);
		 snprintf(baifenbi,6,"%.2f",100.1); 
		//FToStr1(((sensor_val* 100) / (amplitude / 0.9f)) ,baifenbi,4);
		
		
		for(tmp_i = 0 ; tmp_i < strlen(baifenbi) ; tmp_i++)
		{

			clear_16x8(1,80 + tmp_i * 8);
			
			if(baifenbi[tmp_i] == '.')
			{
				if(tmp_i == 3)
				{
					continue;
				}
				/*显示传感器数值*/
				disp_blink_16x8(1,80 + tmp_i * 8,clear);
				disp_blink_16x8(1,80+ tmp_i * 8,disp_cursor_16x8[10]);
			}
			else 
			{
				/*显示传感器数值*/
				disp_blink_16x8(1,80 + tmp_i * 8,clear);
				disp_blink_16x8(1,80 + tmp_i * 8,disp_cursor_16x8[baifenbi[tmp_i] - '0']);
			}
			
		}
		
		disp_blink_16x8(1,96+ (tmp_i * 8 ),baifenhao);
	}
}

extern ADC_HandleTypeDef hadc1;
/* 私有变量 ------------------------------------------------------------------*/
/* 用于保存转换计算后的电压值 */	 
__IO uint16_t Current_Temperature; 

// AD转换结果值
uint16_t ADC_ConvertedValue;


void update_sensor_temp(uint16_t Current_Temperature)
{
	
	char wendu[3] = {0};
	FToStr1(Current_Temperature,wendu,2);
	clear_16x8(7,35);
	disp_blink_16x8(7,35,disp_cursor_16x8[wendu[0] - '0']);
	clear_16x8(7,43);
	disp_blink_16x8(7,43,disp_cursor_16x8[wendu[1] - '0']);
}

void show_main_page(char* data,int len)
{    
  /*更新传感器的值*/
	update_sensor_val(data, len);		/*显示数值.*/
	
	/*更新进度显示*/
	update_sensor_progress(current_sr_val,current_len);
	
}




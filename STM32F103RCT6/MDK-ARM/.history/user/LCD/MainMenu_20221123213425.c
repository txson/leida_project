#include "view_mgr.h"
#include "MainMenu.h"
#include "stdlib.h"

extern UART_HandleTypeDef huart1;
extern uint8_t receive_buff[255];
extern uint8_t uart1_stat;
uint16_t  amplitude = 120;
//extern Menu BasicSetMenu

Menu WaveMenu = { 
	"���ν���\0",						//������
	0,0,0,0,2,							//Ĭ����ʾ0-3��ܹ�4���ǰѡ��0�Ϊ��ʾ����
}; 

Menu MainMenu = { 
	"������\0",						//������
	0,0,0,0,2,						//Ĭ����ʾ0-3��ܹ�4���ǰѡ��0�Ϊ��ʾ����
}; 

Menu ListMenu = { 
	"�б�����\0",						//������
	0,2,3,0,0,						//Ĭ����ʾ0-3��ܹ�4���ǰѡ��0�Ϊ�б�����
}; 


Menu AdvancedSetting = { 
	"�߼�����\0",
	0,3,4,0,0,						//Ĭ����ʾ0-3��ܹ�5���ǰѡ��0�Ϊ�б�����
}; 

Menu BasicSetMenu = { 
	"����\0",
	0,3,8,0,0,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 

Menu ShowMenu = { 
	"��ʾ\0",
	0,3,5,0,0,						//Ĭ����ʾ0-3��ܹ�5���ǰѡ��0�Ϊ�б�����
}; 

Menu Service = { 
	"����\0",
	0,3,5,0,0,						//Ĭ����ʾ0-3��ܹ�5���ǰѡ��0�Ϊ�б�����
}; 

Menu Info = { 
	"��Ϣ\0",
	0,3,3,0,0,						//Ĭ����ʾ0-3��ܹ�3���ǰѡ��0�Ϊ�б�����
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


uchar baifenhao[8] = 	{0x00,0x66,0x16,0x68,0x66,0x00,0x00,0x00};/*"%",0*/

uchar triangle_sign[8] = {0x40,0x70,0x48,0x44,0x44,0x48,0x70,0x40};/*"��",0*/

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
/*--  ���ȿ�  --*/
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF};

uint8_t  data_temp[80]={
/*��������ʾ����ʱ����*/
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF};

uchar  jindu[14] = {
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
};
uchar  thermometer[105]={
/*--  �¶ȼ�ͼƬ��ʾ����  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xF8,0xFC,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,
0xFC,0xFC,0xFC,0xF0,0x00,0x00,0x00,0x1C,0x14,0x1C,0x00,0xF0,0xF0,0x18,0x08,0x08,
0x08,0x10,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xFF,0x7F,0x3F,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x3F,0x7F,0xFF,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x01,0x03,
0x06,0x04,0x04,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x1F,0x3F,0x3F,0x70,0xE0,0xE0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0x60,0x30,0x3F,0x3F,0x1F,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};



void line(uint16_t line_num,uint16_t lie,uint16_t line_numlen,uint16_t lielen)
{
	uint8_t i = 0;
	uint16_t j = 0;
		//uint8_t i = 0, j = 0;
	uint8_t remainder = 0;   //��������
	uint8_t integer = 0;	 //��������
	
	integer = line_num / 8;
	remainder = line_num % 8;
	i = 1 << remainder;
	for(j = lie ; j < lielen + lie +1 ; j++)   //����i��
	{
		jindutiao(integer + 1,j,&i);
	}
}


/*дָ�LCDģ��*/
void transfer_command(int data1)   
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

void progress_bar_show(uchar page,uchar column,uchar *dp,uchar jindu)
{
    volatile uchar i = 0,j = 0,k = 0,l = 0,m = 0;   /*��ʱ����*/

	volatile uchar integer = 0,decimal = 0;
	volatile char jindu_to_line = jindu /2.5;  /*���ٷֱȽ���ת��Ϊ������ 100 / 40 = 2.5*/
	integer = jindu_to_line / 8;  /*�������ְ���page��ʾ*/
	decimal = jindu_to_line % 8;  /*С�����ְ���ÿһ����ʾ*/

	/*����ǰ������������г�ʼ��*/
	for(m = 0;m<80;m++)
	{
		data_temp[m] = Progress_box[m];
	}
	
	
		/*����ҳ��ȥ��ʼ��������*/
		for(l = 0;l<integer +1;l++)
		{
			if(l == (integer ))
			{
				for(k = 0 ; k < decimal ; k++)
				{					
					for(j = (65 - l*16) ; j < (14 + 65 - l*16) ; j++)
					{
						data_temp[j] |=  0x80 >> k;  /*��ǰpage������ʾ*/
					}					
				}
			}
			else
			{
				for(j = (65 - l*16) ; j < (14 + 65 - l*16) ; j++)
					{
						data_temp[j] =  0XFF;      /*��page��ʾ*/
					}
			}
		}
		for(l=0;l<5;l++)
		{
			/*k����ʾÿһ��ҳ���*/

			
			lcd_address(page+l,column);
			for (i=0;i<16;i++)
			{	

				transfer_data(data_temp[l*16+i]);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
				//data_temp;
			}
		}
	
}

/*
lcd��ʾ ����1:��ʾ��ҳ��
*/


void display_clear(uchar page,uchar column,uint16_t row_num,uint16_t col_num)
{
	uchar i,j;
	for(j = 0;j < (row_num / 8);j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<col_num;i++)
		{	

			transfer_data(0x00);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
		}
	}
	
}


/*��������ʾ*/

void lcd_disp_blink(uchar page,uchar column,uchar *dp,uint16_t row_num,uint16_t col_num)
{
	uchar i = 0;
	uchar j = 0;
	uchar *data_temp = NULL;	
	data_temp=dp;
	lcd_address(page,column);
	for(j=0;j<(row_num/8);j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<col_num;i++)
		{	

			transfer_data(*data_temp);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
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
uint8_t time_out_cnt = 0;
/*��������ʾ*/
void main_menu_func(uint8_t key_value)
{
	switch(key_value)
	{
		case OK_KEY:		/*OK�������б�����*/
		{
			MenuManager.cur_menu = MenuManager.cur_menu->subMenus[0];	/*�л����ӽ���*/
			MenuManager.menu_status  = 1;								/*����״̬  ��ʾ״̬Ϊ���л������״̬*/
			break;
		}
		case UP_KEY:
		{
			break;
		}
		case DOWN_KEY:
		{
			MenuManager.cur_menu->selected = 0;							/*��ʼ��ѡ�б��*/
			MenuManager.menu_status  = 1;								/*����״̬Ϊ���л�״̬*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;		/*�л������ν���*/
			break;
		}
		case BACK_KEY:
		{
			MenuManager.cur_menu->selected = 0;		//�������������ݽ���
			break;
		}
		default://����A��ȷ�ϰ�����
		{
			
			if(MenuManager.menu_status == 1)	/*��һ���л��������г�ʼ��*/
			{
				time_out_cnt = 0;
				MenuManager.cur_menu->selected = 1;
				cnt = HAL_GetTick();
				main_page_init();
				MenuManager.menu_status = 0;
			}
			else if (!((cnt - cnt_start) % 1000))		/*1sˢ��һ���¶�*/
			{
					main_page_init();
			}
			else if (!(cnt%100000))		/*1sˢ��һ���¶�*/
			{
				
//					update_sensor_temp();
			}
			else
			{
				start_cnt = HAL_GetTick();
			}
			cnt_start = HAL_GetTick();
			break;
		}
	}
}



uint8_t Ordinate[8] = 
{
0xff,0xff,0xff,0xff
};/*"δ�����ļ�",0*/
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

				transfer_data(*data_temp);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
				data_temp++;
			}
		}
}

char boxin_dm[8] = "0.00";
char boxin_Adb[8] = "0.00";
/*������ʾ*/
extern volatile float g_new_dis;
extern volatile int g_max_db;
#define Y_MAX_VAL 	128//(0x8FF)		/*Y����ʾ�����ֵ32*/
#define Y_POINT_MAX  48				/*Y�����48����λ*/
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


void show_boxin_page(char* val_data,int len)
{
	volatile uint8_t show_x = 0;	/*���ڱ��������꣬����ÿһ�����������ֵ��ʾ*/
	uint8_t x_start = 6;			/*x�Ὺʼ������*/
	uchar show_led_val[6] = {0};	/*���ڼ�¼ÿ����������ʾ������*/

	short  previous_data = 0;		/*֮ǰ������*/
	short  current_data = 0;		/*��ǰ������*/

	volatile int show_cy_val = 0;	/*���ڼ�¼��ǰ������Ҫ��ʾ��y���λ  val_data[(current x)] y*/
	volatile int show_py_val = 0;	/*���ڼ�¼ǰһ��x�����������val_data[(current x) -1]*/
	volatile int tmp_y_val = 0;		/*��ʱ���� show_py_val �ƽ� show_cy_val ����*/



	/*��ͷ��ʾ*/
	display_string_5x8(1,2,(unsigned char *)"d(m):");
	display_string_5x8(1,30,(unsigned char *)boxin_dm);
	display_string_5x8(1,60,(unsigned char *)"A(dB):");
	display_string_5x8(1,96,(unsigned char *)boxin_Adb);

	/*��β��ʾ*/
	display_string_5x8(8,1,"0");
	display_string_5x8(8,112,"20");
	
	/*	1.��������ֵ��ʾ			*/
	lcd_disp_blink(3,x_start,Ordinate,64,1);
	lcd_disp_blink(3,120 + x_start,Ordinate,64,1);
	
	/*	2.��������ֵ��ʾ			*/
	lcd_disp_blink(7,x_start,Abscissa_under,8,121);
	lcd_disp_blink(2,x_start,Abscissa,8,121);
	/*	3.��ʾ��						*/

	/*	4.��ʾ��ֵ					*/
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
			memcpy((void*)&previous_data,(void*)&val_data[(show_x - 1) * 2],2);		/*��һ�ε�����*/
			show_py_val = Y_POINT_MAX - (previous_data * Y_POINT_MAX / (g_max_db / 0.9f)) ;
			
			memcpy((void*)&current_data,(void*)&val_data[(show_x) * 2],2);			/*��һ�ε�����*/
			show_cy_val = Y_POINT_MAX - (current_data * Y_POINT_MAX / (g_max_db / 0.9f)) ;//  -  ( (tmp_i) * Y_POINT_MAX / (g_max_db / 0.9f) ) ;
			
			tmp_y_val = show_py_val;		/*��¼ǰһ��x�������*/
			while(1){

				for(volatile uint8_t page = 0 ; page < 6 ; page++)		/*���ڼ�¼y������Ҫ���ĵ�*/
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
				else if(tmp_y_val < show_cy_val )		/*�ȵ�ǰ����С  ������ƽ�*/
				{
					tmp_y_val++;
				}
				else									/*�ȵ�ǰ���ݴ�  ������ƽ�*/
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

/*������ʾ����*/
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
		default://����A��ȷ�ϰ�����
		{
			cnt = HAL_GetTick();
			if (MenuManager.menu_status == 1)		/*��һ���л���ҳ�����һ��ˢ��*/
			{
				clear_screen(); 
				show_boxin_page(test_buf,sizeof(test_buf));
				MenuManager.menu_status = 0;
				
			}
			else if(!((cnt) %5000))					//5s��ˢ��һ����Ļ
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
	MainMenu.parent = &WaveMenu;			/*������ķ�����ǲ��ν���*/
	MainMenu.subMenus[0] = &ListMenu;		/*��������ӽ���Ϊ�б�����*/
	
	WaveMenu.parent = &MainMenu;			/*���ν��游����Ϊ������*/
	WaveMenu.func = wave_show;
	
	
	/*�������ʼ��*/
	ListMenu.subMenus[0] = &BasicSetMenu;
	ListMenu.subMenus[1] = &ShowMenu;
	ListMenu.subMenus[2] = &AdvancedSetting;
//	ListMenu.subMenus[3] = &Service;
//	ListMenu.subMenus[4] = &Info;
	ListMenu.parent = &MainMenu;			/*�б������ϼ�Ŀ¼Ϊ������*/
	ListMenu.func = ListMenuFunc;
	


	
	
	MenuManager.cur_menu = &MainMenu;
	MenuManager.DataSelectionStatus = 0;
}


/*��������ʾ*/
void ListMenuFunc(uint8_t key_value)
{
		switch(key_value)
		{
			case OK_KEY://����A��ȷ�ϰ�����
			{
				clear_screen(); 
				if( MenuManager.cur_menu->subMenus[MenuManager.cur_menu->selected] != NULL)
				{
					MenuManager.cur_menu = MenuManager.cur_menu->subMenus[MenuManager.cur_menu->selected];
				}
				displaymenu();
				break;
			}
			case UP_KEY://����B����һ�в˵���
			{
				if(MenuManager.cur_menu->selected == 0)
				{
					/*��ǰѡ���Ѿ�Ϊ��һ�� ���ز����д���*/
					break;
				}
				else
				{
					clear_screen(); 
					if(MenuManager.cur_menu->selected != 0)
					{
						/*�б�ѡ���Ϸ�*/
						MenuManager.cur_menu->selected--;
					}
					if(MenuManager.cur_menu->selected < MenuManager.cur_menu->range_from)
					{
						/*�Ѿ�������ǰҳ���һ�� �����ҳ����ʾ��ѡ��*/
						MenuManager.cur_menu->range_from = MenuManager.cur_menu->selected;
						MenuManager.cur_menu->range_to = MenuManager.cur_menu->range_from+3;
					}

					displaymenu();
				}
				break;
			}
			case DOWN_KEY://����C����һ�в˵� ��
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
			case BACK_KEY://����D�����أ�
			{
				if(MenuManager.cur_menu->parent != NULL)
				{
					MenuManager.cur_menu = MenuManager.cur_menu->parent;
				}
				MenuManager.menu_status = 1;
				break;
			}
			default:   //����ˢ��
			{
				//displaymenu(MenuManager.cur_menu->selected);
			//��˸ ������select
				

			//�������
				if(MenuManager.menu_status  == 1)	//��һ�ν���ҳ��  ����ˢ��
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

/*�����ʼ��*/
void main_page_init(void)
{
	clear_screen(); 
	
	
	/*�¶ȼ�ͼ����ʾ*/
	lcd_disp_blink(6,0,thermometer,24,35);

	update_sensor_tem();
	
	/*��������λ��ʾ*/
	lcd_disp_blink(1,24,unit[0],8,8);
	lcd_disp_blink(1,24 + 1*8,unit[1],8,8);
	lcd_disp_blink(1,24 + 2*8,unit[2],8,8);
	lcd_disp_blink(1,24 +  3*8,unit[3],8,8);

	/*�¶ȼƴ�������ʾ*/
	time_out_cnt++;
	if(time_out_cnt > 5)
	{
		display_GB2312_string(7,58,"Sensor E1",0,0);
	}
	else
	{
		display_GB2312_string(7,58,"Sensor OK",0,0);
	}	
	/*����һ���ߵ�λ����������*/
	update_sensor_val(current_sr_val,current_len);
	
	/*���½�����ʾ*/
	update_sensor_progress(current_sr_val,current_len);
}

/*��ʾ��������ֵ*/
void update_sensor_val(char* buf,int len)
{
	volatile uint8_t tmp_i = 0;
	/*��ʾ�ַ�*/
	for(tmp_i = 0 ; tmp_i < 7 ; tmp_i++)
	{
		if(tmp_i > (len -1))   /*����Ϊ6�±�Ҫ-1*/
		{
			display_clear(2,18 + tmp_i * 16,32,16);
		}
		
		else if(buf[tmp_i] == '.')
		{
			/*��ʾ��������ֵ*/
			display_clear(2,18 + tmp_i * 16,32,16);
			lcd_disp_blink(2,18+ tmp_i * 16,disp_cursor_16x40[10],32,16);
		}
		else 
		{
			/*��ʾ��������ֵ*/
			display_clear(2,18 + tmp_i * 16,32,16);
			lcd_disp_blink(2,18+ tmp_i * 16,disp_cursor_16x40[buf[tmp_i] - '0'],32,16);
		}
	}

}

/*���½������Ͱٷֱ���ʾ
�������:out_data : ����İٷֱȵ�ֵ
		 len	  : ����ٷֱȵ�ֵ�����ݳ���
*/
extern F_VAL HighlowAdjetMenu_Val[2];
uint8_t baifenbi_x = 80;
void update_sensor_progress(char* data,int len)
{
	volatile uint8_t tmp_i = 0;
	float sensor_val = 0;
	float tmp_val = 0.0;
	uchar sensor_per_val = 0;
	char baifenbi[6] = {0};
	
	/*����ȫ��*/
	amplitude = HighlowAdjetMenu_Val[0].float_val - HighlowAdjetMenu_Val[1].float_val;
	if(amplitude > 0 )
	{
		if(atof(data) < HighlowAdjetMenu_Val[1].float_val)			/*���С�ڸ�λ����*/
		{
			sensor_val = 0;
		}
		else if(atof(data) > HighlowAdjetMenu_Val[0].float_val)	/*������ڵ�λ����,������ֵΪ��λ������ֵ*/
		{
			sensor_val = amplitude;
		}
		else
		{
			sensor_val = atof(data);//������ֵΪ����ֵ
		}
		tmp_val = ((sensor_val * 100) / (amplitude / 0.9f));

		sensor_per_val = tmp_val;		
		display_clear(1,1,40,16);

		/*��������ʾ*/
		progress_bar_show(1, 1,Progress_box,sensor_per_val);
		memset(baifenbi,0,6);
		snprintf(baifenbi,6,"%.3f",tmp_val); 
		
		/*��ʾ�����α�־*/
		display_clear(1,64,8,8);
		lcd_disp_blink(1,baifenbi_x - 10,triangle_sign,8,8);
		
		for(tmp_i = 0 ; tmp_i < strlen(baifenbi) ; tmp_i++)
		{

			display_clear(1,baifenbi_x + tmp_i * 8,8,16);
			
			if(baifenbi[tmp_i] == '.')
			{
				/*��ʾС����*/
				display_clear(1,baifenbi_x + tmp_i * 8,8,8);
				lcd_disp_blink(1,baifenbi_x+ tmp_i * 8,disp_cursor_16x8[10],8,8);
			}
			else 
			{
				/*��ʾ����*/
				display_clear(1,baifenbi_x + tmp_i * 8,8,8);
				lcd_disp_blink(1,baifenbi_x + tmp_i * 8,disp_cursor_16x8[baifenbi[tmp_i] - '0'],8,8);
			}
			
		}
		lcd_disp_blink(1,baifenbi_x + (tmp_i * 8 ),baifenhao,8,8);	/*��ʾ�ٷֺ�*/
	}
}




extern ADC_HandleTypeDef hadc1;
static __IO uint16_t Current_Temperature; 

uint16_t Get_Adc_Average(uint8_t times)
{
    uint32_t temp_val=0;
    uint8_t t;
    for(t=0;t<times;t++)
    {
        temp_val += HAL_ADC_GetValue(&hadc1);
        HAL_Delay(5);
    }
    return temp_val/times;
}


void update_sensor_temp(void)
{
	char temp[3] = {0};
	uint32_t ADC_Value;
	uint32_t V_val;
	uint32_t tmp_val;
	
	ADC_Value = Get_Adc_Average(50);   //获取AD值
	tmp_val = 1.43 - (float)ADC_Value*(3.3/4096) / 0.0043 + 25;
	snprintf(temp,6,"%d",tmp_val); 											/*���¶�ֵת��Ϊ�ַ���*/
	display_clear(7,34,8,16);
	lcd_disp_blink(7,35,disp_cursor_16x8[temp[0] - '0'],8.,8);
	display_clear(7,41,8,16);
	lcd_disp_blink(7,43,disp_cursor_16x8[temp[1] - '0'],8,8);
}

void show_main_page(char* data,int len)
{    
  /*���´�������ֵ*/
	update_sensor_val(data, len);		/*��ʾ��ֵ.*/
	
	/*���½�����ʾ*/
	update_sensor_progress(current_sr_val,current_len);
	
}




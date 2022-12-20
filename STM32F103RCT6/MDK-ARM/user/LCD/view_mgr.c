#include "view_mgr.h"
#include "uart.h"
//#include "malloc.h"
extern UART_HandleTypeDef huart1;
extern uint8_t receive_buff[255];
extern uint8_t uart1_stat;

MenuMgr MenuManager;
/*�˵��ṹ��*/


/**
 * @Date: 2022-11-23 23:15:54
 * @LastEditors: herod
 * @Description: ͨ�����ͽ�����ʾ
 */
void displaymenu()
{
	uchar HighlowAdjustmentBuf[4] = {0};
	volatile uint16_t i = 0;
	//if(MenuManager.cur_menu->view_type == 0)		//�б����
	{	
		/*4��ѭ����ӡ�˵�*/
		for(i = 0;i<4;i++)
		{
			if(MenuManager.cur_menu->subMenus[i+MenuManager.cur_menu->range_from] == NULL)
			{
				break;
			}
			if(i+MenuManager.cur_menu->range_from == MenuManager.cur_menu->selected )
			{
				display_GB2312_string(i*2+1,16,"*",0,0);
				display_GB2312_string(i*2+1,16*2,(uchar*)(MenuManager.\
					cur_menu->subMenus[i+MenuManager.cur_menu->range_from]->menu_name),1,0);
			}
			else
			{
				display_GB2312_string(i*2+1,16*2,(uchar *)(MenuManager.\
					cur_menu->subMenus[i+MenuManager.cur_menu->range_from]->menu_name),0,0);
			}
		}
	}
}

/**
 * @Date: 2022-11-23 23:16:24
 * @LastEditors: herod
 * @param {Menu} *MainMenu
 * @param {uint8_t} key_value
 * @Description: ������
 */
void Fun(Menu *MainMenu,uint8_t key_value)
{
	//printf(MainMenu->menu_name);
	MainMenu->func(key_value);
}

/**
 * @Date: 2022-11-23 23:16:31
 * @LastEditors: herod
 * @Description: ���н����ʼ��
 */
void meunu_init(void)
{
	MainMeunuInit();		/*��������س�ʼ��*/
	BasicSetMenuInit();		/*�������ó�ʼ��*/
	ShowMenuInit();			/*��ʾ��س�ʼ��*/
	AdvSettMenuInit();		/*�߼����ý���*/
	
	main_page_init();		/*��ʼ����һ��ҳ����ʾ*/
	MenuManager.cur_menu->selected = 1;
}

uint8_t g_yorn_opt_sel = INIT_VAL;
int save_modification(uint8_t key_val)
{
	switch(key_val)
	{
		case UP_KEY:		/*�Ϸ���*/
		{
			if(g_yorn_opt_sel != 0)
			{
				g_yorn_opt_sel--;
			}
		}
		break;
		case DOWN_KEY:		/*�·���*/
		{
			g_yorn_opt_sel++;
			if(g_yorn_opt_sel > MAX_SEL)
			{
				g_yorn_opt_sel = MAX_SEL;
			}
		}
		break;
		case BACK_KEY:		/*���ؼ�*/
		{
			MenuManager.cur_menu->view_type = FUC;
			return g_yorn_opt_sel;
		}
		break;
		case OK_KEY:		/*ȷ�ϼ�*/
		{
			if(g_yorn_opt_sel == SEL_YES)
			{
				MenuManager.menu_status = SAVE_DATA;
			}
			MenuManager.cur_menu->view_type = FUC;
			g_yorn_opt_sel = INIT_VAL;
		}
		break;
		default:
		{
			if(g_yorn_opt_sel == INIT_VAL)
			{
				clear_screen();
				g_yorn_opt_sel = SEL_NO;
			}
			display_GB2312_string(1,8,"�Ƿ�ȷ���޸�",0,0);
			if(g_yorn_opt_sel == SEL_YES)
			{
				display_GB2312_string(3,32,"��",1,0);
				display_GB2312_string(3,64,"��",0,0);
			}
			else if(g_yorn_opt_sel == SEL_NO)
			{
				display_GB2312_string(3,32,"��",0,0);
				display_GB2312_string(3,64,"��",1,0);
			}
		}
		break;
	}
}
/**
 * @Date: 2022-11-23 23:16:44
 * @LastEditors: herod
 * @Description: ������ѭ��
 */
void menu_looper(void)
{	
	uint8_t Key_val = 0;
	displaymenu();   /*��ʾ��ǰ����*/
	while(1)
	{
		Key_val = KEY_Scan(0);								/*��ȡ�����¼�*/
		if(MenuManager.cur_menu->view_type == SAVE_OR_NO)
		{
			save_modification(Key_val);
		}
		else
		{
			Fun(MenuManager.cur_menu,Key_val);		/*���н��溯��*/
		}
		uart_process_data();									/*��������ҵ��*/
	}
}






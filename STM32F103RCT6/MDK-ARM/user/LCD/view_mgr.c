#include "view_mgr.h"
#include "uart.h"
//#include "malloc.h"
extern UART_HandleTypeDef huart1;
extern uint8_t receive_buff[255];
extern uint8_t uart1_stat;

MenuMgr MenuManager;
/*菜单结构体*/


/**
 * @Date: 2022-11-23 23:15:54
 * @LastEditors: herod
 * @Description: 通用类型界面显示
 */
void displaymenu()
{
	uchar HighlowAdjustmentBuf[4] = {0};
	volatile uint16_t i = 0;
	//if(MenuManager.cur_menu->view_type == 0)		//列表界面
	{	
		/*4次循环打印菜单*/
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
 * @Description: 任务函数
 */
void Fun(Menu *MainMenu,uint8_t key_value)
{
	//printf(MainMenu->menu_name);
	MainMenu->func(key_value);
}

/**
 * @Date: 2022-11-23 23:16:31
 * @LastEditors: herod
 * @Description: 所有界面初始化
 */
void meunu_init(void)
{
	MainMeunuInit();		/*主界面相关初始化*/
	BasicSetMenuInit();		/*基本设置初始化*/
	ShowMenuInit();			/*显示相关初始化*/
	AdvSettMenuInit();		/*高级设置界面*/
	
	main_page_init();		/*初始化第一个页面显示*/
	MenuManager.cur_menu->selected = 1;
}

uint8_t g_yorn_opt_sel = INIT_VAL;
int save_modification(uint8_t key_val)
{
	switch(key_val)
	{
		case UP_KEY:		/*上翻键*/
		{
			if(g_yorn_opt_sel != 0)
			{
				g_yorn_opt_sel--;
			}
		}
		break;
		case DOWN_KEY:		/*下翻键*/
		{
			g_yorn_opt_sel++;
			if(g_yorn_opt_sel > MAX_SEL)
			{
				g_yorn_opt_sel = MAX_SEL;
			}
		}
		break;
		case BACK_KEY:		/*返回键*/
		{
			MenuManager.cur_menu->view_type = FUC;
			return g_yorn_opt_sel;
		}
		break;
		case OK_KEY:		/*确认键*/
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
			display_GB2312_string(1,8,"是否确认修改",0,0);
			if(g_yorn_opt_sel == SEL_YES)
			{
				display_GB2312_string(3,32,"是",1,0);
				display_GB2312_string(3,64,"否",0,0);
			}
			else if(g_yorn_opt_sel == SEL_NO)
			{
				display_GB2312_string(3,32,"是",0,0);
				display_GB2312_string(3,64,"否",1,0);
			}
		}
		break;
	}
}
/**
 * @Date: 2022-11-23 23:16:44
 * @LastEditors: herod
 * @Description: 主任务循环
 */
void menu_looper(void)
{	
	uint8_t Key_val = 0;
	displaymenu();   /*显示当前界面*/
	while(1)
	{
		Key_val = KEY_Scan(0);								/*获取按键事件*/
		if(MenuManager.cur_menu->view_type == SAVE_OR_NO)
		{
			save_modification(Key_val);
		}
		else
		{
			Fun(MenuManager.cur_menu,Key_val);		/*运行界面函数*/
		}
		uart_process_data();									/*串口数据业务*/
	}
}






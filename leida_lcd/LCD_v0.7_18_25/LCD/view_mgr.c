#include "view_mgr.h"

//#include "malloc.h"
extern UART_HandleTypeDef huart1;
extern uint8_t receive_buff[255];
extern uint8_t uart1_stat;

MenuMgr MenuManager;
/*菜单结构体*/

/*列表界面显示*/
void displaymenu()
{
	uchar HighlowAdjustmentBuf[4] = {0};
	volatile uint16_t i = 0;
	if(MenuManager.cur_menu->view_type == 0)		//列表界面
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
				display_GB2312_string(i*2+1,16*2,MenuManager.\
					cur_menu->subMenus[i+MenuManager.cur_menu->range_from]->menu_name,1,0);
			}
			else
			{
				display_GB2312_string(i*2+1,16*2,MenuManager.\
					cur_menu->subMenus[i+MenuManager.cur_menu->range_from]->menu_name,0,0);
			}
		}
	}
	else if(MenuManager.cur_menu->view_type == 1)	//浮点数界面
	{
//		/*4次循环打印菜单*/
//		for(i = 0;i<4;i++)
//		{
////			if(MenuManager.cur_menu->subMenus[i+MenuManager.cur_menu->range_from]->menu_name[0] == '.')
////			{
////				MenuManager.cur_menu->selected++;
////			}
//			if(i == MenuManager.cur_menu->selected )
//			{
//				if(MenuManager.DataSelectionStatus == 0)
//				{
//					display_Signle_GB2312_string(3,16*(2+i),MenuManager.\
//						cur_menu->subMenus[i+MenuManager.cur_menu->range_from]->menu_name,0,1);  //显示下划线
//				}
//				else if(MenuManager.DataSelectionStatus == 1)
//				{
//					display_Signle_GB2312_string(3,16*(2+i),MenuManager.\
//						cur_menu->subMenus[i+MenuManager.cur_menu->range_from]->menu_name,1,1);  //反色
//				}
//			}
//			else
//			{
//				display_Signle_GB2312_string(3,16*(2+i),MenuManager.\
//					cur_menu->subMenus[i+MenuManager.cur_menu->range_from]->menu_name,0,0);
//			}
//		}
	
//		display_GB2312_string(1,16*(2+i),"低位调整(m)",0,0); 
//		display_GB2312_string(3,16*(2+i),HighlowAdjustmentBuf,0,1);  //显示下划线
//		display_GB2312_string(5,16*(2+i),"高位调整(m)",0,0); 
//		display_GB2312_string(7,16*(2+i),HighlowAdjustmentBuf,0,1);  //显示下划线
	}
	else if(MenuManager.cur_menu->view_type == 2)
	{
		//显示界面
	}
}
//执行传入进来的menu
void Fun(Menu *MainMenu,uint8_t key_value)
{
	//printf(MainMenu->menu_name);
	MainMenu->func(key_value);
}

void meunu_init(void)
{
	MainMeunuInit();		/*主界面相关初始化*/
	BasicSetMenuInit();		/*基本设置初始化*/
	ShowMenuInit();			/*显示相关初始化*/
	AdvSettMenuInit();		/*高级设置界面*/
	
	main_page_init();		/*初始化第一个页面显示*/
}

void menu_looper(void)
{	
	uint8_t Key_val = 0;
	displaymenu();   /*显示当前界面*/
	while(1)
	{
		Key_val = KEY_Scan(0);				/*获取按键事件*/
		Fun(MenuManager.cur_menu,Key_val);	/*运行界面函数*/
		uart_process_data();				/*串口数据业务*/
	}
}


void data_display(unsigned char page,unsigned char column,uint8_t *data_char,uint8_t reverse,uint8_t select)
{
	//sprintf((char*)data_char,"%.2lf",*text);
	volatile uint8_t tmp_i = 0;
	for(tmp_i = 0 ; tmp_i < 4 ; tmp_i++)
	{
		if(tmp_i == select)
		{
			display_Signle_GB2312_string(3,column+tmp_i*16,&data_char[tmp_i],0,1);
		}
		else
		{
			display_Signle_GB2312_string(3,column+tmp_i*16,&data_char[tmp_i],0,1);	
		}
	}
}





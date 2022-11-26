/*
 * @Date: 2022-11-16 22:46:21
 * @LastEditTime: 2022-11-23 21:33:03
 * @LastEditors: herod
 * @Description: 基本设置界面源文件
 * @FilePath: \MDK-ARM\user\LCD\BasicSetMenu.c
 * XXXX
 */
#include "BasicSetMenu.h"
#include <string.h>
float HighlowAdjustment = 0.01;
uint8_t HighlowAdjustmentBuf[7] = {0};
extern Menu BasicSetMenu;

//Menu HighlowAdjustmentBit0 = {		//百位
//	&HighlowAdjustmentBuf[0],
//	0,0,0,0,1,
//};
//Menu HighlowAdjustmentBit1 = {		//十位
//	&HighlowAdjustmentBuf[1],
//	0,0,0,0,1,
//};
//Menu HighlowAdjustmentBit2 = {		//个位
//	&HighlowAdjustmentBuf[2],
//	0,0,0,0,1,
//};
//Menu HighlowAdjustmentBit3 = {		//小数点后一位
//	&HighlowAdjustmentBuf[3],
//	0,0,0,0,1,
//};
//Menu HighlowAdjustmentBit4 = {		//小数点后两位
//	&HighlowAdjustmentBuf[3],
//	0,0,0,0,1,
//};
//Menu HighlowAdjustmentBit5 = {		//小数点后三位
//	&HighlowAdjustmentBuf[3],
//	0,0,0,0,1,
//};

F_VAL Range_Val = {"量程(m)","000.000",0.00};
Menu Range= { 						
	"量程\0",					
	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
}; 
/*高低位调整*/
F_VAL HighlowAdjetMenu_Val[2] = {{"低位调整(m)","000.000",30.00},{"高位调整(m)","000.000",2.00}};
Menu HighlowAdjetMenu = { 	//高低位调整界面
	"高低位调整\0",					
	0,3,4,0,1,						//默认显示0-3项，总共8项，当前选择0项，
}; 

F_VAL BlindArea_Val = {"盲区(m)","00.000",0.00};
Menu BlindArea= { 						
	"盲区\0",					
	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
}; 

F_VAL Distance_Val = {"距离偏执(m)","+0.000",0.00};
Menu Distance_Paranoia= { 						
	"距离偏置\0",					
	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
}; 

OPT Materia_Val = {"物料性质",0,3};
Menu MaterialProperties= { 						
	"物料性质\0",					
	0,3,3,0,0,						//默认显示0-3项，总共8项，当前选择0项，
}; 


OPT CurrentOutPut_Val = {"电流输出",0,2};
Menu CurrentOutPut= { 						
	"电流输出\0",					
	0,2,2,0,0,						//默认显示0-3项，总共8项，当前选择0项，
}; 
OPT WaveFollowing_Val = {"跟波设置",0,2};
Menu WaveFollowingSet = { 
	"跟波设置\0",
	0,2,2,0,0,						//默认显示0-3项，总共4项，当前选择0项，	
}; 

F_VAL Gain_Val = {"距离偏执(m)","00",0.00};
Menu GainSet = { 
	"增益设置\0",
	0,3,3,0,1,						//默认显示0-3项，总共4项，当前选择0项，	
}; 

F_VAL WNT_Set_val[2] = {{"跟踪宽度(m)","0.00",0.00},{"保持时间(s)","0000",0.00}};
Menu WNTSet = { 					/*宽度和时间设置界面*/
	"宽度和时间\0",
	0,3,3,0,1,						//默认显示0-3项，总共4项，当前选择0项，	
}; 



/**
 * @Date: 2022-11-23 21:26:01
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 基本设置界面函数回调
 */
void BasicSetFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
		switch(key_value)
		{
			case OK_KEY://按键A（确认按键）
			{
				//clear_screen(); 
				if( MenuManager.cur_menu->subMenus[MenuManager.cur_menu->selected]->func != NULL)
				{
					MenuManager.cur_menu = MenuManager.cur_menu->subMenus[MenuManager.cur_menu->selected];
				}
				MenuManager.menu_status = 1;
				goto_flag = 1;
				//displaymenu();
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
					//clear_screen(); 
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
					//displaymenu();
				}
				
				break;
			}
			case DOWN_KEY://按键C（下一行菜单 ）
			{
				if(MenuManager.cur_menu->selected == MenuManager.cur_menu->itemCount-1)
				{
					break;
				}
				//clear_screen(); 
				if(MenuManager.cur_menu->selected <= MenuManager.cur_menu->itemCount)
				{
					MenuManager.cur_menu->selected++;

				}
				if(MenuManager.cur_menu->selected > MenuManager.cur_menu->range_to)
				{
					MenuManager.cur_menu->range_to = MenuManager.cur_menu->selected;
					MenuManager.cur_menu->range_from = MenuManager.cur_menu->range_to-3;
				}
				//displaymenu();
				break;
			}	
			case BACK_KEY://按键D（返回）
			{	
				if(MenuManager.cur_menu->parent != NULL)
				{
					MenuManager.cur_menu = MenuManager.cur_menu->parent;
				}
				MenuManager.menu_status = 1;
				//clear_screen();
				//displaymenu();
				
				break;
			}
			default:   //界面刷新
			{

				break;
			}
		}
		if(goto_flag == 1)
		{
			goto_flag = 0;
			return;
		}
		
		else if((key_value != 0) || (MenuManager.menu_status == 1))
		{
			clear_screen();
			displaymenu();
			MenuManager.menu_status = 0;
		}
		return;
}




uint8_t set_ok_flag = 0;
/**
 * @Date: 2022-11-23 21:27:40
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 高低位调整界面回调
 */
void HighlowAdjFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
		switch(key_value)
		{
			case OK_KEY://按键A（确认按键）
			{
				//clear_screen(); 
//				if( MenuManager.cur_menu->subMenus[MenuManager.cur_menu->selected] != NULL)
//				{
//					MenuManager.cur_menu = MenuManager.cur_menu->subMenus[MenuManager.cur_menu->selected];
//				}
//				if(MenuManager.DataSelectionStatus == 0)
//				{
//					MenuManager.DataSelectionStatus = 1;
//				}
//				else if (MenuManager.DataSelectionStatus == 1)
//				{
//					sscanf((char*)HighlowAdjustmentBuf,"%.2lf",HighlowAdjustment);
//					MenuManager.DataSelectionStatus = 0;
//				}
				if(set_ok_flag == 0)
				{
					set_ok_flag = 1;			//选中状态
				}
				else
				{
					set_ok_flag = 0;			//未选中状态
				}

				break;
			}
			case DOWN_KEY://按键B（上一行菜单）
			{

//				if('0'> ((F_VAL *)(MenuManager.cur_menu->item_val)) ->char_val[0]||\
//					((F_VAL *)(MenuManager.cur_menu->item_val)) ->char_val[0] >= '9')	//判断当前数据是否合法
//				{
//					break;
//				}
				//clear_screen(); 
				if(set_ok_flag == 0)
				{
					/*下一项*/
					//if(MenuManager.cur_menu->selected >= 0 && MenuManager.cur_menu->selected < (2 * 7 -1))
					{
						if(MenuManager.cur_menu->selected >=  (2 * 7 -1))
						{
							MenuManager.cur_menu->selected = 0;
						}
						else
						{
							MenuManager.cur_menu->selected++;
						}
						if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 7 ].char_val[MenuManager.cur_menu->selected % 7] == '.')
							MenuManager.cur_menu->selected++;
					}

				}
				else if (set_ok_flag == 1)
				{
					((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 7].char_val[MenuManager.cur_menu->selected % 7]++;
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 7].char_val[MenuManager.cur_menu->selected % 7] < '0')
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 7].char_val[MenuManager.cur_menu->selected % 7] ='9';
					}
					else if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 7].char_val[MenuManager.cur_menu->selected % 7] > '9' )
					{
						 ((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 7].char_val[MenuManager.cur_menu->selected % 7] ='0';
					}
				}
				
				break;
			}
			case UP_KEY://按键C（下一行菜单 ）
			{
				/*暂时不做上翻功能*/
				break;
			}	
			case BACK_KEY://按键D（返回）
			{	
				//clear_screen(); 
				
				MenuManager.cur_menu = MenuManager.cur_menu->parent;
				MenuManager.menu_status = 1;
				goto_flag = 1;
				break;
			}
			default:   //界面刷新
			{

				break;
			}
		}
		if(goto_flag == 1)
		{
			goto_flag = 0;
			return;
		}
		else if((key_value != 0) || (MenuManager.menu_status == 1))
		{
			volatile uint8_t tmp_i = 0;
			clear_screen();
			display_GB2312_string(1,16,((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name,0,0); 
			for(tmp_i  ; tmp_i < 7 * 1 ; tmp_i ++)
			{

				if(MenuManager.cur_menu->selected == tmp_i)
				{
					display_Signle_GB2312_string(3,16+(8 * tmp_i),&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],set_ok_flag,1);
				}
				else
				{
					display_Signle_GB2312_string(3,16+(8 * tmp_i),&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],0,0);
				}
			}
			
			display_GB2312_string(5,16,((F_VAL *)(MenuManager.cur_menu->item_val))[1].val_name,0,0); 
			for(tmp_i  ; tmp_i < 7 * 2 ; tmp_i ++)
			{
				if(MenuManager.cur_menu->selected == tmp_i)
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 7)),&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 7],set_ok_flag,1);
				}
				else
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 7)),&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 7],0,0);
				}
			}
			MenuManager.menu_status = 0;
		}
}

/**
 * @Date: 2022-11-23 21:28:25
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 量程界面回调
 */
void RangeFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	switch(key_value)
	{
		case OK_KEY://按键A（确认按键）
		{
			/*OK按键功能*/
			if(set_ok_flag == 0)
			{
				set_ok_flag = 1;			//选中状态
			}
			else
			{
				set_ok_flag = 0;			//未选中状态
			}
			break;
		}
		case DOWN_KEY://按键B（上一行菜单）
		{
			/*下翻按键功能*/
				if(set_ok_flag == 0)
				{
					if(MenuManager.cur_menu->selected >=  (7 -1))
					{
						MenuManager.cur_menu->selected = 0;
					}
					else
					{
						MenuManager.cur_menu->selected++;
					}
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 7 ].char_val[MenuManager.cur_menu->selected % 7] == '.')
						MenuManager.cur_menu->selected++;

				}
				else if (set_ok_flag == 1)
				{
					((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected].char_val[MenuManager.cur_menu->selected % 7]++;
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 7].char_val[MenuManager.cur_menu->selected % 7] < '0')
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 7].char_val[MenuManager.cur_menu->selected % 7] ='9';
					}
					else if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 7].char_val[MenuManager.cur_menu->selected % 7] > '9' )
					{
						 ((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 7].char_val[MenuManager.cur_menu->selected % 7] ='0';
					}
				}
			break;
		}
		case UP_KEY://按键C（下一行菜单 ）
		{
			/*上翻按键功能*/
			break;
		}	
		case BACK_KEY://按键D（返回）
		{	
			/*返回按键功能*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;
			MenuManager.menu_status = 1;
			goto_flag = 1;
			break;
		}
		default:   //界面刷新
		{
			break;
		}
	}
	if(goto_flag == 1)
	{
		/*直接退出*/
		goto_flag = 0;
		return;
	}
	else if((key_value != 0) || (MenuManager.menu_status == 1))
	{
		/*页面显示*/
		volatile uint8_t tmp_i = 0;
		clear_screen();
		display_GB2312_string(1,16,((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name,0,0); 
		for(tmp_i  ; tmp_i < 7 * 1 ; tmp_i ++)
		{

			if(MenuManager.cur_menu->selected == tmp_i)
			{
				display_Signle_GB2312_string(3,16+(8 * tmp_i),&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],set_ok_flag,1);
			}
			else
			{
				display_Signle_GB2312_string(3,16+(8 * tmp_i),&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],0,0);
			}
		}
		MenuManager.menu_status = 0;
	}
}

/**
 * @Date: 2022-11-23 21:29:33
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 盲区界面显示回调
 */
void BlindFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	switch(key_value)
	{
		case OK_KEY://按键A（确认按键）
		{
			/*OK按键功能*/
			if(set_ok_flag == 0)
			{
				set_ok_flag = 1;			//选中状态
			}
			else
			{
				set_ok_flag = 0;			//未选中状态
			}
			break;
		}
		case DOWN_KEY://按键B（上一行菜单）
		{
			
			if(set_ok_flag == 0)
			{
				if(MenuManager.cur_menu->selected >=  (6 -1))
				{
					MenuManager.cur_menu->selected = 0;
				}
				else
				{
					MenuManager.cur_menu->selected++;
				}
				/*下翻按键功能*/
				if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 6 ].char_val[ (MenuManager.cur_menu->selected % 6)] == '.')
					MenuManager.cur_menu->selected++;
			}
			else if (set_ok_flag == 1)
			{
				((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected].char_val[MenuManager.cur_menu->selected % 6]++;
				if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 6].char_val[MenuManager.cur_menu->selected % 6] < '0')
				{
					((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 6].char_val[MenuManager.cur_menu->selected % 6] ='9';
				}
				else if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 6].char_val[MenuManager.cur_menu->selected % 6] > '9' )
				{
					 ((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 6].char_val[MenuManager.cur_menu->selected % 6] ='0';
				}
			}
			break;
		}
		case UP_KEY://按键C（下一行菜单 ）
		{
			/*上翻按键功能*/

			break;
		}	
		case BACK_KEY://按键D（返回）
		{	
			/*返回按键功能*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;
			MenuManager.menu_status = 1;
			goto_flag = 1;
			break;
		}
		default:   //界面刷新
		{
			break;
		}
	}
	if(goto_flag == 1)
	{
		/*直接退出*/
		goto_flag = 0;
		return;
	}
	else if((key_value != 0) || (MenuManager.menu_status == 1))
	{
		/*页面显示*/
				/*页面显示*/
		volatile uint8_t tmp_i = 0;
		clear_screen();
		display_GB2312_string(1,16,((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name,0,0); 
		for(tmp_i  ; tmp_i < 6 * 1 ; tmp_i ++)
		{

			if(MenuManager.cur_menu->selected == tmp_i)
			{
				display_Signle_GB2312_string(3,16+(8 * tmp_i),&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],set_ok_flag,1);
			}
			else
			{
				display_Signle_GB2312_string(3,16+(8 * tmp_i),&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],0,0);
			}
		}
		MenuManager.menu_status = 0;
	}
}

/**
 * @Date: 2022-11-23 21:29:50
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 距离偏执界面回调
 */
void DistanceFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	switch(key_value)
	{
		case OK_KEY://按键A（确认按键）
		{
			/*OK按键功能*/
			if(set_ok_flag == 0)
			{
				set_ok_flag = 1;			//选中状态
			}
			else
			{
				set_ok_flag = 0;			//未选中状态
			}
			break;
		}
		case DOWN_KEY://按键B（上一行菜单）
		{
			
			if(set_ok_flag == 0)
			{
				if(MenuManager.cur_menu->selected >=  (6 -1))
				{
					MenuManager.cur_menu->selected = 0;
				}
				else
				{
					MenuManager.cur_menu->selected++;
				}
				/*下翻按键功能*/
				if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 6 ].char_val[ (MenuManager.cur_menu->selected % 6)] == '.')
					MenuManager.cur_menu->selected++;
			}
			else if (set_ok_flag == 1)
			{
				if(MenuManager.cur_menu->selected == 0)
				{
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected].char_val[MenuManager.cur_menu->selected % 6] == '+')
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected].char_val[MenuManager.cur_menu->selected % 6] = '-';
					}
					else 
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected].char_val[MenuManager.cur_menu->selected % 6] = '+';
					}
				}
				else 
				{
					((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected].char_val[MenuManager.cur_menu->selected % 6]++;
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 6].char_val[MenuManager.cur_menu->selected % 6] < '0')
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 6].char_val[MenuManager.cur_menu->selected % 6] ='9';
					}
					else if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 6].char_val[MenuManager.cur_menu->selected % 6] > '9' )
					{
						 ((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 6].char_val[MenuManager.cur_menu->selected % 6] ='0';
					}
				}
			}
			break;
		}
		case UP_KEY://按键C（下一行菜单 ）
		{
			/*上翻按键功能*/

			break;
		}	
		case BACK_KEY://按键D（返回）
		{	
			/*返回按键功能*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;
			MenuManager.menu_status = 1;
			goto_flag = 1;
			break;
		}
		default:   //界面刷新
		{
			break;
		}
	}
	if(goto_flag == 1)
	{
		/*直接退出*/
		goto_flag = 0;
		return;
	}
	else if((key_value != 0) || (MenuManager.menu_status == 1))
	{
		/*页面显示*/
		uchar tmp_ch = '+';
		volatile uint8_t tmp_i = 0;
		clear_screen();
		display_GB2312_string(1,8,((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name,0,0); 
		for(tmp_i  ; tmp_i < 6 * 1 ; tmp_i ++)
		{

			if(MenuManager.cur_menu->selected == tmp_i)
			{
				display_Signle_GB2312_string(3,16+(8 * tmp_i),&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],set_ok_flag,1);
			}
			else
			{
				display_Signle_GB2312_string(3,16+(8 * tmp_i),&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],0,0);
			}
		}
		MenuManager.menu_status = 0;
	}
}


/**
 * @Date: 2022-11-23 21:30:27
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 物料性质界面回调
 */
void MaterialFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	switch(key_value)
	{
		case OK_KEY://按键A（确认按键）
		{
			/*OK按键功能*/
			if(set_ok_flag == 0)
			{
				set_ok_flag = 1;			//选中状态
			}
			else
			{
				set_ok_flag = 0;			//未选中状态
			}
			break;
		}
		case DOWN_KEY://按键B（上一行菜单）
		{
			if(set_ok_flag == 0)		/*未选中*/
			{
			}
			else if (set_ok_flag == 1)	/*选中*/
			{
			}
			if(MenuManager.cur_menu->selected >= 2)
			{
				MenuManager.cur_menu->selected = 0;
			}
			else
			{
				MenuManager.cur_menu->selected++;
			}
			break;
		}
		case UP_KEY://按键C（下一行菜单 ）
		{
			/*上翻按键功能*/
			
			break;
		}	
		case BACK_KEY://按键D（返回）
		{	
			/*返回按键功能*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;
			MenuManager.menu_status = 1;
			goto_flag = 1;
			break;
		}
		default:   //界面刷新
		{
			break;
		}
	}
	if(goto_flag == 1)
	{
		/*直接退出*/
		goto_flag = 0;
		return;
	}
	else if((key_value != 0) || (MenuManager.menu_status == 1))
	{
		/*页面显示*/
		uchar tmp_ch = '*';
		volatile uint8_t tmp_i = 0;
		clear_screen();
		display_GB2312_string(1,8,((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name,0,0); 
		display_Signle_GB2312_string(3+(MenuManager.cur_menu->selected * 2),16+(8 * tmp_i),&tmp_ch,0,0);
		display_GB2312_string(3,32,"液体",0,0); 
		display_GB2312_string(5,32,"固体",0,0); 
		display_GB2312_string(7,32,"搅拌",0,0); 
		MenuManager.menu_status = 0;
	}
}


/**
 * @Date: 2022-11-23 21:30:48
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 电流输出界面回调
 */
void CurrentOutPuFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	switch(key_value)
	{
		case OK_KEY://按键A（确认按键）
		{
			/*OK按键功能*/
			if(set_ok_flag == 0)
			{
				set_ok_flag = 1;			//选中状态
			}
			else
			{
				set_ok_flag = 0;			//未选中状态
			}
			break;
		}
		case DOWN_KEY://按键B（上一行菜单）
		{
			if(set_ok_flag == 0)		/*未选中*/
			{
			}
			else if (set_ok_flag == 1)	/*选中*/
			{
			}
			if(MenuManager.cur_menu->selected >= 1)
			{
				MenuManager.cur_menu->selected = 0;
			}
			else
			{
				MenuManager.cur_menu->selected++;
			}
			break;
		}
		case UP_KEY://按键C（下一行菜单 ）
		{
			/*上翻按键功能*/
			
			break;
		}	
		case BACK_KEY://按键D（返回）
		{	
			/*返回按键功能*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;
			MenuManager.menu_status = 1;
			goto_flag = 1;
			break;
		}
		default:   //界面刷新
		{
			break;
		}
	}
	if(goto_flag == 1)
	{
		/*直接退出*/
		goto_flag = 0;
		return;
	}
	else if((key_value != 0) || (MenuManager.menu_status == 1))
	{
		/*页面显示*/
		uchar tmp_ch = '*';
		volatile uint8_t tmp_i = 0;
		clear_screen();
		display_GB2312_string(1,8,((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name,0,0); 
		display_Signle_GB2312_string(3+(MenuManager.cur_menu->selected * 2),16+(8 * tmp_i),&tmp_ch,0,0);
		display_GB2312_string(3,32,"20-4mA",0,0); 
		display_GB2312_string(5,32,"4-20mA",0,0); 
		MenuManager.menu_status = 0;
	}
}


/**
 * @Date: 2022-11-23 21:31:01
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 跟波设置界面回调
 */
void WaveFollowingFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	switch(key_value)
	{
		case OK_KEY://按键A（确认按键）
		{
			/*OK按键功能*/
			MenuManager.cur_menu = MenuManager.cur_menu->subMenus[0];
			MenuManager.menu_status = 1;

			break;
		}
		case DOWN_KEY://按键B（上一行菜单）
		{
			if(set_ok_flag == 0)		/*未选中*/
			{
			}
			else if (set_ok_flag == 1)	/*选中*/
			{
			}
			if(MenuManager.cur_menu->selected >= 1)
			{
				MenuManager.cur_menu->selected = 0;
			}
			else
			{
				MenuManager.cur_menu->selected++;
			}
			break;
		}
		case UP_KEY://按键C（下一行菜单 ）
		{
			/*上翻按键功能*/
			
			break;
		}	
		case BACK_KEY://按键D（返回）
		{	
			/*返回按键功能*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;
			MenuManager.menu_status = 1;
			goto_flag = 1;
			break;
		}
		default:   //界面刷新
		{
			break;
		}
	}
	if(goto_flag == 1)
	{
		/*直接退出*/
		goto_flag = 0;
		return;
	}
	else if((key_value != 0) || (MenuManager.menu_status == 1))
	{
		/*页面显示*/
		uchar tmp_ch = '*';
		volatile uint8_t tmp_i = 0;
		clear_screen();
		display_GB2312_string(1,8,((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name,0,0); 
		display_Signle_GB2312_string(3+(MenuManager.cur_menu->selected * 2),16+(8 * tmp_i),&tmp_ch,0,0);
		display_GB2312_string(3,32,"是",0,0); 
		display_GB2312_string(5,32,"否",0,0); 
		MenuManager.menu_status = 0;
	}
}

/**
 * @Date: 2022-11-23 21:31:41
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 宽度和时间设置界面回调
 */
void WNTSetFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
		switch(key_value)
		{
			case OK_KEY://按键A（确认按键）
			{
				//clear_screen(); 
//				if( MenuManager.cur_menu->subMenus[MenuManager.cur_menu->selected] != NULL)
//				{
//					MenuManager.cur_menu = MenuManager.cur_menu->subMenus[MenuManager.cur_menu->selected];
//				}
//				if(MenuManager.DataSelectionStatus == 0)
//				{
//					MenuManager.DataSelectionStatus = 1;
//				}
//				else if (MenuManager.DataSelectionStatus == 1)
//				{
//					sscanf((char*)HighlowAdjustmentBuf,"%.2lf",HighlowAdjustment);
//					MenuManager.DataSelectionStatus = 0;
//				}
				if(set_ok_flag == 0)
				{
					set_ok_flag = 1;			//选中状态
				}
				else
				{
					set_ok_flag = 0;			//未选中状态
				}

				break;
			}
			case DOWN_KEY://按键B（上一行菜单）
			{

//				if('0'> ((F_VAL *)(MenuManager.cur_menu->item_val)) ->char_val[0]||\
//					((F_VAL *)(MenuManager.cur_menu->item_val)) ->char_val[0] >= '9')	//判断当前数据是否合法
//				{
//					break;
//				}
				//clear_screen(); 
				if(set_ok_flag == 0)
				{
					/*下一项*/
					//if(MenuManager.cur_menu->selected >= 0 && MenuManager.cur_menu->selected < (2 * 7 -1))
					{
						if(MenuManager.cur_menu->selected >=  (2 * 4 -1))
						{
							MenuManager.cur_menu->selected = 0;
						}
						else
						{
							MenuManager.cur_menu->selected++;
						}
						if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 4 ].char_val[MenuManager.cur_menu->selected % 4] == '.')
							MenuManager.cur_menu->selected++;
					}

				}
				else if (set_ok_flag == 1)
				{
					((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 4].char_val[MenuManager.cur_menu->selected % 4]++;
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 4].char_val[MenuManager.cur_menu->selected % 4] < '0')
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 4].char_val[MenuManager.cur_menu->selected % 4] ='9';
					}
					else if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 4].char_val[MenuManager.cur_menu->selected % 4] > '9' )
					{
						 ((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 4].char_val[MenuManager.cur_menu->selected % 4] ='0';
					}
				}
				
				break;
			}
			case UP_KEY://按键C（下一行菜单 ）
			{
				/*暂时不做上翻功能*/
				break;
			}	
			case BACK_KEY://按键D（返回）
			{	
				//clear_screen(); 
				
				MenuManager.cur_menu = MenuManager.cur_menu->parent;
				MenuManager.menu_status = 1;
				goto_flag = 1;
				break;
			}
			default:   //界面刷新
			{

				break;
			}
		}
		if(goto_flag == 1)
		{
			goto_flag = 0;
			return;
		}
		else if((key_value != 0) || (MenuManager.menu_status == 1))
		{
			volatile uint8_t tmp_i = 0;
			clear_screen();
			display_GB2312_string(1,16,((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name,0,0); 
			for(tmp_i  ; tmp_i < 4 * 1 ; tmp_i ++)
			{

				if(MenuManager.cur_menu->selected == tmp_i)
				{
					display_Signle_GB2312_string(3,16+(8 * tmp_i),&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],set_ok_flag,1);
				}
				else
				{
					display_Signle_GB2312_string(3,16+(8 * tmp_i),&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],0,0);
				}
			}
			
			display_GB2312_string(5,16,((F_VAL *)(MenuManager.cur_menu->item_val))[1].val_name,0,0); 
			for(tmp_i  ; tmp_i < 4 * 2 ; tmp_i ++)
			{
				if(MenuManager.cur_menu->selected == tmp_i)
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 4)),&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 4],set_ok_flag,1);
				}
				else
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 4)),&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 4],0,0);
				}
			}
			MenuManager.menu_status = 0;
		}
}

/*距离偏执界面显示*/
/**
 * @Date: 2022-11-23 21:32:02
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 增益设置界面回调
 */
void GainFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	switch(key_value)
	{
		case OK_KEY://按键A（确认按键）
		{
			/*OK按键功能*/
			if(set_ok_flag == 0)
			{
				set_ok_flag = 1;			//选中状态
			}
			else
			{
				set_ok_flag = 0;			//未选中状态
			}
			break;
		}
		case DOWN_KEY://按键B（上一行菜单）
		{
			
			if(set_ok_flag == 0)
			{
				if(MenuManager.cur_menu->selected >=  (2 -1))
				{
					MenuManager.cur_menu->selected = 0;
				}
				else
				{
					MenuManager.cur_menu->selected++;
				}
				/*下翻按键功能*/
				if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 2 ].char_val[ (MenuManager.cur_menu->selected % 2)] == '.')
					MenuManager.cur_menu->selected++;
			}
			else if (set_ok_flag == 1)
			{
				if(MenuManager.cur_menu->selected == 0)
				{
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected].char_val[MenuManager.cur_menu->selected % 2] == '+')
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected].char_val[MenuManager.cur_menu->selected % 2] = '-';
					}
					else 
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected].char_val[MenuManager.cur_menu->selected % 2] = '+';
					}
				}
				else 
				{
					((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected].char_val[MenuManager.cur_menu->selected % 2]++;
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 2].char_val[MenuManager.cur_menu->selected % 2] < '0')
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 2].char_val[MenuManager.cur_menu->selected % 2] ='9';
					}
					else if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 2].char_val[MenuManager.cur_menu->selected % 2] > '9' )
					{
						 ((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 2].char_val[MenuManager.cur_menu->selected % 2] ='0';
					}
				}
			}
			break;
		}
		case UP_KEY://按键C（下一行菜单 ）
		{
			/*上翻按键功能*/

			break;
		}	
		case BACK_KEY://按键D（返回）
		{	
			/*返回按键功能*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;
			MenuManager.menu_status = 1;
			goto_flag = 1;
			break;
		}
		default:   //界面刷新
		{
			break;
		}
	}
	if(goto_flag == 1)
	{
		/*直接退出*/
		goto_flag = 0;
		return;
	}
	else if((key_value != 0) || (MenuManager.menu_status == 1))
	{
		/*页面显示*/
				/*页面显示*/
		uchar tmp_ch = '+';
		volatile uint8_t tmp_i = 0;
		clear_screen();
		display_GB2312_string(1,8,((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name,0,0); 
		for(tmp_i  ; tmp_i < 2 * 1 ; tmp_i ++)
		{

			if(MenuManager.cur_menu->selected == tmp_i)
			{
				display_Signle_GB2312_string(3,16+(8 * tmp_i),&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],set_ok_flag,1);
			}
			else
			{
				display_Signle_GB2312_string(3,16+(8 * tmp_i),&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],0,0);
			}
		}
		MenuManager.menu_status = 0;
	}
}


/**
 * @Date: 2022-11-23 21:33:10
 * @LastEditors: herod
 * @Description: 基本设置界面初始胡
 */
void BasicSetMenuInit(void)
{
	/*基本设置界面初始化*/
	BasicSetMenu.subMenus[0] = &Range;
	
	//memset(HighlowAdjetMenu_Val,0,(sizeof(HighlowAdjetMenu_Val) * 2));
	
	
	BasicSetMenu.subMenus[1] = &HighlowAdjetMenu;
	BasicSetMenu.subMenus[2] = &BlindArea;
	BasicSetMenu.subMenus[3] = &Distance_Paranoia;
	BasicSetMenu.subMenus[4] = &MaterialProperties;
	BasicSetMenu.subMenus[5] = &CurrentOutPut;
	BasicSetMenu.subMenus[6] = &WaveFollowingSet;
	BasicSetMenu.subMenus[7] = &GainSet;
	BasicSetMenu.parent = &ListMenu;			/*主界面没有上级目录*/
	BasicSetMenu.func = BasicSetFunc;
	
//	/*跟波宽度设置*/
//	GainSet.subMenus[0]
	
	/*高低位调整页面*/
	HighlowAdjetMenu.item_val = &HighlowAdjetMenu_Val;
	HighlowAdjetMenu.func = HighlowAdjFunc;
	HighlowAdjetMenu.parent = &BasicSetMenu;
	
	/*量程页面*/
	Range.item_val = &Range_Val;
	Range.func = RangeFunc;
	Range.parent = &BasicSetMenu;
	
	/*盲区页面*/
	BlindArea.item_val = &BlindArea_Val;
	BlindArea.func = BlindFunc;
	BlindArea.parent = &BasicSetMenu;
	
	/*距离偏执页面*/
	Distance_Paranoia.item_val = &Distance_Val;
	Distance_Paranoia.func = DistanceFunc;
	Distance_Paranoia.parent = &BasicSetMenu;
	
	/*物料性质页面*/
	MaterialProperties.item_val = &Materia_Val;		
	MaterialProperties.func = MaterialFunc;
	MaterialProperties.parent = &BasicSetMenu;
	
	/*电流输出页面*/
	CurrentOutPut.item_val = &CurrentOutPut_Val;		
	CurrentOutPut.func = CurrentOutPuFunc;
	CurrentOutPut.parent = &BasicSetMenu;
	
	/*跟波设置页面*/
	WaveFollowingSet.item_val = &WaveFollowing_Val;		
	WaveFollowingSet.func = WaveFollowingFunc;
	WaveFollowingSet.parent = &BasicSetMenu;
	WaveFollowingSet.subMenus[0] = &WNTSet;
	
	/*跟波宽度和时间设置*/
	WNTSet.item_val = &WNT_Set_val;
	WNTSet.func = WNTSetFunc;
	WNTSet.parent = &WaveFollowingSet;
	
	/*增益设置*/
	GainSet.item_val = &Gain_Val;		
	GainSet.func = GainFunc;
	GainSet.parent = &BasicSetMenu;
}

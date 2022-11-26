/*
 * @Date: 2022-11-16 22:46:21
 * @LastEditTime: 2022-11-23 21:22:09
 * @LastEditors: herod
 * @Description: 高级设置界面
 * @FilePath: \MDK-ARM\user\LCD\advanced_setting.c
 * XXXX
 */
#include "advanced_setting.h"
#include <string.h>

extern Menu AdvancedSetting;
Menu ClutterUpdate= { 						
	"杂波更新\0",					
	0,3,4,0,0,						//默认显示0-3项，总共8项，当前选择0项，
}; 

F_VAL ThresholdSettings_Val = {"阈值门限(dB)","00",0.00};
/*杂波更新子界面开始*/
Menu ThresholdSettings= { 						
	"阈值设置\0",					
	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
}; 

F_VAL LocalSettings1_Val[2] = {{"杂波范围(m)","000.0-000.0",0.00},{"杂波门限(dB)","00",0.00}};
Menu LocalSettings1= { 						
	"局部设置1\0",					
	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
}; 

F_VAL LocalSettings2_Val[2] = {{"杂波范围(m)","000.0-000.0",0.00},{"杂波门限(dB)","00",0.00}};
Menu LocalSettings2= { 						
	"局部设置2\0",					
	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
}; 

F_VAL LocalSettings3_Val[2] = {{"杂波范围(m)","000.0-000.0",0.00},{"杂波门限(dB)","00",0.00}};
Menu LocalSettings3= { 						
	"局部设置3\0",					
	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
}; 
/*杂波更新子界面结束*/
OPT NoSignalOutput_Val = {"无信号输出",0,2};
Menu NoSignalOutput= { 						
	"无信号输出\0",					
	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
}; 
///*无信号输出子界面开始*/
//Menu CurrentValue= { 						
//	"当前值\0",					
//	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
//}; 
//Menu FullScale= { 						
//	"满量程\0",					
//	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
//}; 
//Menu EmptyRange= { 						
//	"空量程\0",					
//	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
//}; 
/*无信号输出子界面结束*/
F_VAL DampingTime_Val = {"阻尼时间","00",0.00};
Menu DampingTime= { 						
	"阻尼时间\0",					
	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
}; 


F_VAL DampingCoefficient_val = {"阻尼系数","00",0.00};
Menu DampingCoefficient= { 						
	"阻尼系数\0",					
	0,3,3,0,1,						//默认显示0-3项，总共8项，当前选择0项，
}; 


/**
 * @Date: 2022-11-23 21:19:58
 * @LastEditors: herod
 * @param {uint8_t} key_value	掺入操作按键
 * @Description: 高级设置回调函数
 */
void AdvSetFunc(uint8_t key_value)
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


/**
 * @Date: 2022-11-23 21:20:41
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 杂波更新回调函数
 */
void ClutterUpdateFunc(uint8_t key_value)
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

extern uint8_t set_ok_flag;
/**
 * @Date: 2022-11-23 21:21:31
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 阈值设置回调函数
 */
void ThresholdSettingsFunc(uint8_t key_value)
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
					if(MenuManager.cur_menu->selected >=  (2 -1))
					{
						MenuManager.cur_menu->selected = 0;
					}
					else
					{
						MenuManager.cur_menu->selected++;
					}
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 2 ].char_val[MenuManager.cur_menu->selected % 2] == '.')
						MenuManager.cur_menu->selected++;

				}
				else if (set_ok_flag == 1)
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
 * @Date: 2022-11-23 21:22:02
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: 局部设置回调函数
 */
void LocalSettings1Func(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	uint8_t tmp_val = 0;
		switch(key_value)
		{
			case OK_KEY://按键A（确认按键）
			{
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
					/*下一项*/
					//if(MenuManager.cur_menu->selected >= 0 && MenuManager.cur_menu->selected < (2 * 7 -1))
					{
						if(MenuManager.cur_menu->selected >=  ((11 + 2) -1))
						{
							MenuManager.cur_menu->selected = 0;
						}
						else
						{
							MenuManager.cur_menu->selected++;
						}
						if(MenuManager.cur_menu->selected  > 11)
						{
							tmp_val = MenuManager.cur_menu->selected - 11;
						}
						else
						{
							tmp_val = MenuManager.cur_menu->selected;
						}
						if((((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11 ].char_val[tmp_val] == '.') || \
							(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11 ].char_val[tmp_val] == '-') )
							MenuManager.cur_menu->selected++;
					}

				}
				else if (set_ok_flag == 1)
				{
					((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val]++;
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val] < '0')
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val] ='9';
					}
					else if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val] > '9' )
					{
						 ((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val] ='0';
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
			for(tmp_i  ; tmp_i < 11  ; tmp_i ++)
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
			for(tmp_i  ; tmp_i < (11 + 2) ; tmp_i ++)
			{
				if(MenuManager.cur_menu->selected == tmp_i)
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 11)),&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 11],set_ok_flag,1);
				}
				else
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 11)),&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 11],0,0);
				}
			}
			MenuManager.menu_status = 0;
		}
}

void LocalSettings2Func(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	uint8_t tmp_val = 0;
		switch(key_value)
		{
			case OK_KEY://按键A（确认按键）
			{
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
					/*下一项*/
					//if(MenuManager.cur_menu->selected >= 0 && MenuManager.cur_menu->selected < (2 * 7 -1))
					{
						if(MenuManager.cur_menu->selected >=  ((11 + 2) -1))
						{
							MenuManager.cur_menu->selected = 0;
						}
						else
						{
							MenuManager.cur_menu->selected++;
						}
						if(MenuManager.cur_menu->selected  > 11)
						{
							tmp_val = MenuManager.cur_menu->selected - 11;
						}
						else
						{
							tmp_val = MenuManager.cur_menu->selected;
						}
						if((((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11 ].char_val[tmp_val] == '.') || \
							(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11 ].char_val[tmp_val] == '-') )
							MenuManager.cur_menu->selected++;
					}

				}
				else if (set_ok_flag == 1)
				{
					((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val]++;
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val] < '0')
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val] ='9';
					}
					else if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val] > '9' )
					{
						 ((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val] ='0';
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
			for(tmp_i  ; tmp_i < 11  ; tmp_i ++)
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
			for(tmp_i  ; tmp_i < (11 + 2) ; tmp_i ++)
			{
				if(MenuManager.cur_menu->selected == tmp_i)
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 11)),&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 11],set_ok_flag,1);
				}
				else
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 11)),&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 11],0,0);
				}
			}
			MenuManager.menu_status = 0;
		}
}

void LocalSettings3Func(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	uint8_t tmp_val = 0;
		switch(key_value)
		{
			case OK_KEY://按键A（确认按键）
			{
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
					/*下一项*/
					//if(MenuManager.cur_menu->selected >= 0 && MenuManager.cur_menu->selected < (2 * 7 -1))
					{
						if(MenuManager.cur_menu->selected >=  ((11 + 2) -1))
						{
							MenuManager.cur_menu->selected = 0;
						}
						else
						{
							MenuManager.cur_menu->selected++;
						}
						if(MenuManager.cur_menu->selected  > 11)
						{
							tmp_val = MenuManager.cur_menu->selected - 11;
						}
						else
						{
							tmp_val = MenuManager.cur_menu->selected;
						}
						if((((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11 ].char_val[tmp_val] == '.') || \
							(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11 ].char_val[tmp_val] == '-') )
							MenuManager.cur_menu->selected++;
					}

				}
				else if (set_ok_flag == 1)
				{
					((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val]++;
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val] < '0')
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val] ='9';
					}
					else if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val] > '9' )
					{
						 ((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 11].char_val[tmp_val] ='0';
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
			for(tmp_i  ; tmp_i < 11  ; tmp_i ++)
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
			for(tmp_i  ; tmp_i < (11 + 2) ; tmp_i ++)
			{
				if(MenuManager.cur_menu->selected == tmp_i)
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 11)),&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 11],set_ok_flag,1);
				}
				else
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 11)),&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 11],0,0);
				}
			}
			MenuManager.menu_status = 0;
		}
}


/*无信号输出显示*/
void NoSignalOutputFunc(uint8_t key_value)
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
		display_GB2312_string(3,32,"当前值",0,0); 
		display_GB2312_string(5,32,"满量程",0,0); 
		display_GB2312_string(7,32,"空量程",0,0); 
		MenuManager.menu_status = 0;
	}
}

void DampingTimeFunc(uint8_t key_value)
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
					if(MenuManager.cur_menu->selected >=  (2 -1))
					{
						MenuManager.cur_menu->selected = 0;
					}
					else
					{
						MenuManager.cur_menu->selected++;
					}
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 2 ].char_val[MenuManager.cur_menu->selected % 2] == '.')
						MenuManager.cur_menu->selected++;

				}
				else if (set_ok_flag == 1)
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

void DampingCoefficientFunc(uint8_t key_value)
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
					if(MenuManager.cur_menu->selected >=  (2 -1))
					{
						MenuManager.cur_menu->selected = 0;
					}
					else
					{
						MenuManager.cur_menu->selected++;
					}
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 2 ].char_val[MenuManager.cur_menu->selected % 2] == '.')
						MenuManager.cur_menu->selected++;

				}
				else if (set_ok_flag == 1)
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

void AdvSettMenuInit(void)
{
	/*显示界面初始化*/
	AdvancedSetting.subMenus[0] = &ClutterUpdate;
	AdvancedSetting.subMenus[1] = &NoSignalOutput;
	AdvancedSetting.subMenus[2] = &DampingTime;
	AdvancedSetting.subMenus[3] = &DampingCoefficient;
	AdvancedSetting.parent = &ListMenu;			/*主界面没有上级目录*/
	AdvancedSetting.func = AdvSetFunc;
	
	
	ClutterUpdate.subMenus[0] = &ThresholdSettings;
	ClutterUpdate.subMenus[1] = &LocalSettings1;
	ClutterUpdate.subMenus[2] = &LocalSettings2;
	ClutterUpdate.subMenus[3] = &LocalSettings3;
	ClutterUpdate.parent = &AdvancedSetting;	
	ClutterUpdate.func = ClutterUpdateFunc;
	
	
	ThresholdSettings.item_val = &ThresholdSettings_Val;		
	ThresholdSettings.func = ThresholdSettingsFunc;
	ThresholdSettings.parent = &ClutterUpdate;
	
	LocalSettings1.item_val = &LocalSettings1_Val;		
	LocalSettings1.func = LocalSettings1Func;
	LocalSettings1.parent = &ClutterUpdate;
	
	LocalSettings2.item_val = &LocalSettings2_Val;		
	LocalSettings2.func = LocalSettings2Func;
	LocalSettings2.parent = &ClutterUpdate;
	
	LocalSettings3.item_val = &LocalSettings3_Val;		
	LocalSettings3.func = LocalSettings3Func;
	LocalSettings3.parent = &ClutterUpdate;
	
	NoSignalOutput.func = &NoSignalOutputFunc;
	NoSignalOutput.item_val = &NoSignalOutput_Val;
	NoSignalOutput.parent = &ClutterUpdate;
	
	DampingTime.func = &DampingTimeFunc;
	DampingTime.item_val = &DampingTime_Val;
	DampingTime.parent = &ClutterUpdate;
	
	DampingCoefficient.func = &DampingCoefficientFunc;
	DampingCoefficient.item_val = &DampingCoefficient_val;
	DampingCoefficient.parent = &ClutterUpdate;
}

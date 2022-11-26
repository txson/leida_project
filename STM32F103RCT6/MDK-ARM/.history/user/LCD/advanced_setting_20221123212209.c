/*
 * @Date: 2022-11-16 22:46:21
 * @LastEditTime: 2022-11-23 21:22:09
 * @LastEditors: herod
 * @Description: �߼����ý���
 * @FilePath: \MDK-ARM\user\LCD\advanced_setting.c
 * XXXX
 */
#include "advanced_setting.h"
#include <string.h>

extern Menu AdvancedSetting;
Menu ClutterUpdate= { 						
	"�Ӳ�����\0",					
	0,3,4,0,0,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 

F_VAL ThresholdSettings_Val = {"��ֵ����(dB)","00",0.00};
/*�Ӳ������ӽ��濪ʼ*/
Menu ThresholdSettings= { 						
	"��ֵ����\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 

F_VAL LocalSettings1_Val[2] = {{"�Ӳ���Χ(m)","000.0-000.0",0.00},{"�Ӳ�����(dB)","00",0.00}};
Menu LocalSettings1= { 						
	"�ֲ�����1\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 

F_VAL LocalSettings2_Val[2] = {{"�Ӳ���Χ(m)","000.0-000.0",0.00},{"�Ӳ�����(dB)","00",0.00}};
Menu LocalSettings2= { 						
	"�ֲ�����2\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 

F_VAL LocalSettings3_Val[2] = {{"�Ӳ���Χ(m)","000.0-000.0",0.00},{"�Ӳ�����(dB)","00",0.00}};
Menu LocalSettings3= { 						
	"�ֲ�����3\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 
/*�Ӳ������ӽ������*/
OPT NoSignalOutput_Val = {"���ź����",0,2};
Menu NoSignalOutput= { 						
	"���ź����\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 
///*���ź�����ӽ��濪ʼ*/
//Menu CurrentValue= { 						
//	"��ǰֵ\0",					
//	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
//}; 
//Menu FullScale= { 						
//	"������\0",					
//	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
//}; 
//Menu EmptyRange= { 						
//	"������\0",					
//	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
//}; 
/*���ź�����ӽ������*/
F_VAL DampingTime_Val = {"����ʱ��","00",0.00};
Menu DampingTime= { 						
	"����ʱ��\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 


F_VAL DampingCoefficient_val = {"����ϵ��","00",0.00};
Menu DampingCoefficient= { 						
	"����ϵ��\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 


/**
 * @Date: 2022-11-23 21:19:58
 * @LastEditors: herod
 * @param {uint8_t} key_value	�����������
 * @Description: �߼����ûص�����
 */
void AdvSetFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
		switch(key_value)
		{
			case OK_KEY://����A��ȷ�ϰ�����
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
			case UP_KEY://����B����һ�в˵���
			{
				if(MenuManager.cur_menu->selected == 0)
				{
					/*��ǰѡ���Ѿ�Ϊ��һ�� ���ز����д���*/
					break;
				}

				else
				{
					//clear_screen(); 
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
					//displaymenu();
				}
				
				break;
			}
			case DOWN_KEY://����C����һ�в˵� ��
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
			case BACK_KEY://����D�����أ�
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
			default:   //����ˢ��
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
 * @Description: �Ӳ����»ص�����
 */
void ClutterUpdateFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
		switch(key_value)
		{
			case OK_KEY://����A��ȷ�ϰ�����
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
			case UP_KEY://����B����һ�в˵���
			{
				if(MenuManager.cur_menu->selected == 0)
				{
					/*��ǰѡ���Ѿ�Ϊ��һ�� ���ز����д���*/
					break;
				}

				else
				{
					//clear_screen(); 
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
					//displaymenu();
				}
				
				break;
			}
			case DOWN_KEY://����C����һ�в˵� ��
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
			case BACK_KEY://����D�����أ�
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
			default:   //����ˢ��
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
 * @Description: ��ֵ���ûص�����
 */
void ThresholdSettingsFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	switch(key_value)
	{
		case OK_KEY://����A��ȷ�ϰ�����
		{
			/*OK��������*/
			if(set_ok_flag == 0)
			{
				set_ok_flag = 1;			//ѡ��״̬
			}
			else
			{
				set_ok_flag = 0;			//δѡ��״̬
			}
			break;
		}
		case DOWN_KEY://����B����һ�в˵���
		{
			/*�·���������*/
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
		case UP_KEY://����C����һ�в˵� ��
		{
			/*�Ϸ���������*/
			break;
		}	
		case BACK_KEY://����D�����أ�
		{	
			/*���ذ�������*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;
			MenuManager.menu_status = 1;
			goto_flag = 1;
			break;
		}
		default:   //����ˢ��
		{
			break;
		}
	}
	if(goto_flag == 1)
	{
		/*ֱ���˳�*/
		goto_flag = 0;
		return;
	}
	else if((key_value != 0) || (MenuManager.menu_status == 1))
	{
		/*ҳ����ʾ*/
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
 * @Description: �ֲ����ûص�����
 */
void LocalSettings1Func(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	uint8_t tmp_val = 0;
		switch(key_value)
		{
			case OK_KEY://����A��ȷ�ϰ�����
			{
				if(set_ok_flag == 0)
				{
					set_ok_flag = 1;			//ѡ��״̬
				}
				else
				{
					set_ok_flag = 0;			//δѡ��״̬
				}

				break;
			}
			case DOWN_KEY://����B����һ�в˵���
			{

				if(set_ok_flag == 0)
				{
					/*��һ��*/
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
			case UP_KEY://����C����һ�в˵� ��
			{
				/*��ʱ�����Ϸ�����*/
				break;
			}	
			case BACK_KEY://����D�����أ�
			{	
				//clear_screen(); 
				
				MenuManager.cur_menu = MenuManager.cur_menu->parent;
				MenuManager.menu_status = 1;
				goto_flag = 1;
				break;
			}
			default:   //����ˢ��
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
			case OK_KEY://����A��ȷ�ϰ�����
			{
				if(set_ok_flag == 0)
				{
					set_ok_flag = 1;			//ѡ��״̬
				}
				else
				{
					set_ok_flag = 0;			//δѡ��״̬
				}

				break;
			}
			case DOWN_KEY://����B����һ�в˵���
			{

				if(set_ok_flag == 0)
				{
					/*��һ��*/
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
			case UP_KEY://����C����һ�в˵� ��
			{
				/*��ʱ�����Ϸ�����*/
				break;
			}	
			case BACK_KEY://����D�����أ�
			{	
				//clear_screen(); 
				
				MenuManager.cur_menu = MenuManager.cur_menu->parent;
				MenuManager.menu_status = 1;
				goto_flag = 1;
				break;
			}
			default:   //����ˢ��
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
			case OK_KEY://����A��ȷ�ϰ�����
			{
				if(set_ok_flag == 0)
				{
					set_ok_flag = 1;			//ѡ��״̬
				}
				else
				{
					set_ok_flag = 0;			//δѡ��״̬
				}

				break;
			}
			case DOWN_KEY://����B����һ�в˵���
			{

				if(set_ok_flag == 0)
				{
					/*��һ��*/
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
			case UP_KEY://����C����һ�в˵� ��
			{
				/*��ʱ�����Ϸ�����*/
				break;
			}	
			case BACK_KEY://����D�����أ�
			{	
				//clear_screen(); 
				
				MenuManager.cur_menu = MenuManager.cur_menu->parent;
				MenuManager.menu_status = 1;
				goto_flag = 1;
				break;
			}
			default:   //����ˢ��
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


/*���ź������ʾ*/
void NoSignalOutputFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	switch(key_value)
	{
		case OK_KEY://����A��ȷ�ϰ�����
		{
			/*OK��������*/
			if(set_ok_flag == 0)
			{
				set_ok_flag = 1;			//ѡ��״̬
			}
			else
			{
				set_ok_flag = 0;			//δѡ��״̬
			}
			break;
		}
		case DOWN_KEY://����B����һ�в˵���
		{
			if(set_ok_flag == 0)		/*δѡ��*/
			{
			}
			else if (set_ok_flag == 1)	/*ѡ��*/
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
		case UP_KEY://����C����һ�в˵� ��
		{
			/*�Ϸ���������*/
			
			break;
		}	
		case BACK_KEY://����D�����أ�
		{	
			/*���ذ�������*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;
			MenuManager.menu_status = 1;
			goto_flag = 1;
			break;
		}
		default:   //����ˢ��
		{
			break;
		}
	}
	if(goto_flag == 1)
	{
		/*ֱ���˳�*/
		goto_flag = 0;
		return;
	}
	else if((key_value != 0) || (MenuManager.menu_status == 1))
	{
		/*ҳ����ʾ*/
		uchar tmp_ch = '*';
		volatile uint8_t tmp_i = 0;
		clear_screen();
		display_GB2312_string(1,8,((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name,0,0); 
		display_Signle_GB2312_string(3+(MenuManager.cur_menu->selected * 2),16+(8 * tmp_i),&tmp_ch,0,0);
		display_GB2312_string(3,32,"��ǰֵ",0,0); 
		display_GB2312_string(5,32,"������",0,0); 
		display_GB2312_string(7,32,"������",0,0); 
		MenuManager.menu_status = 0;
	}
}

void DampingTimeFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	switch(key_value)
	{
		case OK_KEY://����A��ȷ�ϰ�����
		{
			/*OK��������*/
			if(set_ok_flag == 0)
			{
				set_ok_flag = 1;			//ѡ��״̬
			}
			else
			{
				set_ok_flag = 0;			//δѡ��״̬
			}
			break;
		}
		case DOWN_KEY://����B����һ�в˵���
		{
			/*�·���������*/
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
		case UP_KEY://����C����һ�в˵� ��
		{
			/*�Ϸ���������*/
			break;
		}	
		case BACK_KEY://����D�����أ�
		{	
			/*���ذ�������*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;
			MenuManager.menu_status = 1;
			goto_flag = 1;
			break;
		}
		default:   //����ˢ��
		{
			break;
		}
	}
	if(goto_flag == 1)
	{
		/*ֱ���˳�*/
		goto_flag = 0;
		return;
	}
	else if((key_value != 0) || (MenuManager.menu_status == 1))
	{
		/*ҳ����ʾ*/
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
		case OK_KEY://����A��ȷ�ϰ�����
		{
			/*OK��������*/
			if(set_ok_flag == 0)
			{
				set_ok_flag = 1;			//ѡ��״̬
			}
			else
			{
				set_ok_flag = 0;			//δѡ��״̬
			}
			break;
		}
		case DOWN_KEY://����B����һ�в˵���
		{
			/*�·���������*/
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
		case UP_KEY://����C����һ�в˵� ��
		{
			/*�Ϸ���������*/
			break;
		}	
		case BACK_KEY://����D�����أ�
		{	
			/*���ذ�������*/
			MenuManager.cur_menu = MenuManager.cur_menu->parent;
			MenuManager.menu_status = 1;
			goto_flag = 1;
			break;
		}
		default:   //����ˢ��
		{
			break;
		}
	}
	if(goto_flag == 1)
	{
		/*ֱ���˳�*/
		goto_flag = 0;
		return;
	}
	else if((key_value != 0) || (MenuManager.menu_status == 1))
	{
		/*ҳ����ʾ*/
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
	/*��ʾ�����ʼ��*/
	AdvancedSetting.subMenus[0] = &ClutterUpdate;
	AdvancedSetting.subMenus[1] = &NoSignalOutput;
	AdvancedSetting.subMenus[2] = &DampingTime;
	AdvancedSetting.subMenus[3] = &DampingCoefficient;
	AdvancedSetting.parent = &ListMenu;			/*������û���ϼ�Ŀ¼*/
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

#include "ShowMenu.h"
#include <string.h>

extern Menu ShowMenu;


OPT Language_Val = {"����",0,2};
Menu Language= { 						
	"����\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 


F_VAL Curve_RangeMenu_Val[2] = {{"���߷�Χ[����](m)","000.00",0.00},{"���߷�Χ[����]","000.00",0.00}};
Menu Curve_RangeMenu = { 	//�ߵ�λ��������
	"���߷�Χ\0",					
	0,3,4,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 

OPT CompanyArea_Val = {"��λ",0,2};
Menu CompanyArea= { 						
	"��λ\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 

OPT Show_Contents_Val = {"��λ",0,2};
Menu Show_Contents= { 						
	"��ʾ����\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 

F_VAL Amplitude_Range_Val[2] = {{"��С(dB)","000",0.00},{"���(dB)","000",0.00}};
Menu Amplitude_Range= { 						
	"���ȷ�Χ\0",					
	0,3,3,0,0,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 


/*��ʾ����*/
void ShowFunc(uint8_t key_value)
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

/*����ѡ��*/
void LanguageFunc(uint8_t key_value)
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
		display_GB2312_string(1,8,(unsigned char *)(((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name),0,0); 
		display_Signle_GB2312_string(3+(MenuManager.cur_menu->selected * 2),16+(8 * tmp_i),&tmp_ch,0,0);
		display_GB2312_string(3,32,(unsigned char *)"����",0,0); 
		display_GB2312_string(5,32,(unsigned char *)"English",0,0); 
		MenuManager.menu_status = 0;
	}
}

void Curve_RangeMenuFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
		switch(key_value)
		{
			case OK_KEY://����A��ȷ�ϰ�����
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

//				if('0'> ((F_VAL *)(MenuManager.cur_menu->item_val)) ->char_val[0]||\
//					((F_VAL *)(MenuManager.cur_menu->item_val)) ->char_val[0] >= '9')	//�жϵ�ǰ�����Ƿ�Ϸ�
//				{
//					break;
//				}
				//clear_screen(); 
				if(set_ok_flag == 0)
				{
					/*��һ��*/
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
			display_GB2312_string(1,16,(unsigned char *)(((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name),0,0); 
			for(tmp_i  ; tmp_i < 7 * 1 ; tmp_i ++)
			{

				if(MenuManager.cur_menu->selected == tmp_i)
				{
					display_Signle_GB2312_string(3,16+(8 * tmp_i),(unsigned char *)&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],set_ok_flag,1);
				}
				else
				{
					display_Signle_GB2312_string(3,16+(8 * tmp_i),(unsigned char *)&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],0,0);
				}
			}
			
			display_GB2312_string(5,16,(unsigned char *)(((F_VAL *)(MenuManager.cur_menu->item_val))[1].val_name),0,0); 
			for(tmp_i  ; tmp_i < 7 * 2 ; tmp_i ++)
			{
				if(MenuManager.cur_menu->selected == tmp_i)
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 7)),(unsigned char *)&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 7],set_ok_flag,1);
				}
				else
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 7)),(unsigned char *)&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 7],0,0);
				}
			}
			MenuManager.menu_status = 0;
		}
}


/*��λѡ��*/
void CompanyAreaFunc(uint8_t key_value)
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
		display_GB2312_string(1,8,(unsigned char *)(((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name),0,0); 
		display_Signle_GB2312_string(3+(MenuManager.cur_menu->selected * 2),16+(8 * tmp_i),&tmp_ch,0,0);
		display_GB2312_string(3,32,"��(m)",0,0); 
		display_GB2312_string(5,32,"����(mm)",0,0); 
		display_GB2312_string(5,32,"Ӣ��(tt)",0,0); 
		MenuManager.menu_status = 0;
	}
}

/*��ʾ����*/
void Show_Contents_Func(uint8_t key_value)
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
		display_GB2312_string(1,8,(unsigned char *)(((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name),0,0); 
		display_Signle_GB2312_string(3+(MenuManager.cur_menu->selected * 2),16+(8 * tmp_i),&tmp_ch,0,0);
		display_GB2312_string(3,32,(unsigned char *)"�ϸ�",0,0); 
		display_GB2312_string(5,32,(unsigned char *)"�ո�",0,0); 
		MenuManager.menu_status = 0;
	}
}

/*���ȷ�Χ*/
void Amplitude_Range_Func(uint8_t key_value)
{
	uint8_t goto_flag = 0;
		switch(key_value)
		{
			case OK_KEY://����A��ȷ�ϰ�����
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

//				if('0'> ((F_VAL *)(MenuManager.cur_menu->item_val)) ->char_val[0]||\
//					((F_VAL *)(MenuManager.cur_menu->item_val)) ->char_val[0] >= '9')	//�жϵ�ǰ�����Ƿ�Ϸ�
//				{
//					break;
//				}
				//clear_screen(); 
				if(set_ok_flag == 0)
				{
					/*��һ��*/
					//if(MenuManager.cur_menu->selected >= 0 && MenuManager.cur_menu->selected < (2 * 7 -1))
					{
						if(MenuManager.cur_menu->selected >=  (2 * 3 -1))
						{
							MenuManager.cur_menu->selected = 0;
						}
						else
						{
							MenuManager.cur_menu->selected++;
						}
						if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 3 ].char_val[MenuManager.cur_menu->selected % 3] == '.')
							MenuManager.cur_menu->selected++;
					}

				}
				else if (set_ok_flag == 1)
				{
					((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 3].char_val[MenuManager.cur_menu->selected % 3]++;
					if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 3].char_val[MenuManager.cur_menu->selected % 3] < '0')
					{
						((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 3].char_val[MenuManager.cur_menu->selected % 3] ='9';
					}
					else if(((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 3].char_val[MenuManager.cur_menu->selected % 3] > '9' )
					{
						 ((F_VAL *)(MenuManager.cur_menu->item_val))[MenuManager.cur_menu->selected / 3].char_val[MenuManager.cur_menu->selected % 3] ='0';
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
			display_GB2312_string(1,16,(unsigned char *)((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name,0,0); 
			for(tmp_i  ; tmp_i < 3 * 1 ; tmp_i ++)
			{

				if(MenuManager.cur_menu->selected == tmp_i)
				{
					display_Signle_GB2312_string(3,16+(8 * tmp_i),(unsigned char *)&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],set_ok_flag,1);
				}
				else
				{
					display_Signle_GB2312_string(3,16+(8 * tmp_i),(unsigned char *)&((F_VAL *)(MenuManager.cur_menu->item_val))[0].char_val[tmp_i],0,0);
				}
			}
			
			display_GB2312_string(5,16,(unsigned char *)((F_VAL *)(MenuManager.cur_menu->item_val))[1].val_name,0,0); 
			for(tmp_i  ; tmp_i < 3 * 2 ; tmp_i ++)
			{
				if(MenuManager.cur_menu->selected == tmp_i)
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 3)),(unsigned char *)&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 3],set_ok_flag,1);
				}
				else
				{
					display_Signle_GB2312_string(7,16+(8 * (tmp_i - 3)),(unsigned char *)&((F_VAL *)(MenuManager.cur_menu->item_val))[1].char_val[tmp_i - 3],0,0);
				}
			}
			MenuManager.menu_status = 0;
		}
}

void ShowMenuInit(void)
{
	/*��ʾ�����ʼ��*/
	ShowMenu.subMenus[0] = &Language;
	
	
	ShowMenu.subMenus[1] = &Curve_RangeMenu;
	ShowMenu.subMenus[2] = &CompanyArea;
	ShowMenu.subMenus[3] = &Show_Contents;
	ShowMenu.subMenus[4] = &Amplitude_Range;
	ShowMenu.parent = &ListMenu;			/*������û���ϼ�Ŀ¼*/
	ShowMenu.func = ShowFunc;
	
	/*����*/
	Language.item_val = &Language_Val;
	Language.func = &LanguageFunc;
	Language.parent = &ShowMenu;
	
	/*���߷�Χ*/
	Curve_RangeMenu.item_val = &Curve_RangeMenu_Val;
	Curve_RangeMenu.func = &Curve_RangeMenuFunc;
	Curve_RangeMenu.parent = &ShowMenu;
	
	/*��λ*/
	CompanyArea.item_val = &CompanyArea_Val;
	CompanyArea.func = &CompanyAreaFunc;
	CompanyArea.parent = &ShowMenu;
	
	/*��ʾ����*/
	Show_Contents.item_val = &Show_Contents_Val;
	Show_Contents.func = &Show_Contents_Func;
	Show_Contents.parent = &ShowMenu;
	
	/*���ȷ�Χ*/
	Amplitude_Range.item_val = &Amplitude_Range_Val;
	Amplitude_Range.func = &Amplitude_Range_Func;
	Amplitude_Range.parent = &ShowMenu;
}

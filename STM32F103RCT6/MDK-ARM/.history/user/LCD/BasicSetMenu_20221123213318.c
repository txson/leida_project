/*
 * @Date: 2022-11-16 22:46:21
 * @LastEditTime: 2022-11-23 21:33:03
 * @LastEditors: herod
 * @Description: �������ý���Դ�ļ�
 * @FilePath: \MDK-ARM\user\LCD\BasicSetMenu.c
 * XXXX
 */
#include "BasicSetMenu.h"
#include <string.h>
float HighlowAdjustment = 0.01;
uint8_t HighlowAdjustmentBuf[7] = {0};
extern Menu BasicSetMenu;

//Menu HighlowAdjustmentBit0 = {		//��λ
//	&HighlowAdjustmentBuf[0],
//	0,0,0,0,1,
//};
//Menu HighlowAdjustmentBit1 = {		//ʮλ
//	&HighlowAdjustmentBuf[1],
//	0,0,0,0,1,
//};
//Menu HighlowAdjustmentBit2 = {		//��λ
//	&HighlowAdjustmentBuf[2],
//	0,0,0,0,1,
//};
//Menu HighlowAdjustmentBit3 = {		//С�����һλ
//	&HighlowAdjustmentBuf[3],
//	0,0,0,0,1,
//};
//Menu HighlowAdjustmentBit4 = {		//С�������λ
//	&HighlowAdjustmentBuf[3],
//	0,0,0,0,1,
//};
//Menu HighlowAdjustmentBit5 = {		//С�������λ
//	&HighlowAdjustmentBuf[3],
//	0,0,0,0,1,
//};

F_VAL Range_Val = {"����(m)","000.000",0.00};
Menu Range= { 						
	"����\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 
/*�ߵ�λ����*/
F_VAL HighlowAdjetMenu_Val[2] = {{"��λ����(m)","000.000",30.00},{"��λ����(m)","000.000",2.00}};
Menu HighlowAdjetMenu = { 	//�ߵ�λ��������
	"�ߵ�λ����\0",					
	0,3,4,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 

F_VAL BlindArea_Val = {"ä��(m)","00.000",0.00};
Menu BlindArea= { 						
	"ä��\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 

F_VAL Distance_Val = {"����ƫִ(m)","+0.000",0.00};
Menu Distance_Paranoia= { 						
	"����ƫ��\0",					
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 

OPT Materia_Val = {"��������",0,3};
Menu MaterialProperties= { 						
	"��������\0",					
	0,3,3,0,0,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 


OPT CurrentOutPut_Val = {"�������",0,2};
Menu CurrentOutPut= { 						
	"�������\0",					
	0,2,2,0,0,						//Ĭ����ʾ0-3��ܹ�8���ǰѡ��0�
}; 
OPT WaveFollowing_Val = {"��������",0,2};
Menu WaveFollowingSet = { 
	"��������\0",
	0,2,2,0,0,						//Ĭ����ʾ0-3��ܹ�4���ǰѡ��0�	
}; 

F_VAL Gain_Val = {"����ƫִ(m)","00",0.00};
Menu GainSet = { 
	"��������\0",
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�4���ǰѡ��0�	
}; 

F_VAL WNT_Set_val[2] = {{"���ٿ��(m)","0.00",0.00},{"����ʱ��(s)","0000",0.00}};
Menu WNTSet = { 					/*��Ⱥ�ʱ�����ý���*/
	"��Ⱥ�ʱ��\0",
	0,3,3,0,1,						//Ĭ����ʾ0-3��ܹ�4���ǰѡ��0�	
}; 



/**
 * @Date: 2022-11-23 21:26:01
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: �������ý��溯���ص�
 */
void BasicSetFunc(uint8_t key_value)
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




uint8_t set_ok_flag = 0;
/**
 * @Date: 2022-11-23 21:27:40
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: �ߵ�λ��������ص�
 */
void HighlowAdjFunc(uint8_t key_value)
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
 * @Description: ���̽���ص�
 */
void RangeFunc(uint8_t key_value)
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
 * @Description: ä��������ʾ�ص�
 */
void BlindFunc(uint8_t key_value)
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
				/*�·���������*/
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
				/*ҳ����ʾ*/
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
 * @Description: ����ƫִ����ص�
 */
void DistanceFunc(uint8_t key_value)
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
				/*�·���������*/
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
 * @Description: �������ʽ���ص�
 */
void MaterialFunc(uint8_t key_value)
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
		display_GB2312_string(3,32,"Һ��",0,0); 
		display_GB2312_string(5,32,"����",0,0); 
		display_GB2312_string(7,32,"����",0,0); 
		MenuManager.menu_status = 0;
	}
}


/**
 * @Date: 2022-11-23 21:30:48
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: �����������ص�
 */
void CurrentOutPuFunc(uint8_t key_value)
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
 * @Description: �������ý���ص�
 */
void WaveFollowingFunc(uint8_t key_value)
{
	uint8_t goto_flag = 0;
	switch(key_value)
	{
		case OK_KEY://����A��ȷ�ϰ�����
		{
			/*OK��������*/
			MenuManager.cur_menu = MenuManager.cur_menu->subMenus[0];
			MenuManager.menu_status = 1;

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
		display_GB2312_string(1,8,((F_VAL *)(MenuManager.cur_menu->item_val))[0].val_name,0,0); 
		display_Signle_GB2312_string(3+(MenuManager.cur_menu->selected * 2),16+(8 * tmp_i),&tmp_ch,0,0);
		display_GB2312_string(3,32,"��",0,0); 
		display_GB2312_string(5,32,"��",0,0); 
		MenuManager.menu_status = 0;
	}
}

/**
 * @Date: 2022-11-23 21:31:41
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: ��Ⱥ�ʱ�����ý���ص�
 */
void WNTSetFunc(uint8_t key_value)
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

/*����ƫִ������ʾ*/
/**
 * @Date: 2022-11-23 21:32:02
 * @LastEditors: herod
 * @param {uint8_t} key_value
 * @Description: �������ý���ص�
 */
void GainFunc(uint8_t key_value)
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
				/*�·���������*/
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
				/*ҳ����ʾ*/
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
 * @Description: �������ý����ʼ��
 */
void BasicSetMenuInit(void)
{
	/*�������ý����ʼ��*/
	BasicSetMenu.subMenus[0] = &Range;
	
	//memset(HighlowAdjetMenu_Val,0,(sizeof(HighlowAdjetMenu_Val) * 2));
	
	
	BasicSetMenu.subMenus[1] = &HighlowAdjetMenu;
	BasicSetMenu.subMenus[2] = &BlindArea;
	BasicSetMenu.subMenus[3] = &Distance_Paranoia;
	BasicSetMenu.subMenus[4] = &MaterialProperties;
	BasicSetMenu.subMenus[5] = &CurrentOutPut;
	BasicSetMenu.subMenus[6] = &WaveFollowingSet;
	BasicSetMenu.subMenus[7] = &GainSet;
	BasicSetMenu.parent = &ListMenu;			/*������û���ϼ�Ŀ¼*/
	BasicSetMenu.func = BasicSetFunc;
	
//	/*�����������*/
//	GainSet.subMenus[0]
	
	/*�ߵ�λ����ҳ��*/
	HighlowAdjetMenu.item_val = &HighlowAdjetMenu_Val;
	HighlowAdjetMenu.func = HighlowAdjFunc;
	HighlowAdjetMenu.parent = &BasicSetMenu;
	
	/*����ҳ��*/
	Range.item_val = &Range_Val;
	Range.func = RangeFunc;
	Range.parent = &BasicSetMenu;
	
	/*ä��ҳ��*/
	BlindArea.item_val = &BlindArea_Val;
	BlindArea.func = BlindFunc;
	BlindArea.parent = &BasicSetMenu;
	
	/*����ƫִҳ��*/
	Distance_Paranoia.item_val = &Distance_Val;
	Distance_Paranoia.func = DistanceFunc;
	Distance_Paranoia.parent = &BasicSetMenu;
	
	/*��������ҳ��*/
	MaterialProperties.item_val = &Materia_Val;		
	MaterialProperties.func = MaterialFunc;
	MaterialProperties.parent = &BasicSetMenu;
	
	/*�������ҳ��*/
	CurrentOutPut.item_val = &CurrentOutPut_Val;		
	CurrentOutPut.func = CurrentOutPuFunc;
	CurrentOutPut.parent = &BasicSetMenu;
	
	/*��������ҳ��*/
	WaveFollowingSet.item_val = &WaveFollowing_Val;		
	WaveFollowingSet.func = WaveFollowingFunc;
	WaveFollowingSet.parent = &BasicSetMenu;
	WaveFollowingSet.subMenus[0] = &WNTSet;
	
	/*������Ⱥ�ʱ������*/
	WNTSet.item_val = &WNT_Set_val;
	WNTSet.func = WNTSetFunc;
	WNTSet.parent = &WaveFollowingSet;
	
	/*��������*/
	GainSet.item_val = &Gain_Val;		
	GainSet.func = GainFunc;
	GainSet.parent = &BasicSetMenu;
}

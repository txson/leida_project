#ifndef __VIEW_MGR_H
#define __VIEW_MGR_H
#include <stdint.h>  
#include "stdio.h"
#include "string.h"
#include "lcd12864.h"
#include "stdio.h"
#include "key.h"
#include <stdlib.h>
#include <BasicSetMenu.h>
#include "ShowMenu.h"
#include "advanced_setting.h"
#include "MainMenu.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define MENUS_MAX_NUM 17


//void (**func(uint8_t key_value))();
/*����ṹ��*/
typedef struct menu
{
	char *menu_name; 					 	//��ǰ��������
	uint8_t range_from,range_to; 			//��ǰѡ����ʼ����������
	uint8_t itemCount;						//��Ŀ����
	uint8_t selected;						//��ǰѡ����
	uint8_t view_type;						//��ǰ�����������  0:�б����  1:��ʾ
	void *  item_val;								//��ֵָ��
	struct menu *subMenus[MENUS_MAX_NUM];	//�Ӳ˵�  ����д�����
	struct menu *parent;					//�ϼ��˵����������˵���Ϊnull
	void (*func) (uint8_t key_value);			//��Ӧ����ĺ���
}Menu; 										//ÿһ������Ľṹ��

typedef struct float_val {
	char val_name[32];				//��������
	char char_val[16];			//����ʹ�������ʾ
	float float_val;			//ʹ�ø�������ʾ
}F_VAL;

typedef struct option_list {
	char val_name[32];		//��������
	uint8_t val;			//����ʹ�������ʾ		ѡ���ѡ��
	uint8_t max_item;
}OPT;

/*�������ṹ��*/
typedef struct 
{
	Menu *cur_menu;//
	uint8_t menu_status;				//1Ϊ��һ�ν���ҳ��   0Ϊҳ���Ѿ���ѭ������
	uint8_t DataSelectionStatus;
} MenuMgr;

extern MenuMgr MenuManager;
extern Menu MainMenu;

/*���н����ʼ������*/
void meunu_init(void);

/***********************************************************************************************
*������ ��		displaymenu
*������������ ����ʾ�б����ͽ���
*�������� ��	��
*��������ֵ ��	��
*���� ��		
*������������ ��2022-08-06
*�����޸����� ��
*�޸��� ��
*�޸�ԭ�� ��	
*�汾 ��		v0.1
*��ʷ�汾 ��
***********************************************************************************************/
void displaymenu();

/***********************************************************************************************
*������ ��		��������ʾ
*������������ ����ʾ�б����ͽ���
*�������� ��	��
*��������ֵ ��	��
*���� ��		
*������������ ��2022-08-06
*�����޸����� ��
*�޸��� ��
*�޸�ԭ�� ��	
*�汾 ��		v0.1
*��ʷ�汾 ��
***********************************************************************************************/
void data_display(unsigned char page,unsigned char column,uint8_t *data_char,uint8_t reverse,uint8_t select);

/*�������ý��溯��*/
//void BasicSetFunc(uint8_t key_value);
//void MainMenuFunc(uint8_t key_value);
//��ʾ�����ַ�
//void data_display(uchar page,uchar column,uint8_t *text,uint8_t reverse,uint8_t select);
#ifdef __cplusplus
}
#endif
#endif

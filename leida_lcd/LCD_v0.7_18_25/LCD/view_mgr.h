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
/*界面结构体*/
typedef struct menu
{
	char *menu_name; 					 	//当前界面名称
	uint8_t range_from,range_to; 			//当前选择的项开始及结束符号
	uint8_t itemCount;						//项目总数
	uint8_t selected;						//当前选择项
	uint8_t view_type;						//当前界面界面类型  0:列表界面  1:显示
	void *  item_val;								//数值指针
	struct menu *subMenus[MENUS_MAX_NUM];	//子菜单  这里写到最大
	struct menu *parent;					//上级菜单，若是主菜单则为null
	void (*func) (uint8_t key_value);			//对应界面的函数
}Menu; 										//每一个界面的结构体

typedef struct float_val {
	char val_name[32];				//数据名称
	char char_val[16];			//数据使用数组表示
	float float_val;			//使用浮点数表示
}F_VAL;

typedef struct option_list {
	char val_name[32];		//数据名称
	uint8_t val;			//数据使用数组表示		选择的选项
	uint8_t max_item;
}OPT;

/*界面管理结构体*/
typedef struct 
{
	Menu *cur_menu;//
	uint8_t menu_status;				//1为第一次进入页面   0为页面已经在循环运行
	uint8_t DataSelectionStatus;
} MenuMgr;

extern MenuMgr MenuManager;
extern Menu MainMenu;

/*所有界面初始化函数*/
void meunu_init(void);

/***********************************************************************************************
*函数名 ：		displaymenu
*函数功能描述 ：显示列表类型界面
*函数参数 ：	无
*函数返回值 ：	无
*作者 ：		
*函数创建日期 ：2022-08-06
*函数修改日期 ：
*修改人 ：
*修改原因 ：	
*版本 ：		v0.1
*历史版本 ：
***********************************************************************************************/
void displaymenu();

/***********************************************************************************************
*函数名 ：		浮点数显示
*函数功能描述 ：显示列表类型界面
*函数参数 ：	无
*函数返回值 ：	无
*作者 ：		
*函数创建日期 ：2022-08-06
*函数修改日期 ：
*修改人 ：
*修改原因 ：	
*版本 ：		v0.1
*历史版本 ：
***********************************************************************************************/
void data_display(unsigned char page,unsigned char column,uint8_t *data_char,uint8_t reverse,uint8_t select);

/*基本设置界面函数*/
//void BasicSetFunc(uint8_t key_value);
//void MainMenuFunc(uint8_t key_value);
//显示单独字符
//void data_display(uchar page,uchar column,uint8_t *text,uint8_t reverse,uint8_t select);
#ifdef __cplusplus
}
#endif
#endif

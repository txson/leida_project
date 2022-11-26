#ifndef __MAIN_MENU_H
#define __MAIN_MENU_H
#include <stdint.h>  
#include "stdio.h"
#include "view_mgr.h"
#include "string.h"
#include "lcd12864.h"
#include "stdio.h"
#include "key.h"
#include <stdlib.h>

#ifdef __cplusplus
 extern "C" {
#endif

extern struct menu ListMenu;

/*�������ʼ��*/
void MainMeunuInit(void);

void ListMenuFunc(uint8_t key_value);

/*�������ʼ��*/
void main_page_init(void);

/*������������ʾ*/
void show_main_page(char* data,int len);

/*�����¶���ʾ*/
void update_sensor_temp(void);

/*���´�������ֵ��ʾ*/
void update_sensor_val(char* data,int len);

/*���½������Ͱٷֱ���ʾ*/
void update_sensor_progress(char* data,int len);

/*��ʾ���ν���*/
void show_boxin_page(char* data,int len);

void update_tempval(void);
#ifdef __cplusplus
}
#endif
#endif


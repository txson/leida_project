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

/*主界面初始化*/
void MainMeunuInit(void);

void ListMenuFunc(uint8_t key_value);

/*主界面初始化*/
void main_page_init(void);

/*主界面内容显示*/
void show_main_page(char* out_data,int len);

/*更新温度显示*/
void update_sensor_temp(uint16_t Current_Temperature);

/*更新传感器数值显示*/
void update_sensor_val(char* out_data,int len);

/*更新进度条和百分比显示*/
void update_sensor_progress(char* out_data,int len);

/*显示波形界面*/
void show_boxin_page(char* out_data,int len);
#ifdef __cplusplus
}
#endif
#endif


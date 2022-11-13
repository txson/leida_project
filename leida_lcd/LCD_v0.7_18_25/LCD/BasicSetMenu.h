#ifndef _BASIC_SET_MENU_H_
#define _BASIC_SET_MENU_H_
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

extern struct menu BasicSetMenu;

/*基本设置界面初始化*/
void BasicSetMenuInit(void);

void BasicSetFunc(uint8_t key_value);
void HighlowAdjFunc(uint8_t key_value);
void HighlowAdjMenuMenuInit(void);
void show_main_page(char* out_data,int len);
#ifdef __cplusplus
}
#endif
#endif


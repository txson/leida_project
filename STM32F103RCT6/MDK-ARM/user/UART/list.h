#ifndef __LIST_H__
#define __LIST_H__

typedef struct 
{
	unsigned int in_data;/* 数据入队下标 */
	unsigned int out_data;/* 数据出队下标 */ 
	unsigned int cur_depth;/* 当前深度,缓存的帧数 */ 
	unsigned int max_depth;/* 最大帧数，能够缓存的最大帧数 */ 
	unsigned int max_len; /* 缓存单帧数据的最大长度 */ 
	unsigned char over_flow; /* 缓存满，溢出标志位 */ 
	char *data_buf; /* 数据缓冲数据 */ 
	int *cnt_buf; /* 数据长度缓冲数组 */ 
} List;

void list_init(List *list, char* data_buf, int* cnt_buf, int max_len, int max_depth);
int list_in(List *list, char *data, int len);
int list_out(List *list, char *out_data);

#endif 

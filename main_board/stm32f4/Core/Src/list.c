#include "list.h"
#include <stdio.h>
#include <string.h>

void list_init(List *list, char* data_buf, int* cnt_buf, int max_len, int max_depth)
{
	if (list == NULL || data_buf == NULL || cnt_buf == NULL)
		return ;
		
	//printf("max_len:%d max_buf:%d \r\n", max_len, max_depth);	
	
	memset(list, 0, sizeof(List));
	list->data_buf = data_buf;
	list->cnt_buf  = cnt_buf;
	list->max_depth = max_depth;
	list->max_len = max_len;
	list->in_data = 0;
	list->out_data = 0;
	list->cur_depth = 0;
}

int list_in(List *list, char *data, int len)
{
	//printf("list in:%s  \r\n", data);
	//printf("cur_depth:%d, in_data:%d \r\n", list->cur_depth, list->in_data);
	
	/* 判断缓冲是否满啦 */
	if (list->cur_depth + 1 >= list->max_depth)
	{
		//printf("over flow \r\n");
		list->over_flow = 1;
		return -1;
	}
	if (len > list->max_len)
	{
		/* 缓冲过小 */
		//printf("data too long \r\n");
		return -1;
	}
	
	/* 数据入队 */ 
	memcpy((char*)&list->data_buf[list->in_data * list->max_len], data, len);
	list->cnt_buf[list->in_data] = len;	
	
	/* 标志更新 */ 
	list->in_data ++;
	list->in_data = list->in_data % list->max_depth;
	list->cur_depth ++;
	
	return 0;
}

int list_out(List *list, char *out_data)
{
	int len = 0; 
	 
	/* 判断队列是否有缓冲数据 */ 
	if (list->cur_depth == 0)
	{
		//printf("no data \r\n");
	 	return 0;
	}
	 
	/* 数据出队 */ 
	//printf("list out:%s ", (char*)&(list->data_buf[list->out_data * list->max_len]));
	len = list->cnt_buf[list->out_data];
	memcpy(out_data, (char*)&(list->data_buf[list->out_data * list->max_len]), len);
	 
	
	/* 标志位更新,数据清零 */ 
	memset((char*)&(list->data_buf[list->out_data * list->max_len]), 0, list->max_len);
	list->cnt_buf[list->out_data] = 0;
	list->cur_depth --;
	list->out_data ++;
	list->out_data = list->out_data % list->max_depth;	
	
	return len;
}

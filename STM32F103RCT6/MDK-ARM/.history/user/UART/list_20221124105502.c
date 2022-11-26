#include "list.h"
#include <stdio.h>
#include <string.h>

/**
 * @Date: 2022-11-24 10:54:55
 * @LastEditors: herod
 * @param {List} *list
 * @param {char*} data_buf
 * @param {int*} cnt_buf
 * @param {int} max_len
 * @param {int} max_depth
 * @Description: 消息队列初始化
 */
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
	
	/* �жϻ����Ƿ����� */
	if (list->cur_depth + 1 >= list->max_depth)
	{
		//printf("over flow \r\n");
		list->over_flow = 1;
		return -1;
	}
	if (len > list->max_len)
	{
		/* �����С */
		//printf("data too long \r\n");
		return -1;
	}
	
	/* ������� */ 
	memcpy((char*)&list->data_buf[list->in_data * list->max_len], data, len);
	list->cnt_buf[list->in_data] = len;	
	
	/* ��־���� */ 
	list->in_data ++;
	list->in_data = list->in_data % list->max_depth;
	list->cur_depth ++;
	
	return 0;
}

int list_out(List *list, char *out_data)
{
	int len = 0; 
	 
	/* �ж϶����Ƿ��л������� */ 
	if (list->cur_depth == 0)
	{
		//printf("no data \r\n");
	 	return 0;
	}
	 
	/* ���ݳ��� */ 
	//printf("list out:%s ", (char*)&(list->data_buf[list->out_data * list->max_len]));
	len = list->cnt_buf[list->out_data];
	memcpy(out_data, (char*)&(list->data_buf[list->out_data * list->max_len]), len);
	 
	
	/* ��־λ����,�������� */ 
	memset((char*)&(list->data_buf[list->out_data * list->max_len]), 0, list->max_len);
	list->cnt_buf[list->out_data] = 0;
	list->cur_depth --;
	list->out_data ++;
	list->out_data = list->out_data % list->max_depth;	
	
	return len;
}

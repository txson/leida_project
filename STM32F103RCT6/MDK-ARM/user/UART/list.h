#ifndef __LIST_H__
#define __LIST_H__

typedef struct 
{
	unsigned int in_data;/* ��������±� */
	unsigned int out_data;/* ���ݳ����±� */ 
	unsigned int cur_depth;/* ��ǰ���,�����֡�� */ 
	unsigned int max_depth;/* ���֡�����ܹ���������֡�� */ 
	unsigned int max_len; /* ���浥֡���ݵ���󳤶� */ 
	unsigned char over_flow; /* �������������־λ */ 
	char *data_buf; /* ���ݻ������� */ 
	int *cnt_buf; /* ���ݳ��Ȼ������� */ 
} List;

void list_init(List *list, char* data_buf, int* cnt_buf, int max_len, int max_depth);
int list_in(List *list, char *data, int len);
int list_out(List *list, char *out_data);

#endif 

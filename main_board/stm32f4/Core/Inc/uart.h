#ifndef __UART_H__
#define __UART_H__

/* ����������� */
#define FIFO_DEPTH	      6 	
/* ���λ������󳤶� */ 
#define UART5_DATA_LEN    256

void uart5_init(void);
void uart5_start_dma(void);
void uart5_process_data(void);

#endif

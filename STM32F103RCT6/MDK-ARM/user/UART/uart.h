#ifndef __UART_H__
#define __UART_H__

/* ����������� */
#define FIFO_DEPTH	      12 	
/* ���λ������󳤶� */ 
#define UART1_DATA_LEN    1024

extern void uart_init(void);
extern void uart_start_dma(void);
extern int uart_process_data(void);

#endif

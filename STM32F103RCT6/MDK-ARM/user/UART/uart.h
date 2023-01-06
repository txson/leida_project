#ifndef __UART_H__
#define __UART_H__

/* 缓冲的最大深度 */
#define FIFO_DEPTH	      12 	
/* 单次缓冲的最大长度 */ 
#define UART1_DATA_LEN    1024
#define SEND_DATA_MAX_LEN    128

//extern uint8_t uart_send_buf[SEND_DATA_MAX_LEN];



//#define GEBUG 

extern void uart_init(void);
extern void uart_start_dma(void);
extern int uart_process_data(void);

#endif

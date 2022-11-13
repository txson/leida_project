#ifndef __UART_H__
#define __UART_H__

/* 缓冲的最大深度 */
#define FIFO_DEPTH	      6 	
/* 单次缓冲的最大长度 */ 
#define UART5_DATA_LEN    256

void uart5_init(void);
void uart5_start_dma(void);
void uart5_process_data(void);

#endif

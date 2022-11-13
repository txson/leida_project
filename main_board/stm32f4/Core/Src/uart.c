#include "list.h"
#include "uart.h"
#include "stm32f4xx_hal.h"
#include <string.h>

extern UART_HandleTypeDef huart5;

/* 初始化串口一缓冲内存 */
uint8_t g_uart5_dma_buf[UART5_DATA_LEN] = {0};
static char uart5_data_buf[FIFO_DEPTH * UART5_DATA_LEN] = {0};
static int uart5_len_buf[FIFO_DEPTH] = {0};
static List uart5_list = {0};


/* 串口5初始化函数 */
void uart5_init(void)
{
	list_init(&uart5_list, uart5_data_buf, uart5_len_buf, UART5_DATA_LEN, FIFO_DEPTH);
}

/* 将串口的数据缓冲内存 */
static void uart5_receive_idle(UART_HandleTypeDef* huart, List *list, uint8_t *dma_buf)
{
    int len = 0;
    
    len = list->max_len - huart->hdmarx->Instance->NDTR;
    list_in(&uart5_list, (char*)dma_buf, len);
}

/* 在前台处理数据 */
void uart5_process_data(void)
{
    int len = 0;
    uint8_t out_data[UART5_DATA_LEN] = {0};
	
    /* 数据出队 */
    len = list_out(&uart5_list, (char *)out_data);
	
    /* 数据处理 */
    if (0 != len)
    {   

    }    
}

/* 代码首次开启dma传输 */
void uart5_start_dma(void)
{
    HAL_UART_Receive_DMA(&huart5, g_uart5_dma_buf, UART5_DATA_LEN);
}

/* 串口5中断处理函数 */
void UART5_IRQHandler(void)
{
    /* 处理中断溢出 */
	if(__HAL_UART_GET_FLAG(&huart5,UART_FLAG_ORE) != RESET) 
    {
        __HAL_UART_CLEAR_OREFLAG(&huart5);
        memset(&g_uart5_dma_buf, 0, UART5_DATA_LEN);
        HAL_UART_Receive_DMA(&huart5, g_uart5_dma_buf, UART5_DATA_LEN);
    }
    /* 处理空闲中断 */
    if((__HAL_UART_GET_FLAG(&huart5,UART_FLAG_IDLE) != RESET))
    { 
        __HAL_UART_CLEAR_IDLEFLAG(&huart5);
        HAL_UART_DMAStop(&huart5);
        uart5_receive_idle(&huart5, &uart5_list, g_uart5_dma_buf);
        HAL_UART_DMAResume(&huart5);
        __HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE);
        memset(&g_uart5_dma_buf, 0, UART5_DATA_LEN);
        HAL_UART_Receive_DMA(&huart5, g_uart5_dma_buf, UART5_DATA_LEN);
    } 
    
    HAL_UART_IRQHandler(&huart5);
}


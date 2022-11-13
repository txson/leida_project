#include "list.h"
#include "uart.h"
#include "stm32f1xx_hal.h"
#include "main.h"
#include "MainMenu.h"
extern uint32_t cnt_start;
extern UART_HandleTypeDef huart1;
extern uint8_t time_out_cnt;
//extern UART_HandleTypeDef huart6;

/* 初始化串口一缓冲内存 */
uint8_t g_uart_dma_buf[UART1_DATA_LEN] = {0};
static char uart_data_buf[FIFO_DEPTH * UART1_DATA_LEN] = {0};
static int uart_len_buf[FIFO_DEPTH] = {0};
static List uart_list = {0};

/* 串口5初始化函数 */
void uart_init(void)
{
	list_init(&uart_list, uart_data_buf, uart_len_buf, UART1_DATA_LEN, FIFO_DEPTH);
}

/* 将串口的数据缓冲内存 */
static void uart_receive_idle(UART_HandleTypeDef* huart, List *list, uint8_t *dma_buf)
{
    int len = 0;
    
    len = list->max_len - huart->hdmarx->Instance->CNDTR;  
    list_in(&uart_list, (char*)dma_buf, len);
}

uint8_t out_data[UART1_DATA_LEN] = {0};


/* 在前台处理数据 */
int uart_process_data(void)
{
    int len = 0;
    
    /* 数据出队 */
    len = list_out(&uart_list, (char *)out_data);
    
    /* 数据处理 */
	if(!(strcmp(MenuManager.cur_menu->menu_name,"主界面")))
	{
		if (!(strncmp("dis:",(char *)out_data,4)) && 0 != len)
		{   
			show_main_page((char *)out_data ,len);
			cnt_start = HAL_GetTick();
			time_out_cnt = 0;
			display_GB2312_string(7,58,"Sensor OK",0,0);	
		} 
	}	
	else if(!(strcmp(MenuManager.cur_menu->menu_name,"波形界面")))
	{
		show_boxin_page();
	}
}

/* 代码首次开启dma传输 */
void uart_start_dma(void)
{
    HAL_UART_Receive_DMA(&huart1, g_uart_dma_buf, UART1_DATA_LEN);
}


void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

	
	//    /* 处理中断溢出 */
	if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_ORE) != RESET) 
    {
        __HAL_UART_CLEAR_OREFLAG(&huart1);
        HAL_UART_Receive_DMA(&huart1, g_uart_dma_buf, UART1_DATA_LEN);
    }
  /* USER CODE BEGIN USART1_IRQn 1 */
	if(RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))   //判断是否是空闲中断
	{

		__HAL_UART_CLEAR_IDLEFLAG(&huart1);                       //清除空闲中断标志
		HAL_UART_DMAStop(&huart1);                                //停止本次DMA传输    
		
		uart_receive_idle(&huart1, &uart_list, g_uart_dma_buf);
		//huart1.RxXferSize = 255 - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);   //计算接收到的数据长度
		
		HAL_UART_DMAResume(&huart1);
		
		__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
		//HAL_UART_Transmit(&huart1,receive_buff,data_length,0x200);             //测试函数：将接收到的数据打印出去
		//memset(receive_buff,0,data_length);                                            
		//uart1_stat = 1;								//接收到数据准备好
		//HAL_UART_Receive_DMA(&huart1, (uint8_t*)receive_buff, 100);                      //清除空闲中断标志		
		HAL_UART_Receive_DMA(&huart1, g_uart_dma_buf, UART1_DATA_LEN);
	}
	HAL_UART_IRQHandler(&huart1);
  /* USER CODE END USART1_IRQn 0 */
  
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}
///* 串口5中断处理函数 */
//void UART5_IRQHandler(void)
//{
//    /* 处理中断溢出 */
//	if(__HAL_UART_GET_FLAG(&huart5,UART_FLAG_ORE) != RESET) 
//    {
//        __HAL_UART_CLEAR_OREFLAG(&huart5);
//        HAL_UART_Receive_DMA(&huart5, g_uart_dma_buf, UART1_DATA_LEN);
//    }
//    /* 处理空闲中断 */
//    if((__HAL_UART_GET_FLAG(&huart5,UART_FLAG_IDLE) != RESET))
//    { 
//        __HAL_UART_CLEAR_IDLEFLAG(&huart5);
//        HAL_UART_DMAStop(&huart5);
//        uart_receive_idle(&huart5, &uart_list, g_uart_dma_buf);
//        HAL_UART_DMAResume(&huart5);
//        __HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE);
//        HAL_UART_Receive_DMA(&huart5, g_uart_dma_buf, UART1_DATA_LEN);
//    } 
//    
//    HAL_UART_IRQHandler(&huart5);
//}

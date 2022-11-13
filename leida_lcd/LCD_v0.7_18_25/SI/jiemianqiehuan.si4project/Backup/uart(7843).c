#include "list.h"
#include "uart.h"
#include "stm32f1xx_hal.h"
#include "main.h"
#include "MainMenu.h"
extern uint32_t cnt_start;
extern UART_HandleTypeDef huart1;
extern uint8_t time_out_cnt;
//extern UART_HandleTypeDef huart6;

/* ��ʼ������һ�����ڴ� */
uint8_t g_uart_dma_buf[UART1_DATA_LEN] = {0};
static char uart_data_buf[FIFO_DEPTH * UART1_DATA_LEN] = {0};
static int uart_len_buf[FIFO_DEPTH] = {0};
static List uart_list = {0};

/* ����5��ʼ������ */
void uart_init(void)
{
	list_init(&uart_list, uart_data_buf, uart_len_buf, UART1_DATA_LEN, FIFO_DEPTH);
}

/* �����ڵ����ݻ����ڴ� */
static void uart_receive_idle(UART_HandleTypeDef* huart, List *list, uint8_t *dma_buf)
{
    int len = 0;
    
    len = list->max_len - huart->hdmarx->Instance->CNDTR;  
    list_in(&uart_list, (char*)dma_buf, len);
}

uint8_t out_data[UART1_DATA_LEN] = {0};


/* ��ǰ̨�������� */
int uart_process_data(void)
{
    int len = 0;
    
    /* ���ݳ��� */
    len = list_out(&uart_list, (char *)out_data);
    
    /* ���ݴ��� */
	if(!(strcmp(MenuManager.cur_menu->menu_name,"������")))
	{
		if (!(strncmp("dis:",(char *)out_data,4)) && 0 != len)
		{   
			show_main_page((char *)out_data ,len);
			cnt_start = HAL_GetTick();
			time_out_cnt = 0;
			display_GB2312_string(7,58,"Sensor OK",0,0);	
		} 
	}	
	else if(!(strcmp(MenuManager.cur_menu->menu_name,"���ν���")))
	{
		show_boxin_page();
	}
}

/* �����״ο���dma���� */
void uart_start_dma(void)
{
    HAL_UART_Receive_DMA(&huart1, g_uart_dma_buf, UART1_DATA_LEN);
}


void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

	
	//    /* �����ж���� */
	if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_ORE) != RESET) 
    {
        __HAL_UART_CLEAR_OREFLAG(&huart1);
        HAL_UART_Receive_DMA(&huart1, g_uart_dma_buf, UART1_DATA_LEN);
    }
  /* USER CODE BEGIN USART1_IRQn 1 */
	if(RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))   //�ж��Ƿ��ǿ����ж�
	{

		__HAL_UART_CLEAR_IDLEFLAG(&huart1);                       //��������жϱ�־
		HAL_UART_DMAStop(&huart1);                                //ֹͣ����DMA����    
		
		uart_receive_idle(&huart1, &uart_list, g_uart_dma_buf);
		//huart1.RxXferSize = 255 - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);   //������յ������ݳ���
		
		HAL_UART_DMAResume(&huart1);
		
		__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
		//HAL_UART_Transmit(&huart1,receive_buff,data_length,0x200);             //���Ժ����������յ������ݴ�ӡ��ȥ
		//memset(receive_buff,0,data_length);                                            
		//uart1_stat = 1;								//���յ�����׼����
		//HAL_UART_Receive_DMA(&huart1, (uint8_t*)receive_buff, 100);                      //��������жϱ�־		
		HAL_UART_Receive_DMA(&huart1, g_uart_dma_buf, UART1_DATA_LEN);
	}
	HAL_UART_IRQHandler(&huart1);
  /* USER CODE END USART1_IRQn 0 */
  
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}
///* ����5�жϴ����� */
//void UART5_IRQHandler(void)
//{
//    /* �����ж���� */
//	if(__HAL_UART_GET_FLAG(&huart5,UART_FLAG_ORE) != RESET) 
//    {
//        __HAL_UART_CLEAR_OREFLAG(&huart5);
//        HAL_UART_Receive_DMA(&huart5, g_uart_dma_buf, UART1_DATA_LEN);
//    }
//    /* ��������ж� */
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

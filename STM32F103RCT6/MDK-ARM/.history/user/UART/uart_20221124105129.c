#include "list.h"
#include "uart.h"
#include "stm32f1xx_hal.h"
#include "main.h"
#include "MainMenu.h"
#include "crc.h"
extern uint32_t cnt_start;
extern UART_HandleTypeDef huart1;
extern uint8_t time_out_cnt;
//extern UART_HandleTypeDef huart6;

/* 串口缓冲区 */
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

extern uint8_t test_buf[1024];
extern char boxin_dm[8];
extern char boxin_Adb[8];
uint16_t g_data_max = 0;
volatile float g_new_dis = 0;
volatile int g_max_db = 128;

/* ��ǰ̨�������� */
int uart_process_data(void)
{

    int len = 0;
	short data_len = 0;
	uint16_t crc_val = 0;
    float dis = 0;
    char dis_data[16] = {0}; 
    
    /* ���ݳ��� */
    len = list_out(&uart_list, (char *)out_data);
    if(out_data[0] == 0x68)
	{
		memcpy(&data_len,out_data + 2,2);
		HAL_UART_Transmit(&huart1,&out_data[2],2,1000);
		//HAL_UART_Transmit(&huart1,out_data[3],1,1000);
		//show_main_page((char *)(&out_data[4]) ,data_len/*���ݳ���*/);
		switch(out_data[1])		//�����ַ�
		{
			case 0x01:{
				
				if(out_data[data_len + 6 /**/ ] == 0x16)
				{
					/*����CRCУ��*/
					//crc_val = jysf((&out_data[3]),out_data[2]);
					//if(out_data[3+out_data[2]] == ((uint8_t *)&crc_val)[1] || out_data[3+out_data[2]] == ((uint8_t *)&crc_val)[0])
					{
						/*����*/

						cnt_start = HAL_GetTick();
						time_out_cnt = 0;
                        /*����*/
                        memset(dis_data, 0, sizeof(dis_data));
                        dis = *(float*)&out_data[4];
                        g_new_dis = dis;
                        sprintf(dis_data, "%2.3f", dis);
                        
						if(!strncmp(MenuManager.cur_menu->menu_name,"������\0",sizeof("������\0")))
						{
                            show_main_page(dis_data , strlen(dis_data));
                            cnt_start = HAL_GetTick();
                            time_out_cnt = 0;
                            display_GB2312_string(7,58,"Sensor OK",0,0);
                            HAL_UART_Transmit(&huart1,"loop star1",11,1000);	
						}
						HAL_UART_Transmit(&huart1,"loop star1",11,1000);	
					}
					HAL_UART_Transmit(&huart1,out_data + 4,data_len,1000);	
				}
				break;
			}
			case 0x02:{
				if(out_data[data_len + 6 ] == 0x16)	//�жϽ�����
				{
					
//					//if(out_data[3+out_data[2]] == ((uint8_t *)&crc_val)[1] || out_data[3+out_data[2]] == ((uint8_t *)&crc_val)[0])
					memset(test_buf,0,data_len);
					memcpy(test_buf,&out_data[4],data_len );				/*ʵ������������ƫ��2λ����  ��һ������������¼����ԭ��*/
                    g_max_db = 0;
                    for (int i = 0; i < data_len/2 ;)
                    {
                        if (g_max_db < *(uint16_t*)&(test_buf[i]))
                        {
                            g_max_db = *(uint16_t*)&(test_buf[i]);
                        }
                            
                        i += 2;
                    }
					if(!strncmp(MenuManager.cur_menu->menu_name,"���ν���\0",sizeof("���ν���\0")))
					{
						show_boxin_page((char*)test_buf , data_len);
					}
					HAL_UART_Transmit(&huart1,"loop star2",11,1000); 
				}
				break;
			}
			case 0x03:{
				if(out_data[out_data[2] + 6 ] == 0x16)	//�жϽ�����
				{
					crc_val = jysf((&out_data[4]),out_data[2]);
					//if(out_data[3+out_data[2]] == ((uint8_t *)&crc_val)[1] || out_data[3+out_data[2]] == ((uint8_t *)&crc_val)[0])
					{
						memset(boxin_dm,0,8);
						memcpy(boxin_dm,&out_data[4],out_data[2]);
						show_boxin_page(test_buf,sizeof(test_buf));
						HAL_UART_Transmit(&huart1,"loop star2",11,1000); 
					}
				}
				break;
				HAL_UART_Transmit(&huart1,"loop star3",11,1000); 
				break;
			}
			case 0x04:{
				if(out_data[out_data[2] + 5 ] == 0x16)	//�жϽ�����
				{
					crc_val = jysf((&out_data[3]),out_data[2]);
					//if(out_data[3+out_data[2]] == ((uint8_t *)&crc_val)[1] || out_data[3+out_data[2]] == ((uint8_t *)&crc_val)[0])
					{
						memset(boxin_Adb,0,8);
						memcpy(boxin_Adb,&out_data[3],out_data[2]);
						show_boxin_page(test_buf,sizeof(test_buf));
						HAL_UART_Transmit(&huart1,"loop star2",11,1000); 
					}
				}
				break;
				HAL_UART_Transmit(&huart1,"loop star3",11,1000); 
				break;
			}
		}
//		/* ���ݴ��� */
//		if(!(strcmp(MenuManager.cur_menu->menu_name,"������")))				//������������ʾ
//		{
//			if (!(strncmp("dis:",(char *)out_data,4)) && 0 != len)
//			{   
//				show_main_page((char *)out_data ,len);
//				cnt_start = HAL_GetTick();
//				time_out_cnt = 0;
//				display_GB2312_string(7,58,"Sensor OK",0,0);	
//			} 
//		}	
//		else if(!(strcmp(MenuManager.cur_menu->menu_name,"���ν���")))		//������ʾ
//		{
//			show_boxin_page();
//		}
	}
	memset(out_data,0,UART1_DATA_LEN);
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
///* ����5�жϴ������� */
//void UART5_IRQHandler(void)
//{
//    /* �����ж���� */
//	if(__HAL_UART_GET_FLAG(&huart5,UART_FLAG_ORE) != RESET) 
//    {
//        __HAL_UART_CLEAR_OREFLAG(&huart5);
//        HAL_UART_Receive_DMA(&huart5, g_uart_dma_buf, UART1_DATA_LEN);
//    }
//    /* ���������ж� */
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

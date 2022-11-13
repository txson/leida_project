#include "iwr_config.h"
#include "string.h"
#include "list.h"
#include "crc.h"

#define CMD_NUM 13

extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart5;

/* 缓冲的最大深度 */
#define UART6_FIFO_DEPTH    6 	
/* 单次缓冲的最大长度 */ 
#define UART6_DATA_LEN    300

/* 初始化串口一缓冲内存 */
uint8_t g_uart6_dma_buf[UART6_DATA_LEN] = {0};
uint8_t g_uart6_str_buf[UART6_DATA_LEN] = {0};
static char uart6_data_buf[UART6_FIFO_DEPTH * UART6_DATA_LEN] = {0};
static int uart6_len_buf[UART6_FIFO_DEPTH] = {0};
static List uart6_list = {0};

float dis_x = 0.0f;
float dis_y = 0.0f;
float dis_z = 0.0f;

typedef enum
{
    START_INIT = 0,
    SEND_CMD,
    WAIT_RESP,
    CMD_RESP,
    INIT_FINISH,
} SEND_CMD_STATUS;

/* 配置命令字符串数组,默认参数 */
#if 0
char* config_cmd[CMD_NUM] = {
"sensorStop\r\n",
"flushCfg\r\n",
"dfeDataOutputMode 1\r\n",
"channelCfg 8 1 0\r\n",
"adcCfg 2 1\r\n",
"adcbufCfg 0 1 0 1\r\n",
"profileCfg 0 77 7 7 212.8 0 0  18.32 1 1024 5000 0 0 40\r\n",
"chirpCfg 0 0 0 0 0 0 0 1\r\n",
"frameCfg 0 0 1 0 500 1 0\r\n",
"calibDcRangeSig 0 -5 5 32\r\n",
"guiMonitor 1   1 0  0 0  1\r\n",
"RangeLimitCfg 0 1.0 10.0\r\n",
"sensorStart\r\n"
};
#endif
/* 测试参数，提高穿透性 
RangeLimitCfg:高度限制，设置为不生效，这个在应用代码里面做限制
channelCfg：修改了发射天线的数量，7 代表3个tx同时发射,经过检测这个是没有用的
calibDcRangeSig:这个参数加上，可以使效果明显变好
*/ 
#if 0
char* config_cmd[CMD_NUM] = {
"sensorStop\r\n",
"flushCfg\r\n",
"dfeDataOutputMode 1\r\n",
"channelCfg 8 1 0\r\n",
"adcCfg 2 1\r\n",
"adcbufCfg 0 1 0 1\r\n",
"profileCfg 0 77 7 7 212.8 0 0  18.32 1 1024 5000 0 0 40\r\n",
"chirpCfg 0 0 0 0 0 0 0 1\r\n",
"frameCfg 0 0 1 0 500 1 0\r\n",
"calibDcRangeSig 1 -5 5 32\r\n",
"guiMonitor 1   1 0  0 0  1\r\n",
"RangeLimitCfg 1 0.1 10.0\r\n",
"sensorStart\r\n"
};
#endif


#if 1
char* config_cmd[CMD_NUM] = {
"sensorStop\r\n",
"flushCfg\r\n",
"dfeDataOutputMode 1\r\n",
"channelCfg 8 1 0\r\n",
"adcCfg 2 1\r\n",
"adcbufCfg 0 1 0 1\r\n",
"profileCfg 0 77 7 7 212.8 0 0  18.32 1 1024 5000 0 0 40\r\n",
"chirpCfg 0 0 0 0 0 0 0 1\r\n",
"frameCfg 0 0 1 0 500 1 0\r\n",
"calibDcRangeSig 0 -5 5 32\r\n",
"guiMonitor 1   1 0  0 0  1\r\n",
"RangeLimitCfg 1 0.1 15.0\r\n",
"sensorStart\r\n"
};
#endif

static SEND_CMD_STATUS g_cmd_status = START_INIT;
static uint8_t g_cmd_step = 0;

void iwr_polling(void)
{
    static int send_time = 0;
    
    // 上电复位之后等待设备命令行
    if (g_cmd_status == START_INIT)
    {
        return ;
    }

    // 初始化完成
    if (g_cmd_status == INIT_FINISH)
    {
        return ;
    }

    if (g_cmd_status == SEND_CMD)
    {
        //发送配置命令
        HAL_UART_Transmit(&huart6, (uint8_t*)config_cmd[g_cmd_step], strlen(config_cmd[g_cmd_step]), 100);
        send_time = HAL_GetTick();
        // 发送数据等待应答
        g_cmd_status = WAIT_RESP;
    }
    else if (g_cmd_status == WAIT_RESP)
    {
        if (HAL_GetTick() - send_time > 1000)
        {
            //超过没有应答错误处理机制
        }
    }
    else if (g_cmd_status == CMD_RESP)
    {
        //准备发送下一个命令
        g_cmd_step ++;
        //最后一个命令发送完成
        if (g_cmd_step >= CMD_NUM)
        {
            g_cmd_status = INIT_FINISH; 
        }
        else
        {
            g_cmd_status = SEND_CMD;
        }
    }
}


int seccess = 0;
int fail = 0;
DIS_DATA dis_data = {0};
FLOW_DATA flow_data = {0};

/* 解析iwr cmd 返回的数据 */
void iwr_cmd_process(uint8_t *data, int len)
{
    char result_data[3][4] = {0};
    char send_data[32] = {0};
    
    
    if (g_cmd_status == START_INIT)
    {
        if (strstr((char*)data, "xWR14xx") != 0)
        {
            /* 首次上电成功，准备开始发送命令 */
            g_cmd_status = SEND_CMD;     
            g_cmd_step = 0;
        }

        return;
    }
    else if (g_cmd_status == INIT_FINISH)
    {
        // 解析iwr 传回来的数据 
        if (data[0] == 0xAA && data[1] == 0xFF &&
            data[255] == 0x55 && data[256] == 0xFF)
        {
            if (CRC4_ITU(data, 254) == data[254])
            {
                memcpy((char*)&result_data[0], &data[2], 4);
                dis_x = *(float*)&result_data[0];

#if 1                
                /* 发送距离数据 */
                memset(&dis_data, 0, sizeof(DIS_DATA));
                dis_data.head = 0x68;
                dis_data.cmd = 0x01;
                dis_data.len = 4;
                memcpy(dis_data.buf, (uint8_t*)&dis_x, 4);
                dis_data.crc = CRC4_LCD((uint8_t*)&dis_x, 4);
                dis_data.end = 0x16;
                seccess ++;
                HAL_UART_Transmit(&huart5, (uint8_t*)&dis_data, 11, 100);
#endif                              

                HAL_Delay(5);
#if 0                
                if (dis_x > 0.0f && dis_x < 120.0f)
                {
                    sprintf(send_data, "dis:%.6f \r\n", dis_x);
                    HAL_UART_Transmit(&huart5, send_data, 16, 1000);
                    //HAL_UART_Transmit(&huart5, data, len, 100);
                    
                    return ;
                }
#endif          

#if 1                
                /* 发送波形数据 */
                memset(&flow_data, 0, sizeof(DIS_DATA));
                flow_data.head = 0x68;
                flow_data.cmd = 0x02;
                flow_data.len = 240;
                memcpy(flow_data.buf, (uint8_t*)&data[14], 240);
                flow_data.crc = 0xAA55;
                flow_data.end = 0x16;
                seccess ++;
                HAL_UART_Transmit(&huart5, (uint8_t*)&flow_data, 247, 1000);
#endif 
                return;
            }
            else
            {    
                fail++;
                return ;
            }
        }
        else
        { 
            fail ++;
            return ;
        }
    }

    if (strstr((char*)data, "mmwDemo") != 0)
    {
        if (g_cmd_status == WAIT_RESP)
        {
            g_cmd_status = CMD_RESP;
        }
    }
}

/* 串口5初始化函数 */
void uart6_init(void)
{
	list_init(&uart6_list, uart6_data_buf, uart6_len_buf, UART6_DATA_LEN, UART6_FIFO_DEPTH);
}

/* 将串口的数据缓冲内存 */
static void uart6_receive_idle(UART_HandleTypeDef* huart, List *list, uint8_t *dma_buf)
{
    int len = 0;
    int i = 0;
    int j = 0;
    
    len = list->max_len - huart->hdmarx->Instance->NDTR;
    
    memset(&g_uart6_str_buf, 0, sizeof(g_uart6_str_buf));
    // 删除转义字符
    for (i = 0; i < len; i++)
    {
        if (i > 0 && 
            dma_buf[i] == 0x0D && 
            dma_buf[i-1] == 0x0A)
        {
            // 0x0A 后面的0x0D为转义字符需要删掉
        }
        else
        {
            g_uart6_str_buf[j] = dma_buf[i];
            j++;
        }
    }
    
    list_in(&uart6_list, (char*)g_uart6_str_buf, len);
}


uint8_t out_data[UART6_DATA_LEN] = {0};

/* 在前台处理数据 */
void uart6_process_data(void)
{
    int len = 0;
	    
	memset(out_data, 0, UART6_DATA_LEN);
    /* 数据出队 */
    len = list_out(&uart6_list, (char *)out_data);
    
    /* 数据处理 */
    if (0 != len)
    {   
        iwr_cmd_process(out_data, len); 
    }    
}

/* 代码首次开启dma传输 */
void uart6_start_dma(void)
{
    HAL_UART_Receive_DMA(&huart6, g_uart6_dma_buf, UART6_DATA_LEN);
}

/* 串口5中断处理函数 */
void USART6_IRQHandler(void)
{
    /* 处理中断溢出 */
	if(__HAL_UART_GET_FLAG(&huart6,UART_FLAG_ORE) != RESET) 
    {
        __HAL_UART_CLEAR_OREFLAG(&huart6);
        memset(&g_uart6_dma_buf, 0, UART6_DATA_LEN);
        HAL_UART_Receive_DMA(&huart6, g_uart6_dma_buf, UART6_DATA_LEN);
    }
    /* 处理空闲中断 */
    if((__HAL_UART_GET_FLAG(&huart6,UART_FLAG_IDLE) != RESET))
    { 
        __HAL_UART_CLEAR_IDLEFLAG(&huart6);
        HAL_UART_DMAStop(&huart6);
        uart6_receive_idle(&huart6, &uart6_list, g_uart6_dma_buf);
        HAL_UART_DMAResume(&huart6);
        __HAL_UART_ENABLE_IT(&huart6, UART_IT_IDLE);
        memset(&g_uart6_dma_buf, 0, UART6_DATA_LEN);
        HAL_UART_Receive_DMA(&huart6, g_uart6_dma_buf, UART6_DATA_LEN);
    } 
    
    HAL_UART_IRQHandler(&huart6);
}






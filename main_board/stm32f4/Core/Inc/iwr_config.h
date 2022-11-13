#ifndef __IWR_CONFIG_H__
#define __IWR_CONFIG_H__

#include "stm32f4xx_hal.h"

void iwr_polling(void);
void iwr_cmd_process(uint8_t *data, int len);
void uart6_init(void);
void uart6_start_dma(void);
void uart6_process_data(void);

typedef struct 
{
    uint8_t head;
    uint8_t cmd;
    uint16_t len;
    uint8_t buf[4];
    uint16_t crc;
    uint8_t end;
} DIS_DATA;

typedef struct 
{
    uint8_t head;
    uint8_t cmd;
    uint16_t len;
    uint8_t buf[240];
    uint16_t crc;
    uint8_t end;
} FLOW_DATA;

#endif 


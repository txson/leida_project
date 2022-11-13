#ifndef __CRC_H__
#define __CRC_H__

#include "stm32f4xx_hal.h"

unsigned char CRC4_ITU(unsigned char *data, unsigned int datalen);
uint16_t CRC4_LCD(uint8_t *buffer, uint16_t buffer_length);
#endif

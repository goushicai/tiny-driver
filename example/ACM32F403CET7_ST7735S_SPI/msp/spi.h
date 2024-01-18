#ifndef __SPI_H__
#define __SPI_H__

#include "ACM32Fxx_HAL.h"
#include "gpio_config.h"

extern SPI_HandleTypeDef lcdSpiHandle;

void SPI_Init(void);

/**
 * 此函数给lcd驱动层调用
  */
HAL_StatusTypeDef spiTxlcd(uint8_t *data,uint32_t size);


#endif /* __SPI_H__ */


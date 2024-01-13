#ifndef __SPI_H__
#define __SPI_H__

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"

#define LCD_SPI_ENABLE_DMA	0 	//置1为开启DMA,开启DMA要求SPI有相应的配置

extern SPI_HandleTypeDef hspi1;
extern DMA_HandleTypeDef hdma_spi1_tx;

void SPI_Init(void);

/**
 * 此函数给lcd驱动层调用
  Timeout 不能设置为0, 否则可能导致超时,
    具体请参考HAL_SPI_Transmit源代码:
    stm32f1xx_hal_spi.c 880行
  */
HAL_StatusTypeDef spiTxlcd(uint8_t *data,uint32_t size);

#if(LCD_SPI_ENABLE_DMA == 1)
HAL_StatusTypeDef spiTxlcdDMA(uint8_t *data,uint32_t size);
#endif

#endif /* __SPI_H__ */


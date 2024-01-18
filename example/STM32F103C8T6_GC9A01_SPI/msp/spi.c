#include "spi.h"

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

void SPI_Init(void){
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  HAL_SPI_Init(&hspi1);
}

/**
[TO_MODITY]

	不同的开发库,对于SPI的GPIO初始化可能有所不同,
	如STM32等提供的HAL库有一个 weak 修饰的 HAL_SPI_MspInit 函数,
	在 SPI_Init() 函数中调用,用户可以编码同名函数覆盖此

请根据实际的情况初始化SPI的GPIO
*/
void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle){
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if(spiHandle->Instance==SPI1){
		
		// SPI1 clock enable
		__HAL_RCC_SPI1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();

		/**SPI1 GPIO Configuration
		PA5     ------> SPI1_SCK
		PA7     ------> SPI1_MOSI
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

#if(LCD_SPI_ENABLE_DMA == 1)
		
		/* SPI1 DMA Init */
		hdma_spi1_tx.Instance = DMA1_Channel3;
		hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_spi1_tx.Init.Mode = DMA_NORMAL;
		hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
		HAL_DMA_Init(&hdma_spi1_tx);

		__HAL_LINKDMA(spiHandle,hdmatx,hdma_spi1_tx);

		HAL_DMA_IRQHandler(&hdma_spi1_tx);
		
		/* DMA controller clock enable */
		__HAL_RCC_DMA1_CLK_ENABLE();

		/* DMA interrupt init */
		/* DMA1_Channel3_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
		  
#endif
	}
}

HAL_StatusTypeDef spiTxlcd(uint8_t *data,uint32_t size){
	/**
	Timeout 不能设置为0, 否则可能导致超时,
		具体请参考HAL_SPI_Transmit源代码:
		stm32f1xx_hal_spi.c 880行
	*/
	return HAL_SPI_Transmit(&hspi1, data, size, 100);
}


HAL_StatusTypeDef spiTxlcdDMA(uint8_t *data,uint32_t size){
	return HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)data, size);
}

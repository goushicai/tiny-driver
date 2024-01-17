#include "spi.h"

SPI_HandleTypeDef lcdSpiHandle;

void SPI_Init(void){
	
    lcdSpiHandle.Instance                   = SPI2;
    lcdSpiHandle.Init.SPI_Mode              = SPI_MODE_MASTER;
    lcdSpiHandle.Init.SPI_Work_Mode         = SPI_WORK_MODE_3;
    lcdSpiHandle.Init.X_Mode                = SPI_1X_MODE;
    lcdSpiHandle.Init.First_Bit             = SPI_FIRSTBIT_MSB;
    lcdSpiHandle.Init.BaudRate_Prescaler    = SPI_BAUDRATE_PRESCALER_4;

    HAL_SPI_Init(&lcdSpiHandle);
}


void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle){
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if(spiHandle->Instance==SPI2){
		// SPI2 clock enable
		System_Module_Enable(EN_SPI2);

		/**SPI2 GPIO Configuration
		PB12	------> SPI2_CS
		PB13    ------> SPI2_SCK
		PB15    ------> SPI2_MOSI
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Alternate = GPIO_FUNCTION_4;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		NVIC_ClearPendingIRQ(SPI2_IRQn);    // Clear Pending Interrupt
		NVIC_EnableIRQ(SPI2_IRQn);          // Enable External Interrupt
	}
}

HAL_StatusTypeDef spiTxlcd(uint8_t *data,uint32_t size){
	
	return HAL_SPI_Transmit(&lcdSpiHandle, data, size, 0);
	
}

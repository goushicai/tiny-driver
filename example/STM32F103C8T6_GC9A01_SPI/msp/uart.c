#include "uart.h"

UART_HandleTypeDef uart1Handle;

int fputc(int ch, FILE *f){
  HAL_UART_Transmit(&uart1Handle, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

void UART_Init(){
	/*开启Uart时钟*/
	__HAL_RCC_USART1_CLK_ENABLE();
	
	uart1Handle.Instance        = USART1;
	uart1Handle.Init.BaudRate   = UART_Baud_Rate;
	uart1Handle.Init.WordLength = UART_WORDLENGTH_8B;
	uart1Handle.Init.StopBits   = UART_STOPBITS_1;
	uart1Handle.Init.Parity     = UART_PARITY_NONE;
	uart1Handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	uart1Handle.Init.Mode       = UART_MODE_TX_RX;
	
	HAL_UART_Init(&uart1Handle);
	
	printf("Uart1 is ready\n");
}


void HAL_UART_MspInit(UART_HandleTypeDef *huart){
	GPIO_InitTypeDef  GPIO_InitStruct;	

	//开启GPIO时钟
	if(UART_TX_PORT == GPIOA || UART_RX_PORT == GPIOA){
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	}
	if(UART_TX_PORT == GPIOB || UART_RX_PORT == GPIOB){
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	}
	if(UART_TX_PORT == GPIOC || UART_RX_PORT == GPIOC){
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	}
	if(UART_TX_PORT == GPIOD || UART_RX_PORT == GPIOD){
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	}
	
	HAL_GPIO_WritePin(UART_TX_PORT, UART_TX_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(UART_TX_PORT,UART_RX_PIN, GPIO_PIN_SET);
	
	GPIO_InitStruct.Pin       = UART_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(UART_TX_PORT, &GPIO_InitStruct); //初始化UartTx管脚

	GPIO_InitStruct.Pin = UART_RX_PIN;
	HAL_GPIO_Init(UART_RX_PORT, &GPIO_InitStruct); //初始化UartRx管脚
	
}

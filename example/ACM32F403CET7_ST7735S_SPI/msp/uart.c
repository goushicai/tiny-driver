#include "uart.h"

UART_HandleTypeDef uart3Handle;

void UART_Init(uint32_t baudRate){
	uart3Handle.Instance        = UART3; 
    uart3Handle.Init.BaudRate   = baudRate;
    uart3Handle.Init.WordLength = UART_WORDLENGTH_8B;
    uart3Handle.Init.StopBits   = UART_STOPBITS_1;
    uart3Handle.Init.Parity     = UART_PARITY_NONE;
    uart3Handle.Init.Mode       = UART_MODE_TX_RX_DEBUG;
    uart3Handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	
    HAL_UART_Init(&uart3Handle);
	
	/* ENABLE FIFO */ 
    HAL_UART_Enable_Disable_FIFO(&uart3Handle,FUNC_ENABLE); 
	
	printfS("Uart3 is ready\n");
}


void HAL_UART_MspInit(UART_HandleTypeDef *huart){
	if (huart->Instance == UART3) {
		GPIO_InitTypeDef GPIO_Uart3;//UART3 PB10 Tx, PB11 Rx , GPIO_FUNCTION_2
		
        /* Enable Clock */
        System_Module_Enable(EN_UART3);  
        System_Module_Enable(EN_GPIOAB);      
        /* Initialization GPIO */
		
        GPIO_Uart3.Pin       = UART_TX_PIN | UART_RX_PIN;
        GPIO_Uart3.Mode      = GPIO_MODE_AF_PP;
        GPIO_Uart3.Pull      = GPIO_PULLUP;
        GPIO_Uart3.Alternate = GPIO_FUNCTION_2;
        
        HAL_GPIO_Init(GPIOB, &GPIO_Uart3);   
		
		HAL_GPIO_WritePin(GPIOB, UART_TX_PIN, GPIO_PIN_CLEAR);
		HAL_GPIO_WritePin(GPIOB, UART_RX_PIN, GPIO_PIN_CLEAR);
		
        /*
        NVIC_ClearPendingIRQ(UART3_IRQn);
        NVIC_SetPriority(UART3_IRQn, (1U << __NVIC_PRIO_BITS) - 2);  
        NVIC_EnableIRQ(UART3_IRQn);  
		*/
    }
	
}

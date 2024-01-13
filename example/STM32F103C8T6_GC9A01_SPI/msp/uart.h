#ifndef __USART_H__
#define __USART_H__

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#include "stdio.h"

#define UART_TX_PORT 	GPIOA
#define UART_TX_PIN 	GPIO_PIN_9
#define UART_RX_PORT  	GPIOA
#define UART_RX_PIN 	GPIO_PIN_10

#define UART_Baud_Rate  115200

int fputc(int ch, FILE *f);

void UART_Init(void);

#endif /* __USART_H__ */


#ifndef __GPIO_CONFIG_H__
#define __GPIO_CONFIG_H__

//lcd����,����������ҪBLK
#define LCD_BLK_PORT 	GPIOA
#define LCD_BLK_PIN  	GPIO_PIN_9

//lcd spi mosi 
#define LCD_SCK_PORT 	GPIOB
#define LCD_SCK_PIN  	GPIO_PIN_13

//lcd spi clk 
#define LCD_SDA_PORT 	GPIOB
#define LCD_SDA_PIN  	GPIO_PIN_15

//lcd D/C,��������ѡ��
#define LCD_DC_PORT  	GPIOB
#define LCD_DC_PIN   	GPIO_PIN_14

//lcd CS Ƭѡ
#define LCD_CS_PORT  	GPIOB
#define LCD_CS_PIN   	GPIO_PIN_12

//lcd RST ����
#define LCD_RST_PORT 	GPIOA
#define LCD_RST_PIN  	GPIO_PIN_8

//uart1 gpio
#define UART_TX_PORT 	GPIOB
#define UART_TX_PIN 	GPIO_PIN_10

#define UART_RX_PORT  	GPIOB
#define UART_RX_PIN 	GPIO_PIN_11

//����led��
#define LED_PORT		GPIOB
#define LED_PIN     	GPIO_PIN_7


#endif 


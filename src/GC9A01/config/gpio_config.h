#ifndef __GPIO_CONFIG_H__
#define __GPIO_CONFIG_H__

/***
[TO_MODITY]

本配置文件是MCU 与LCD 屏相关的 GPIO 宏定义,
	在gpio_config.h中有 对相关GPIO管脚操作的宏定义函数
	GPIO初始化时也有用到
*/

//lcd背光,部分屏不需要BLK
#define LCD_BLK_PORT 	GPIOA
#define LCD_BLK_PIN  	GPIO_PIN_2

//lcd spi mosi 
#define LCD_SCK_PORT 	GPIOA
#define LCD_SCK_PIN  	GPIO_PIN_5

//lcd spi clk 
#define LCD_SDA_PORT 	GPIOA
#define LCD_SDA_PIN  	GPIO_PIN_7

//lcd D/C,命令数据选择
#define LCD_DC_PORT  	GPIOA
#define LCD_DC_PIN   	GPIO_PIN_3

//lcd CS 片选
#define LCD_CS_PORT  	GPIOA
#define LCD_CS_PIN   	GPIO_PIN_4

//lcd RST 重置
#define LCD_RST_PORT 	GPIOA
#define LCD_RST_PIN  	GPIO_PIN_6

//uart1 gpio
#define UART_TX_PORT 	GPIOA
#define UART_TX_PIN 	GPIO_PIN_9
#define UART_RX_PORT  	GPIOA
#define UART_RX_PIN 	GPIO_PIN_10

//板载led灯
#define LED_PORT		GPIOA
#define LED_PIN     	GPIO_PIN_8


#endif 


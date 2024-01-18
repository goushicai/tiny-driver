#ifndef __GPIO_CONFIG_H__
#define __GPIO_CONFIG_H__

/***
[TO_MODITY]

�������ļ���MCU ��LCD ����ص� GPIO �궨��,
	��gpio_config.h���� �����GPIO�ܽŲ����ĺ궨�庯��
	GPIO��ʼ��ʱҲ���õ�
*/

//lcd����,����������ҪBLK
#define LCD_BLK_PORT 	GPIOA
#define LCD_BLK_PIN  	GPIO_PIN_2

//lcd spi mosi 
#define LCD_SCK_PORT 	GPIOA
#define LCD_SCK_PIN  	GPIO_PIN_5

//lcd spi clk 
#define LCD_SDA_PORT 	GPIOA
#define LCD_SDA_PIN  	GPIO_PIN_7

//lcd D/C,��������ѡ��
#define LCD_DC_PORT  	GPIOA
#define LCD_DC_PIN   	GPIO_PIN_3

//lcd CS Ƭѡ
#define LCD_CS_PORT  	GPIOA
#define LCD_CS_PIN   	GPIO_PIN_4

//lcd RST ����
#define LCD_RST_PORT 	GPIOA
#define LCD_RST_PIN  	GPIO_PIN_6

//uart1 gpio
#define UART_TX_PORT 	GPIOA
#define UART_TX_PIN 	GPIO_PIN_9
#define UART_RX_PORT  	GPIOA
#define UART_RX_PIN 	GPIO_PIN_10

//����led��
#define LED_PORT		GPIOA
#define LED_PIN     	GPIO_PIN_8


#endif 


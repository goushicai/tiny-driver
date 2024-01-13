STM32_F103C8T6_GC9A01 的驱动示例程序
======================================

## 0. 说明

代码中用到的取字模,图片取模,颜色转换等,请访问

	https://www.buziot.com/tools


## 2. 目录结构

	proj
		keil项目相关文件
	sys
		CMSIS及HAL库相关内容
	msp
		mcu相关资源的内容,如RCC,RTC,GPIO,UART,SPI等初始化与功能等
	bsp
		与板载资源相关的内容,如LED,按键, ADC等
	drv
		驱动层,用于存放硬件的驱动程序
	api
		接口层,用于解除硬件层与应用层,以便于移植与复用
	lib
		第三方库相关的内容
	res
		资源文件,如图片,字库等, 图片与取字模的工具请访问 https://www.buziot.com/tools
	ui
		ui组件,如文本lable,输入框input,按键button等ui组件
	app
		应用层,用户存放应用层的文件,如系统状态机, main.c等文件
	config
		配置文件,将常见的可变内容抽离出来,通过配置即可实现移植与复用

## 3. 使用介绍

	创建 keil 项目后配置好 系统时钟, SPI, UART等

### 3.1 gpio_config.h

	在config/文件夹中找到 gpio_config.h, 根据实际情况配置好管脚

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

### 3.2 gc9a01_config.h

	在config/文件夹中找到 gc9a01_config.h

	1. 包含 gpio_config.h, spi.h 等头文件,并配置好SPI等功能

		确保调用SPI发送数据的功能已实现,示例代码中的函数为 HAL_StatusTypeDef spiTxlcd(uint8_t *data,uint32_t size) 

	2. 按实际情况 修改LCD_WIDTH,LCD_HEIGHT,DISPLAY_RAM_SIZE等参数

	3. 宏定义毫秒延时函数,驱动程序中用到毫秒延时函数 HAL_Delay(n), 若没有,请修改宏定义,如:

		#define HAL_Delay 		delay_ms

	4. 按实际情况配置好 CS,DC,RST,BLK等管脚的拉高拉低操作

		#define LCD_CS_ENABLE()   HAL_GPIO_WritePin(LCD_CS_PORT,LCD_CS_PIN,GPIO_PIN_RESET)  //片选  
		#define LCD_CS_DISABLE()  HAL_GPIO_WritePin(LCD_CS_PORT,LCD_CS_PIN,GPIO_PIN_SET)    //未选中   
		
		#define LCD_DATA_ENABLE() HAL_GPIO_WritePin(LCD_DC_PORT,LCD_DC_PIN,GPIO_PIN_SET)    //高电平数据    
		#define LCD_CMD_ENABLE()  HAL_GPIO_WritePin(LCD_DC_PORT,LCD_DC_PIN,GPIO_PIN_RESET)  //低电平命令
		
		#define LCD_RST_ENABLE()  HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN,GPIO_PIN_RESET) //复位,低电平有效      
		#define LCD_RST_DISABLE() HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN,GPIO_PIN_SET)   //保持  
		
		#define LCD_BLK_ENABLE()  HAL_GPIO_WritePin(LCD_BLK_PORT,LCD_BLK_PIN,GPIO_PIN_SET) //打开背光      
		#define LCD_BLK_DISABLE() HAL_GPIO_WritePin(LCD_BLK_PORT,LCD_BLK_PIN,GPIO_PIN_RESET)   //关闭背光  

	
### 3.3 display_config.h

	在config/文件夹中找到 display_config.h 

	1. 包含 lcd驱动程序 gc9a01.h , 资源文件, font.h, pic.h, color.h 等头文件
	2. 按实际情况修改 屏幕宽度,高度,旋转,镜像等参数

### 3.4 接口层API

	请参考 display.h 文件

	接口层在驱动层与应用层之间,是对硬件驱动的抽象,用于解除应用层与硬件驱动的耦合.

	当硬件发生变化,应该基于接口层的规范,实现新硬件的驱动,应用层无须修改.

## 4. 其它

	有一些简单的规范

	1. 文件名全部小写,用下划线连接 如 gpio_config.h
	2. 宏定义全部大写,用下划线连接 如 SCREEN_WIDTH
	3. 枚举类型全部大大写,用下划线连接 如 LCD_STATUS_OK
	4. 函数名全部采用驼峰命名法,如 displayInit(), 以便与HAL库中的函数区别
	5. 变量名全部采用驼峰命名法
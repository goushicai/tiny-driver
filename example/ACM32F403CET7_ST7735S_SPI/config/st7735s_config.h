#ifndef __GC9A01_CONFIG_H
#define __GC9A01_CONFIG_H

/***
[TO_MODITY]

本配置文件是基于ST7735S驱动IC的LCD屏的相关配置,
	
	驱动程序用到操作GPIO的功能,需要用到 HAL_GPIO_WritePin
	相关的GPIO管脚在 gpio_config.h中定义
	驱动程序用到SPI通讯,故需要包含 spi 相关头文件
	驱动程序用到毫秒延时函数,请视情况用宏定义替换 HAL_Delay (这是STM32 HAL的毫秒延时函数)
	
	LCD屏的宽高必须指定,旋转与镜像建议默认在display中调用相关的功能设置
	
*/

#include "ACM32Fxx_HAL.h"	// 包含有操作管脚电平的头文件,如 HAL_GPIO_WritePin
#include "gpio_config.h"	//lcd相关的端口与管脚的宏定义
#include "spi.h" 			//驱动需要用到spi中 spiTxlcd 函数发送数据

//LCD的屏宽
#define LCD_WIDTH 		128
//LCD的屏高
#define LCD_HEIGHT 		160

//显示内容旋转 0,1,2,3 分别逆时针旋转0,90,180,270度
#define LCD_ROTATION	0

//显示镜像 0,1,2,3 分别为不镜像,水平镜像,垂直镜像,水平与垂直均镜像 
#define LCD_MIRROR 		0

/**
显存,暂时只支持16bit颜色,显存字节数是此值的2倍,如:　
	DISPLAY_RAM_SIZE=128,是指缓存了个128个像素点的颜色,由于16位色每个像素的颜色占2 byte,
	故程序中实际用的RAM是 128*2=256 byte
*/
#define DISPLAY_RAM_SIZE		(LCD_WIDTH * 4)

/**
毫秒延时函数,HAL_Delay 是STM32 HAL提供的毫秒延时函数, 
System_Delay_MS 是ACM32 HAL库提供的毫秒延时函数
*/
#define HAL_Delay 		System_Delay_MS

/**
请将HAL_GPIO_WritePin替换成对应的函数,若不用HAL库,可以修改成用寄存器操作
*/
#define LCD_CS_ENABLE()   HAL_GPIO_WritePin(LCD_CS_PORT,LCD_CS_PIN,GPIO_PIN_CLEAR)  //片选  
#define LCD_CS_DISABLE()  HAL_GPIO_WritePin(LCD_CS_PORT,LCD_CS_PIN,GPIO_PIN_SET)    //未选中   

#define LCD_DATA_ENABLE() HAL_GPIO_WritePin(LCD_DC_PORT,LCD_DC_PIN,GPIO_PIN_SET)    //高电平数据    
#define LCD_CMD_ENABLE()  HAL_GPIO_WritePin(LCD_DC_PORT,LCD_DC_PIN,GPIO_PIN_CLEAR)  //低电平命令

#define LCD_RST_ENABLE()  HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN,GPIO_PIN_CLEAR) //复位,低电平有效      
#define LCD_RST_DISABLE() HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN,GPIO_PIN_SET)   //保持  

#define LCD_BLK_ENABLE()  HAL_GPIO_WritePin(LCD_BLK_PORT,LCD_BLK_PIN,GPIO_PIN_SET) //打开背光      
#define LCD_BLK_DISABLE() HAL_GPIO_WritePin(LCD_BLK_PORT,LCD_BLK_PIN,GPIO_PIN_CLEAR)   //关闭背光  

#endif

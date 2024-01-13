/**
 * 本文件基于 STM32 HAL库,是关于LCD屏及驱动相关的配置,在驱动文件 st7735s.h会包含此文件
 * 
 * 不同的MCU,相就的HAL库头文件,或者函数会不同,故独立抽取出来
 * 同一个驱动可能有多个规格的屏,故屏幕的尺寸需要配置
 * 屏的 CS, DC, RST 管脚可能会有变化,故与之相关的内容也要配置
 * */

#ifndef __ST7735S_CONFIG_H
#define __ST7735S_CONFIG_H

#include "stm32f1xx_hal.h" 	// 包含有操作管脚电平的头文件,如 HAL_GPIO_WritePin
#include "gpio_config.h" 	//lcd相关的端口与管脚的宏定义
#include "spi.h" 			//驱动需要用到spi中spiTxlcd函数发送数据

//LCD的屏宽
#define LCD_WIDTH 		128
//LCD的屏高
#define LCD_HEIGHT 		160

//显示内容旋转 0,1,2,3 分别逆时针旋转0,90,180,270度
#define LCD_ROTATION	0

//显示镜像 0,1,2,3 分别为不镜像,水平镜像,垂直镜像,水平与垂直均镜像 
#define LCD_MIRROR 		0

//显存, 目前只支持16bit颜色,显存字节数是此值的2倍
#define DISPLAY_RAM_SIZE		(LCD_WIDTH * 4)

//毫秒延时函数,厂家的毫秒延时函数与STM32 HAL库的不同,请在此替换
//#define HAL_Delay 		HAL_Delay

//请将HAL_GPIO_WritePin替换成对应的函数,或者直接寄存器操作
#define LCD_CS_ENABLE()   HAL_GPIO_WritePin(LCD_CS_PORT,LCD_CS_PIN,GPIO_PIN_RESET)  //片选  
#define LCD_CS_DISABLE()  HAL_GPIO_WritePin(LCD_CS_PORT,LCD_CS_PIN,GPIO_PIN_SET)    //未选中   

#define LCD_DATA_ENABLE() HAL_GPIO_WritePin(LCD_DC_PORT,LCD_DC_PIN,GPIO_PIN_SET)    //高电平数据    
#define LCD_CMD_ENABLE()  HAL_GPIO_WritePin(LCD_DC_PORT,LCD_DC_PIN,GPIO_PIN_RESET)  //低电平命令

#define LCD_RST_ENABLE()  HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN,GPIO_PIN_RESET) //复位,低电平有效      
#define LCD_RST_DISABLE() HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN,GPIO_PIN_SET)   //保持  

#define LCD_BLK_ENABLE()  HAL_GPIO_WritePin(LCD_BLK_PORT,LCD_BLK_PIN,GPIO_PIN_RESET) //打开背光,有些屏无背光      
#define LCD_BLK_DISABLE() HAL_GPIO_WritePin(LCD_BLK_PORT,LCD_BLK_PIN,GPIO_PIN_SET)   //关闭背光  

#endif

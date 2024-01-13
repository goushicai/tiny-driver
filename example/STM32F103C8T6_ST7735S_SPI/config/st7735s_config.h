/**
 * 本文件是关于LCD屏及驱动相关的配置,在驱动文件 ST7735S.h会包含此文件
 *
 * 不同的MCU,相就的HAL库头文件,或者函数会不同,故独立抽取出来
 * 同一个驱动可能有多个规格的屏,故屏幕的尺寸需要配置
 * 屏的 CS, DC, RST 管脚可能会有变化,故与之相关的内容也要配置
 * */

/*
	本程序 是基于 STM32 HAL库的 ST7735S SPI的驱动程序的 配置文件,会被驱动文件 ST7735S.h 包含.
	为便于跨平台移植,将 片选(CS), 命令数据选择(DC,或RS),复位(RST)三个管脚独立出来作为配置,
	其内容在st7735s_config.h文件,开发者需要完成以下几个项内容
	
	1. 包含头文件:
		* GPIO操作相关的头文件,要对管脚进行拉搞或者拉低的操作
		* SPI 批量发送接口所有的头文件,并实现 spiTxlcd(uint8_t *data,uint32_t size) 函数
		
	2. 修改宏定义
		- 毫秒延时函数, 若有必要请用实际的毫秒延时函数替换 HAL_Delay
		- 端口,请修改LCD_CS_PORT,LCD_PORT,LCD_PORT三个端口的实际值,如GPIOA,GPIOB等
		- 管脚,请修改LCD_CS_PIN,LCD_DC_PIN,LCD_RST_PIN三个管脚的实际值,如 GPIO_PIN_3,GPIO_PIN_4等
		- 宏定义函数,请根据实际情况以下六个函数,若不须实现其值可空,宏定义名称不可删改
			#define LCD_CS_ENABLE()  	HAL_GPIO_WritePin(LCD_PORT,LCD_CS_PIN, GPIO_PIN_RESET)    	//片选	
			#define LCD_CS_DISABLE() 	HAL_GPIO_WritePin(LCD_PORT,LCD_CS_PIN, GPIO_PIN_SET) 		//未选中  	
			#define	LCD_DATA_ENABLE()	HAL_GPIO_WritePin(LCD_PORT,LCD_DC_PIN, GPIO_PIN_SET)       //高电平数据    
			#define	LCD_CMD_ENABLE()	HAL_GPIO_WritePin(LCD_PORT,LCD_DC_PIN, GPIO_PIN_RESET)     //低电平命令
			#define	LCD_RST_ENABLE()	HAL_GPIO_WritePin(LCD_PORT,LCD_RST_PIN, GPIO_PIN_RESET)   	//复位,低电平有效		  
			#define	LCD_RST_DISABLE()	HAL_GPIO_WritePin(LCD_PORT,LCD_RST_PIN, GPIO_PIN_SET)  		//保持	
			
	3. 若只有一个屏,且MCU管脚资源紧张,CS可直接接地,若不需要硬件复位功能,RST也可以直接接地 
	
	4. 若需要开启,请完成DMA相关的配置,并实现 spiTxlcdDMA(uint8_t *data,uint32_t size)
	
	5. 当前功能只用SPI驱动屏,暂不支持同一个SPI接口分别控制多个屏
*/

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
#define HAL_Delay 		HAL_Delay

//请将HAL_GPIO_WritePin替换成对应的函数,或者直接寄存器操作
#define LCD_CS_ENABLE()   HAL_GPIO_WritePin(LCD_CS_PORT,LCD_CS_PIN,GPIO_PIN_RESET)  //片选  
#define LCD_CS_DISABLE()  HAL_GPIO_WritePin(LCD_CS_PORT,LCD_CS_PIN,GPIO_PIN_SET)    //未选中   

#define LCD_DATA_ENABLE() HAL_GPIO_WritePin(LCD_DC_PORT,LCD_DC_PIN,GPIO_PIN_SET)    //高电平数据    
#define LCD_CMD_ENABLE()  HAL_GPIO_WritePin(LCD_DC_PORT,LCD_DC_PIN,GPIO_PIN_RESET)  //低电平命令

#define LCD_RST_ENABLE()  HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN,GPIO_PIN_RESET) //复位,低电平有效      
#define LCD_RST_DISABLE() HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN,GPIO_PIN_SET)   //保持  

#define LCD_BLK_ENABLE()  HAL_GPIO_WritePin(LCD_BLK_PORT,LCD_BLK_PIN,GPIO_PIN_RESET) //打开背光      
#define LCD_BLK_DISABLE() HAL_GPIO_WritePin(LCD_BLK_PORT,LCD_BLK_PIN,GPIO_PIN_SET)   //关闭背光  

#endif

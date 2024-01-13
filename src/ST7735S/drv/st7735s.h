/*
//如果使用官方库函数定义下列底层，速度将会下降到14帧每秒，建议采用我司推荐方法
//以下IO定义直接操作寄存器，快速IO操作，刷屏速率可以达到28帧每秒！ 

//GPIO置位（拉高）,端口设置寄存器BSRR 置1为拉高,端口清除寄存器BRR置1为拉低

#define LCD_CS_ENABLE()  	LCD_PORT->BSRR|=(uint32_t)LCD_CS_PIN<<16u    	//片选,低电平有效	
#define LCD_CS_DISABLE() 	LCD_PORT->BSRR|=LCD_CS_PIN						// 	

#define	LCD_CMD_ENABLE()	LCD_PORT->BSRR|=(uint32_t)LCD_DC_PIN<<16u   	//低电平命令
#define	LCD_DATA_ENABLE()	LCD_PORT->BSRR|=LCD_DC_PIN      				//数据    

#define	LCD_RST_ENABLE()	LCD_PORT->BSRR|=(uint32_t)LCD_DC_PIN<<16u   	//复位,低电平有效		  
#define	LCD_RST_DISABLE()	LCD_PORT->BSRR|=LCD_RST_PIN 					//复位	

///////////////////////////////////////////////////////////////////////////////////////////

//国产mcu的库函数,寄存器可能不同
//为方便移植，并尽量减少对驱动文件的修改，这部分几个函数转移到 gpio.h中

#define LCD_CS_ENABLE()  	HAL_GPIO_WritePin(LCD_PORT,LCD_CS_PIN, GPIO_PIN_RESET)    	//片选	
#define LCD_CS_DISABLE() 	HAL_GPIO_WritePin(LCD_PORT,LCD_CS_PIN, GPIO_PIN_SET) 		//未选中  	

#define	LCD_DATA_ENABLE()	HAL_GPIO_WritePin(LCD_PORT,LCD_DC_PIN, GPIO_PIN_SET)       //高电平数据    
#define	LCD_CMD_ENABLE()	HAL_GPIO_WritePin(LCD_PORT,LCD_DC_PIN, GPIO_PIN_RESET)     //低电平命令

#define	LCD_RST_ENABLE()	HAL_GPIO_WritePin(LCD_PORT,LCD_RST_PIN, GPIO_PIN_RESET)   	//复位,低电平有效		  
#define	LCD_RST_DISABLE()	HAL_GPIO_WritePin(LCD_PORT,LCD_RST_PIN, GPIO_PIN_SET)  		//保持	
*/

/**
*******************************以下为引用****************************************

//如果使用官方库函数定义下列底层，速度将会下降到14帧每秒，建议采用我司推荐方法
//以下IO定义直接操作寄存器，快速IO操作，刷屏速率可以达到28帧每秒！ 

*******************************引用结束******************************************

以上认为是寄存器操作引起的速度变化是错误的, GPIO 速度的远小于SPI, 
最影响速度的操作是频繁的 GPIO 操作,即不断地操作CS,D/C,
在批量发送数据时,把D/C拉高,再用HAL_SPI_Transmit 发送数据即可,大大减少 GPIO 的操作

SPI时钟18M的情况下,刷新率可以轻松达到50FPS,用DMA还可以提升速度,但完全没有必要

* 测试平台：SMT32F103C8T6核心开发板(正点原子M48Z), 1.8寸 128*160 ST7735S驱动 LCD 显示屏 
* 系统时钟: 72M
* SPI时钟: 18M
* 开发环境: Keil 5.29 , STM32 HAL 库

以下不同显存情况下，用不同的16bit颜色清屏(128*160)刷新的的 FPS 数据

无编译优化

DisRam	|256	|512	|1024	|2048	|3072	|4096	|5120	|6144	|7168	|8192
--------|-------|-------|-------|-------|-------|-------|-------|-------|-------|------
no dma	|45.68	|46.43	|46.69	|46.6	|46.36	|46.13	|45.85	|45.58	|45.31	|45.05
by dma	|51.12	|53.02	|53.91	|54.05	|53.79	|53.59	|53.16	|52.83	|52.47	|52.27
性能提升|10.64%	|12.43%	|13.39%	|13.78%	|13.81%	|13.92%	|13.75%	|13.72%	|13.65%	|13.81%


开启 O1 编译优化后

DisRam	|256	|512	|1024	|2048	|3072	|4096	|5120	|6144	|7168	|8192
--------|-------|-------|-------|-------|-------|-------|-------|-------|-------|------
no dma	|51.33	|52.14	|52.49	|52.49	|52.36	|52.19	|52		|51.79	|51.6	|51.39
by dma	|51.71	|53.39	|54.17	|54.38	|54.35	|54.05	|54.05	|53.82	|53.62	|53.11
性能提升|0.73%	|2.34%	|3.10%	|3.48%	|3.66%	|3.44%	|3.79%	|3.77%	|3.77%	|3.24%

可以看出,开启编译优化后,无DMA的与有DMA的性能相差在很小.

还可以看出显存并不是越多性能越好,显存在大约2048附近性能最佳,可能与SPI的机制有关
显存不能于低于16byte,低于16byte字符显示功能会有异常


以上数据仅做参考,不同的代码组织,不同的硬件平台测得的数据会略有不同

对于嵌入式开发,25以上的fps已足够使用,采用DMA方式再提升刷新性能并无意义，而由此占用了dma资源,
并且由于DMA中断,导致代码结构复杂,与其它功能耦合,不利于移植与复用,综合来看,不建议启用DMA

只有在以下两种场景下，可以考虑启用DMA

1. MCU负载较重，用DMA减轻显示的MCU的负载
2. RAM资源足够，能设置全屏显存,可以用DMA一次性刷新全屏,而不必分批发送,全屏显存可以做一些复杂的显示操作,
	全屏显存会导致FPS性能略有下降,若屏支持,可以考虑使用24位以达到更好的显示效果,本驱动暂只支持16位颜色

根据S7735S的官方文档,时钟周期(TSCYCW,Serial Clock Cycle (Write))最小值为66ns,按全屏128*160*16bit数据计算,
刷屏一次约需要21.6ms,FPS约46,若假设时钟信号为理想的方波,只考虑时钟高低电平的持续时间,
其最小周其约为 TSHW + TSLW = 30ns, 可以计算得到时钟周期约33.3M,FPS约为102

从实际的测试结果看,官方文档非常保守(或者官方文档已过时,我参考的版本是V1.5_20150303).
用ACM32F403测试,SPI时钟在22.5M时, FPS可达到67左右,当SPI时钟置为45,开启编译优化后,测得FPS约136,刷新显示依然正常

*/

#ifndef __DRV_ST7735S_H
#define __DRV_ST7735S_H

#include "st7735s_config.h"

//命令未完成列出
#define LCD_CMD_SOFT_RESET		0x01 		// Software Reset

#define LCD_CMD_SLEEP_IN		0x10        //进入睡眠模式
#define LCD_CMD_SLEEP_OUT		0x11        //退出睡眠模式

#define LCD_CMD_INVERSION_OFF	0x20        //关闭反色
#define LCD_CMD_INVERSION_ON	0x21        //开启反色

#define LCD_CMD_DISPLAY_OFF		0x28        //关闭显示
#define LCD_CMD_DISPLAY_ON		0x29        //开启显示

#define LCD_CMD_SET_COLUMN		0x2A        //纵地址设置
#define LCD_CMD_SET_ROW       	0x2B        //页地址设置
#define LCD_CMD_MEMORY_WRITE	0x2C        //内存写

#define LCD_CMD_IDLE_OFF		0x38        //关闭空闲模式
#define LCD_CMD_IDLE_ON			0x39        //开启空闲模式

#define LCD_CMD_MADCTL			0x36        //Memory Access Control,MY,MX,MV,ML,RGB,MH等

#if(LCD_SPI_ENABLE_DMA == 1)
extern volatile uint8_t  dmaSpiTxState;
#endif

typedef enum {
	LCD_STATUS_OK 			= 0x00U,		//前4个继承 HAL_StatusTypeDef
	LCD_STATUS_ERROR    = 0x01U,
	LCD_STATUS_BUSY 		= 0x02U,
	LCD_STATUS_TIMEOUT 	= 0x03U,
	
	LCD_STATUS_X_LESS_THAN_MIN 	= 0x10U,
	LCD_STATUS_X_MORE_THAN_MAX 	= 0x11U,
	
	LCD_STATUS_Y_LESS_THAN_MIN 	= 0x12U,
	LCD_STATUS_Y_MORE_THAN_MAX 	= 0x13U,
	
	LCD_STATUS_WIDTH_LESS_THAN_MIN 	= 0x14U,
	LCD_STATUS_HEIGHT_LESS_THAN_MIN	= 0x15U
	
} LcdStatusTypeDef;

//初始化
LcdStatusTypeDef lcdInit(void);

//复位
LcdStatusTypeDef lcdReset(void);

//进入睡眠模式
LcdStatusTypeDef lcdSleepIn(void);

//退出睡眠模式
LcdStatusTypeDef lcdSleepOut(void);

//打开反色
LcdStatusTypeDef lcdInvertionOn(void);

//关闭反色
LcdStatusTypeDef lcdInvertionOff(void);

//打开显示
LcdStatusTypeDef lcdDisplayOn(void);

//关闭显示
LcdStatusTypeDef lcdDisplayOff(void);

//打开空闲模式
LcdStatusTypeDef lcdDisplayIdleOn(void);

//关闭空闲模式
LcdStatusTypeDef lcdDisplayIdleOff(void);

//发送命令
LcdStatusTypeDef lcdCmd(uint8_t cmd);

//发送单字节数据
LcdStatusTypeDef lcdByte(uint8_t data);

//发送双字节数据
LcdStatusTypeDef lcdHalfWord(uint16_t data);

//发送两个双字节数据
LcdStatusTypeDef lcdWord(uint16_t d1, uint16_t d2);

//发送多字节数据
LcdStatusTypeDef lcdData(uint8_t *p, uint32_t size);

//设置屏幕方向
LcdStatusTypeDef lcdRotation(uint8_t direction); 

//设置屏幕镜像
LcdStatusTypeDef lcdMirror(uint8_t mirror);

//设置显示区域
LcdStatusTypeDef lcdArea(int16_t x,int16_t y,int16_t w,int16_t h);

//设置位置
LcdStatusTypeDef lcdPosition(int16_t x,int16_t y);

//描点
LcdStatusTypeDef lcdPixel(int16_t x,int16_t y, uint16_t color);

//画直线
LcdStatusTypeDef lcdLine(int16_t x0,int16_t y0,int16_t x1,int16_t y1,uint16_t color,int16_t lineWidth);

//清屏/全屏涂色
LcdStatusTypeDef lcdClear(uint16_t color);

//区块涂色
LcdStatusTypeDef lcdBlock(int16_t x,int16_t y, int16_t w,int16_t h,uint16_t color);

//单色位图
LcdStatusTypeDef lcdMonocolour(int16_t x,int16_t y, int16_t w,int16_t h,uint16_t color,uint16_t bgColor, char *data);
  		 
#endif

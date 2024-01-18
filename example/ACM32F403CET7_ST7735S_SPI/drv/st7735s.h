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

typedef enum {
	LCD_STATUS_OK 			= 0x00U,		//前4个继承 HAL_StatusTypeDef
	LCD_STATUS_ERROR    	= 0x01U,
	LCD_STATUS_BUSY 		= 0x02U,
	LCD_STATUS_TIMEOUT 		= 0x03U,
	
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

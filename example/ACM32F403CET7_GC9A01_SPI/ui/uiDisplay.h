/**
 * UI组件定义
 *
 * */

#ifndef __DISPLAY_UI_H__
#define __DISPLAY_UI_H__

#include "drvGC9A01.h"
#include "fontLib.h"
#include "icon.h"
#include "uiCommon.h"

#define INPUT_BG_COLOR        		0x3186 	//文本框背景颜色
#define INPUT_TEXT_COLOR        	0xFFFF 	//文本颜色
#define INPUT_TEXT_FONT_SIZE     	24 		//文本字体
#define INPUT_BORDER_COLOR 			0xFFFF 	//文本边框颜色0xFEFEFE
#define INPUT_LEFT 					60 		//文本框位置
#define INPUT_TOP 					108
#define INPUT_PADDING 				1
#define INPUT_BORDER_WIDTH 			1 
#define INPUT_WIDTH 				120
#define INPUT_HEIGHT				32
#define DISP_RAM_SIZE				1024*2


//颜色倒转打开
void uiDisplayInversionOn();
//颜色倒转关闭
void uiDisplayInversionOff();

void uiDisplayBrightness(uint8_t bright);

void uiDisplayCtrl(uint8_t val);

//清屏
void uiClear(uint16_t color);

//填充矩形
void uiFillRectangle(uint16_t x,uint16_t y, uint16_t w,uint16_t h,uint16_t color);

//画点
void uiDrawPoint(uint16_t x, uint16_t y, uint16_t color);

//画线
void uiDrawLine(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1, uint16_t color);

//画空心圆
void uiDrawCircle(uint16_t x,uint16_t y ,uint16_t r, uint16_t color);

//填充圆
void uiFillCircle(uint16_t x,uint16_t y ,uint16_t r, uint16_t color);

//画环
void uiDrawRing(uiRing ring);

//画圆弧
void uiDrawArc(uiArc arc);

//显示图片
void uiShowImage(uint16_t left,uint16_t top, uint16_t width,uint16_t height,uint8_t * imgData);
	
//显示图标
void uiShowIcon(uint16_t x,uint16_t y, uint8_t iconIdx,uint8_t iconSize, uint16_t color,uint16_t bgColor);
	
//显示单个ascii字符
void uiShowAscii(uint16_t x,uint16_t y, uint8_t ch, uint16_t fontSize,uint16_t color,uint16_t bgColor);

//显示单个汉字字符
void uiShowChinese(uint16_t x,uint16_t y, uint16_t ch,uint16_t fontSize, uint16_t color,uint16_t bgColor);

//显示汉字与ascii混和文本
void uiShowText(uiText txt);

//获取一个默认的文本框对象
uiText getUiTextInstance();


#endif  //__UI_DISPLAY_H__
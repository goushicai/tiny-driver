/**
	UI组件结构体定义
*/

#ifndef __UI_TYPEDEF_H
#define __UI_TYPEDEF_H

#include "stm32f1xx_hal.h" 

//颜色
typedef struct{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha; //透明度0完全不透明,255完全透明,需要简易Alpha混合算法
} uiColor;

//端点
typedef struct{
	int16_t x;
	int16_t y;
} uiPoint;

//像素
typedef struct{
	int16_t x;
	int16_t y;
	uiColor color;
} uiPixel;

//直线
typedef struct{
	uiPoint head; //起点
	uiPoint tail; //终点
	uiColor color;
} uiLine;

//矩形
typedef struct{
	uiPoint leftTop; //左上角
	uiPoint rightBottom; //右下角
	int16_t width;
	int16_t height;
	uint16_t lineWidth; //矩形边框的宽度,lineWidth=0不画边框
	uiColor lineColor; //矩形边框的颜色
	uiColor fillColor; //矩形内部的填充颜色,若透明则不填充
} uiRectangle;

typedef struct{
	uiRectangle border; //边框
	uint8_t *text; //文本
	uint16_t fontSize; //字符的高度,只考虑两种情况,ascii字符宽度为高度的一半,中文长宽一致
	uint16_t lineWidth;
	uiColor fontColor; //字符颜色
	uiColor bgColor; //背景颜色
} uiLabel;

typedef struct{
	uiRectangle border; //边框	
	uiColor fontColor; //字符颜色
	uiColor bgColor; //背景颜色
	uint32_t value; //值,文本按type转成相应的值,若为字符串,则值text的size
	uint8_t *text; //文本
	uint8_t type; //有符号整数,无符号整数,浮点数,字符串,rtcData,rtcTime
	uint8_t align; //居中方式,高4位为水平居中方式,0靠左,1居中,2靠右, 低4位为垂直居中方式,0垂直居中,1靠上,2靠下
	uint8_t fontSize; //字符的高度,只考虑两种情况,ascii字符宽度为高度的一半,中文长宽一致
	uint8_t mode; //[7]0水平1垂直,[6]0左到右,1右到左,[5]0单行,1多行,[4]0不换行,1自动换行,[3]0溢出截断,1溢出显示
} uiInput;


#endif

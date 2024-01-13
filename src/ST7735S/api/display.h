#ifndef __DISPLAY_H

#define __DISPLAY_H

#include "display_config.h"

//初始化
void displayInit(void);

//进入睡眠模式
void displaySleepOn(void);

//退出睡眠模式
void displaySleepOff(void);

//打开反色模式
void displayInvertionOn(void);

//打开反色模式
void displayInvertionOff(void);

//打开空闲模式
void displayIdleOn(void);

//打开空闲模式
void displayIdleOff(void);

//打开显示
void displayOn(void);

//关闭显示
void displayOff(void);

//调节亮度,未实现,若屏幕不支持调节亮度,可以考虑用pwm调整背光led的亮度实现
void displayBrightness(uint8_t val);

//复位
void displayReset(void);

//显示方向设置, 0默认,1逆时钟转90度,2逆时钟转180度,3逆时钟转270度
void displayRotation(uint8_t rotation);

//显示镜像, 0默认,1仅水平镜像,2仅垂直镜像,3水平垂直均镜像
void displayMirror(uint8_t mirror);

//清屏
void displayClear(uint16_t color);

//画一个像素
void drawPixel(int16_t x,int16_t y,uint16_t color);

//画直线,带宽度
void drawLine(int16_t x0,int16_t y0,int16_t x1,int16_t y1,uint16_t color,uint16_t lineWidth);

//画空心矩形
void drawRectangle(int16_t x,int16_t y,uint16_t w,uint16_t h,uint16_t lineColor,uint16_t lineWidth);

//填充矩形
void fillRectangle(int16_t x,int16_t y,uint16_t w,uint16_t h,uint16_t fillColor);

//画圆
void drawCircle(int16_t x,int16_t y ,uint16_t r, uint16_t color);

//填充圆
void fillCircle(int16_t x,int16_t y ,uint16_t r, uint16_t color);

//单色位图,可显示的ascii字符
void drawAscii(char ch, FontSize fontSize, int16_t x,int16_t y, uint16_t color,uint16_t bgColor);

//汉字
void drawChinese(uint16_t gbkCode, FontSize fontSize, int16_t x,int16_t y, uint16_t color,uint16_t bgColor);

//显示图片,16位位图
void drawImage(int16_t x,int16_t y,int16_t w,int16_t h, uint8_t *imgData);


#endif

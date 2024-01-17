/**
 * 进度条
 *
 * 环形进度条
 *
 *  在屏外围画一个圈, 进度达到100% 延时200ms后自动关闭

 * 操作提示:
 *    showSuccess();
 *    showFail();
 *    直接显示 100%进度,绿色 100ms 闪烁2 次 代表 操作成功
 *    直接显示 100%进度,红色 100ms 闪烁2 次 代表 操作失败
 *
 * */


#ifndef __PROGRESS_H__
#define __PROGRESS_H__

#include "uiDisplay.h"

/************** 进度条相关配置 *********************/
//环形进度条宽度
#define PROGRESS_LINE_WIDTH 3
#define FEEDBACK_TWKINLE_DURATION 200


//显示当前进度
void showProgress(uint8_t percent); //若输入数值小于当前值,认为进度倒退

//关闭进度条
/***
 *  delay : 延时关闭, ms
 *  style : 0 无, 1 闪烁
 * */
void closeProgress(uint8_t delay, uint8_t style);

void showTwkinle(uint16_t color,uint16_t bgColor );
void successTwkinle(uint16_t bgColor);

void failTwkinle(uint16_t bgColor);

void showProgressWater(uint8_t percent, uint16_t color,uint16_t bgColor);

#endif  //__PROGRESS_H__
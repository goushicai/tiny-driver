/**
 * 文本页
 *
 * */


#ifndef __TEXT_VIEW_H__
#define __TEXT_VIEW_H__

#include "uiDisplay.h"
#include "encoder.h"
#include "event.h"

#define TEXT_VIEW_COLOR       			0xFFDF 	//菜单标题显示坐标
#define TEXT_VIEW_BG_COLOR       		0x3186 	//菜单标题显示坐标
#define TEXT_VIEW_LEFT       			40 		//菜单标题显示坐标
#define TEXT_VIEW_TOP       			40 		//菜单标题显示坐标
#define TEXT_VIEW_WIDTH       			160
#define TEXT_VIEW_HEIGHT       			160
#define TEXT_VIEW_FONT_SIZE    			FONT_SIZE_32
#define TEXT_VIEW_MAX_COLS    			32 		//每行最多显示ascii字符数

void showTextView(char * text);

//计算文本的行数,支持换行符\n,回车符\r等同换行
uint16_t getTextRows(char *text, uint8_t colSize);

void scrollUp();

void scrollDown();

void TextViewChangeFontSize();

enumViewEvent getTextViewEvent();
#endif  //__TEXT_VIEW_H__
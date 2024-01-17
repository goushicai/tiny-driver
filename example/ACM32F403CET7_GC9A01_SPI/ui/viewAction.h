/**
 * 操作页
 *
 * 函数:
 *
 * 		显示操作页(title, 输入文本框,默认值,显示键盘)
		旋转,修改显示数值(无键盘), 修改选中按钮
		单击,输入当前选中值
		双击,退出当前面
		长按,确认输入

 * */

#ifndef __ACTION_VIEW_H__
#define __ACTION_VIEW_H__

#include <math.h> //用到sin,cos
#include <stdio.h> //用到sprinft
#include <string.h> //用到strlen
#include "keyboard.h" //键盘
#include "option.h" //系统参数
#include "event.h"

/************** 操作页相关配置 *********************/
#define ACTION_BG_COLOR				0x3186 	//操作页默认背景色 0x2222
#define ACTION_TITLE_COLOR			0xFFDF 	//操作页标题颜色 0xFEFEFE
#define ACTION_TITLE_FONT_SIZE		32		//操作页标题字体
#define ACTION_TITLE_LEFT			56 		//操作页标题显示坐标,居中显示
#define ACTION_TITLE_TOP       		75
#define ACTION_TITLE_WIDTH 			128

#define ACTION_INPUT_COLOR 			0xFFDF
#define ACTION_INPUT_BG_COLOR 		0x3186
#define ACTION_INPUT_BORDER_COLOR 	0xFFDF
#define ACTION_INPUT_ERROR_COLOR 	0xF800
#define ACTION_INPUT_FONT_SIZE 		32
#define ACTION_INPUT_LEFT 			56
#define ACTION_INPUT_TOP 			120
#define ACTION_INPUT_WIDTH 			128
#define ACTION_INPUT_BORDER_WIDTH 	1
#define ACTION_INPUT_PADDING 		2

#define ACTION_ERROR_COLOR 			0xFFDF
#define ACTION_ERROR_BG_COLOR 		0xC985
#define ACTION_ERROR_BORDER_COLOR 	0xFFDF
#define ACTION_ERROR_FONT_SIZE 		24
#define ACTION_ERROR_LEFT 			40
#define ACTION_ERROR_TOP 			160
#define ACTION_ERROR_WIDTH 			160
#define ACTION_ERROR_BORDER_WIDTH 	0
#define ACTION_ERROR_PADDING 		0

//显示操作页
void showActionView(Menu menu);

//显示键盘输入
void showActionText();

//在无键盘的情况,编码器旋转,直接修改数值
void InputValueNext();

void InputValuePrev();

void InputCurrentValue();

//保存修改
void saveAction();

enumViewEvent getActionViewEvent();
#endif  //__ACTION_VIEW_H__

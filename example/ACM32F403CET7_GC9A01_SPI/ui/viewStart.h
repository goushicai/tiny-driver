/**
 * 开始页
 *
 * 函数:
 *  自检
	读取菜单数据

 *
 * */


#ifndef __START_VIEW_H__
#define __START_VIEW_H__

#include "uiDisplay.h"

/****************** 菜单页相关配置 ************/

#define START_TEXT_LEFT           		20
#define START_TEXT_TOP          		90
#define START_TEXT_WIDTH           		200
#define START_TEXT_FONT_SIZE        	32

#define START_TEXT_COLOR           		0xFFDF  //文本颜色
#define START_BG_COLOR           		0x0000 	//背景颜色

#define START_PROGRESS_LEFT           	56 	
#define START_PROGRESS_TOP           	160
#define START_PROGRESS_WIDTH           	128
#define START_PROGRESS_HEIGHT           5
#define START_PROGRESS_SETP           	4
#define START_PROGRESS_DURATION         50
#define START_PROGRESS_COLOR           	0x07E0 	//进度条颜色

void showStartView();

void showStartProgress();

//更新启动次数
void updateStartCount();


#endif  //__START_VIEW_H__
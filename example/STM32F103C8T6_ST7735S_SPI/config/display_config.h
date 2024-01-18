#ifndef __DISPLAY_CONFIG_H

#define __DISPLAY_CONFIG_H

#include "st7735s.h"
#include "color.h"
#include "font.h"
#include "pic.h"

/***
[TO_MODITY]

在驱动中已有LCD_WIDTH,LCD_HEIGHT等参数,为什么在显示接口中又有类似的参数

原因驱动层的LCD的宽高是物理宽高,而显示接口层SCREEN的宽高是逻辑概念,
若有必要可以通过复制一份display,并做相应修改,实现对同一个LCD屏的分屏显示功能
或者把 SCREEN 相关的参数做成结构体,对同一LCD屏实现多个SCREEN实例
对于小型的LCD屏这个意义并不大,暂不实现
*/

//屏宽度
#define SCREEN_WIDTH	LCD_WIDTH
//屏高度
#define SCREEN_HEIGHT	LCD_HEIGHT
//水平偏移
#define SCREEN_OFFSET_X	0
//垂直偏移
#define SCREEN_OFFSET_Y	0

//屏幕旋转角度 0默认,1 逆时针转90度, 2 逆时针转180度,  3 逆时针转270度
#define SCREEN_ROTATION	0

//屏幕镜像 0默认,1 水平镜像, 2 垂直镜像,  3 水平垂直均镜像
#define SCREEN_MIRROR 	0


#endif

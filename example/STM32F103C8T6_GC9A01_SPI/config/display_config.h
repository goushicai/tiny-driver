#ifndef __DISPLAY_CONFIG_H

#define __DISPLAY_CONFIG_H

#include "gc9a01.h"
#include "color.h"
#include "font.h"
#include "pic.h"

/***
	若只希望数据在屏的一部分,可以通过屏宽,屏高,以及水平垂直偏移4个参数,
	并在 display.c中对相应的函数进行修改
*/
//屏宽度
#define SCREEN_WIDTH	240
//屏高度
#define SCREEN_HEIGHT	240
//水平偏移
#define SCREEN_OFFSET_X	0
//垂直偏移
#define SCREEN_OFFSET_Y	0

//屏幕旋转角度 0默认,1 逆时针转90度, 2 逆时针转180度,  3 逆时针转270度
#define SCREEN_ROTATION	0

//屏幕镜像 0默认,1 水平镜像, 2 垂直镜像,  3 水平垂直均镜像
#define SCREEN_MIRROR 	0


#endif

/**
 * 空闲页
 *
 * */


#ifndef __IDEL_VIEW_H__
#define __IDEL_VIEW_H__

#include "uiDisplay.h"
#include "rtc.h"
#include "encoder.h"
#include "event.h"

#define IDEL_TIMEOUT    1200 //超过时间,自动进入空闲状态 默认120秒

#define IDEL_VIEW_COLOR       		0xFFDF 	//标题显示
#define IDEL_VIEW_BG_COLOR       	0x0000 	//标题显示
#define IDEL_VIEW_FONTSIZE     		32 		//标题显示

#define IDEL_VIEW_DATE_LEFT       	40 		//标题显示
#define IDEL_VIEW_DATE_TOP       	90 		//标题显示
#define IDEL_VIEW_DATE_WIDTH       	160 	//标题显示

#define IDEL_VIEW_TIME_LEFT       	40 		//标题显示
#define IDEL_VIEW_TIME_TOP       	130 	//标题显示
#define IDEL_VIEW_TIME_WIDTH       	160 	//标题显示

void showIdelView();

void showDateTime();

enumViewEvent getIdelViewEvent();
#endif  //__IDEL_VIEW_H__
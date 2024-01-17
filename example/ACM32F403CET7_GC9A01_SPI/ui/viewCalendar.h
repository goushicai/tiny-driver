/**
 * 日历设置页面
 *
 *
 * */

#ifndef __VIEW_CALENDAR_H__
#define __VIEW_CALENDAR_H__

#include "stdlib.h"
#include "uiDisplay.h"
#include "keyboard.h"
#include "rtc.h"

#define CAL_BG_COLOR			0x3186 	//默认背景色 0x2222
#define CAL_TITLE_COLOR			0xFFDF 	//标题颜色 0xFEFEFE
#define CAL_TITLE_FONT_SIZE		32		//标题字体
#define CAL_TITLE_LEFT			40 		
#define CAL_TITLE_TOP       	90
#define CAL_TITLE_WIDTH 		160

#define CAL_INPUT_COLOR 		0xFFDF
#define CAL_INPUT_BG_COLOR 		0x3186
#define CAL_INPUT_BORDER_COLOR 	0xFFDF
#define CAL_INPUT_FONT_SIZE 	32
#define CAL_INPUT_LEFT 			40
#define CAL_INPUT_TOP 			130
#define CAL_INPUT_WIDTH 		50
#define CAL_INPUT_BORDER_WIDTH 	1
#define CAL_INPUT_PADDING 		2

void showCalendarView(uint8_t type);

//修改日历的事件
void calendarEvent();

void setCalYear(uint8_t val);

void setCalMonth(uint8_t val);

void setCalDate(uint8_t val);

void setCalHour(uint8_t val);

void setCalMinute(uint8_t val);

void setCalSecond(uint8_t val);

#endif  //__VIEW_CALENDAR_H__

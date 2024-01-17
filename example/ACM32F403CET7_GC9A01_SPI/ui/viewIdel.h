/**
 * ����ҳ
 *
 * */


#ifndef __IDEL_VIEW_H__
#define __IDEL_VIEW_H__

#include "uiDisplay.h"
#include "rtc.h"
#include "encoder.h"
#include "event.h"

#define IDEL_TIMEOUT    1200 //����ʱ��,�Զ��������״̬ Ĭ��120��

#define IDEL_VIEW_COLOR       		0xFFDF 	//������ʾ
#define IDEL_VIEW_BG_COLOR       	0x0000 	//������ʾ
#define IDEL_VIEW_FONTSIZE     		32 		//������ʾ

#define IDEL_VIEW_DATE_LEFT       	40 		//������ʾ
#define IDEL_VIEW_DATE_TOP       	90 		//������ʾ
#define IDEL_VIEW_DATE_WIDTH       	160 	//������ʾ

#define IDEL_VIEW_TIME_LEFT       	40 		//������ʾ
#define IDEL_VIEW_TIME_TOP       	130 	//������ʾ
#define IDEL_VIEW_TIME_WIDTH       	160 	//������ʾ

void showIdelView();

void showDateTime();

enumViewEvent getIdelViewEvent();
#endif  //__IDEL_VIEW_H__
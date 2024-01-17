/**
 * ͼƬҳ
 *
 * */


#ifndef __PIC_VIEW_H__
#define __PIC_VIEW_H__

#include "uiDisplay.h"
#include "encoder.h"
#include "event.h"
#include "pic.h"
#include "qr_encode.h"

#define PIC_TITLE_COLOR       		0x3186 	//标题显示
#define PIC_TITLE_BG_COLOR       	0xFFDF 	//标题显示
#define PIC_TITLE_LEFT       		56 		//标题显示
#define PIC_TITLE_TOP       		100 	//标题显示
#define PIC_TITLE_WIDTH       		128 	//标题显示
#define PIC_TITLE_FONTSIZE     		24 		//标题显示

void showPicView();

void showPicById(uint8_t picId);

enumViewEvent getPicViewEvent();

#endif  //__PIC_VIEW_H__
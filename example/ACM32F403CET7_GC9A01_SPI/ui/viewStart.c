/**
 * 菜单页
 *
 * */

#include "viewStart.h"

void showStartView()
{
	uiClear(START_BG_COLOR);
	
	uiText txtOpt = getUiTextInstance();
	
	txtOpt.left = START_TEXT_LEFT;
	txtOpt.top  = START_TEXT_TOP ;
	txtOpt.fontSize = START_TEXT_FONT_SIZE;
	txtOpt.color = START_TEXT_COLOR;
	txtOpt.bgColor = START_BG_COLOR;
	txtOpt.borderColor = START_BG_COLOR;
	txtOpt.width = START_TEXT_WIDTH;
	txtOpt.align = ALIGN_CENTER;
	txtOpt.text = (char *) &hzFontText[0];
	uiShowText(txtOpt);
	
	txtOpt.left = START_TEXT_LEFT;
	txtOpt.top  = START_TEXT_TOP +  FONT_SIZE_32;
	txtOpt.fontSize = FONT_SIZE_24;
	txtOpt.color = START_TEXT_COLOR;
	txtOpt.bgColor = START_BG_COLOR;
	txtOpt.borderColor = START_BG_COLOR;
	txtOpt.width = START_TEXT_WIDTH;
	txtOpt.align = ALIGN_CENTER;
	txtOpt.text = (char *) &hzFontText[1];
	uiShowText(txtOpt);
	
};

void showStartProgress(){
	uint16_t left=0;
	left = START_PROGRESS_LEFT;
	while(left<START_PROGRESS_LEFT + START_PROGRESS_WIDTH){
		uiFillRectangle( left ,START_PROGRESS_TOP, START_PROGRESS_SETP,START_PROGRESS_HEIGHT,START_PROGRESS_COLOR);
		left += START_PROGRESS_SETP;
		System_Delay_MS(START_PROGRESS_DURATION);
	}
}
//更新启动次数与本次开机时间
void updateStartCount()
{
    //启动次数
    uint32_t startCount;
    //上次开机时间, YYMMddmm 如2023-0-01 08:30: 2309010830 uint32足够用
    uint32_t lastStartTime;
}
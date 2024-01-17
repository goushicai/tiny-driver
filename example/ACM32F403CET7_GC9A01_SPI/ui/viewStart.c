/**
 * �˵�ҳ
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
//�������������뱾�ο���ʱ��
void updateStartCount()
{
    //��������
    uint32_t startCount;
    //�ϴο���ʱ��, YYMMddmm ��2023-0-01 08:30: 2309010830 uint32�㹻��
    uint32_t lastStartTime;
}
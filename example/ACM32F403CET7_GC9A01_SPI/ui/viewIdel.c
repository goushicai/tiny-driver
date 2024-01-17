/**
 * ����ҳ
 *
 * */

#include "viewIdel.h"

uiText txtOption;

static uint8_t rtcToday=0xFF;

void displayRtcDate(){
	txtOption.left = IDEL_VIEW_DATE_LEFT;
	txtOption.top  = IDEL_VIEW_DATE_TOP;
	txtOption.fontSize = IDEL_VIEW_FONTSIZE;
	txtOption.color = IDEL_VIEW_COLOR;
	txtOption.bgColor = IDEL_VIEW_BG_COLOR;
	txtOption.width = IDEL_VIEW_DATE_WIDTH;
	txtOption.align = ALIGN_CENTER;
	txtOption.text = getRtcDateString();
	uiShowText(txtOption);
}

void displayRtcTime(){
	txtOption.left = IDEL_VIEW_TIME_LEFT;
	txtOption.top  = IDEL_VIEW_TIME_TOP;
	txtOption.fontSize = IDEL_VIEW_FONTSIZE;
	txtOption.color = IDEL_VIEW_COLOR;
	txtOption.bgColor = IDEL_VIEW_BG_COLOR;
	txtOption.width = IDEL_VIEW_TIME_WIDTH;
	txtOption.align = ALIGN_CENTER;
	txtOption.text = getRtcTimeString();
	uiShowText(txtOption);
}

void showDateTime(){
	if(rtcToday != getRtcDate()){
		rtcToday = getRtcDate();
		displayRtcDate();
	}
	
	displayRtcTime();
}


void showIdelView()
{
	uiClear(IDEL_VIEW_BG_COLOR);
	displayRtcDate();
	showDateTime();
}


//��ȡҳҳ�¼�
enumViewEvent getIdelViewEvent()
{
    int8_t encoderValue,encoderEvent;
    enumViewEvent event = VIEW_EVENT_NONE;
	
	encoderValue = getEncoderVal();
    encoderEvent= getKeyVal();
	
	if(encoderValue != 0 && encoderEvent !=ENCODER_EVENT_NONE) {      //�˻ص��ϼ��˵�
		event = VIEW_EVENT_BACK;
    }
	

    return event;
}
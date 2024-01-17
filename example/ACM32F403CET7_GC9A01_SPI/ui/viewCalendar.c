#include "viewCalendar.h"

uiText calTitle,calInput1,calInput2,calInput3;
RTC_DateTypeDef calDate;
RTC_TimeTypeDef calTime;
char calText[4];
uint8_t calType = 0; //0显示日期与时间,1修改年月日,2修改时分秒 
uint8_t calState = 0;// 0显示只读,1修改年,2修改月,3修改日,4修改时,5修改分,6修改秒


void calUpdate(){
	if(calType == 0){
		HAL_RTC_GetDate(&calDate);
		HAL_RTC_GetTime(&calTime);
		
		calTitle.text = getRtcDateString();
		uiShowText(calTitle);
		calTitle.top  = CAL_INPUT_TOP;
		calTitle.text = getRtcTimeString();
		uiShowText(calTitle);
	}
}

void calTextInit(){
	calTitle = getUiTextInstance();
	calTitle.left 			= CAL_TITLE_LEFT;
	calTitle.top  			= CAL_TITLE_TOP;
	calTitle.width 			= CAL_TITLE_WIDTH;
	calTitle.borderWidth	= 0;
	calTitle.padding		= 0;
	calTitle.fontSize 		= CAL_TITLE_FONT_SIZE;
	calTitle.color 			= CAL_TITLE_COLOR;
	calTitle.bgColor 		= CAL_BG_COLOR;
	calTitle.borderColor 	= CAL_BG_COLOR;
	calTitle.align 			= ALIGN_CENTER;
	
	calInput1 = getUiTextInstance();
	calInput1.left 			= CAL_INPUT_LEFT;
	calInput1.top  			= CAL_INPUT_TOP;
	calInput1.width 		= CAL_INPUT_WIDTH;
	calInput1.borderWidth	= CAL_INPUT_BORDER_WIDTH;
	calInput1.padding		= CAL_INPUT_PADDING;
	calInput1.fontSize 		= CAL_INPUT_FONT_SIZE;
	calInput1.color 		= CAL_INPUT_COLOR;
	calInput1.bgColor 		= CAL_INPUT_BG_COLOR;
	calInput1.borderColor 	= CAL_INPUT_BORDER_COLOR;
	calInput1.align 		= ALIGN_CENTER;
	
	calInput2 = getUiTextInstance();
	calInput2.left 			= calInput1.left + calInput1.width +5;
	calInput2.top  			= CAL_INPUT_TOP;
	calInput2.width 		= CAL_INPUT_WIDTH;
	calInput2.borderWidth	= CAL_INPUT_BORDER_WIDTH;
	calInput2.padding		= CAL_INPUT_PADDING;
	calInput2.fontSize 		= CAL_INPUT_FONT_SIZE;
	calInput2.color 		= CAL_INPUT_COLOR;
	calInput2.bgColor 		= CAL_INPUT_BG_COLOR;
	calInput2.borderColor 	= CAL_INPUT_BORDER_COLOR;
	calInput2.align 		= ALIGN_CENTER;
	
	calInput3 = getUiTextInstance();
	calInput3.left 			= calInput2.left  + calInput2.width +5;;
	calInput3.top  			= CAL_INPUT_TOP;
	calInput3.width 		= CAL_INPUT_WIDTH;
	calInput3.borderWidth	= CAL_INPUT_BORDER_WIDTH;
	calInput3.padding		= CAL_INPUT_PADDING;
	calInput3.fontSize 		= CAL_INPUT_FONT_SIZE;
	calInput3.color 		= CAL_INPUT_COLOR;
	calInput3.bgColor 		= CAL_INPUT_BG_COLOR;
	calInput3.borderColor 	= CAL_INPUT_BORDER_COLOR;
	calInput3.align 		= ALIGN_CENTER;
}

void flushCalendarInput() {
	char *p = getKeyBoardContentString();
	switch(calState){
		case 1: 
			calInput1.text = p;
			uiShowText(calInput1);
			break;
		case 2: 
			calInput2.text = p;
			uiShowText(calInput2);
			break;
		case 3: 
			calInput3.text = p;
			uiShowText(calInput3);
			break;
		case 4: 
			calInput1.text = p;
			uiShowText(calInput1);
			break;
		case 5: 
			calInput2.text = p;
			uiShowText(calInput2);
			break;
		case 6: 
			calInput3.text = p;
			uiShowText(calInput3);
			break;
		default: break;
	}
}

void calActiveYear(){
	calState = 1;
	calTitle.text = (char *) &hzFontText[28];
	uiShowText(calTitle);
	
	calInput1.bgColor = CAL_INPUT_BORDER_COLOR;
	calInput2.bgColor = CAL_INPUT_BG_COLOR;
	calInput3.bgColor = CAL_INPUT_BG_COLOR;
	uiShowText(calInput1);
	uiShowText(calInput2);
	uiShowText(calInput3);
	
	sprintf(calText,"%d",bcd2ten(calDate.u8_Year));
	setKeyBoardContent(calText); //设置键盘默认值与区间
	setKeyboardOptionRange(0,99);
	
}

void calActiveMonth(){
	calState = 2;
	calTitle.text = (char *) &hzFontText[28];
	uiShowText(calTitle);
	
	calInput1.bgColor = CAL_INPUT_BG_COLOR;
	calInput2.bgColor = CAL_INPUT_BORDER_COLOR;
	calInput3.bgColor = CAL_INPUT_BG_COLOR;
	uiShowText(calInput1);
	uiShowText(calInput2);
	uiShowText(calInput3);
	
	sprintf(calText,"%d",bcd2ten(calDate.u8_Month));
	setKeyBoardContent(calText); //设置键盘默认值与区间
	setKeyboardOptionRange(1,12);
}

void calActiveDate(){
	calState = 3;
	calTitle.text = (char *) &hzFontText[28];
	uiShowText(calTitle);
	
	calInput1.bgColor = CAL_INPUT_BG_COLOR;
	calInput2.bgColor = CAL_INPUT_BG_COLOR;
	calInput3.bgColor = CAL_INPUT_BORDER_COLOR;
	uiShowText(calInput1);
	uiShowText(calInput2);
	uiShowText(calInput3);
	sprintf(calText,"%d",bcd2ten(calDate.u8_Date));
	setKeyBoardContent(calText); //设置键盘默认值与区间
	setKeyboardOptionRange(1,31);
}


void calActiveHour(){
	calState = 4;
	calTitle.text = (char *) &hzFontText[29];
	uiShowText(calTitle);
	
	calInput1.bgColor = CAL_INPUT_BORDER_COLOR;
	calInput2.bgColor = CAL_INPUT_BG_COLOR;
	calInput3.bgColor = CAL_INPUT_BG_COLOR;
	uiShowText(calInput1);
	uiShowText(calInput2);
	uiShowText(calInput3);
	
	sprintf(calText,"%d",bcd2ten(calTime.u8_Hours));
	setKeyBoardContent(calText); //设置键盘默认值与区间
	setKeyboardOptionRange(0,23);
}

void calActiveMinute(){
	calState = 5;
	calTitle.text = (char *) &hzFontText[29];
	uiShowText(calTitle);
	
	calInput1.bgColor = CAL_INPUT_BG_COLOR;
	calInput2.bgColor = CAL_INPUT_BORDER_COLOR;
	calInput3.bgColor = CAL_INPUT_BG_COLOR;
	uiShowText(calInput1);
	uiShowText(calInput2);
	uiShowText(calInput3);
	
	sprintf(calText,"%d",bcd2ten(calTime.u8_Minutes));
	setKeyBoardContent(calText); //设置键盘默认值与区间
	setKeyboardOptionRange(0,59);
}

void calActiveSecond(){
	calState = 6;
	calTitle.text = (char *) &hzFontText[29];
	uiShowText(calTitle);
	
	calInput1.bgColor = CAL_INPUT_BG_COLOR;
	calInput2.bgColor = CAL_INPUT_BG_COLOR;
	calInput3.bgColor = CAL_INPUT_BORDER_COLOR;
	uiShowText(calInput1);
	uiShowText(calInput2);
	uiShowText(calInput3);
	
	sprintf(calText,"%d",bcd2ten(calTime.u8_Seconds));
	setKeyBoardContent(calText); //设置键盘默认值与区间
	setKeyboardOptionRange(0,59);
}

void calSave(){
	uint8_t val = getKeyBoardContentUInt8();
	switch(calState){ //选中下一个项目,并设置键盘输入范围
		case 1: setYear(val);break;
		case 2: setMonth(val);break;
		case 3: setDate(val);break;
		case 4: setHour(val);break;
		case 5: setMinute(val);break;
		case 6: setSecond(val);break;
		default: break;
	}
}

void calActiveNextInput(){
	HAL_RTC_GetDate(&calDate);
	HAL_RTC_GetTime(&calTime);
	
	switch(calState){ //激活下一个项目
		case 1: calActiveMonth();break;
		case 2: calActiveDate();break;
		case 3: calActiveYear();break;
		
		case 4: calActiveMinute();break;
		case 5: calActiveSecond();break;
		case 6: calActiveHour();break;
		
		default: break;
	}
}


void showCalendarView(uint8_t type){
	uiClear(CAL_BG_COLOR);
	
	calTextInit();
	
	HAL_RTC_GetDate(&calDate);
	HAL_RTC_GetTime(&calTime);
	
	calType = type;
	
	if(calType == 0){
		
	}else if(calType == 1){
		calState = 1;
		calActiveYear();
	}else if(calType == 2){
		calState = 4;
	}
	
	calUpdate();
}

enumViewEvent getCalendarEvent(){
	int8_t encoderValue,encoderEvent;

    enumViewEvent event = VIEW_EVENT_NONE;
    enumKeyboardEvent keyboardEvent ;
    keyboardEvent = getKeyboardEvent(); //读取键盘事件
	if(calType == 0){
		if(getRtcFlag() == 1){
			calUpdate();
		}
	}else{
		switch(keyboardEvent){
			case KEYBOARD_EVENT_CHANGE:
				flushCalendarInput() ;
				break;
			
			case KEYBOARD_EVENT_OK:
				calSave();
				if(calState == 3 || calState==6){
					event = VIEW_EVENT_BACK ;
				}else{
					calActiveNextInput();
					event = VIEW_TABINDEX ;
				}
				break;
			case KEYBOARD_EVENT_BACK:
				event = VIEW_EVENT_BACK ;
				break;
			
			default:
				break;
		}
	}
	return event;
}
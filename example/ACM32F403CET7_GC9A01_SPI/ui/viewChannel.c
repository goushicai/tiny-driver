#include "viewChannel.h"

uint16_t channelBgColor=0,channelTime=0;
uint8_t currentChannel,channelV,channelA;

void ChannelTimeInc(){
	if(currentChannel < 4){
		channelTime ++;
	}
}


void getChannelStatus(){
	int8_t r ;
	if(currentChannel < 4){
		//status_t = HAL_HRNG_GetHrng_8() >> 2;
		
		r = (rand() >> 29);
		channelV = 220 + r;
		
		r = (rand() >> 25); 
		channelA = 150 + r;
	}else{
		channelTime = 0;
		channelA = 0;
	}
}

void showChannelTitle(){
	uiText title = getUiTextInstance();
	if(currentChannel<4){
		uiShowIcon(CHANNEL_TITLE_LEFT,CHANNEL_TITLE_TOP, 28,28, WHITE,channelBgColor);
	}else{
		uiShowIcon(CHANNEL_TITLE_LEFT,CHANNEL_TITLE_TOP, 28,28, WHITE,RED);
	}
	
	
	title.align = ALIGN_LEFT;
	title.left = CHANNEL_TITLE_LEFT + CHANNEL_TITLE_FONT_SIZE;
	title.top = CHANNEL_TITLE_TOP;
	
	title.color = CHANNEL_TITLE_FONT_COLOR;
	title.bgColor = channelBgColor;
	title.fontSize = CHANNEL_TITLE_FONT_SIZE;
	title.text = (char *) &hzFontText[43][0];
	title.width = sizeof(title.text)/2 * CHANNEL_TITLE_FONT_SIZE;
	uiShowText(title);	
	uiShowAscii(title.left + title.width,CHANNEL_TITLE_TOP, currentChannel + 0x30,CHANNEL_TITLE_FONT_SIZE,CHANNEL_TITLE_FONT_COLOR,channelBgColor);
}

void showChannelText(){
	uiText text = getUiTextInstance();
	char p[16],h,m,s;
	
	text.left = CHANNEL_TEXT_LEFT;
	text.top = CHANNEL_TEXT_TOP;
	text.align = ALIGN_LEFT;
	text.width = 160;
	text.color = CHANNEL_TEXT_FONT_COLOR;
	text.bgColor = channelBgColor;
	text.fontSize = CHANNEL_TEXT_FONT_SIZE;
	
	sprintf(p,"%s: %d V",(char *) &hzFontText[44][0],channelV);
	text.text = p;
	
	uiShowText(text);	
	
	text.top = CHANNEL_TEXT_TOP+ CHANNEL_TEXT_FONT_SIZE;
	sprintf(p,"%s: %d.%d A",(char *) &hzFontText[45][0],channelA/10,channelA %10);
	text.text = p;
	uiShowText(text);	
	
	if(currentChannel < 4){
		h = (char)(channelTime / 3600);
		m = (char)((channelTime % 3600) / 60);
		s = (char)((channelTime % 3600) % 60);
		sprintf(p,"%s: %d:%02d:%02d",(char *) &hzFontText[47][0],h,m,s);
	}else{
		sprintf(p,"%s: %s",(char *) &hzFontText[47][0],"-:--:--");
	}
	
	text.top = CHANNEL_TEXT_TOP + CHANNEL_TEXT_FONT_SIZE + CHANNEL_TEXT_FONT_SIZE;
	text.text = p;
	
	
	uiShowText(text);
}


void showChannelView(uint8_t channel){
	currentChannel = channel;
	channelTime = 0;
	
	if(currentChannel < 4){
		channelBgColor  = CHANNEL_ACTIVE_BG_COLOR;
		
	}else{
		channelBgColor = CHANNEL_DEFAULT_BG_COLOR;
		
	}
	uiClear(channelBgColor);
	
	getChannelStatus();
	
	showChannelTitle();
	showChannelText();
}

void nextChannel(){
	showChannelView((currentChannel+1)%10);
}

void prevChannel(){
	if(currentChannel==0){
		showChannelView(9);
	}else{
		showChannelView(currentChannel-1);
	}

}
enumViewEvent getChannelViewEvent(){
	int8_t encoderValue,encoderEvent;
    enumViewEvent viewEvent = VIEW_EVENT_NONE;
	
	encoderValue = getEncoderVal();clrEncoderVal();
    encoderEvent= getKeyVal();clrKeyVal();
	
	if(encoderValue > 0)
    {
		nextChannel();
        viewEvent = CHANNEL_EVENT_CHANGE;
    }else if(encoderValue < 0){
		prevChannel();
        viewEvent = CHANNEL_EVENT_CHANGE;
    }
	
	if(encoderEvent== ENCODER_EVENT_CLICK){
        viewEvent = CHANNEL_EVENT_SHOW_CHART;
    }
    else if(encoderEvent== ENCODER_EVENT_DOUBLE_CLICK){
		viewEvent = VIEW_EVENT_BACK;
    }
	return viewEvent;
}
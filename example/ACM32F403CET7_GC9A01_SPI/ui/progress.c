#include "progress.h"


uint8_t prgressPercent = 0;
uint8_t progressType = 0;

uint16_t progressRadius=120;
uint8_t progressLineWidth=3;

uint16_t lastHeight = SCREEN_HEIGHT;

void showProgress(uint8_t percent)
{
	
};

void closeProgress(uint8_t delay, uint8_t style)
{

};


//进度条 水位
void showProgressWater(uint8_t percent, uint16_t color,uint16_t bgColor )
{
    uint16_t h =(uint16_t)(SCREEN_HEIGHT * (100-percent) / 100.0);
	if(percent == 0){
		lcdFillRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, bgColor);
		lastHeight = SCREEN_HEIGHT;
	}else if(percent >= 100){
		lcdFillRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, color);
		lastHeight = 0;
	}else{
		if( h > lastHeight){
			lcdFillRectangle(0,lastHeight,SCREEN_WIDTH,h-lastHeight, bgColor);
		}else if(h<lastHeight){
			lcdFillRectangle(0,h,SCREEN_WIDTH,lastHeight-h, color);
		}
		lastHeight = h;
	}
}

//光反馈, 屏幕外圈闪不同颜色
void showTwkinle(uint16_t color,uint16_t bgColor )
{	
	uiClear(color);
	uiFillCircle(SCREEN_CENTER_X, SCREEN_CENTER_Y, OUTER_RADIUS - PROGRESS_LINE_WIDTH,bgColor);	
}

void successTwkinle(uint16_t bgColor){
	showTwkinle(SUCCESS_COLOR,bgColor);
}

void failTwkinle(uint16_t bgColor){
	showTwkinle(DANGER_COLOR,bgColor);
}

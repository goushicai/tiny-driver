/**
* ¥ÌŒÛ“≥£¨œ‘ æ¥ÌŒÛ±‡¬Î”Î–≈œ¢
 *
 * */

#include "viewError.h"

void showErrorCode(uint8_t errorCode)
{
	char errCode[13];
	sprintf(( char *)errCode,"errCode:%x",errorCode);
	
	uiClear(RED);
	uiText txtError = getUiTextInstance();
	
	txtError.text = errCode;
	txtError.left = 20;
	txtError.top = 90;
	txtError.fontSize = FONT_SIZE_32;
	txtError.color = WHITE;
	txtError.bgColor = RED;
	txtError.width = 200;
	txtError.align = ALIGN_CENTER;
	
	uiShowText(txtError);
}

void showErrorText(uint8_t errorCode, char * txt)
{
	showErrorCode(errorCode);
	
	uiText txtError = getUiTextInstance();
	
	txtError.text = txt;
	txtError.left = 30;
	txtError.top = 130;
	txtError.fontSize = FONT_SIZE_32;
	txtError.color = WHITE;
	txtError.bgColor = RED;
	txtError.width = 180;
	txtError.align = ALIGN_CENTER;
	
	uiShowText(txtError);
}

uint8_t getErrorCode(uint8_t errorCode)
{
    return 0;
}

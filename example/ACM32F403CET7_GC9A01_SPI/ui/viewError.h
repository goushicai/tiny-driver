/**
 * ¥ÌŒÛ“≥
 *
 * */


#ifndef __ERROR_VIEW_H__
#define __ERROR_VIEW_H__


#include "uiDisplay.h"


void showErrorCode(uint8_t errorCode);

void showErrorText(uint8_t errorCode, char * txt);

uint8_t getErrorCode(uint8_t errorCode);

#endif  //__ERROR_VIEW_H__
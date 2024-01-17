/**
 * �ı�ҳ
 *
 * */


#ifndef __TEXT_VIEW_H__
#define __TEXT_VIEW_H__

#include "uiDisplay.h"
#include "encoder.h"
#include "event.h"

#define TEXT_VIEW_COLOR       			0xFFDF 	//�˵�������ʾ����
#define TEXT_VIEW_BG_COLOR       		0x3186 	//�˵�������ʾ����
#define TEXT_VIEW_LEFT       			40 		//�˵�������ʾ����
#define TEXT_VIEW_TOP       			40 		//�˵�������ʾ����
#define TEXT_VIEW_WIDTH       			160
#define TEXT_VIEW_HEIGHT       			160
#define TEXT_VIEW_FONT_SIZE    			FONT_SIZE_32
#define TEXT_VIEW_MAX_COLS    			32 		//ÿ�������ʾascii�ַ���

void showTextView(char * text);

//�����ı�������,֧�ֻ��з�\n,�س���\r��ͬ����
uint16_t getTextRows(char *text, uint8_t colSize);

void scrollUp();

void scrollDown();

void TextViewChangeFontSize();

enumViewEvent getTextViewEvent();
#endif  //__TEXT_VIEW_H__
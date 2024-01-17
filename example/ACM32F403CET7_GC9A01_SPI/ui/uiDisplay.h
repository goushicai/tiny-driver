/**
 * UI�������
 *
 * */

#ifndef __DISPLAY_UI_H__
#define __DISPLAY_UI_H__

#include "drvGC9A01.h"
#include "fontLib.h"
#include "icon.h"
#include "uiCommon.h"

#define INPUT_BG_COLOR        		0x3186 	//�ı��򱳾���ɫ
#define INPUT_TEXT_COLOR        	0xFFFF 	//�ı���ɫ
#define INPUT_TEXT_FONT_SIZE     	24 		//�ı�����
#define INPUT_BORDER_COLOR 			0xFFFF 	//�ı��߿���ɫ0xFEFEFE
#define INPUT_LEFT 					60 		//�ı���λ��
#define INPUT_TOP 					108
#define INPUT_PADDING 				1
#define INPUT_BORDER_WIDTH 			1 
#define INPUT_WIDTH 				120
#define INPUT_HEIGHT				32
#define DISP_RAM_SIZE				1024*2


//��ɫ��ת��
void uiDisplayInversionOn();
//��ɫ��ת�ر�
void uiDisplayInversionOff();

void uiDisplayBrightness(uint8_t bright);

void uiDisplayCtrl(uint8_t val);

//����
void uiClear(uint16_t color);

//������
void uiFillRectangle(uint16_t x,uint16_t y, uint16_t w,uint16_t h,uint16_t color);

//����
void uiDrawPoint(uint16_t x, uint16_t y, uint16_t color);

//����
void uiDrawLine(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1, uint16_t color);

//������Բ
void uiDrawCircle(uint16_t x,uint16_t y ,uint16_t r, uint16_t color);

//���Բ
void uiFillCircle(uint16_t x,uint16_t y ,uint16_t r, uint16_t color);

//����
void uiDrawRing(uiRing ring);

//��Բ��
void uiDrawArc(uiArc arc);

//��ʾͼƬ
void uiShowImage(uint16_t left,uint16_t top, uint16_t width,uint16_t height,uint8_t * imgData);
	
//��ʾͼ��
void uiShowIcon(uint16_t x,uint16_t y, uint8_t iconIdx,uint8_t iconSize, uint16_t color,uint16_t bgColor);
	
//��ʾ����ascii�ַ�
void uiShowAscii(uint16_t x,uint16_t y, uint8_t ch, uint16_t fontSize,uint16_t color,uint16_t bgColor);

//��ʾ���������ַ�
void uiShowChinese(uint16_t x,uint16_t y, uint16_t ch,uint16_t fontSize, uint16_t color,uint16_t bgColor);

//��ʾ������ascii����ı�
void uiShowText(uiText txt);

//��ȡһ��Ĭ�ϵ��ı������
uiText getUiTextInstance();


#endif  //__UI_DISPLAY_H__
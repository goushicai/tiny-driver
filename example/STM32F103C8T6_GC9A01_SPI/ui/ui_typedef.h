/**
	UI����ṹ�嶨��
*/

#ifndef __UI_TYPEDEF_H
#define __UI_TYPEDEF_H

#include "stm32f1xx_hal.h" 

//��ɫ
typedef struct{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha; //͸����0��ȫ��͸��,255��ȫ͸��,��Ҫ����Alpha����㷨
} uiColor;

//�˵�
typedef struct{
	int16_t x;
	int16_t y;
} uiPoint;

//����
typedef struct{
	int16_t x;
	int16_t y;
	uiColor color;
} uiPixel;

//ֱ��
typedef struct{
	uiPoint head; //���
	uiPoint tail; //�յ�
	uiColor color;
} uiLine;

//����
typedef struct{
	uiPoint leftTop; //���Ͻ�
	uiPoint rightBottom; //���½�
	int16_t width;
	int16_t height;
	uint16_t lineWidth; //���α߿�Ŀ��,lineWidth=0�����߿�
	uiColor lineColor; //���α߿����ɫ
	uiColor fillColor; //�����ڲ��������ɫ,��͸�������
} uiRectangle;

typedef struct{
	uiRectangle border; //�߿�
	uint8_t *text; //�ı�
	uint16_t fontSize; //�ַ��ĸ߶�,ֻ�����������,ascii�ַ����Ϊ�߶ȵ�һ��,���ĳ���һ��
	uint16_t lineWidth;
	uiColor fontColor; //�ַ���ɫ
	uiColor bgColor; //������ɫ
} uiLabel;

typedef struct{
	uiRectangle border; //�߿�	
	uiColor fontColor; //�ַ���ɫ
	uiColor bgColor; //������ɫ
	uint32_t value; //ֵ,�ı���typeת����Ӧ��ֵ,��Ϊ�ַ���,��ֵtext��size
	uint8_t *text; //�ı�
	uint8_t type; //�з�������,�޷�������,������,�ַ���,rtcData,rtcTime
	uint8_t align; //���з�ʽ,��4λΪˮƽ���з�ʽ,0����,1����,2����, ��4λΪ��ֱ���з�ʽ,0��ֱ����,1����,2����
	uint8_t fontSize; //�ַ��ĸ߶�,ֻ�����������,ascii�ַ����Ϊ�߶ȵ�һ��,���ĳ���һ��
	uint8_t mode; //[7]0ˮƽ1��ֱ,[6]0����,1�ҵ���,[5]0����,1����,[4]0������,1�Զ�����,[3]0����ض�,1�����ʾ
} uiInput;


#endif

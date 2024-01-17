/**
 * �ı�ҳ
 *
 * */


#ifndef __CHART_VIEW_H__
#define __CHART_VIEW_H__

#include "uiDisplay.h"
#include "encoder.h"
#include "event.h"

#define CHART_BG_COLOR       			0xFFFF 	//������ɫ
#define CHART_COLORS       				{0x2B12,0x44E8,0xECA3,0xC985,0xF81F,0x07FF,0xFFE0,0x3186} //��ɫ

#define X_AXIS_Y       					120 	//x����ʾλ��
#define Y_AXIS_X       					120 	//y����ʾλ��

#define X_AXIS_LABEL       				x 		//x�����
#define Y_AXIS_LABEL       				y 		//y�����

#define X_AXIS_TICK       				40 		//x��̶ȼ��
#define Y_AXIS_TICK       				40 		//y��̶ȼ��

#define LINE_CHART_LEFT       			0 		//����ͼ����ʾ��Χ
#define LINE_CHART_TOP       			40 		//����ͼ����ʾ��Χ
#define LINE_CHART_WIDTH       			240 	//����ͼ����ʾ��Χ
#define LINE_CHART_HEIGHT       		160 	//����ͼ����ʾ��Χ

#define CHART_AXIS_COLOR       			0x0000 	//Ĭ����ɫ
#define CHART_AXIS_LINE_WIDTH   		1 		//�߿�

#define CHART_GRID_COLOR       			0xAD55 	//��������ɫ,Ĭ���߿�1px
#define CHART_GRID_INTERVAL 			40 		//�����߼��
#define CHART_AXIS_FONT_SIZE       		8
#define CHART_AXIS_STEP_PX       		40
#define CHART_LEGEND_FONT_SIZE    		FONT_SIZE_16

#define CHART_LEGEND_LEFT    			80
#define CHART_LEGEND_TOP    			20
#define CHART_STEP 						4		//����
#define CHART_DATA_LENGTH 				(LINE_CHART_WIDTH/CHART_STEP + 1) //����Ԫ��,��������

typedef struct{
	uint8_t chartType; //0 line,1:bar,2:pie
	int16_t maxValue;
	int16_t minValue;
	uint16_t duration; // ˢ������ms,0������
	char *xLabel; //x�����
	char *yLabel; //y�����
	uint8_t xTicks; //x��̶ȼ��
	uint8_t yTicks; //y��̶ȼ��
	uint8_t gridInterval;
}  ChartTypeDef ;

//׷��һ������,����������ͼ
void flushLineChart(int16_t val);

void showChartView(ChartTypeDef chartOpt);

void drawLineSeries(int16_t *data, uint8_t clearFlag);

enumViewEvent getChartViewEvent();

#endif  //__CHART_VIEW_H__
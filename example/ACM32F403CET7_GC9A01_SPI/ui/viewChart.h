/**
 * 文本页
 *
 * */


#ifndef __CHART_VIEW_H__
#define __CHART_VIEW_H__

#include "uiDisplay.h"
#include "encoder.h"
#include "event.h"

#define CHART_BG_COLOR       			0xFFFF 	//背景颜色
#define CHART_COLORS       				{0x2B12,0x44E8,0xECA3,0xC985,0xF81F,0x07FF,0xFFE0,0x3186} //颜色

#define X_AXIS_Y       					120 	//x轴显示位置
#define Y_AXIS_X       					120 	//y轴显示位置

#define X_AXIS_LABEL       				x 		//x轴标题
#define Y_AXIS_LABEL       				y 		//y轴标题

#define X_AXIS_TICK       				40 		//x轴刻度间隔
#define Y_AXIS_TICK       				40 		//y轴刻度间隔

#define LINE_CHART_LEFT       			0 		//折线图表显示范围
#define LINE_CHART_TOP       			40 		//折线图表显示范围
#define LINE_CHART_WIDTH       			240 	//折线图表显示范围
#define LINE_CHART_HEIGHT       		160 	//折线图表显示范围

#define CHART_AXIS_COLOR       			0x0000 	//默认颜色
#define CHART_AXIS_LINE_WIDTH   		1 		//线宽

#define CHART_GRID_COLOR       			0xAD55 	//网络线颜色,默认线宽1px
#define CHART_GRID_INTERVAL 			40 		//网络线间隔
#define CHART_AXIS_FONT_SIZE       		8
#define CHART_AXIS_STEP_PX       		40
#define CHART_LEGEND_FONT_SIZE    		FONT_SIZE_16

#define CHART_LEGEND_LEFT    			80
#define CHART_LEGEND_TOP    			20
#define CHART_STEP 						4		//步长
#define CHART_DATA_LENGTH 				(LINE_CHART_WIDTH/CHART_STEP + 1) //队列元素,算上两端

typedef struct{
	uint8_t chartType; //0 line,1:bar,2:pie
	int16_t maxValue;
	int16_t minValue;
	uint16_t duration; // 刷新周期ms,0不更新
	char *xLabel; //x轴标题
	char *yLabel; //y轴标题
	uint8_t xTicks; //x轴刻度间隔
	uint8_t yTicks; //y轴刻度间隔
	uint8_t gridInterval;
}  ChartTypeDef ;

//追加一个数据,并更新折线图
void flushLineChart(int16_t val);

void showChartView(ChartTypeDef chartOpt);

void drawLineSeries(int16_t *data, uint8_t clearFlag);

enumViewEvent getChartViewEvent();

#endif  //__CHART_VIEW_H__
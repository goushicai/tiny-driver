#include "viewChart.h"

int16_t chartData[CHART_DATA_LENGTH];
uint8_t queueLength=0,queueHead=0,queueTail=0;//队列长度,头指针,尾指针
int16_t chartMaxValue =0,chartMinValue=0;
uiText txtTitle;
uint16_t chartColors[] = {0xC985,0xECA3,0x44E8,0xF81F,0x07FF,0xFFE0,0x2B12,0x3186};

uint8_t serieIdx=0;
int8_t multiple=0;

uint8_t gridInterval = CHART_GRID_INTERVAL;
uint16_t chartStep = CHART_STEP;

char *xLabel=NULL,*yLabel=NULL; //x,y轴标题

uint8_t xTicks = X_AXIS_TICK,yTicks = Y_AXIS_TICK; //x轴刻度间隔

//循环队列,只用到入队,用于显示动态更新的折线图
void pushQueue(int16_t val){
	int16_t tmpVal;
	//将数据转成图表上的y值
	//tmpVal = (int16_t)((double)(val - chartMinValue)/(double)(chartMaxValue - chartMinValue) * LINE_CHART_HEIGHT + 0.5); //4舍五入
	//tmpVal = LINE_CHART_HEIGHT - tmpVal + LINE_CHART_TOP;
	
	//截断超出范围的数据
	//tmpVal = tmpVal < LINE_CHART_TOP ? LINE_CHART_TOP : tmpVal;
	//tmpVal = tmpVal > LINE_CHART_TOP + LINE_CHART_HEIGHT  ? LINE_CHART_TOP + LINE_CHART_HEIGHT : tmpVal;
	
	//入队, 队尾指针始终指向下一个要写入的位置
	chartData[queueTail++] = val;
	//循环队尾
	if(queueTail >= CHART_DATA_LENGTH){ 
		queueTail = 0;
	}
	
	//队列长度+1
	if(queueLength < CHART_DATA_LENGTH){
		queueLength++;
	}else{
		queueHead = queueTail; //当队列满时,队首与队尾指针指向相同,队首指针指向队列第一个元素,队尾指针指向下一个可插入的位置
	}
}

void clearQueue(){
	uint8_t i = 0;

	for(i = 0;i<CHART_DATA_LENGTH;i++){
		chartData[i]=0;
	}
	queueLength = 0;
	queueHead = 0;
	queueTail = 0;
}

//填充队列
void fillQueue(int16_t *data,uint8_t len){
	uint8_t i = 0;
	if(len > CHART_DATA_LENGTH){
		len = CHART_DATA_LENGTH;
	}
	clearQueue();
	
	for(i = 0;i<len;i++){
		pushQueue(*(data+i)) ;
	}
}

void drawGrid(){
	uint16_t i = 0;
	//网格线
	if(gridInterval > 0 && gridInterval < SCREEN_WIDTH/2){
		//纵向
		for(i = LINE_CHART_LEFT; i <= LINE_CHART_LEFT + LINE_CHART_WIDTH ;i+=gridInterval){
			//uiDrawLine(i, LINE_CHART_TOP,	i, LINE_CHART_TOP + LINE_CHART_HEIGHT, 	CHART_GRID_COLOR);
			
			uiFillRectangle(i,LINE_CHART_TOP,1,LINE_CHART_HEIGHT,CHART_GRID_COLOR);
		}
		//横向
		for(i = LINE_CHART_TOP; i <= LINE_CHART_TOP + LINE_CHART_HEIGHT ;i+=gridInterval){
			//uiDrawLine(LINE_CHART_LEFT, i, LINE_CHART_LEFT+ LINE_CHART_WIDTH,i , CHART_GRID_COLOR);
			uiFillRectangle(LINE_CHART_LEFT,i,LINE_CHART_WIDTH,1,CHART_GRID_COLOR);
		}
	}
}

void drawAxisLabelTick(){
	//显示x,y轴标签名
	txtTitle.fontSize = FONT_SIZE_16;
	txtTitle.color = CHART_AXIS_COLOR;
	txtTitle.bgColor = CHART_BG_COLOR;
	txtTitle.width = strlen(xLabel) * txtTitle.fontSize/2;
	txtTitle.align = ALIGN_LEFT;
	
	txtTitle.left = SCREEN_WIDTH - txtTitle.width - 5;
	txtTitle.top = SCREEN_CENTER_Y - txtTitle.fontSize-5;
	txtTitle.text = xLabel;
	uiShowText(txtTitle);
	
	txtTitle.width = strlen(yLabel)* txtTitle.fontSize/3; 
	txtTitle.left = SCREEN_WIDTH / 2 + 5;
	txtTitle.top  = LINE_CHART_TOP - txtTitle.fontSize - 5;
	txtTitle.text = yLabel;
	uiShowText(txtTitle);
	
	txtTitle.width = txtTitle.fontSize*3; 
	txtTitle.left = SCREEN_WIDTH/2 - txtTitle.width;
	txtTitle.top  = LINE_CHART_TOP - txtTitle.fontSize - 5;
	switch(multiple){
		case -4: txtTitle.text = "m:1/16"; break;
		case -3: txtTitle.text = "m:1/8"; break;
		case -2: txtTitle.text = "m:1/4"; break;
		case -1: txtTitle.text = "m:1/2"; break;
		case 1:  txtTitle.text = "m:2"; break;
		case 2:  txtTitle.text = "m:4"; break;
		case 3:  txtTitle.text = "m:8"; break;
		case 4:  txtTitle.text = "m:16"; break;
		default: txtTitle.text = "m:1"; break;
	}
	uiShowText(txtTitle);
}
void drawAxis(){
	//x轴
	uiFillRectangle(0,X_AXIS_Y, SCREEN_WIDTH,1,CHART_AXIS_COLOR);
	//y轴
	uiFillRectangle(Y_AXIS_X,0,1,SCREEN_HEIGHT,CHART_AXIS_COLOR);
	
	drawAxisLabelTick();
}

void drawLegend(){

}

void clearLineSeries(){
	uiFillRectangle(LINE_CHART_LEFT,LINE_CHART_TOP,LINE_CHART_WIDTH,LINE_CHART_HEIGHT,CHART_BG_COLOR);
	drawGrid();
	drawAxis();
}

//画折线图
void drawChartLine(uint16_t color){
	uint16_t x =LINE_CHART_LEFT;
	int16_t y0,y1;
	uint8_t idx =0,i=0;
	if(queueLength < 2){
		uiDrawPoint(x,chartData[0],color);
	}else{
		if(queueLength >= CHART_DATA_LENGTH){
			clearLineSeries(); //擦除折线区域,重画坐标与网格线
		}
		
		for(i = 1;i < queueLength;i ++){
			idx = (queueHead + i) % CHART_DATA_LENGTH;
			
			if(idx == 0){
				y0 = chartData[CHART_DATA_LENGTH-1];
				y1 = chartData[0];
				
			}else{
				y0 = chartData[idx-1];
				y1 = chartData[idx];
			}
			
			if(multiple>0){
				y0 = y0 << multiple;
				y1 = y1 << multiple;
			}else if(multiple<0){
				y0 = y0 >> (0 - multiple);
				y1 = y1 >> (0 - multiple);
			}
			
			y0 = (int16_t)((double)(y0 - chartMinValue)/(double)(chartMaxValue - chartMinValue) * LINE_CHART_HEIGHT + 0.5); //4舍五入
			y1 = (int16_t)((double)(y1 - chartMinValue)/(double)(chartMaxValue - chartMinValue) * LINE_CHART_HEIGHT + 0.5); //4舍五入
	
			
			y0 = LINE_CHART_HEIGHT - y0 + LINE_CHART_TOP;
			y1 = LINE_CHART_HEIGHT - y1 + LINE_CHART_TOP;
			
			y0 = y0 < LINE_CHART_TOP ? LINE_CHART_TOP : y0;
			y0 = y0 > LINE_CHART_TOP + LINE_CHART_HEIGHT  ? LINE_CHART_TOP + LINE_CHART_HEIGHT : y0;
			y1 = y1 < LINE_CHART_TOP ? LINE_CHART_TOP : y1;
			y1 = y1 > LINE_CHART_TOP + LINE_CHART_HEIGHT  ? LINE_CHART_TOP + LINE_CHART_HEIGHT : y1;
			
			uiDrawLine(x, y0,x+chartStep, y1, color);
			x += chartStep;
		}	
	}
}


void flushLineChart(int16_t val){
	pushQueue(val);
	drawChartLine(chartColors[serieIdx]);
}

void showLineChart(){
	
	drawGrid();
	drawAxis();
	
	drawChartLine(chartColors[serieIdx]);
}

void showChartView(ChartTypeDef chartOpt){
	uint8_t i=0;
	int16_t data[CHART_DATA_LENGTH];
	
	uiClear(CHART_BG_COLOR);
	
	clearQueue();
	
	chartMaxValue = chartOpt.maxValue;
	chartMinValue = chartOpt.minValue;
	
	xLabel = chartOpt.xLabel;
	yLabel = chartOpt.yLabel;
	xTicks = chartOpt.xTicks;
	yTicks = chartOpt.yTicks;
	gridInterval = chartOpt.gridInterval;
	
	if(chartMaxValue == 0 && chartMinValue == 0){
		chartMinValue = 0;
		chartMaxValue = LINE_CHART_HEIGHT;
	}
	
	showLineChart();
}

void showBarChart(){

}

void showPieChart(){

}

//获取页页事件
enumViewEvent getChartViewEvent()
{
    int8_t encoderValue,encoderEvent;
    enumViewEvent event = VIEW_EVENT_NONE;
	encoderValue = getEncoderVal();
    encoderEvent= getKeyVal();
	
	if(encoderEvent== ENCODER_EVENT_DOUBLE_CLICK) {      //退回到上级菜单
		event = VIEW_EVENT_BACK;
    }else if(encoderEvent== ENCODER_EVENT_PRESS){ //清除图表数据
		event = CHART_EVENT_CLEAR;
		
		clearQueue(); //清除数据
		clearLineSeries();//清除当前图形
		multiple = 0;
	}
	
	if(encoderValue > 0){
		clrEncoderVal();
		if(multiple < 4){
			multiple ++;
			clearLineSeries();//清除当前图形
			drawAxisLabelTick();
			drawChartLine(chartColors[serieIdx]);
		}
	}else if(encoderValue < 0 ){
		clrEncoderVal();
		if(multiple>-4){
			multiple --;
			clearLineSeries();//清除当前图形
			drawAxisLabelTick();
			drawChartLine(chartColors[serieIdx]);
		}
	}
	
    return event;
}
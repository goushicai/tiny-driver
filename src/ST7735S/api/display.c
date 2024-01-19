#include "display.h"

void displayInit(void){
	lcdInit();
	
	lcdRotation(SCREEN_ROTATION);
	lcdMirror(SCREEN_MIRROR);
}

//进入睡眠模式
void displaySleepOn(void){
	lcdSleepIn();
}

//退出睡眠模式
void displaySleepOff(void){
	lcdSleepOut();
}

//打开反色模式
void displayInvertionOn(void){
	lcdInvertionOn();
}

//打开反色模式
void displayInvertionOff(void){
	lcdInvertionOff();
}

//打开空闲模式
void displayIdleOn(void){
	lcdDisplayIdleOn();
}

//打开空闲模式
void displayIdleOff(void){
	lcdDisplayIdleOff();
}

//打开显示
void displayOn(void){
	lcdDisplayOn();
}

//关闭显示
void displayOff(void){
	lcdDisplayOff();
}

//复位
void displayReset(void){
	lcdReset();
}

void displayBrightness(uint8_t val){
	/**
		若屏幕不支持调节亮度,可以考虑用pwm调整背光led的亮度实现
	*/
}
//显示方向设置, 0默认,1逆时钟转90度,2逆时钟转180度,3逆时钟转270度
void displayRotation(uint8_t rotation){
	lcdRotation(rotation);
}

//显示镜像, 0默认,1仅水平镜像,2仅垂直镜像,3水平垂直均镜像
void displayMirror(uint8_t mirror){
	lcdMirror(mirror);
}

//清屏
void displayClear(uint16_t color){
	lcdClear(color);
}

void drawPixel(int16_t x,int16_t y,uint16_t color){
	/*
		x = x > SCREEN_WIDTH ? SCREEN_WIDTH: x;
		x = x < SCREEN_OFFSET_X ? SCREEN_OFFSET_X: x;
		
		y = y > SCREEN_HEIGHT ? SCREEN_HEIGHT: y;
		y = y < SCREEN_OFFSET_Y ? SCREEN_OFFSET_Y: y;
		*/
	
	lcdPixel(x,y,color);
}

void drawLine(int16_t x0,int16_t y0,int16_t x1,int16_t y1,uint16_t color,uint16_t lineWidth){
	/*
	x0 = x0 > SCREEN_WIDTH ? SCREEN_WIDTH: x0;
	x0 = x0 < SCREEN_OFFSET_X ? SCREEN_OFFSET_X: x0;
	
	x1 = x1 > SCREEN_WIDTH ? SCREEN_WIDTH: x1;
	x1 = x1 < SCREEN_OFFSET_X ? SCREEN_OFFSET_X: x1;
	
	y0 = y0 > SCREEN_HEIGHT ? SCREEN_HEIGHT: y0;
	y0 = y0 < SCREEN_OFFSET_Y ? SCREEN_OFFSET_Y: y0;
	
	y1 = y1 > SCREEN_HEIGHT ? SCREEN_HEIGHT: y1;
	y1 = y1 < SCREEN_OFFSET_Y ? SCREEN_OFFSET_Y: y1;
	*/
	lcdLine( x0, y0, x1, y1, color, lineWidth);
}

void drawRectangle(int16_t x,int16_t y,uint16_t w,uint16_t h,uint16_t lineColor,uint16_t lineWidth){
	lineWidth = lineWidth < 1 ? 1: lineWidth;
	
	/*
	x = x > SCREEN_WIDTH ? SCREEN_WIDTH: x;
	x = x < SCREEN_OFFSET_X ? SCREEN_OFFSET_X: x;
	
	y = y > SCREEN_HEIGHT ? SCREEN_HEIGHT: y;
	y = y < SCREEN_OFFSET_Y ? SCREEN_OFFSET_Y: y;
	*/
	
	lcdBlock( x, y,  w, lineWidth, lineColor); //上
	lcdBlock( x+w-lineWidth,  y, lineWidth, h, lineColor);//右
	lcdBlock( x, y+h-lineWidth,  w, lineWidth, lineColor); //下
	lcdBlock( x, y,  lineWidth,h, lineColor); //左
}

void fillRectangle(int16_t x,int16_t y,uint16_t w,uint16_t h,uint16_t color){
	/*
	x = x > SCREEN_WIDTH ? SCREEN_WIDTH: x;
	x = x < SCREEN_OFFSET_X ? SCREEN_OFFSET_X: x;
	
	y = y > SCREEN_HEIGHT ? SCREEN_HEIGHT: y;
	y = y < SCREEN_OFFSET_Y ? SCREEN_OFFSET_Y: y;
	*/
	
	lcdBlock( x, y,  w, h, color);
}

void drawCircle(int16_t x,int16_t y ,uint16_t r, uint16_t color){
	uint16_t dx=0,dy=r,rr=r*r;
	
	/*
	x = x > SCREEN_WIDTH ? SCREEN_WIDTH: x;
	x = x < SCREEN_OFFSET_X ? SCREEN_OFFSET_X: x;
	
	y = y > SCREEN_HEIGHT ? SCREEN_HEIGHT: y;
	y = y < SCREEN_OFFSET_Y ? SCREEN_OFFSET_Y: y;
	*/
	
	for(dx = 0;dx<=dy;dx++){
		lcdPixel(x + dx,y - dy,color);// 1/4 PI ~ 2/4 PI
		lcdPixel(x + dy,y - dx,color);// 0/4 PI ~ 1/4 PI
		
		lcdPixel(x + dy,y + dx,color);// 7/4 PI ~ 8/4 PI
		lcdPixel(x + dx,y + dy,color);// 6/4 PI ~ 7/4 PI
		
		lcdPixel(x - dx,y + dy,color);// 5/4 PI ~ 6/4 PI
		lcdPixel(x - dy,y + dx,color);// 4/4 PI ~ 5/4 PI
		
		lcdPixel(x - dy,y - dx,color);// 3/4 PI ~ 4/4 PI
		lcdPixel(x - dx,y - dy,color);// 2/4 PI ~ 3/4 PI
		
		if(( dx*dx + dy*dy ) > rr){//离圆心的距离,可以优化成bresenham算法
			dy--;
		}
	}
}

//用横线填充,从上到下分为四个区域,要考虑不在显示区域的处理
void fillCircle(int16_t x,int16_t y ,uint16_t r, uint16_t color){
	int16_t dx,dy,rr,xLeft,w;
	dx = 0,dy = r,rr=r*r;
	
	/*
	x = x > SCREEN_WIDTH ? SCREEN_WIDTH: x;
	x = x < SCREEN_OFFSET_X ? SCREEN_OFFSET_X: x;
	
	y = y > SCREEN_HEIGHT ? SCREEN_HEIGHT: y;
	y = y < SCREEN_OFFSET_Y ? SCREEN_OFFSET_Y: y;
	*/
	
	for(dx = 0; dx <= dy; dx ++){
		if(y > dy  && y - dy <= SCREEN_HEIGHT && y - dy >= 0){
			xLeft = x - dx; //横线左点
			w = dx * 2;
			
			if(xLeft < 0){
				xLeft = 0;
				w = dx + x;//线长
			}
			
			if(w > SCREEN_WIDTH){
				w = SCREEN_WIDTH;
			}
			
			if(w > 0 ){
				//上半圆上部
				fillRectangle(xLeft,y - dy, w ,1,color);
			}
		}
		
		if(y > dx && y - dx <= SCREEN_HEIGHT && y - dx >= 0){
			xLeft = x - dy;
			w = dy * 2;
			if(xLeft < 0){
				xLeft = 0;
				w = dy + x;
			}
			
			if(w > SCREEN_WIDTH){
				w = SCREEN_WIDTH;
			}
			
			//上半圆下部
			if(w > 0 ){
				fillRectangle(xLeft,y - dx, w ,1,color);
			}
		}
		
		if(y + dx <= SCREEN_HEIGHT && y + dx >= 0){
			xLeft = x - dy;
			w =  dy * 2;
			if(xLeft < 0){
				xLeft = 0;
				w = dy + x;
			}
			
			if(w > SCREEN_WIDTH){
				w = SCREEN_WIDTH;
			}
			if(w > 0 ){
				//下半圆上部
				fillRectangle(xLeft,y + dx, w ,1,color);
			}
		}
		
		if(y + dy <= SCREEN_HEIGHT && y + dy >= 0){
			xLeft = x - dx;
			w =  dx * 2;
			if(xLeft < 0){
				xLeft = 0;
				w = dx + x;
			}
			if(w > SCREEN_WIDTH){
				w = SCREEN_WIDTH;
			}
			if(w > 0 ){
				//下半圆下部
				fillRectangle(xLeft,y + dy, w ,1,color);
			}
		}
		
		if(( dx * dx + dy * dy ) > rr){//离圆心的距离
			dy--;
		}
	}
}

/**
单色位图,如ascii字符,汉字,单色图标等数据
位图数据,一个字节对应8个像素,每个字节的高位到低位 byte[7:0]对应第0-7个像素
位图取模工具请访问 https://www.buziot.com/tools
*/
//画ascii字符
void drawAscii(char ch, FontSize fontSize, int16_t x,int16_t y, uint16_t color,uint16_t bgColor){
	uint16_t idx = 0;
	if(ch <32 || ch > 126){
		return;
	}
	
	/*
	x = x > SCREEN_WIDTH ? SCREEN_WIDTH: x;
	x = x < SCREEN_OFFSET_X ? SCREEN_OFFSET_X: x;
	
	y = y > SCREEN_HEIGHT ? SCREEN_HEIGHT: y;
	y = y < SCREEN_OFFSET_Y ? SCREEN_OFFSET_Y: y;
	*/

	idx = ch - 32;
	if(fontSize == FontSize16){
		lcdMonocolour( x, y,  8, 16, color, bgColor, (char *)ascii8X16[idx]);
	}else if(fontSize == FontSize24){
		lcdMonocolour( x, y,  12, 24, color, bgColor, (char *)ascii12X24[idx]);
	}else if(fontSize == FontSize32) {
		lcdMonocolour( x, y,  16, 32, color, bgColor, (char *)ascii16X32[idx]);
	}
}

//画汉字
void drawChinese(uint16_t gbkCode, FontSize fontSize, int16_t x,int16_t y, uint16_t color,uint16_t bgColor){
	uint16_t i=0,idx = 0,len=0;
	len = sizeof(hzFontIndex)/sizeof(hzFontIndex[0]);
	for(i = 0;i<len;i++){
		if((gbkCode>>8) == hzFontIndex[i][0] && (gbkCode & 0x00FF) == hzFontIndex[i][1]){
			idx = i; //找到汉字,若找不到默认为0, 第0个显示一个黑框
			break;
		}
	}
	if(i >0){
		/*
		x = x > SCREEN_WIDTH ? SCREEN_WIDTH: x;
		x = x < SCREEN_OFFSET_X ? SCREEN_OFFSET_X: x;
		
		y = y > SCREEN_HEIGHT ? SCREEN_HEIGHT: y;
		y = y < SCREEN_OFFSET_Y ? SCREEN_OFFSET_Y: y;
		*/
		
		if(fontSize == FontSize16){
			lcdMonocolour( x, y,  16, 16, color, bgColor, (char *)hzFont16[idx]);
		}else if(fontSize == FontSize24){
			lcdMonocolour( x, y,  24, 24, color, bgColor, (char *)hzFont24[idx]);
		}else if(fontSize == FontSize32){
			lcdMonocolour( x, y,  32, 32, color, bgColor, (char *)hzFont32[idx]);
		}
	}
}

/**
画图片,暂只支持16位色
图片取模工具请访问 https://www.buziot.com/tools
*/
void drawImage(int16_t x,int16_t y,int16_t w,int16_t h,uint8_t *imgData){
	/*
		x = x > SCREEN_WIDTH ? SCREEN_WIDTH: x;
		x = x < SCREEN_OFFSET_X ? SCREEN_OFFSET_X: x;
		
		y = y > SCREEN_HEIGHT ? SCREEN_HEIGHT: y;
		y = y < SCREEN_OFFSET_Y ? SCREEN_OFFSET_Y: y;
		*/
	
	lcdArea( x, y, w, h);
	lcdCmd(LCD_CMD_MEMORY_WRITE);
	lcdData(imgData,w * h * 2);
}

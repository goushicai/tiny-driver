#include "display.h"

void displayInit(void){
	lcdInit();
	
	lcdRotation(SCREEN_ROTATION);
	lcdMirror(SCREEN_MIRROR);
}

//����˯��ģʽ
void displaySleepOn(void){
	lcdSleepIn();
}

//�˳�˯��ģʽ
void displaySleepOff(void){
	lcdSleepOut();
}

//�򿪷�ɫģʽ
void displayInvertionOn(void){
	lcdInvertionOn();
}

//�򿪷�ɫģʽ
void displayInvertionOff(void){
	lcdInvertionOff();
}

//�򿪿���ģʽ
void displayIdleOn(void){
	lcdDisplayIdleOn();
}

//�򿪿���ģʽ
void displayIdleOff(void){
	lcdDisplayIdleOff();
}

//����ʾ
void displayOn(void){
	lcdDisplayOn();
}

//�ر���ʾ
void displayOff(void){
	lcdDisplayOff();
}

//��λ
void displayReset(void){
	lcdReset();
}

void displayBrightness(uint8_t val){
	/**
		����Ļ��֧�ֵ�������,���Կ�����pwm��������led������ʵ��
	*/
}
//��ʾ��������, 0Ĭ��,1��ʱ��ת90��,2��ʱ��ת180��,3��ʱ��ת270��
void displayRotation(uint8_t rotation){
	lcdRotation(rotation);
}

//��ʾ����, 0Ĭ��,1��ˮƽ����,2����ֱ����,3ˮƽ��ֱ������
void displayMirror(uint8_t mirror){
	lcdMirror(mirror);
}

//����
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
	
	lcdBlock( x, y,  w, lineWidth, lineColor); //��
	lcdBlock( x+w-lineWidth,  y, lineWidth, h, lineColor);//��
	lcdBlock( x, y+h-lineWidth,  w, lineWidth, lineColor); //��
	lcdBlock( x, y,  lineWidth,h, lineColor); //��
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
		
		if(( dx*dx + dy*dy ) > rr){//��Բ�ĵľ���,�����Ż���bresenham�㷨
			dy--;
		}
	}
}

//�ú������,���ϵ��·�Ϊ�ĸ�����,Ҫ���ǲ�����ʾ����Ĵ���
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
			xLeft = x - dx; //�������
			w = dx * 2;
			
			if(xLeft < 0){
				xLeft = 0;
				w = dx + x;//�߳�
			}
			
			if(w > SCREEN_WIDTH){
				w = SCREEN_WIDTH;
			}
			
			if(w > 0 ){
				//�ϰ�Բ�ϲ�
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
			
			//�ϰ�Բ�²�
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
				//�°�Բ�ϲ�
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
				//�°�Բ�²�
				fillRectangle(xLeft,y + dy, w ,1,color);
			}
		}
		
		if(( dx * dx + dy * dy ) > rr){//��Բ�ĵľ���
			dy--;
		}
	}
}

/**
��ɫλͼ,��ascii�ַ�,����,��ɫͼ�������
λͼ����,һ���ֽڶ�Ӧ8������,ÿ���ֽڵĸ�λ����λ byte[7:0]��Ӧ��0-7������
λͼȡģ��������� https://www.buziot.com/tools
*/
//��ascii�ַ�
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

//������
void drawChinese(uint16_t gbkCode, FontSize fontSize, int16_t x,int16_t y, uint16_t color,uint16_t bgColor){
	uint16_t i=0,idx = 0,len=0;
	len = sizeof(hzFontIndex)/sizeof(hzFontIndex[0]);
	for(i = 0;i<len;i++){
		if((gbkCode>>8) == hzFontIndex[i][0] && (gbkCode & 0x00FF) == hzFontIndex[i][1]){
			idx = i; //�ҵ�����,���Ҳ���Ĭ��Ϊ0, ��0����ʾһ���ڿ�
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
��ͼƬ,��ֻ֧��16λɫ
ͼƬȡģ��������� https://www.buziot.com/tools
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

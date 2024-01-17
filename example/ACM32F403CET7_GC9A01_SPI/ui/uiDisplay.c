#include "uiDisplay.h"

unsigned char DisplayRams[DISP_RAM_SIZE] ;
uiText txtDef;
uiRing ringDef;

void TransmitDRam(uint16_t x,uint16_t y,uint16_t width,uint16_t height){
	lcdWritRegByte(_ColumnAddSet);//列地址设置
    lcdWritBus32(x, x + width - 1);
    lcdWritRegByte(_PageAddSet);//行地址设置
    lcdWritBus32(y,y + height-1);
    lcdWritRegByte(_MemoryWrite);//储存器写
	
    lcdCSClr();
    HAL_SPI_Transmit(&lcdSpiHandle, DisplayRams, width*height*2, 0);
    lcdCSSet();
}

//将字模数据转成显存
void fontDataToDram(const char *p,uint16_t byteCount,uint16_t color, uint16_t bgColor){
	uint8_t ch,txtColorL,txtColorH,bgColorL,bgColorH;
	uint16_t i=0,idx=0;
	txtColorH = color >> 8;
	txtColorL = color & 0x00FF;
	bgColorH = bgColor >> 8;
	bgColorL = bgColor & 0x00FF;
	
	for(i = 0;i < byteCount; i++){
		ch = *(p+i);
		DisplayRams[idx++] = (ch & 0x80)==0 ? bgColorH : txtColorH;
		DisplayRams[idx++] = (ch & 0x80)==0 ? bgColorL : txtColorL;
		DisplayRams[idx++] = (ch & 0x40)==0 ? bgColorH : txtColorH;
		DisplayRams[idx++] = (ch & 0x40)==0 ? bgColorL : txtColorL;
		DisplayRams[idx++] = (ch & 0x20)==0 ? bgColorH : txtColorH;
		DisplayRams[idx++] = (ch & 0x20)==0 ? bgColorL : txtColorL;
		DisplayRams[idx++] = (ch & 0x10)==0 ? bgColorH : txtColorH;
		DisplayRams[idx++] = (ch & 0x10)==0 ? bgColorL : txtColorL;
		DisplayRams[idx++] = (ch & 0x08)==0 ? bgColorH : txtColorH;
		DisplayRams[idx++] = (ch & 0x08)==0 ? bgColorL : txtColorL;
		DisplayRams[idx++] = (ch & 0x04)==0 ? bgColorH : txtColorH;
		DisplayRams[idx++] = (ch & 0x04)==0 ? bgColorL : txtColorL;
		DisplayRams[idx++] = (ch & 0x02)==0 ? bgColorH : txtColorH;
		DisplayRams[idx++] = (ch & 0x02)==0 ? bgColorL : txtColorL;
		DisplayRams[idx++] = (ch & 0x01)==0 ? bgColorH : txtColorH;
		DisplayRams[idx++] = (ch & 0x01)==0 ? bgColorL : txtColorL;
	}
}

void uiShowImage(uint16_t left,uint16_t top, uint16_t width,uint16_t height,uint8_t * imgData){
	lcdWritRegByte(_ColumnAddSet);//列地址设置
    lcdWritBus32(left, left + width - 1);
    lcdWritRegByte(_PageAddSet);//行地址设置
    lcdWritBus32(top,top + height-1);
    lcdWritRegByte(_MemoryWrite);//储存器写
	
    lcdCSClr();
    HAL_SPI_Transmit(&lcdSpiHandle, imgData, width*height*2, 0);
    lcdCSSet();
}
void uiShowIcon(uint16_t x,uint16_t y, uint8_t iconIdx,uint8_t iconSize, uint16_t color,uint16_t bgColor){
	uint16_t w,h;
	
	// 图标数据为阴码,要进行反转
	uint16_t tmp;
	tmp = color;color = bgColor;bgColor = tmp;
	
	if(iconSize == 24){
		fontDataToDram(gIcon24[iconIdx], sizeof(gIcon24[iconIdx]), color,bgColor);
		w = 32;
		h = 32;
	}else if(iconSize == 28){
		fontDataToDram(gIcon28[iconIdx], sizeof(gIcon28[iconIdx]), color,bgColor);
		w = 32;
		h = 32;
	}else{
		fontDataToDram(gIcon24[iconIdx], sizeof(gIcon24[iconIdx]), color,bgColor);
		w = 32;
		h = 32;
	}
	
	TransmitDRam(x,y, w,h);
}
void uiShowAscii(uint16_t x,uint16_t y, uint8_t ch, uint16_t fontSize,uint16_t color,uint16_t bgColor){
	uint16_t idx = ch - 32;
	if(fontSize == FONT_SIZE_16){
		fontDataToDram(ascii8X16[idx], sizeof(ascii8X16[idx]), color,bgColor);
	}else if(fontSize == FONT_SIZE_24){
		fontDataToDram(ascii12X24[idx], sizeof(ascii12X24[idx]), color,bgColor);
	}else if(fontSize == FONT_SIZE_32){
		fontDataToDram(ascii16X32[idx], sizeof(ascii16X32[idx]), color,bgColor);
	}else{//默认24
		fontDataToDram(ascii12X24[idx], sizeof(ascii12X24[idx]), color,bgColor);
	}
	
	TransmitDRam(x,y, fontSize/2,fontSize);
}

void uiShowChinese(uint16_t x,uint16_t y, uint16_t ch,uint16_t fontSize, uint16_t color,uint16_t bgColor){
	
	uint16_t l = 0,i=0,idx=0;
	l = sizeof(hzFontIndex)/sizeof(hzFontIndex[0]);
	
	for(i = 0;i < l;i++){
		if((ch>>8) == hzFontIndex[i][0] && (ch & 0x00FF) == hzFontIndex[i][1]){
			idx = i; //找到汉字,若找不到默认为0, 第0个显示一个黑框
			break;
		}
	}
	
	if(fontSize == FONT_SIZE_16){
		fontDataToDram(hzFont16[idx], sizeof(hzFont16[idx]), color,bgColor);
	}else if(fontSize == FONT_SIZE_24){
		fontDataToDram(hzFont24[idx], sizeof(hzFont24[idx]), color,bgColor);
	}else if(fontSize == FONT_SIZE_32){
		fontDataToDram(hzFont32[idx], sizeof(hzFont32[idx]), color,bgColor);
	}
	
	TransmitDRam(x,y, fontSize,fontSize);
}

void uiDisplayInversionOn(){
	lcdWritRegByte(_DispInverON);//显示倒转,打开
}
void uiDisplayInversionOff(){
	lcdWritRegByte(_DispInverOFF);//显示倒转,关闭
}

void uiDisplayBrightness(uint8_t bright){
	lcdSetBright(bright);
}

void uiDisplayCtrl(uint8_t val){
	lcdSetDispCTRL(val);
}

/**
	显示文本

	文本包括中文与ascii码,中文点两个字节,显示宽度为fontsize,
	ascii占一个字节,显示宽度为fontsize/2

	故实际的显示宽度为 byteCount * fontsize/2

	以下函数中注意 无符号整数减法溢出导致的bug
*/

void uiShowText(uiText txt){
	uint8_t i,left,top,w,h,pages=0,rows=0,cols=0;
	uint16_t ch ,byteCount,textWidth;
	byteCount = strlen(txt.text);
	textWidth = byteCount * txt.fontSize / 2;
	textWidth = textWidth > SCREEN_WIDTH ? SCREEN_WIDTH: textWidth;
	
	//默认字体
	if(txt.fontSize != FONT_SIZE_16 && txt.fontSize != FONT_SIZE_24 && txt.fontSize != FONT_SIZE_32){
		txt.fontSize = FONT_SIZE_24;
	}
	//默认对齐方式
	if(txt.align != ALIGN_LEFT && txt.align != ALIGN_CENTER && txt.align != ALIGN_RIGHT){
		txt.align = ALIGN_CENTER;
	}
	
	//默认显示位置
	txt.left = (txt.left <0 || txt.left >= SCREEN_WIDTH) ? 0 : txt.left;
	txt.top =  (txt.top < 0 || txt.top  >= SCREEN_HEIGHT) ? 0 : txt.top;
	
	//默认边框宽度
	txt.borderWidth = (txt.borderWidth < 0 || txt.borderWidth > SCREEN_WIDTH/2)
					? INPUT_BORDER_WIDTH : txt.borderWidth;
	
	//默认内补丁
	txt.padding = (txt.padding < 0 || txt.padding > SCREEN_WIDTH/2) 
					? INPUT_PADDING : txt.padding;
	
	//默认边框颜色
	//txt.borderColor = txt.borderColor == 0 ? INPUT_BORDER_COLOR : txt.borderColor;
	
	//默认文本框宽高
	txt.width  = (txt.width < txt.fontSize  || txt.width > SCREEN_WIDTH)  ?  textWidth   : txt.width;
	txt.height = (txt.height < txt.fontSize || txt.height > SCREEN_HEIGHT) ? txt.fontSize: txt.height;
	
	//todo 自动换行
	/*
	if(txt.overflow==1){
		
	}else{
		//文本超长截断
		byteCount = textWidth > txt.textboxWidth ? txt.textboxWidth / (txt.fontSize/2) : byteCount;
	}*/
	
	//文本超长截断
	byteCount = textWidth > txt.width ? txt.width / (txt.fontSize/2) : byteCount;
		
	//显示边框
	if(txt.borderWidth>0){
		left = txt.left > (txt.padding + txt.borderWidth) ? txt.left - (txt.padding + txt.borderWidth) : 0;
		top = txt.top > (txt.padding + txt.borderWidth) ? txt.top - (txt.padding + txt.borderWidth) : 0;
		w = txt.width + (txt.padding + txt.borderWidth)*2;
		h = txt.height+ (txt.padding + txt.borderWidth)*2;
		
		lcdFillRectangle(left,top,w,h,txt.borderColor);
	}
	
	//清除内补丁
	left = txt.left > txt.padding ? txt.left - txt.padding : 0 ;
	top  = txt.top  > txt.padding ? txt.top  - txt.padding : 0 ;
	w = txt.width + (txt.padding *2);
	h = txt.height+ (txt.padding *2);
	
	lcdFillRectangle(left,top,w,h,txt.bgColor);
		
	if(txt.align==ALIGN_CENTER){
		left = (txt.width - (byteCount * txt.fontSize / 2) )/2 + txt.left;
	}else if(txt.align==ALIGN_RIGHT){
		left = (txt.height - (byteCount * txt.fontSize / 2) ) + txt.left;
	}else {
		//默认靠左
		left = txt.left;
	}
	
	for(i=0;i<byteCount;i++){
		if(*(txt.text + i) & 0x80 ){ //汉字
			ch = (*(txt.text+i)<<8) | (*(txt.text+i+1));
			uiShowChinese(left + (txt.fontSize/2) * i,txt.top,ch, txt.fontSize,txt.color,  txt.bgColor);
			i ++;
		}else{ //ascii
			uiShowAscii(left + (txt.fontSize/2) * i,txt.top, *(txt.text+i), txt.fontSize, txt.color,  txt.bgColor);
		}
		if(txt.duration>0){
			System_Delay_MS(txt.duration);
		}
	}
}


//清屏
void uiClear(uint16_t color){
	lcdFillRectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,color);
}

//填充矩形
void uiFillRectangle(uint16_t x,uint16_t y, uint16_t w,uint16_t h,uint16_t color){
	lcdFillRectangle(x,y,w,h,color);
}

//画点
void uiDrawPoint(uint16_t x, uint16_t y, uint16_t color){
	lcdPoint(x,y,color);
}
//画线, bresenham算法
void uiDrawLine(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1, uint16_t color){
	int16_t dx,dy,sx,sy,err1,err2;
	
	dx = x1 > x0 ? (x1 - x0): (x0 - x1);
	sx = x0 < x1 ? 1 : -1; 
	dy = y1 > y0 ? (y1 - y0): (y0 - y1);
	sy = y0 < y1 ? 1 : -1; 
	
    err1 = (dx > dy ? dx : -dy) / 2;

    while (x0 != x1 || y0 != y1) {
		lcdPoint(x0,y0, color);
        err2 = err1;
        if (err2 > -dx) { err1 -= dy; x0 += sx; }
        if (err2 <  dy) { err1 += dx; y0 += sy; }
    }
}

void uiDrawCircle(uint16_t x,uint16_t y ,uint16_t r, uint16_t color){
	uint16_t dx=0,dy=r,rr=r*r;
	
	for(dx = 0;dx<=dy;dx++){
		lcdPoint(x + dx,y - dy,color);// 1/4 PI ~ 2/4 PI
		lcdPoint(x + dy,y - dx,color);// 0/4 PI ~ 1/4 PI
		
		lcdPoint(x + dy,y + dx,color);// 7/4 PI ~ 8/4 PI
		lcdPoint(x + dx,y + dy,color);// 6/4 PI ~ 7/4 PI
		
		lcdPoint(x - dx,y + dy,color);// 5/4 PI ~ 6/4 PI
		lcdPoint(x - dy,y + dx,color);// 4/4 PI ~ 5/4 PI
		
		lcdPoint(x - dy,y - dx,color);// 3/4 PI ~ 4/4 PI
		lcdPoint(x - dx,y - dy,color);// 2/4 PI ~ 3/4 PI
		
		if(( dx*dx + dy*dy ) > rr){//离圆心的距离
			dy--;
		}
	}
}

//用横线填充,从上到下分为四个区域
// 圆心必须在屏幕显示范围内,x,y不小于0,不大于屏幕范围, 圆至少要屏幕上显示1/4,
// todo x,y可为负数, 允许少于1/4圆的部分显示在屏幕上
void uiFillCircle(uint16_t x,uint16_t y ,uint16_t r, uint16_t color){
	uint16_t dx = 0,dy = r,rr=r*r,xo,yo,w;
	
	for(dx = 0; dx <= dy; dx ++){
		//要考虑不在显示区域的处理
		if(y > dy  && y - dy <= SCREEN_HEIGHT){
			xo = x - dx;
			w = dx * 2;
			if(x < dx){
				xo = 0;
				w = dx + x;
			}
				
			//上半圆上部
			lcdFillRectangle(xo,y - dy, w ,1,color);
		}
		
		if(y > dx && y - dx <= SCREEN_HEIGHT){
			xo = x - dy;
			w = dy * 2;
			if(x < dy){
				xo = 0;
				w = dy + x;
			}
			//上半圆下部
			lcdFillRectangle(x - dy,y - dx, w ,1,color);
		}
		
		if(y + dx <= SCREEN_HEIGHT){
			xo = x - dy;
			w =  dy * 2;
			if(x < dy){
				xo = 0;
				w = dy + x;
			}
			
			//下半圆上部
			lcdFillRectangle(xo,y + dx, w ,1,color);
		}
		
		if(y + dy <= SCREEN_HEIGHT){
			xo = x - dx;
			w =  dx * 2;
			if(x < dy){
				xo = 0;
				w = dx + x;
			}
			
			//下半圆下部
			lcdFillRectangle(xo,y + dy, w ,1,color);
		}
		
		/*
		//上半圆
		lcdFillRectangle(x - dx,y - dy, dx * 2 ,1,color);
		lcdFillRectangle(x - dy,y - dx, dy * 2 ,1,color);
		
		//下半圆
		lcdFillRectangle(x - dy,y + dx, dy * 2 ,1,color);
		lcdFillRectangle(x - dx,y + dy, dx * 2 ,1,color);
		*/
		
		if(( dx * dx + dy * dy ) > rr){//离圆心的距离
			dy--;
		}
	}
}

//画环
void uiDrawRing(uiRing ring){
	ring.ox = ring.ox == 0 ? SCREEN_CENTER_X : ring.ox ;
	ring.oy = ring.oy == 0 ? SCREEN_CENTER_Y : ring.oy ;
	
	if(ring.radius ==0){
		return;
	}else if(ring.radius == 1){
		lcdPoint(ring.ox,ring.oy,ring.color);
		return;
	}else if(ring.radius == OUTER_RADIUS){//环向外扩展一个像素,以免边缘某些像素不能正常显示
		ring.radius = ring.radius +1;
	}
	
	uiFillCircle(ring.ox, ring.oy, ring.radius,ring.color);
	uiFillCircle(ring.ox, ring.oy, ring.radius - ring.lineWidth,ring.bgColor);
}

//画圆弧
void uiDrawArc(uiArc arc){

}

uiText getUiTextInstance(){
	uiText instance;
	instance.align = ALIGN_CENTER;
	instance.fontSize = FONT_SIZE_24;
	instance.color = INPUT_TEXT_COLOR;
	instance.bgColor = INPUT_BG_COLOR;
	instance.borderColor = INPUT_BORDER_COLOR;
	
	instance.left = INPUT_LEFT;
	instance.top = INPUT_TOP;
	instance.borderWidth = 0;
	instance.padding = INPUT_PADDING;
	instance.width = INPUT_WIDTH;
	instance.height = INPUT_HEIGHT > FONT_SIZE_24 ? INPUT_HEIGHT : FONT_SIZE_24;
	instance.duration = 0;
	instance.overflow = 0;
	instance.dataType = 0;
	return instance;
}
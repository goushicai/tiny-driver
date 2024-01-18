#include "st7735s.h"
uint8_t 	_DisplayRAM[DISPLAY_RAM_SIZE*2];
uint8_t 	_LcdRotation=LCD_ROTATION,_LcdMirror=LCD_MIRROR;
uint16_t 	_LcdWidth=LCD_WIDTH,_LcdHeight=LCD_HEIGHT;

LcdStatusTypeDef lcdDisplayOn(){
	return lcdCmd(LCD_CMD_DISPLAY_ON);
}

LcdStatusTypeDef lcdDisplayOff(){
	return lcdCmd(LCD_CMD_DISPLAY_OFF);
}

//复位,有硬件复位管脚,则用硬件复位,否则用软复位
LcdStatusTypeDef lcdReset(void) {
#ifdef LCD_RST_PIN
	LCD_RST_ENABLE();
	HAL_Delay(1);	// 复位信号持续至少 9us (pdf v1.5 p93)
	LCD_RST_DISABLE();
	HAL_Delay(120); //复位后需要时间恢复,最大120ms (pdf v1.5 p93)
	return LCD_STATUS_OK;
	
#else
	lcdCmd(LCD_CMD_SOFT_RESET);
	HAL_Delay(120);
	return LCD_STATUS_OK;
#endif	
}

LcdStatusTypeDef lcdSleepIn(void){
	lcdCmd(LCD_CMD_SLEEP_IN);//进入睡眠模式,之后要延时120ms
	HAL_Delay(120);	
	return LCD_STATUS_OK;
}

LcdStatusTypeDef lcdSleepOut(void){
	lcdCmd(LCD_CMD_SLEEP_OUT);//退出睡眠模式,之后要延时120ms
	HAL_Delay(120);	
	return LCD_STATUS_OK;
}

//打开反色
LcdStatusTypeDef lcdInvertionOn(void){
	return lcdCmd(LCD_CMD_INVERSION_ON);
}

//关闭反色
LcdStatusTypeDef lcdInvertionOff(void){
	return lcdCmd(LCD_CMD_INVERSION_OFF);
}

//打开空闲模式
LcdStatusTypeDef lcdDisplayIdleOn(void){
	return lcdCmd(LCD_CMD_IDLE_ON);
}

//关闭空闲模式
LcdStatusTypeDef lcdDisplayIdleOff(void){
	return lcdCmd(LCD_CMD_IDLE_OFF);
}


LcdStatusTypeDef lcdInit(void){
	LCD_CS_ENABLE();//片选

	lcdReset();//复位
	
	lcdCmd(0x11);//退出睡眠模式,之后要延时120ms
	HAL_Delay(120);	
	
	/*帧率说明
		Frame Rate=Fosc/((RTNA*2+40) * (LINE+FPA+BPA+2))
		Fosc=850kHz, 要求FPA>0,BPA>0
	
	GM[1:0]=11,即 RGB 128*160 时
		RTNA/FPA/BPA 默认为 05h/3Ch/3Ch
		代入上面的公式可以计算得 
		Frame Rate = 850k / ((5 * 2 + 40) * (160 + 60 + 60 +2) )
					= 850000 / (50*222)
					= 60;
	*/
	//lcdCmd(0xB1); //设置帧率1(In normal mode/ Full colors)
	//lcdByte(0x01); //RTNA[3:0]
	//lcdByte(0x2C); //FPA[5:0]
	//lcdByte(0x2D); //BPA[5:0]
	
	//lcdCmd(0xB2); //设置帧率2(In Idle mode/ 8-colors)
	//lcdByte(0x01); 
	//lcdByte(0x2C); 
	//lcdByte(0x2D); 
	
	//lcdCmd(0xB3); //设置帧率3(In Partial mode/ full colors),
	//lcdByte(0x01);//前三个字节用于dot Inversion mode 
	//lcdByte(0x2C); 
	//lcdByte(0x2D); 
	//lcdByte(0x01); //后三个字节用于column inversion mode
	//lcdByte(0x2C); 
	//lcdByte(0x2D); 	
	lcdCmd(0xB4); //Column inversion 
	lcdByte(0x07); 	//全部置为 column inversion mode
	
	/**
		电源设置PWCTR1
		3个参数 
		param0: [7:5] AVDD[2:0], [4:0] VRHP[4:0]
		param1: [7:5] 000      , [4:0] VRHN[4:0]
		param2: [7:6] MODE[1:0], [5:2] 0001, [1] VRHN5, [0]VRHP5
		
		VRHP 用于指定 GVDD
		VRHN 用于指定 GVCL
		
		MODE[1:0]:  00 2X, 01 reserve, 10 AUTO, 01 reserve
		
		AVDD=4.5V ~ 5.2V
		GVDD = 3.15 ~ 5V
		GVCL = -3.15V ~ -5V
		
		默认值 A8h/08h/84h
		AVDD[2:0]=101 即AVDD5;
		VRHP[4:0]=01000,VRHP5=0,即GVDD = 4.3V
		VRHN[4:0]=01000,VRHN5=0,即GVCL = -4.3V
	*/
	
	//lcdCmd(0xC0);  // Power Control 1
	//lcdByte(0xA2); // AVDD=101,即AVDD = 5, VRHP[4:0]=2
	//lcdByte(0x02); // VRHN[4:0]=2
	//lcdByte(0x84); // MODE=10 AUTO, VRHN5=0,VRHP5=0,即GVDD=4.6,GVCL=-4.6
	/**
		电源设置PWCTR2
		默认值 C0h
	*/
	//lcdCmd(0xC1);  // Power Control 2
	//lcdByte(0xC5); 
	
	/**
		电源设置PWCTR3
		默认值 0Ah/00h
	*/
	//lcdCmd(0xC2);  // Power Control 3 (in Normal mode/ Full colors)
	//lcdByte(0x0A); 
	//lcdByte(0x00); 
	/**
		电源设置PWCTR4
		默认值 8Ah/26h
	*/
	lcdCmd(0xC3);  //Power Control 4 (in Idle mode/ 8-colors)
	lcdByte(0x8A); 
	lcdByte(0x2A); 
	
	/**
		电源设置PWCTR5
		默认值 8Ah/EEh
	*/
	lcdCmd(0xC4);  //Power Control 5 (in Partial mode/ full-colors
	lcdByte(0x8A); 
	lcdByte(0xEE); 
	
	/**
		VMCTR1 VCOM Control 1
		默认值 05h
	*/
	
	lcdCmd(0xC5); //VCOM 
	lcdByte(0x0E); 	
	
	/**
		Memory Data Access Control
		默认值 00h
		[7] MY 内存行读写顺序,0正常,1反转
		[6] MX 内存列读写,0正常,1反转
		[5] MV 内存行列互换,0正常,1互换
		[4] ML LCD刷新顺序,0,从上到下,1从下到上
		[3] RGB RGB颜色模式 0=RGB,1=BGR
		[2] MH LCD刷新顺序 0从左到右,1从右到左
		[1:0] 保留
	*/
	lcdCmd(0x36); //MX, MY, RGB mode 
	lcdByte(0x00); 
	
	//ST7735R Gamma Sequence
	lcdCmd(0xe0); 
	lcdByte(0x0f); 
	lcdByte(0x1a); 
	lcdByte(0x0f); 
	lcdByte(0x18); 
	lcdByte(0x2f); 
	lcdByte(0x28); 
	lcdByte(0x20); 
	lcdByte(0x22); 
	lcdByte(0x1f); 
	lcdByte(0x1b); 
	lcdByte(0x23); 
	lcdByte(0x37); 
	lcdByte(0x00); 	
	lcdByte(0x07); 
	lcdByte(0x02); 
	lcdByte(0x10); 
	
	lcdCmd(0xe1); 
	lcdByte(0x0f); 
	lcdByte(0x1b); 
	lcdByte(0x0f); 
	lcdByte(0x17); 
	lcdByte(0x33); 
	lcdByte(0x2c); 
	lcdByte(0x29); 
	lcdByte(0x2e); 
	lcdByte(0x30); 
	lcdByte(0x30); 
	lcdByte(0x39); 
	lcdByte(0x3f); 
	lcdByte(0x00); 
	lcdByte(0x07); 
	lcdByte(0x03); 
	lcdByte(0x10);  
	
	lcdCmd(0x2a); //设置列地址 0x00-0x7F (128)
	lcdByte(0x00);
	lcdByte(0x00);
	lcdByte(0x00);
	lcdByte(0x7f);
	
	lcdCmd(0x2b);//设置行地址 0x00 - 0x9F (159)
	lcdByte(0x00);
	lcdByte(0x00);
	lcdByte(0x00);
	lcdByte(0x9f);
	
	lcdCmd(0xF0); //Enable test command  
	lcdByte(0x01); 
	
	lcdCmd(0xF6); //Disable ram power save mode 
	lcdByte(0x00); 	
	/**
		COLMOD (3Ah): Interface Pixel Format
		
		[2:0] IFPF[2:0]
		
		001 12bit
		101 16bit
		110 18bit
	*/
	lcdCmd(0x3A); //像素颜色模式
	lcdByte(0x05); // 16bit
	
	lcdCmd(0x29);//Display on	

	//lcdDirection(LCD_ROTATION);//设置LCD显示方向
	//LCD_LED=1;//点亮背光	 
	
	lcdClear(0xFFFF);//清屏
	
	lcdRotation(_LcdRotation);
	lcdMirror(_LcdMirror);
	
	return LCD_STATUS_OK;
}

//屏幕方向
LcdStatusTypeDef lcdRotation(uint8_t direction){ 
	switch(direction){		  
		case 0:						 	 		
		    _LcdWidth=_LcdWidth;
			_LcdHeight=_LcdHeight;
			_LcdRotation = 0x00;//MY=0,MX=0,MV=0,ML=0,BGR=0,MH=0
			lcdCmd(0x36);
			lcdByte(_LcdRotation);
			break;
		case 1:
			_LcdWidth=_LcdHeight;
			_LcdHeight=_LcdWidth;
			_LcdRotation = 0xA0;//MY=1,MX=0,MV=1,ML=0,BGR=0,MH=0
			lcdCmd(0x36);
			lcdByte(_LcdRotation);
			break;
		case 2:	
			_LcdWidth=_LcdWidth;
			_LcdHeight=_LcdHeight;
			_LcdRotation = 0xC0;//MY=1,MX=1,MV=0,ML=0,BGR=0,MH=0
			lcdCmd(0x36);
			lcdByte(_LcdRotation);
			break;
		case 3:
			_LcdWidth=_LcdHeight;
			_LcdHeight=_LcdWidth;
			_LcdRotation = 0X60;//MY=0,MX=1,MV=1,ML=0,BGR=0,MH=0
			lcdCmd(0x36);
			lcdByte(_LcdRotation);
			break;
		default:break;
	}
	return LCD_STATUS_OK;		
}	


LcdStatusTypeDef lcdMirror(uint8_t mirror){
	uint8_t m = _LcdRotation;
	switch(mirror){		  
		case 0:
			m &= 0x3F; 	// MY = 0,MX = 0
			lcdCmd(LCD_CMD_MADCTL);
			lcdByte(m);
			break;
		case 1: //水平 MY = 0,MX = 1
			m &= 0x7F;
			m |= 0x40;  
			lcdCmd(LCD_CMD_MADCTL);
			lcdByte(m);
			break;
		case 2:	//垂直 MY = 1,MX = 0
			m |= 0x80; 
			m &= 0xBF;
			lcdCmd(LCD_CMD_MADCTL);
			lcdByte(m);
			break;
		case 3: //both	MY = 1,MX = 1
			m |= 0xC0;
			lcdCmd(LCD_CMD_MADCTL);
			lcdByte(m);
			break;
		default:
			break;
	}
	
	return LCD_STATUS_OK;		
}

//发送数据或命令, D/C在此函数之前要确定
LcdStatusTypeDef writeBus(uint8_t data){
	if(spiTxlcd( &data, 1) == HAL_OK){
		return LCD_STATUS_OK;
	}else{
		return LCD_STATUS_ERROR;
	}
}

//发送命令
LcdStatusTypeDef lcdCmd(uint8_t cmd){ 
	LCD_CMD_ENABLE(); 
	return writeBus(cmd);
}

//发送单字节数据
LcdStatusTypeDef lcdByte(uint8_t data){ 
	LCD_DATA_ENABLE(); 
	return writeBus(data);
}

//发送多字节数据
LcdStatusTypeDef lcdData(uint8_t *data, uint32_t size){
	LCD_DATA_ENABLE();
	if(spiTxlcd( data, size) == HAL_OK){
		return LCD_STATUS_OK;
	}else{
		return LCD_STATUS_ERROR;
	}
}

//发送双字节
LcdStatusTypeDef lcdHalfWord(uint16_t data){
	uint8_t d[2];
	d[0] = data >> 8;
	d[1] = (uint8_t)data;

	return lcdData(d, 2);
}

//发送两个双字节
LcdStatusTypeDef lcdWord(uint16_t d1, uint16_t d2){
	uint8_t d[4];
	d[0] = d1 >> 8;
	d[1] = (uint8_t)d1;
	d[2] = d2 >> 8;
	d[3] = (uint8_t)d2;

	return lcdData(d, 4);
}

LcdStatusTypeDef lcdCheckParam(int16_t x,int16_t y,int16_t w,int16_t h){
	if(x < 0 ){
		return LCD_STATUS_X_LESS_THAN_MIN;
	}else if(x > _LcdWidth){
		return LCD_STATUS_X_MORE_THAN_MAX;
	}
	
	if(y < 0 ){
		return LCD_STATUS_Y_LESS_THAN_MIN;
	}else if(x > _LcdWidth){
		return LCD_STATUS_Y_MORE_THAN_MAX;
	}
	
	if(w < 1){
		return LCD_STATUS_WIDTH_LESS_THAN_MIN;
	}
	
	if(h < 1){
		return LCD_STATUS_HEIGHT_LESS_THAN_MIN;
	}
	return LCD_STATUS_OK;
}

//设定操作区域
LcdStatusTypeDef lcdArea(int16_t x,int16_t y,int16_t w,int16_t h){
	LcdStatusTypeDef status = lcdCheckParam( x, y, w, h);
	if(status != LCD_STATUS_OK){
		return status;
	}
	
	w = (w+x)>_LcdWidth? _LcdWidth-x: w; //忽略屏幕范围以外的数据
	h = (h+y)>_LcdHeight? _LcdHeight-y: h;
	
	lcdCmd(LCD_CMD_SET_COLUMN);	
	lcdWord(x,x + w - 1);
	
	lcdCmd(LCD_CMD_SET_ROW);
	lcdWord(y,y + h - 1);
	
	return LCD_STATUS_OK;
}

LcdStatusTypeDef lcdPosition(int16_t x,int16_t y){
	return lcdArea(x,y,1,1); 
}

LcdStatusTypeDef lcdClear(uint16_t color){
	return lcdBlock(0,0,_LcdWidth,_LcdHeight,color);
}  

LcdStatusTypeDef lcdPixel(int16_t x,int16_t y, uint16_t color){
	LcdStatusTypeDef status = lcdPosition(x,y);
	if(status != LCD_STATUS_OK){
		return status;
	}

	lcdCmd(LCD_CMD_MEMORY_WRITE);

	return lcdHalfWord(color);
}

LcdStatusTypeDef lcdLine(int16_t x0,int16_t y0,int16_t x1,int16_t y1,uint16_t color,int16_t lineWidth){
	int16_t dx,dy,sx,sy,err1,err2;
	
	dx = x1 > x0 ? (x1 - x0): (x0 - x1);
	sx = x0 < x1 ? 1 : -1; 
	dy = y1 > y0 ? (y1 - y0): (y0 - y1);
	sy = y0 < y1 ? 1 : -1; 
    err1 = (dx > dy ? dx : -dy) / 2;
	lineWidth = lineWidth < 1 ? 1:lineWidth;
	
	//水平线与垂直线直接调用色块方法
	if(x0 == x1){
		return lcdBlock(x0,y0, dx,lineWidth, color); 
	}else if(y0 == y1){
		return lcdBlock(x0,y0, lineWidth,dy, color);
	}
	
    while (x0 != x1 || y0 != y1) {
		//lcdPixel(x0,y0, color);
		lcdBlock(x0,y0, lineWidth,lineWidth, color);
        err2 = err1;
        if (err2 > -dx) { 
			err1 -= dy; 
			x0 += sx; 
			if(x0 < 0 || x0 >_LcdWidth){
				continue;
			}
		}
        if (err2 <  dy) { 
			err1 += dx; 
			y0 += sy; 
			if(y0 < 0 || y0 >_LcdHeight){
				continue;
			}
		}
    }
    return LCD_STATUS_OK;
}

/**
单色位图,如文本,单色图标等数据
位图数据,一个字节对应8个像素,每个字节的高位到低位 byte[7:0]对应第0-7个像素
位图取模功能请访问 https://www.buziot.com/tools
*/
LcdStatusTypeDef lcdMonocolour(int16_t x,int16_t y, int16_t w,int16_t h,uint16_t color,uint16_t bgColor, char *data){
	
	uint8_t ch,tcH,tcL,bcH,bcL;
	int16_t xs,ys,i,j,k,ramIdx;
	int32_t byteIdx;
	
	if( (w <= 0 || h <= 0 ) 
		|| (x + w < 0 || y + h < 0 || x > _LcdWidth || y > _LcdHeight)
		|| ( w * h % 8 != 0) ) //区域像素为8的整数倍,但w并不定是8的整数倍
	{
		return LCD_STATUS_ERROR;
	}
	
	tcH = color   >> 8; tcL = (uint8_t)color;
	bcH = bgColor >> 8; bcL = (uint8_t)bgColor;
	
	xs=x; ys=y;i=w;j=h;
	
	if(x < 0){
		xs = 0; i = w + x;
	}
	if(y < 0){
		ys = 0; j = h + y;
	}
	
	ramIdx = 0;
	
	lcdArea(xs,ys,i,j);
	lcdCmd(LCD_CMD_MEMORY_WRITE);
	LCD_DATA_ENABLE(); 
	
	for(j = 0;j < h; j++){
		if( (y + j) < 0 || (y + j) >= _LcdHeight){
			continue;
		}
		for(i = 0;i < w;i++){
			if( (x + i) < 0 || (x + i) >= _LcdWidth){
				continue;
			}
			
			byteIdx = (j * w + i);
			k = byteIdx % 8;
			byteIdx = byteIdx >> 3;
			
			ch = *(data + byteIdx);
			
			
			if( (ch & (0x80 >> k)) == 0 ){
				_DisplayRAM[ramIdx++] = bcH ;
				_DisplayRAM[ramIdx++] = bcL;
			}else{
				_DisplayRAM[ramIdx++] = tcH ;
				_DisplayRAM[ramIdx++] = tcL;
			}
			
			//显存不可少于2字节
			if(ramIdx >= DISPLAY_RAM_SIZE * 2){
				spiTxlcd(_DisplayRAM,DISPLAY_RAM_SIZE * 2);
				ramIdx=0;
			}
		}
	}
	
	if(ramIdx > 0){
		spiTxlcd(_DisplayRAM,ramIdx);
	}
	 return LCD_STATUS_OK;
}
LcdStatusTypeDef lcdBlock(int16_t x,int16_t y, int16_t w,int16_t h,uint16_t color){
	uint16_t i=0,count=0,remain=0;
	
	if(w<=0 || h<=0){
		return LCD_STATUS_ERROR;
	}
	LcdStatusTypeDef status = lcdCheckParam( x, y, w, h);
	if(status != LCD_STATUS_OK){
		return status;
	}
	
	for(i = 0;i < DISPLAY_RAM_SIZE;i++){
		_DisplayRAM[2*i] = color>>8;
		_DisplayRAM[2*i+1] = (uint8_t)color;
	}
	
	w = (w+x)>_LcdWidth? _LcdWidth-x: w; //强制操作区域在屏幕范围
	h = (h+y)>_LcdHeight? _LcdHeight-y: h;
	
	count=(w * h)/ DISPLAY_RAM_SIZE;
	remain = (w * h)% DISPLAY_RAM_SIZE;
	
	lcdArea(x,y,w,h);
	lcdCmd(LCD_CMD_MEMORY_WRITE);
	LCD_DATA_ENABLE();
	
	for(i = 0; i<count; i++){
		spiTxlcd(_DisplayRAM,DISPLAY_RAM_SIZE*2);
    }
    if(remain > 0){
		spiTxlcd(_DisplayRAM,remain*2);
    }
	return LCD_STATUS_OK;
}


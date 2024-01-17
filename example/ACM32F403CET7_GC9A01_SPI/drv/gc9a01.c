#include "gc9a01.h"
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
	HAL_Delay(1);
	LCD_RST_DISABLE();
	HAL_Delay(1);
	return LCD_STATUS_OK;
	
#else
	lcdCmd(LCD_CMD_SOFT_RESET);
	HAL_Delay(120);
	return LCD_STATUS_OK
#endif	
}

/*
Sleep In Mode can 
only be left by the Sleep Out Command (11h). It will be necessary to wait 5msec before 
sending next to command, this is to allow time for the supply voltages and clock circuits to 
stabilize
*/
LcdStatusTypeDef lcdSleepIn(void){
	lcdCmd(LCD_CMD_SLEEP_IN);//进入睡眠模式至少要延时5ms ,文档 p101
	HAL_Delay(5);	
	return LCD_STATUS_OK;
}

/*
Sleep Out Mode 
can only be left by the Sleep In Command (10h). It will be necessary to wait 5msec before 
sending next command, this is to allow time for the supply voltages and clock circuits 
stabilize
*/
LcdStatusTypeDef lcdSleepOut(void){
	lcdCmd(LCD_CMD_SLEEP_OUT);//退出睡眠模式至少要延时5ms ,文档 p103
	HAL_Delay(5);	
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

//以下代码在官方提供的初始程序基础上修改而来
LcdStatusTypeDef lcdInit(void){
	LCD_BLK_ENABLE();
	LCD_CS_ENABLE();//片选

	lcdReset();//复位
	
	lcdCmd(0x11);//退出睡眠模式,之后延时120ms
	HAL_Delay(120);

	//lcdCmd(0xEF);
	//lcdCmd(0xEB);  //文档上没有找到此命令
	//lcdByte(0x14); 
	
	/*
		要将Inter_command置为高
		需要先写 0xFE 再写0xEF
	
		绝大部分指令要求Inter_command状态为高
	*/
    lcdCmd(0xFE);			 
	lcdCmd(0xEF); 

	/*
	lcdCmd(0xEB);	 //文档上没有找到此命令
	lcdByte(0x14); 

	//文档上没有找到0x8开头的所有命令
	lcdCmd(0x84);			
	lcdByte(0x40); 

	lcdCmd(0x85);			
	lcdByte(0xFF); 

	lcdCmd(0x86);			
	lcdByte(0xFF); 

	lcdCmd(0x87);			
	lcdByte(0xFF);

	lcdCmd(0x88);			
	lcdByte(0x0A);

	lcdCmd(0x89);			
	lcdByte(0x21); 

	lcdCmd(0x8A);			
	lcdByte(0x00); 

	lcdCmd(0x8B);			
	lcdByte(0x80); 

	lcdCmd(0x8C);			
	lcdByte(0x01); 

	lcdCmd(0x8D);			
	lcdByte(0x01); 

	lcdCmd(0x8E);			
	lcdByte(0xFF); 

	lcdCmd(0x8F);			
	lcdByte(0xFF); 
*/

/*
	0xB6 Display Function Control
	参数1,无效但必须有
	参数2 D6: GS, D5: SS
	
	SS: Sourc Output Scan Direction ,0: S1 -> S360, 1: S360 -> S1
	GS: Gate Output Scan Direction, 0: G1 -> G32 ,1 : G32 -> G1
*/
	lcdCmd(0xB6); 
	lcdByte(0x00);
	lcdByte(0x00);

/**
	Memory Access Control,MX, MY, RGB mode等
	
	文档中 [D3]为BGR标志
	Color selector switch control
	(0=RGB color filter panel, 1=BGR color filter panel)
	这里的描述可能有误, 当D3=0时,颜色模式是BRG,当D3=1时为RGB

*/
	lcdCmd(LCD_CMD_MADCTL); 
	lcdByte(0x48);//D3 = 1, 实测结果为RGB
	
	lcdCmd(0x3A); //像素颜色模式[D6:D4]用于rgb接口, [D2:D0]用于mcu接口,
	lcdByte(0x55); // 101:16bit,110:18bit, 011:12bit 仅mcu接口有效
/*
	lcdCmd(0x90);	//文档中找不到	
	lcdByte(0x08);
	lcdByte(0x08);
	lcdByte(0x08);
	lcdByte(0x08); 

	lcdCmd(0xBD);	//文档中找不到		
	lcdByte(0x06);
	
	lcdCmd(0xBC);	 //文档中找不到		
	lcdByte(0x00);	

	lcdCmd(0xFF);	//文档中找不到			
	lcdByte(0x60);
	lcdByte(0x01);
	lcdByte(0x04);
*/
/*
	Power Control 1 (C1h),	
	1个参数, [D1]:VCIRE	
	VCIRE:  0 Internal reference voltage 2.5V (default),
			1 External reference voltage Vci
*/
	//lcdCmd(0xC1); 
	//lcdByte(0x00); 
	
/*
	Power Control 2 (C3h)
	参数默认值 3Ch,
	
	Set the voltage level value to output the VREG1A and VREG1B OUT level, which is a 
	reference level for the grayscale voltage level.(Table is valid when vrh=0x28) 
	VREG1A = (vrh+vbp_d) * 0.02 + 4
	VREG1B = vbp_d * 0.02 + 0.3
	vrh = 0x28

	lcdCmd(0xC3);			
	lcdByte(0x13); // VREG1A=(0x28+0x13)*0.02+4=5.18 ,VREG1B=0.68
*/	

/*
	Power Control 3 (C4h)
	参数默认值 3Ch
	
	Set the voltage level value to output the VREG2A OUT level, which is a reference level for 
	the grayscale voltage level(Table is valid when vrh=0x28)
	
	VREG2A=(vbn_d-vrh) * 0.02 - 3.4
	VREG2B= vbn_d * 0.02 + 0.3
	
	

	lcdCmd(0xC4);			
	lcdByte(0x13); //VREG2A= -3.82, VREG2B = 0.68
*/	
/*
	Power Control 4 (C9h)
	参数默认值 28h
	
	Set the voltage level value to output the VREG1A OUT level, which is a reference level for 
	the grayscale voltage level. (Table is valid when vbp_d=0x3C and vbn_d=0x3C)
	VREG1A= (vrh + vbp_d) * 0.02 + 4
	VREG2A= (vbn_d - vrh) * 0.02 - 3.4
	
	vbp_d即 C3h 的值 , vbn_d 即C4h的值
	
	Inter_command should be set high to enable this command

	lcdCmd(0xC9);	//vbn_d !=3Ch,	vbp_d!=3Ch,此设置无效	
	lcdByte(0x22); 
*/

//	lcdCmd(0xBE);	//文档中找不到		
//	lcdByte(0x11); 

//	lcdCmd(0xE1);	 //文档中找不到			
//	lcdByte(0x10); 
//	lcdByte(0x0E);

//	lcdCmd(0xDF);	//文档中找不到		 	
//	lcdByte(0x21);
//	lcdByte(0x0c);
//	lcdByte(0x02);

	lcdCmd(0xF0);   //SET_GAMMA1
	lcdByte(0x45);
	lcdByte(0x09);
	lcdByte(0x08);
	lcdByte(0x08);
	lcdByte(0x26);
 	lcdByte(0x2A);

 	lcdCmd(0xF1);    //SET_GAMMA2
 	lcdByte(0x43);
 	lcdByte(0x70);
 	lcdByte(0x72);
 	lcdByte(0x36);
 	lcdByte(0x37);  
 	lcdByte(0x6F);

 	lcdCmd(0xF2);   //SET_GAMMA3
 	lcdByte(0x45);
 	lcdByte(0x09);
 	lcdByte(0x08);
 	lcdByte(0x08);
 	lcdByte(0x26);
 	lcdByte(0x2A);

 	lcdCmd(0xF3);   //SET_GAMMA4
 	lcdByte(0x43);
 	lcdByte(0x70);
 	lcdByte(0x72);
 	lcdByte(0x36);
 	lcdByte(0x37); 
 	lcdByte(0x6F);

//	lcdCmd(0xED);	//文档中找不到		
//	lcdByte(0x1B); 
//	lcdByte(0x0B); 

//	lcdCmd(0xAE);	//文档中找不到			
//	lcdByte(0x77);
//	
//	lcdCmd(0xCD);	//文档中找不到			
//	lcdByte(0x63);		


//	lcdCmd(0x70);	//文档中找不到			
//	lcdByte(0x07);
//	lcdByte(0x07);
//	lcdByte(0x04);
//	lcdByte(0x0E); 
//	lcdByte(0x0F); 
//	lcdByte(0x09);
//	lcdByte(0x07);
//	lcdByte(0x08);
//	lcdByte(0x03);

/*
	
	[D7:D4] = DINV[3:0],默认值 0x10 
	
	DINV[3:0] 
		0: column inversion
		1: 1 dot inversion
		2: 2 dot inversion
		3: 3 dot inversion
		4: 4 dot inversion
	

	lcdCmd(0xE8);	//Frame Rate (E8h)
	lcdByte(0x14);
*/

//	lcdCmd(0x62);	//文档中找不到			
//	lcdByte(0x18);
//	lcdByte(0x0D);
//	lcdByte(0x71);
//	lcdByte(0xED);
//	lcdByte(0x70); 
//	lcdByte(0x70);
//	lcdByte(0x18);
//	lcdByte(0x0F);
//	lcdByte(0x71);
//	lcdByte(0xEF);
//	lcdByte(0x70); 
//	lcdByte(0x70);

//	lcdCmd(0x63);	//文档中找不到			
//	lcdByte(0x18);
//	lcdByte(0x11);
//	lcdByte(0x71);
//	lcdByte(0xF1);
//	lcdByte(0x70); 
//	lcdByte(0x70);
//	lcdByte(0x18);
//	lcdByte(0x13);
//	lcdByte(0x71);
//	lcdByte(0xF3);
//	lcdByte(0x70); 
//	lcdByte(0x70);

//	lcdCmd(0x64);		//文档中找不到		
//	lcdByte(0x28);
//	lcdByte(0x29);
//	lcdByte(0xF1);
//	lcdByte(0x01);
//	lcdByte(0xF1);
//	lcdByte(0x00);
//	lcdByte(0x07);

	lcdCmd(0x66);			//文档中找不到,但删除会影响显示	
	lcdByte(0x3C);
	lcdByte(0x00);
	lcdByte(0xCD);
	lcdByte(0x67);
	lcdByte(0x45);
	lcdByte(0x45);
	lcdByte(0x10);
	lcdByte(0x00);
	lcdByte(0x00);
	lcdByte(0x00);

	lcdCmd(0x67);		//文档中找不到,但删除会影响显示			
	lcdByte(0x00);
	lcdByte(0x3C);
	lcdByte(0x00);
	lcdByte(0x00);
	lcdByte(0x00);
	lcdByte(0x01);
	lcdByte(0x54);
	lcdByte(0x10);
	lcdByte(0x32);
	lcdByte(0x98);

//	lcdCmd(0x74);		//文档中找不到			
//	lcdByte(0x10);	
//	lcdByte(0x85);	
//	lcdByte(0x80);
//	lcdByte(0x00); 
//	lcdByte(0x00); 
//	lcdByte(0x4E);
//	lcdByte(0x00);					
//	
//	lcdCmd(0x98);		//文档中找不到		
//	lcdByte(0x3e);
//	lcdByte(0x07);

/**
	文档中描述中,只有D0有效,其它位无效,但若只将值设为 0x01,颜色会显示为补色,设为0x21才能正常显示
*/
	lcdCmd(0x35);	//Tearing Effect Line ON (35h),默认00h
	lcdCmd(0x21);

	lcdCmd(0x29);//Display on
	HAL_Delay(20);
	
	return LCD_STATUS_OK;
}

//屏幕方向
LcdStatusTypeDef lcdRotation(uint8_t direction){ 
	switch(direction){		  
		case 0:						 	 		
		    _LcdWidth=_LcdWidth;
			_LcdHeight=_LcdHeight;
			_LcdRotation = 0x48;//MY=0,MX=1,MV=0,ML=0,BGR=1,MH=0
			lcdCmd(LCD_CMD_MADCTL);
			lcdByte(_LcdRotation);
			break;
		case 1:
			_LcdWidth=_LcdHeight;
			_LcdHeight=_LcdWidth;
			_LcdRotation = 0xE8;//MY=1,MX=1,MV=1,ML=0,BGR=1,MH=0
			lcdCmd(LCD_CMD_MADCTL);
			lcdByte(_LcdRotation);
			break;
		case 2:	
			_LcdWidth=_LcdWidth;
			_LcdHeight=_LcdHeight;
			_LcdRotation = 0x88;//MY=1,MX=0,MV=0,ML=0,BGR=1,MH=0
			lcdCmd(LCD_CMD_MADCTL);
			lcdByte(_LcdRotation);
			break;
		case 3:
			_LcdWidth=_LcdHeight;
			_LcdHeight=_LcdWidth;
			_LcdRotation = 0X28;//MY=0,MX=0,MV=1,ML=0,BGR=1,MH=0
			lcdCmd(LCD_CMD_MADCTL);
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
			m &= 0x7F; //  MY = 0,MX = 1
			m |= 0x40;  // 
			lcdCmd(LCD_CMD_MADCTL);
			lcdByte(m);
			break;
		case 1: //水平
			m &= 0x3F; 	// MY = 0,MX = 0
			lcdCmd(LCD_CMD_MADCTL);
			lcdByte(m);
			break;
		case 2:	//垂直
			m |= 0xC0;  // MY = 1,MX = 1
			lcdCmd(LCD_CMD_MADCTL);
			lcdByte(m);
			break;
		case 3: //both	MY = 1,MX = 0
			m |= 0x80; 
			m &= 0xBF;
			lcdCmd(LCD_CMD_MADCTL);
			lcdByte(m);
			break;
		default:
			break;
	}
	
	return LCD_STATUS_OK;		
}

//发送命令
LcdStatusTypeDef lcdCmd(uint8_t cmd){ 
	LcdStatusTypeDef state = LCD_STATUS_ERROR;
	LCD_CMD_ENABLE(); 
	if(spiTxlcd( &cmd, 1) == HAL_OK){
		state =  LCD_STATUS_OK;
	}
	return state;
}

//发送单字节数据
LcdStatusTypeDef lcdByte(uint8_t data){
	LcdStatusTypeDef state = LCD_STATUS_ERROR;
	LCD_DATA_ENABLE(); 
	if(spiTxlcd( &data, 1) == HAL_OK){
		state =  LCD_STATUS_OK;
	}	
	return state;
}

//发送多字节数据
LcdStatusTypeDef lcdData(uint8_t *data, uint32_t size){
	LcdStatusTypeDef state = LCD_STATUS_ERROR;
	LCD_DATA_ENABLE();
	if(spiTxlcd( data, size) == HAL_OK){
		state =  LCD_STATUS_OK;
	}
	return state;
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
	if(x0 == x1){//垂直线
		return lcdBlock(x0,y0, lineWidth,dy, color); 
	}else if(y0 == y1){//水平线
		return lcdBlock(x0,y0, dx,lineWidth, color);
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
			continue; //忽略超出显示范围
		}
		for(i = 0;i < w;i++){
			if( (x + i) < 0 || (x + i) >= _LcdWidth){
				continue;//忽略超出显示范围
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


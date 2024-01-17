#include "viewPic.h"

uint8_t pixelSize = 3;

void showQRcode(){
	uint8_t i,j,k, x,y;
	uint16_t left,top;
	uiClear(WHITE);
	
	pixelSize = pixelSize <1 ? 1: pixelSize;
	pixelSize = pixelSize >5 ? 5: pixelSize;
	
	left = (SCREEN_WIDTH - (m_nSymbleSize * pixelSize))/2;
	top  = (SCREEN_HEIGHT - (m_nSymbleSize * pixelSize))/2;
	
	for(i = 0;i<m_nSymbleSize;i++){
		for(j = 0;j<m_nSymbleSize;j++){
			x = left + (i * pixelSize) ;
			y = top  + (j * pixelSize) ;
			if( m_byModuleData[i][j]==1){
				uiFillRectangle(x,y,pixelSize,pixelSize,BLACK);
			}else{
				uiFillRectangle(x,y,pixelSize,pixelSize,WHITE);
			}
		}
	}
}
void showPicView(void)
{
	char *str="QRCode:Hello World!";
	//uiShowImage(40,40, 160,160,(uint8_t *)gImage_qrcode);
	//System_Delay_MS(2000);
	
	//printfS("showPicView EncodeData start");
	EncodeData(str);
	//printfS("showPicView EncodeData done");
	showQRcode();
}


void showPicById(uint8_t picId){

}

//像数放大
void pixelUp(){
	if(pixelSize <5){
		pixelSize ++;
		showQRcode();
	}
}
//像数缩小
void pixelDown(){
	if(pixelSize > 1){
		pixelSize--;
		showQRcode();
	}
}
//获取页页事件
enumViewEvent getPicViewEvent()
{
    int8_t encoderValue,encoderEvent;

    enumViewEvent event = VIEW_EVENT_NONE;
    
	encoderValue = getEncoderVal();
    encoderEvent= getKeyVal();
	clrKeyVal();
	clrEncoderVal();
	
	if(encoderValue > 0){
		pixelUp();
	}else if(encoderValue < 0){
		pixelDown();
	}
	
	if(encoderEvent== ENCODER_EVENT_DOUBLE_CLICK) {      //退回到上级菜单
		event = VIEW_EVENT_BACK;
    }

    return event;
}
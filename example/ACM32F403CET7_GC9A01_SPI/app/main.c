#include "msp.h"
#include "bsp.h"
#include "api.h"

/**
本工程是ACM32F403 GC9A01 的驱动的演示, 代码中有本屏图片以及字库等内容

为了方便对汉字以及图片取模,我写了一个网页的端工具,若有需要可以访问
	https://www.buziot.com/tools

若有发现bug,或有什么意见与建议,请发送邮件:
	goushicai@qq.com 

或者提交issue : 
	https://github.com/goushicai/tiny-driver 
*/
extern volatile uint32_t gu32_SystemCount;

//获取系统tick
uint32_t HAL_GetTick(){
	return gu32_SystemCount;

}
//刷新率测试, uart输出
void fpsTest(){
	printfS("fpsTest is running\n");
	uint16_t uiColor[8]={0xF800,0x07E0,0x001F,0x52AA ,0x33D6 ,0x5DCB,0xF569,0xDA89};
	uint32_t i=0,tick,repeatCount;
	repeatCount = 100;
	tick = gu32_SystemCount;	
	for( i = 0;i<repeatCount;i++){
		lcdClear(uiColor[i%8]);
	}
	tick = HAL_GetTick() - tick;//时间差, fps = 1000/tick * 1000; 
	printfS("NO DMA, DRam:%d, Repeat:%d,Time: %dms, Fps: %0.2f\n",DISPLAY_RAM_SIZE*2,repeatCount, tick, ((double)(repeatCount*1000))/tick); 
	
	
	HAL_Delay(1000);
	
	printfS("fpsTest is finish\n");
}

void imageTest(){
	printfS("imageTest is running\n");
	
	drawImage(56,40,128,160,(uint8_t *)m48z);
	printfS("imageTest imgSize: %d\n", sizeof(m48z));
	HAL_Delay(1000);
	printfS("imageTest is finish\n");
}

void asciiTest(){
	int16_t i = 0,l = 0;
	printfS("asciiTest is running\n");
	
	for(l = 0;l < 5;l ++){
		for(i = 0;i < 30;i++){
			drawAscii((i+65), FontSize16,i*8,l*16,0xFFFF,0xF800);
		}
	}
	for(l = 0;l < 3;l ++){
		for(i = 0;i < 20;i++){
			drawAscii((i+65), FontSize24,i*12,l*24+80,0xFFFF,0xF800);
		}
	}
	
	for(l = 0;l < 2;l ++){
		for(i = 0;i < 15;i++){
			drawAscii((i+65), FontSize32,i*16,l*32+152,0xFFFF,0xF800);
		}
	}
	
	HAL_Delay(1000);
	printfS("asciiTest is finish\n");
}

void chineseTest(){
	int16_t offsetx;
	printfS("chineseTest is running\n");
	for(offsetx=-64;offsetx<240+64;offsetx++){
		//电流
		drawChinese(0xB5E7,FontSize32, offsetx,    0,0xFFFF,0xF800);
		drawChinese(0xC1F7,FontSize32, offsetx+32, 0,0xFFFF,0xF800);
		//电压
		drawChinese(0xB5E7,FontSize32, offsetx+0, 32,0xFFFF,0xF800);
		drawChinese(0xD1B9,FontSize32,offsetx+32, 32,0xFFFF,0xF800);
		//温度
		drawChinese(0xCEC2,FontSize32, offsetx+0, 64,0xFFFF,0xF800);
		drawChinese(0xB6C8,FontSize32,offsetx+32, 64,0xFFFF,0xF800);
		//速度
		drawChinese(0xCBD9,FontSize32, offsetx+0, 96,0xFFFF,0xF800);
		drawChinese(0xB6C8,FontSize32,offsetx+32, 96,0xFFFF,0xF800);
	}
	HAL_Delay(1000);
	printfS("chineseTest is finish\n");
}


void drawTest(){
	int16_t i = 0;
	printfS("chineseTest is running\n");
	displayClear(0xFFFF);
	
	drawLine(120,0, 120,240, 0xF800,5);//垂直线
	drawLine(0,120, 240, 120, 0x001F,5);//水平线
	
	drawLine(0,0, 240,240, 0xF800,1);//直线
	drawLine(0,240, 240,0, 0xF800,1);//直线
	
	drawRectangle(0,0, 60,30, 0x07E0,5);//空心矩形
	fillRectangle(64,0, 60,30, 0x001F);//实心矩形
	
	drawCircle(120,120, 60, 0x0000);//空心圆 
	
	for(i = -40;i<280;i+=8){
		if(i>=0){
			fillCircle(i-8,120, 40, 0xFFFF);//实心圆 
		}
		fillCircle(i,120, 40, 0xF569);//实心圆 
		HAL_Delay(500);
	}
	
	
	HAL_Delay(2000);
	printfS("drawTest is finish\n");
}

int main(void){
	uint8_t i = 0;
	
	System_Init();
	
	UART_Init(115200);//debug printfS
	
	SPI_Init(); //spi2
	
	GPIO_Init();
	
	//显示初始化
	displayInit();
	
	//displayClear(0xFFFF);//清屏
	
	//屏幕方向测试
	
	/*
	lcdRotation(0);//正常
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0x0000);
	
	lcdRotation(1);//逆时针转90度
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0xF800);
	
	lcdRotation(2);//逆时针转180度
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0x07E0);
	
	lcdRotation(3);//逆时针转270度
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0x001F);
	*/
	
	//镜像测试
	/*
	lcdMirror(0);//正常
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0x0000);
	
	lcdMirror(1);//水平镜像
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0xF800);
	
	lcdMirror(2);//垂直镜像
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0x07E0);
	
	lcdMirror(3);//水平垂直均镜像
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0x001F);
	*/
	
	while (1){
		ledTwinkle(2,500);//led闪烁两次
		
		fpsTest();
		imageTest();
		asciiTest();
		chineseTest();
		drawTest();
		
	}
}

#include "msp.h"
#include "bsp.h"
#include "api.h"

/**
本工程是STM32F103C8T6 ST7735S 的驱动的演示, 代码中有本屏图片以及字库等内容

为了方便对汉字以及图片取模,我写了一个网页的端工具,若有需要可以访问
	https://www.buziot.com/tools

若有发现bug,或有什么意见与建议,请发送邮件:
	goushicai@qq.com 

或者提交issue : 
	https://github.com/goushicai/tiny-driver 
	
本示例中含有DMA功能,可在 spi.h 中修改LCD_SPI_ENABLE_DMA以打开或关闭
*/
void HAL_MspInit(void){
  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_AFIO_REMAP_SWJ_NOJTAG();

	SystemClock_Config();
	
	GPIO_Init();
	
	SPI_Init(); //spi1
	
	UART_Init();//printf重定向到uart1口,方便调试输出
}
//刷新率测试, uart输出
void fpsTest(){
	printf("fpsTest is running\n");
	uint16_t uiColor[8]={0xF800,0x07E0,0x001F,0x52AA ,0x33D6 ,0x5DCB,0xF569,0xDA89};
	uint32_t i=0,tick,repeatCount;
	repeatCount = 100;
	tick = HAL_GetTick();	
	for( i = 0;i<repeatCount;i++){
		lcdClear(uiColor[i%8]);
	}
	tick = HAL_GetTick() - tick;//时间差, fps = 1000/tick * 1000; 
	printf("NO DMA, DRam:%d, Repeat:%d,Time: %dms, Fps: %0.2f\n",DISPLAY_RAM_SIZE*2,repeatCount, tick, ((double)(repeatCount*1000))/tick); 
		
	HAL_Delay(1000);
	
#if(LCD_SPI_ENABLE_DMA == 1)
	tick = HAL_GetTick();	
	for( i = 0;i<repeatCount;i++){
		while(dmaSpiTxState != 0){
			//等待dma调用结束
		}
		lcdClearDMA(uiColor[(i+3)%8]);
	}
	tick = HAL_GetTick() - tick;//时间差, fps = 1000/tick * 1000;
	//printf("BY DMA, DRam:%d, Repeat: %d, Time: %d ms, Fps: %0.2f\n\n",DISPLAY_RAM_SIZE*2,repeatCount, tick, ((double)(repeatCount*1000))/tick); 
	printf("NO DMA count:%d,times: %d ms\n", repeatCount,tick); 
	HAL_Delay(1000);
	
#endif
	printf("fpsTest is finish\n");
}

void imageTest(){
	printf("imageTest is running\n");
	
	drawImage(0,0,128,160,(uint8_t *)m48z);
	printf("imageTest imgSize: %d\n", sizeof(m48z));
	HAL_Delay(1000);
	printf("imageTest is finish\n");
}

void asciiTest(){
	int16_t i = 0;
	printf("asciiTest is running\n");
	for(i = 0;i < 16;i++){
		drawAscii((i+65), FontSize16,i*8,0,0xFFFF,0xF800);
	}
	
	for(i = 0;i < 11;i++){
		drawAscii((i+65), FontSize24,i*12,16,0xFFFF,0xF800);
	}
	
	for(i = 0;i < 8;i++){
		drawAscii((i+65), FontSize32,i*16,40,0xFFFF,0xF800);
	}
	HAL_Delay(1000);
	printf("asciiTest is finish\n");
}

void chineseTest(){
	int16_t offsetx;
	printf("chineseTest is running\n");
	for(offsetx=-64;offsetx<128;offsetx++){
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
	printf("chineseTest is finish\n");
}


void drawTest(){
	int16_t i = 0;
	printf("chineseTest is running\n");
	displayClear(0xFFFF);
	
	drawLine(64,0, 64,160, 0xF800,5);//垂直线
	drawLine(0,80, 0, 160, 0x001F,5);//水平线
	
	drawLine(0,0, 128,160, 0xF800,1);//直线
	drawLine(0,128, 128,0, 0xF800,1);//直线
	
	drawRectangle(0,0, 60,30, 0x07E0,5);//空心矩形
	fillRectangle(64,0, 60,30, 0x001F);//实心矩形
	
	drawCircle(64,80, 60, 0x0000);//空心圆 
	
	for(i = -40;i<162;i+=8){
		if(i>=0){
			fillCircle(i-8,80, 40, 0xFFFF);//实心圆 
		}
		fillCircle(i,80, 40, 0xF569);//实心圆 
		HAL_Delay(500);
	}
	
	
	HAL_Delay(2000);
	printf("drawTest is finish\n");
}

int main(void){
	uint8_t i = 0;
	HAL_Init();
	HAL_Delay(200);
	
	//显示初始化
	displayInit();
	
	displayClear(0xFFFF);//清屏
	
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
		
		//ledTwinkle(2,100);//led闪烁两次
		
		printf("Hello_World_%d\n",i++);
		HAL_Delay(1000);
		
		if(i>200){
			i = 0;
		}
		//drawTest();
		//fpsTest();
		//imageTest();
		//asciiTest();
		//chineseTest();
		
	}
}

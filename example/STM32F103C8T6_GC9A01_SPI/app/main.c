#include "msp.h"
#include "bsp.h"
#include "api.h"

/**

��������st7735s����������ʾ, �������б���ͼƬ�Լ��ֿ������,��̬������50��k,
���ϴ�����ܳ���64k,��STM32F103C8T6�����µ�MCU,����ע��һ���ִ����ٱ�������

Ϊ�˷���Ժ����Լ�ͼƬȡģ,��д��һ����ҳ�Ķ˹���,������Ҫ���Է���
	https://www.buziot.com/tools

���з���bug,����ʲô����뽨��,
����ϵ goushicai@qq.com ,

����Ŀ�ѷ����� github.com/goushicai/open-driver,ϲ��star,fork
������������϶�,����Ŀ�����ڻ����и���,����� 

*/

void HAL_MspInit(void){
  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_AFIO_REMAP_SWJ_NOJTAG();

	SystemClock_Config();
	
	GPIO_Init();
	
	SPI_Init(); //spi1
	
	UART_Init();//printf�ض���uart1��,����������
}
//ˢ���ʲ���, uart���
void fpsTest(){
	printf("fpsTest is running\n");
	uint16_t uiColor[8]={0xF800,0x07E0,0x001F,0x52AA ,0x33D6 ,0x5DCB,0xF569,0xDA89};
	uint32_t i=0,tick,repeatCount;
	repeatCount = 100;
	tick = HAL_GetTick();	
	for( i = 0;i<repeatCount;i++){
		lcdClear(uiColor[i%8]);
	}
	tick = HAL_GetTick() - tick;//ʱ���, fps = 1000/tick * 1000; 
	printf("NO DMA, DRam:%d, Repeat:%d,Time: %dms, Fps: %0.2f\n",DISPLAY_RAM_SIZE*2,repeatCount, tick, ((double)(repeatCount*1000))/tick); 
		
	HAL_Delay(1000);
	
#if(LCD_SPI_ENABLE_DMA == 1)
	tick = HAL_GetTick();	
	for( i = 0;i<repeatCount;i++){
		while(dmaSpiTxState != 0){
			//�ȴ�dma���ý���
		}
		lcdClearDMA(uiColor[(i+3)%8]);
	}
	tick = HAL_GetTick() - tick;//ʱ���, fps = 1000/tick * 1000;
	printf("BY DMA, DRam:%d, Repeat: %d, Time: %d ms, Fps: %0.2f\n\n",DISPLAY_RAM_SIZE*2,repeatCount, tick, ((double)(repeatCount*1000))/tick); 
	
	HAL_Delay(1000);
	
#endif
	printf("fpsTest is finish\n");
}

void imageTest(){
	printf("imageTest is running\n");
	displayClear(0xFFFF);
	drawImage(88,80,64,80,(uint8_t *)m48z);
	printf("imageTest imgSize: %d\n", sizeof(m48z));
	HAL_Delay(1000);
	printf("imageTest is finish\n");
}

void asciiTest(){
	int16_t i = 0;
	printf("asciiTest is running\n");
	displayClear(0xFFFF);
	for(i = 0;i < 30;i++){
		drawAscii((i+65), FontSize16,i*8,40,0xFFFF,0xF800);
	}
	
	for(i = 0;i < 20;i++){
		drawAscii((i+65), FontSize24,i*12,60,0xFFFF,0xF800);
	}
	
	for(i = 0;i < 15;i++){
		drawAscii((i+65), FontSize32,i*16,90,0xFFFF,0xF800);
	}
	HAL_Delay(1000);
	printf("asciiTest is finish\n");
}

void chineseTest(){
	int16_t offsetx;
	printf("chineseTest is running\n");
	displayClear(0xFFFF);
	
	for(offsetx=0;offsetx<240;offsetx++){
		//����
		drawChinese(0xB5E7,FontSize32, offsetx,    0,0xFFFF,0xF800);
		drawChinese(0xC1F7,FontSize32, offsetx+32, 0,0xFFFF,0xF800);
		//��ѹ
		drawChinese(0xB5E7,FontSize32, offsetx+0, 32,0xFFFF,0xF800);
		drawChinese(0xD1B9,FontSize32,offsetx+32, 32,0xFFFF,0xF800);
		//�¶�
		drawChinese(0xCEC2,FontSize32, offsetx+0, 64,0xFFFF,0xF800);
		drawChinese(0xB6C8,FontSize32,offsetx+32, 64,0xFFFF,0xF800);
		//�ٶ�
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
	
	drawLine(120,0, 120,240, 0xF800,5);//��ֱ��
	drawLine(0,120, 240,120,0x001F,5);//ˮƽ��
	
	drawLine(0,0, 240,240, 0xF800,1);//ֱ��
	drawLine(0,240, 240,0, 0xF800,1);//ֱ��
	
	drawRectangle(40,60, 75,40, 0x07E0,5);//���ľ���
	fillRectangle(120,60, 75,40, 0x001F);//ʵ�ľ���
	
	drawCircle(120,120, 100, 0x0000);//����Բ 
	
	for(i = 0;i<240;i+=10){
		fillCircle(i,30, 120, 0xF569);//ʵ��Բ 
	}
	
	
	HAL_Delay(2000);
	printf("drawTest is finish\n");
}

int main(void){
	
	HAL_Init();
	
	//��ʾ��ʼ��
	displayInit();
	
	
	/*
	//��Ļ�������
	displayClear(0xFFFF);//����
	
	lcdRotation(0);//����
	drawAscii('F',FontSize32, 40,    40,0xFFFF,0x0000);
	
	lcdRotation(1);//��ʱ��ת90��
	drawAscii('F',FontSize32, 40,    40,0xFFFF,0xF800);
	
	lcdRotation(2);//��ʱ��ת180��
	drawAscii('F',FontSize32, 40,    40,0xFFFF,0x07E0);
	
	lcdRotation(3);//��ʱ��ת270��
	drawAscii('F',FontSize32, 40,    40,0xFFFF,0x001F);
	*/
	
	//�������
	/*
	displayClear(0xFFFF);//����
	
	lcdMirror(0);//����
	drawAscii('F',FontSize32, 40,    40,0xFFFF,0x0000);
	
	lcdMirror(1);//ˮƽ����
	drawAscii('F',FontSize32, 40,    40,0xFFFF,0xF800);
	
	lcdMirror(2);//��ֱ����
	drawAscii('F',FontSize32, 40,    40,0xFFFF,0x07E0);
	
	lcdMirror(3);//ˮƽ��ֱ������
	drawAscii('F',FontSize32, 40,    40,0xFFFF,0x001F);
	*/
	
	
	while (1){
		
		ledTwinkle(2,100);//led��˸����
		
		drawTest();
		
		//fpsTest();
		//imageTest();
		//asciiTest();
		//chineseTest();
		
		//HAL_Delay(2000);
	}
}

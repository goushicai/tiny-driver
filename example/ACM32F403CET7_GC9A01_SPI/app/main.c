#include "msp.h"
#include "bsp.h"
#include "api.h"

/**
��������ACM32F403 GC9A01 ����������ʾ, �������б���ͼƬ�Լ��ֿ������

Ϊ�˷���Ժ����Լ�ͼƬȡģ,��д��һ����ҳ�Ķ˹���,������Ҫ���Է���
	https://www.buziot.com/tools

���з���bug,����ʲô����뽨��,�뷢���ʼ�:
	goushicai@qq.com 

�����ύissue : 
	https://github.com/goushicai/tiny-driver 
*/
extern volatile uint32_t gu32_SystemCount;

//��ȡϵͳtick
uint32_t HAL_GetTick(){
	return gu32_SystemCount;

}
//ˢ���ʲ���, uart���
void fpsTest(){
	printfS("fpsTest is running\n");
	uint16_t uiColor[8]={0xF800,0x07E0,0x001F,0x52AA ,0x33D6 ,0x5DCB,0xF569,0xDA89};
	uint32_t i=0,tick,repeatCount;
	repeatCount = 100;
	tick = gu32_SystemCount;	
	for( i = 0;i<repeatCount;i++){
		lcdClear(uiColor[i%8]);
	}
	tick = HAL_GetTick() - tick;//ʱ���, fps = 1000/tick * 1000; 
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
	printfS("chineseTest is finish\n");
}


void drawTest(){
	int16_t i = 0;
	printfS("chineseTest is running\n");
	displayClear(0xFFFF);
	
	drawLine(120,0, 120,240, 0xF800,5);//��ֱ��
	drawLine(0,120, 240, 120, 0x001F,5);//ˮƽ��
	
	drawLine(0,0, 240,240, 0xF800,1);//ֱ��
	drawLine(0,240, 240,0, 0xF800,1);//ֱ��
	
	drawRectangle(0,0, 60,30, 0x07E0,5);//���ľ���
	fillRectangle(64,0, 60,30, 0x001F);//ʵ�ľ���
	
	drawCircle(120,120, 60, 0x0000);//����Բ 
	
	for(i = -40;i<280;i+=8){
		if(i>=0){
			fillCircle(i-8,120, 40, 0xFFFF);//ʵ��Բ 
		}
		fillCircle(i,120, 40, 0xF569);//ʵ��Բ 
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
	
	//��ʾ��ʼ��
	displayInit();
	
	//displayClear(0xFFFF);//����
	
	//��Ļ�������
	
	/*
	lcdRotation(0);//����
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0x0000);
	
	lcdRotation(1);//��ʱ��ת90��
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0xF800);
	
	lcdRotation(2);//��ʱ��ת180��
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0x07E0);
	
	lcdRotation(3);//��ʱ��ת270��
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0x001F);
	*/
	
	//�������
	/*
	lcdMirror(0);//����
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0x0000);
	
	lcdMirror(1);//ˮƽ����
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0xF800);
	
	lcdMirror(2);//��ֱ����
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0x07E0);
	
	lcdMirror(3);//ˮƽ��ֱ������
	drawAscii('F',FontSize32, 0,    0,0xFFFF,0x001F);
	*/
	
	while (1){
		ledTwinkle(2,500);//led��˸����
		
		fpsTest();
		imageTest();
		asciiTest();
		chineseTest();
		drawTest();
		
	}
}

/*
//���ʹ�ùٷ��⺯���������еײ㣬�ٶȽ����½���14֡ÿ�룬���������˾�Ƽ�����
//����IO����ֱ�Ӳ����Ĵ���������IO������ˢ�����ʿ��Դﵽ28֡ÿ�룡 

//GPIO��λ�����ߣ�,�˿����üĴ���BSRR ��1Ϊ����,�˿�����Ĵ���BRR��1Ϊ����

#define LCD_CS_ENABLE()  	LCD_PORT->BSRR|=(uint32_t)LCD_CS_PIN<<16u    	//Ƭѡ,�͵�ƽ��Ч	
#define LCD_CS_DISABLE() 	LCD_PORT->BSRR|=LCD_CS_PIN						// 	

#define	LCD_CMD_ENABLE()	LCD_PORT->BSRR|=(uint32_t)LCD_DC_PIN<<16u   	//�͵�ƽ����
#define	LCD_DATA_ENABLE()	LCD_PORT->BSRR|=LCD_DC_PIN      				//����    

#define	LCD_RST_ENABLE()	LCD_PORT->BSRR|=(uint32_t)LCD_DC_PIN<<16u   	//��λ,�͵�ƽ��Ч		  
#define	LCD_RST_DISABLE()	LCD_PORT->BSRR|=LCD_RST_PIN 					//��λ	

///////////////////////////////////////////////////////////////////////////////////////////

//����mcu�Ŀ⺯��,�Ĵ������ܲ�ͬ
//Ϊ������ֲ�����������ٶ������ļ����޸ģ��ⲿ�ּ�������ת�Ƶ� gpio.h��

#define LCD_CS_ENABLE()  	HAL_GPIO_WritePin(LCD_PORT,LCD_CS_PIN, GPIO_PIN_RESET)    	//Ƭѡ	
#define LCD_CS_DISABLE() 	HAL_GPIO_WritePin(LCD_PORT,LCD_CS_PIN, GPIO_PIN_SET) 		//δѡ��  	

#define	LCD_DATA_ENABLE()	HAL_GPIO_WritePin(LCD_PORT,LCD_DC_PIN, GPIO_PIN_SET)       //�ߵ�ƽ����    
#define	LCD_CMD_ENABLE()	HAL_GPIO_WritePin(LCD_PORT,LCD_DC_PIN, GPIO_PIN_RESET)     //�͵�ƽ����

#define	LCD_RST_ENABLE()	HAL_GPIO_WritePin(LCD_PORT,LCD_RST_PIN, GPIO_PIN_RESET)   	//��λ,�͵�ƽ��Ч		  
#define	LCD_RST_DISABLE()	HAL_GPIO_WritePin(LCD_PORT,LCD_RST_PIN, GPIO_PIN_SET)  		//����	
*/

/**
*******************************����Ϊ����****************************************

//���ʹ�ùٷ��⺯���������еײ㣬�ٶȽ����½���14֡ÿ�룬���������˾�Ƽ�����
//����IO����ֱ�Ӳ����Ĵ���������IO������ˢ�����ʿ��Դﵽ28֡ÿ�룡 

*******************************���ý���******************************************

������Ϊ�ǼĴ�������������ٶȱ仯�Ǵ����, GPIO �ٶȵ�ԶС��SPI, 
��Ӱ���ٶȵĲ�����Ƶ���� GPIO ����,�����ϵز���CS,D/C,
��������������ʱ,��D/C����,����HAL_SPI_Transmit �������ݼ���,������ GPIO �Ĳ���

SPIʱ��18M�������,ˢ���ʿ������ɴﵽ50FPS,��DMA�����������ٶ�,����ȫû�б�Ҫ

* ����ƽ̨��SMT32F103C8T6���Ŀ�����(����ԭ��M48Z), 1.8�� 128*160 ST7735S���� LCD ��ʾ�� 
* ϵͳʱ��: 72M
* SPIʱ��: 18M
* ��������: Keil 5.29 , STM32 HAL ��

���²�ͬ�Դ�����£��ò�ͬ��16bit��ɫ����(128*160)ˢ�µĵ� FPS ����

�ޱ����Ż�

DisRam	|256	|512	|1024	|2048	|3072	|4096	|5120	|6144	|7168	|8192
--------|-------|-------|-------|-------|-------|-------|-------|-------|-------|------
no dma	|45.68	|46.43	|46.69	|46.6	|46.36	|46.13	|45.85	|45.58	|45.31	|45.05
by dma	|51.12	|53.02	|53.91	|54.05	|53.79	|53.59	|53.16	|52.83	|52.47	|52.27
��������|10.64%	|12.43%	|13.39%	|13.78%	|13.81%	|13.92%	|13.75%	|13.72%	|13.65%	|13.81%


���� O1 �����Ż���

DisRam	|256	|512	|1024	|2048	|3072	|4096	|5120	|6144	|7168	|8192
--------|-------|-------|-------|-------|-------|-------|-------|-------|-------|------
no dma	|51.33	|52.14	|52.49	|52.49	|52.36	|52.19	|52		|51.79	|51.6	|51.39
by dma	|51.71	|53.39	|54.17	|54.38	|54.35	|54.05	|54.05	|53.82	|53.62	|53.11
��������|0.73%	|2.34%	|3.10%	|3.48%	|3.66%	|3.44%	|3.79%	|3.77%	|3.77%	|3.24%

���Կ���,���������Ż���,��DMA������DMA����������ں�С.

�����Կ����Դ沢����Խ������Խ��,�Դ��ڴ�Լ2048�����������,������SPI�Ļ����й�
�Դ治���ڵ���16byte,����16byte�ַ���ʾ���ܻ����쳣


�������ݽ����ο�,��ͬ�Ĵ�����֯,��ͬ��Ӳ��ƽ̨��õ����ݻ����в�ͬ

����Ƕ��ʽ����,25���ϵ�fps���㹻ʹ��,����DMA��ʽ������ˢ�����ܲ������壬���ɴ�ռ����dma��Դ,
��������DMA�ж�,���´���ṹ����,�������������,��������ֲ�븴��,�ۺ�����,����������DMA

ֻ�����������ֳ����£����Կ�������DMA

1. MCU���ؽ��أ���DMA������ʾ��MCU�ĸ���
2. RAM��Դ�㹻��������ȫ���Դ�,������DMAһ����ˢ��ȫ��,�����ط�������,ȫ���Դ������һЩ���ӵ���ʾ����,
	ȫ���Դ�ᵼ��FPS���������½�,����֧��,���Կ���ʹ��24λ�Դﵽ���õ���ʾЧ��,��������ֻ֧��16λ��ɫ

����S7735S�Ĺٷ��ĵ�,ʱ������(TSCYCW,Serial Clock Cycle (Write))��СֵΪ66ns,��ȫ��128*160*16bit���ݼ���,
ˢ��һ��Լ��Ҫ21.6ms,FPSԼ46,������ʱ���ź�Ϊ����ķ���,ֻ����ʱ�Ӹߵ͵�ƽ�ĳ���ʱ��,
����С����ԼΪ TSHW + TSLW = 30ns, ���Լ���õ�ʱ������Լ33.3M,FPSԼΪ102

��ʵ�ʵĲ��Խ����,�ٷ��ĵ��ǳ�����(���߹ٷ��ĵ��ѹ�ʱ,�Ҳο��İ汾��V1.5_20150303).
��ACM32F403����,SPIʱ����22.5Mʱ, FPS�ɴﵽ67����,��SPIʱ����Ϊ45,���������Ż���,���FPSԼ136,ˢ����ʾ��Ȼ����

*/

#ifndef __DRV_ST7735S_H
#define __DRV_ST7735S_H

#include "st7735s_config.h"

//����δ����г�
#define LCD_CMD_SOFT_RESET		0x01 		// Software Reset

#define LCD_CMD_SLEEP_IN		0x10        //����˯��ģʽ
#define LCD_CMD_SLEEP_OUT		0x11        //�˳�˯��ģʽ

#define LCD_CMD_INVERSION_OFF	0x20        //�رշ�ɫ
#define LCD_CMD_INVERSION_ON	0x21        //������ɫ

#define LCD_CMD_DISPLAY_OFF		0x28        //�ر���ʾ
#define LCD_CMD_DISPLAY_ON		0x29        //������ʾ

#define LCD_CMD_SET_COLUMN		0x2A        //�ݵ�ַ����
#define LCD_CMD_SET_ROW       	0x2B        //ҳ��ַ����
#define LCD_CMD_MEMORY_WRITE	0x2C        //�ڴ�д

#define LCD_CMD_IDLE_OFF		0x38        //�رտ���ģʽ
#define LCD_CMD_IDLE_ON			0x39        //��������ģʽ

#define LCD_CMD_MADCTL			0x36        //Memory Access Control,MY,MX,MV,ML,RGB,MH��

#if(LCD_SPI_ENABLE_DMA == 1)
extern volatile uint8_t  dmaSpiTxState;
#endif

typedef enum {
	LCD_STATUS_OK 			= 0x00U,		//ǰ4���̳� HAL_StatusTypeDef
	LCD_STATUS_ERROR    = 0x01U,
	LCD_STATUS_BUSY 		= 0x02U,
	LCD_STATUS_TIMEOUT 	= 0x03U,
	
	LCD_STATUS_X_LESS_THAN_MIN 	= 0x10U,
	LCD_STATUS_X_MORE_THAN_MAX 	= 0x11U,
	
	LCD_STATUS_Y_LESS_THAN_MIN 	= 0x12U,
	LCD_STATUS_Y_MORE_THAN_MAX 	= 0x13U,
	
	LCD_STATUS_WIDTH_LESS_THAN_MIN 	= 0x14U,
	LCD_STATUS_HEIGHT_LESS_THAN_MIN	= 0x15U
	
} LcdStatusTypeDef;

//��ʼ��
LcdStatusTypeDef lcdInit(void);

//��λ
LcdStatusTypeDef lcdReset(void);

//����˯��ģʽ
LcdStatusTypeDef lcdSleepIn(void);

//�˳�˯��ģʽ
LcdStatusTypeDef lcdSleepOut(void);

//�򿪷�ɫ
LcdStatusTypeDef lcdInvertionOn(void);

//�رշ�ɫ
LcdStatusTypeDef lcdInvertionOff(void);

//����ʾ
LcdStatusTypeDef lcdDisplayOn(void);

//�ر���ʾ
LcdStatusTypeDef lcdDisplayOff(void);

//�򿪿���ģʽ
LcdStatusTypeDef lcdDisplayIdleOn(void);

//�رտ���ģʽ
LcdStatusTypeDef lcdDisplayIdleOff(void);

//��������
LcdStatusTypeDef lcdCmd(uint8_t cmd);

//���͵��ֽ�����
LcdStatusTypeDef lcdByte(uint8_t data);

//����˫�ֽ�����
LcdStatusTypeDef lcdHalfWord(uint16_t data);

//��������˫�ֽ�����
LcdStatusTypeDef lcdWord(uint16_t d1, uint16_t d2);

//���Ͷ��ֽ�����
LcdStatusTypeDef lcdData(uint8_t *p, uint32_t size);

//������Ļ����
LcdStatusTypeDef lcdRotation(uint8_t direction); 

//������Ļ����
LcdStatusTypeDef lcdMirror(uint8_t mirror);

//������ʾ����
LcdStatusTypeDef lcdArea(int16_t x,int16_t y,int16_t w,int16_t h);

//����λ��
LcdStatusTypeDef lcdPosition(int16_t x,int16_t y);

//���
LcdStatusTypeDef lcdPixel(int16_t x,int16_t y, uint16_t color);

//��ֱ��
LcdStatusTypeDef lcdLine(int16_t x0,int16_t y0,int16_t x1,int16_t y1,uint16_t color,int16_t lineWidth);

//����/ȫ��Ϳɫ
LcdStatusTypeDef lcdClear(uint16_t color);

//����Ϳɫ
LcdStatusTypeDef lcdBlock(int16_t x,int16_t y, int16_t w,int16_t h,uint16_t color);

//��ɫλͼ
LcdStatusTypeDef lcdMonocolour(int16_t x,int16_t y, int16_t w,int16_t h,uint16_t color,uint16_t bgColor, char *data);
  		 
#endif

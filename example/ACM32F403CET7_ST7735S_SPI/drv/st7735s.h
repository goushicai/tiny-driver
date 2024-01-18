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

typedef enum {
	LCD_STATUS_OK 			= 0x00U,		//ǰ4���̳� HAL_StatusTypeDef
	LCD_STATUS_ERROR    	= 0x01U,
	LCD_STATUS_BUSY 		= 0x02U,
	LCD_STATUS_TIMEOUT 		= 0x03U,
	
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

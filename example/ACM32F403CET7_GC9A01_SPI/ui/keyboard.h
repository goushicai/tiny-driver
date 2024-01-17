/**
 * �������
 *
 * ����:
 * 		��ʾ����
 * 		�رռ���
 * 		ѡ����һ����λ
 		ѡ����һ����λ
		ȷ�ϵ�ǰ��ֵ
		�˸�ɾ��
		�������

    ���̵�����������  kbInputText ��ʵʱ����,Ӧ�ó����ȡ����ֱ����ʾ���ü���
 * */


#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "uiDisplay.h"
#include "encoder.h"
#include "event.h" //�¼�
#include "progress.h" //����


/*****************����������� ********************/
#define KEYBOARD_COLOR 				0x0000 		//������ɫ
#define KEYBOARD_BG_COLOR 			0x3186 		//���̱���ɫ,���ڻ���ɫ
#define KEYBOARD_TEXT_COLOR 		0xFFDF 		//��λ��ɫ
#define KEYBOARD_ACTIVE_TEXT_COLOR 	0xF800 		//��λѡ����ɫ
#define KEYBOARD_BUTTON_MAX_LENGTH 	16 			//������ʾ�������
#define KEYBOARD_FONT_SIZE 			24			//�����ı�����
#define KEYBOARD_MAX_LENGTH		    16			//���������ַ�����
#define KEYBOARD_WIDTH 				40 			//���μ��̿��


/**
 * ����ѡ��
 *
 * ����֧��������ֵ�����ʾ��ascii��
*/
typedef struct
{
    KeyboardType kbType; //��������
    int16_t minVal;
    int16_t maxVal;
    uint8_t kbShowClose  : 1;  //��ʾ�رռ�
    uint8_t kbShowBack   : 1;  //��ʾ���ؼ�
    uint8_t kbShowOK     : 1;  //��ʾȷ����
    uint8_t kbShowDelete : 1;  //��ʾ�˸�ɾ����
    uint8_t kbShowClear  : 1;  //��ʾ��ռ�
    uint8_t kbShowCaps   : 1;  //��ʾ��С�л���,��������ĸ������Ч
    uint8_t kbShowMinus  : 1;  //��ʾ����
    uint8_t kbShowPoint  : 1;  //��ʾС����
} KeyboardOption;

//��λֵ
typedef struct
{
    uint8_t value; //�����ֵ
    char text; //��ʾ���ı�
} KeyboardButton;


void showKeyboard(KeyboardOption opt);

//��ȡ��ǰ����ļ�λ
KeyboardButton getKeyboardButton();

//�Ӳ˵��л�ȡ���̲���
KeyboardOption getKeyboardOption(Menu menu);

//ѡ����һ����λ
void keyboardNext();

//ѡ����һ����λ
void keyboardPrev();

//���뵱ǰ������ַ�
void keyboardAppend(char ch);

//ɾ�����һ��������ַ�
void keyboardDelete();

//���ȫ������
void keyboardClear();

//���ü�����������
void setKeyBoardContent(char *p);

//���ü������뷶Χ(����)
void setKeyboardOptionRange(int16_t minVal,int16_t maxVal);

//��ȡ������������
char * getKeyBoardContentString();

//��ȡ��������ֵ uint8
uint8_t getKeyBoardContentUInt8();

//��ȡ��������ֵ uint16
uint16_t getKeyBoardContentUInt16();

//��ȡ��������ֵ uint32
uint32_t getKeyBoardContentUInt32();

//��ȡ��������ֵ int8
int8_t getKeyBoardContentInt8();

//��ȡ��������ֵ int16
int16_t getKeyBoardContentInt16();

//��ȡ��������ֵ int32
int32_t getKeyBoardContentInt32();

//��ȡ�����¼�
enumKeyboardEvent getKeyboardEvent();


#endif  //__KEYBOARD_H__


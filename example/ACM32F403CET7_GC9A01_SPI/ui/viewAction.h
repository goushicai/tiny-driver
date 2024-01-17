/**
 * ����ҳ
 *
 * ����:
 *
 * 		��ʾ����ҳ(title, �����ı���,Ĭ��ֵ,��ʾ����)
		��ת,�޸���ʾ��ֵ(�޼���), �޸�ѡ�а�ť
		����,���뵱ǰѡ��ֵ
		˫��,�˳���ǰ��
		����,ȷ������

 * */

#ifndef __ACTION_VIEW_H__
#define __ACTION_VIEW_H__

#include <math.h> //�õ�sin,cos
#include <stdio.h> //�õ�sprinft
#include <string.h> //�õ�strlen
#include "keyboard.h" //����
#include "option.h" //ϵͳ����
#include "event.h"

/************** ����ҳ������� *********************/
#define ACTION_BG_COLOR				0x3186 	//����ҳĬ�ϱ���ɫ 0x2222
#define ACTION_TITLE_COLOR			0xFFDF 	//����ҳ������ɫ 0xFEFEFE
#define ACTION_TITLE_FONT_SIZE		32		//����ҳ��������
#define ACTION_TITLE_LEFT			56 		//����ҳ������ʾ����,������ʾ
#define ACTION_TITLE_TOP       		75
#define ACTION_TITLE_WIDTH 			128

#define ACTION_INPUT_COLOR 			0xFFDF
#define ACTION_INPUT_BG_COLOR 		0x3186
#define ACTION_INPUT_BORDER_COLOR 	0xFFDF
#define ACTION_INPUT_ERROR_COLOR 	0xF800
#define ACTION_INPUT_FONT_SIZE 		32
#define ACTION_INPUT_LEFT 			56
#define ACTION_INPUT_TOP 			120
#define ACTION_INPUT_WIDTH 			128
#define ACTION_INPUT_BORDER_WIDTH 	1
#define ACTION_INPUT_PADDING 		2

#define ACTION_ERROR_COLOR 			0xFFDF
#define ACTION_ERROR_BG_COLOR 		0xC985
#define ACTION_ERROR_BORDER_COLOR 	0xFFDF
#define ACTION_ERROR_FONT_SIZE 		24
#define ACTION_ERROR_LEFT 			40
#define ACTION_ERROR_TOP 			160
#define ACTION_ERROR_WIDTH 			160
#define ACTION_ERROR_BORDER_WIDTH 	0
#define ACTION_ERROR_PADDING 		0

//��ʾ����ҳ
void showActionView(Menu menu);

//��ʾ��������
void showActionText();

//���޼��̵����,��������ת,ֱ���޸���ֵ
void InputValueNext();

void InputValuePrev();

void InputCurrentValue();

//�����޸�
void saveAction();

enumViewEvent getActionViewEvent();
#endif  //__ACTION_VIEW_H__

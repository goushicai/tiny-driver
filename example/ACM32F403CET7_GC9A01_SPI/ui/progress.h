/**
 * ������
 *
 * ���ν�����
 *
 *  ������Χ��һ��Ȧ, ���ȴﵽ100% ��ʱ200ms���Զ��ر�

 * ������ʾ:
 *    showSuccess();
 *    showFail();
 *    ֱ����ʾ 100%����,��ɫ 100ms ��˸2 �� ���� �����ɹ�
 *    ֱ����ʾ 100%����,��ɫ 100ms ��˸2 �� ���� ����ʧ��
 *
 * */


#ifndef __PROGRESS_H__
#define __PROGRESS_H__

#include "uiDisplay.h"

/************** ������������� *********************/
//���ν��������
#define PROGRESS_LINE_WIDTH 3
#define FEEDBACK_TWKINLE_DURATION 200


//��ʾ��ǰ����
void showProgress(uint8_t percent); //��������ֵС�ڵ�ǰֵ,��Ϊ���ȵ���

//�رս�����
/***
 *  delay : ��ʱ�ر�, ms
 *  style : 0 ��, 1 ��˸
 * */
void closeProgress(uint8_t delay, uint8_t style);

void showTwkinle(uint16_t color,uint16_t bgColor );
void successTwkinle(uint16_t bgColor);

void failTwkinle(uint16_t bgColor);

void showProgressWater(uint8_t percent, uint16_t color,uint16_t bgColor);

#endif  //__PROGRESS_H__
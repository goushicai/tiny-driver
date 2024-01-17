/**
 * �˵�ҳ
 *
 * ����:
 *    ����˵�����
 * 		��ʾ�˵�
 * 		ѡ��ָ���˵�
 * 		ѡ����һ���˵�
 		ѡ����һ���˵�
		ȷ�ϵ�ǰ�˵�
		�����ϼ��˵�
 * */


#ifndef __MENU_IMG_VIEW_H__
#define __MENU_IMG_VIEW_H__

#include "viewMenu.h"
#include "event.h"
#include "encoder.h"
#include "jpgDecoder.h"
#include "jpg.h"

/****************** �˵�ҳ������� ************/

#define MENU_IMG_BG_COLOR           	0xFFDF  // �˵�ҳ�汳��ɫ
#define MENU_IMG_SIZE          			48		//�˵�ͼ���С
#define MENU_IMG_ACTIVE_SIZE      		64		//�˵�ͼ���С
#define MENU_IMG_LEFT      				45		//�˵�ͼ�������
#define MENU_IMG_ACTIVE_TOP      		88		//�˵�ͼ��������
#define MENU_IMG_MARGIN      			10		//�˵�ͼ����

#define MENU_IMG_TITLE_FONT_SIZE   		24 		//�˵����������С
#define MENU_IMG_TITLE_ACTIVE_FONT_SIZE 32 		//�˵����������С
#define MENU_IMG_TITLE_LEFT       		110 	//�˵�������ʾ����
#define MENU_IMG_TITLE_TOP       		104 	//�˵�������ʾ����
#define MENU_IMG_TITLE_COLOR  			0x3186	//�˵�ҳ����������ɫ
#define MENU_IMG_TITLE_DISABLE_COLOR  	0xAD55	


void showImgMenuView(uint8_t parentId);

//���õ�ǰ��Ծ�˵�
void setActiveImgMenu(uint8_t idx); //ͬһ���˵�,ָ�����

//��һ���˵�
void imgMenuNext(); //��һ���˵� ,���β˵�,��˳ʱ�뷽��Ϊ��ת
//��һ���˵�
void imgMenuPrev(); //��һ���˵�

enumViewEvent getImgMenuViewEvent();

#endif  //__MENU_IMG_VIEW_H__

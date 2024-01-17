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


#ifndef __MENU_VIEW_H__
#define __MENU_VIEW_H__

#include <math.h>
#include "uiDisplay.h"
#include "encoder.h"
#include "progress.h"
#include "event.h"
#include "uiPassword.h"
#include "eflash.h"
/****************** �˵�ҳ������� ************/
#define MENU_MAX_COUNT          		32 		//�˵�����,һҳ512B,ÿ��16B,��32��
#define MENU_BG_COLOR           		0x3186 // �˵�ҳ�汳��ɫ
#define MENU_RING_WIDTH           		48 		//���β˵����
#define MENU_ITEM_BG_COLOR           	0x0000 	//�˵���δ�����ɫ
#define MENU_ITEM_ACTIVE_BG_COLOR    	0x52aa 	//�˵����ʱ����ɫ
#define MENU_ITEM_ICON_SIZE          	32		//�˵�Ĭ��ͼ������
#define MENU_ITEM_ICON_COLOR         	0xFFDF 	//�˵���ͼ��Ĭ����ɫ
#define MENU_ITEM_ACTIVE_ICON_COLOR  	0x07E0 	//�˵����ͼ����ɫ

#define MENU_TITLE_LEFT       			56 		//�˵�������ʾ����
#define MENU_TITLE_TOP       			100 	//�˵�������ʾ����
#define MENU_TITLE_WIDTH       			128
#define MENU_TITLE_HEIGHT       		32
#define MENU_TITLE_COLOR  				0xFFDF 	////�˵�ҳ����������ɫ
#define MENU_TITLE_FONT_SIZE   			32 		//�˵����������С

//
/**
 * �� eflash NVR page 1��ȡ����,����֯�� Menu����;
 *
 *  ��������0 ,������ֵΪ����
 * */
bool loadMenu();

uint8_t getMenuInitFlag();

void setMenuInitFlag();

void resetMenuData();

//���²˵�
uint8_t writeMenu(uint8_t index, Menu val);

//��ȡ��ǰ�㼶�����в˵�
uint8_t getMenuList(uint8_t pId);

//��Բ����Ļ����ʾ���β˵�
void showMenuView(Menu menu);

//��ʾָ���˵��µ��Ӳ˵�
void showSubMenu(uint8_t pMenuId);

//��ȡ��ǰ��Ծ�˵���fsm����Ӧ�������¼�ʱʹ��
Menu getActiveMenu();

//���õ�ǰ��Ծ�˵�
void setActiveMenu(uint8_t idx); //ͬһ���˵�,ָ�����

//��һ���˵�
void menuNext(); //��һ���˵� ,���β˵�,��˳ʱ�뷽��Ϊ��ת
//��һ���˵�
void menuPrev(); //��һ���˵�

//����menuId��ȡ�˵���
Menu getMenuById(uint8_t mId);

//���������֤�ɹ���ʶ
void clearPasswordAuthFlag();

enumViewEvent getMenuViewEvent();

#endif  //__MENU_VIEW_H__

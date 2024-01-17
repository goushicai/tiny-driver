/**
 * ����ҳ
 *
 * */
#ifndef __UI_PASSWORD_H__
#define __UI_PASSWORD_H__

#include "keyboard.h"

#define PASSWORD_BG_COLOR				0x3186 	//����ҳĬ�ϱ���ɫ 0x2222
#define PASSWORD_TITLE_COLOR			0xFFDF 	//����ҳ������ɫ 0xFEFEFE
#define PASSWORD_TITLE_FONT_SIZE		32		//����ҳ��������
#define PASSWORD_TITLE_LEFT				56 		//����ҳ������ʾ����,������ʾ
#define PASSWORD_TITLE_TOP       		80
#define PASSWORD_TITLE_WIDTH 			128

#define PASSWORD_INPUT_COLOR 			0xFFDF
#define PASSWORD_INPUT_BG_COLOR 		0x3186
#define PASSWORD_INPUT_BORDER_COLOR 	0xFFDF
#define PASSWORD_INPUT_ERROR_COLOR 		0xF800
#define PASSWORD_INPUT_FONT_SIZE 		24
#define PASSWORD_INPUT_LEFT 			56
#define PASSWORD_INPUT_TOP 				120
#define PASSWORD_INPUT_WIDTH 			120
#define PASSWORD_INPUT_BORDER_WIDTH 	1
#define PASSWORD_INPUT_PADDING 			1

#define PASSWORD_MAX_LENGTH 			10 //������󳤶�
#define PASSWORD_VERIFIED_TIME 			120 //���������,������Чʱ��,������ʱ��Ҫ������������,��λ��,0����һֱ��Ч

//����ҳ���������,������֤,�޸�����
typedef enum
{
    PASSWORD_AUTH, //������֤
    PASSWORD_UPDATE_USER, //�޸��û�����
	PASSWORD_UPDATE_ADMIN, //�޸Ĺ���Ա����
	PASSWORD_UPDATE_SUPER, //�޸ĳ�������
} enumPasswordViewType;


//type = 0 �������,type=1,�޸�����
void showPasswordView(uint8_t type); 

//��ȡ������֤ͨ����ʶ
uint8_t getPasswordAuthFlag();
//���������֤ͨ����ʶ
void clearPasswordAuthFlag();

enumViewEvent getPasswordViewEvent();


#endif  //__UI_PASSWORD_H__
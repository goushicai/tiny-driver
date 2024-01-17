/**
 * �������¼�

 *
 * */

#ifndef __EVENT_H__
#define __EVENT_H__


//״̬ö��
typedef enum
{
    FSM_STARTING = 0x00, //����ҳ��
    FSM_VIEW_ERROR, //����ҳ��
    FSM_VIEW_MENU, //�˵�ҳ��
    FSM_VIEW_ACTION,//����ҳ��
    FSM_VIEW_TEXT,//���ı�ҳ��
    FSM_VIEW_PIC, //��ͼƬҳ��
	FSM_VIEW_CHART, //ͼ��ҳ��
	FSM_VIEW_CHANNEL, //��ѯҳ��
    FSM_VIEW_IDEL //����ҳ��
} FSM_STATE;

/***

#define     EVENT_NONE_KEY       0
#define     EVENT_KEY_CLICK          1
#define     EVENT_KEY_DOUBLE_CLICK    2
#define     EVENT_KEY_PRESS          3
#define     EVENT_KEY_RELEASE        4   // >1.2S

*/

//�������¼�
typedef enum
{
    ENCODER_EVENT_NONE = 0x00,
    ENCODER_EVENT_CLICK,
    ENCODER_EVENT_DOUBLE_CLICK,
    ENCODER_EVENT_PRESS,
    ENCODER_EVENT_RELEASE,
    ENCODER_EVENT_VALUE_UP, //ֵ���ϱ仯
    ENCODER_EVENT_VALUE_DOWN,//ֵ���±仯
    ENCODER_EVENT_REVERSE, //����������
    ENCODER_EVENT_ERROR
} enumEncoderEvent;

//�����¼�
typedef enum
{
    KEYBOARD_EVENT_NONE=0x00,
    KEYBOARD_EVENT_ERROR,
    KEYBOARD_EVENT_CHANGE,
    KEYBOARD_EVENT_OK,
    KEYBOARD_EVENT_BACK,
    KEYBOARD_EVENT_CLOSE,
    KEYBOARD_EVENT_CAPS
} enumKeyboardEvent;

typedef enum
{
    VIEW_EVENT_NONE = 0,
	VIEW_EVENT_BACK, //�����ϲ˵�
	VIEW_TABINDEX, //��һ��ѡ����
	VIEW_EVENT_ERROR, //����
	
    MENU_EVENT_ACTIVE_CHANGE, //����˵��ı�
    MENU_EVENT_FIND_MENU, 	//�¼��˵����ǲ˵�
    MENU_EVENT_FIND_ACTION, //�¼��˵��ǲ���ҳ
    MENU_EVENT_FIND_TEXT, 	//�����ı�ҳ
	MENU_EVENT_FIND_PIC, 	//����ͼƬҳ
    MENU_EVENT_FIND_CHART, 	//����ͼ��ҳ
	MENU_EVENT_FIND_CHANNEL, //����ͨ����ѯ
	
    ACTION_EVENT_OK, //ȷ�ϵ�ǰֵ
	
	CHART_EVENT_CLEAR,		// ���ͼ��
	
    TEXT_EVENT_SCROLL_UP, //���Ϲ���һ��
    TEXT_EVENT_SCROLL_DOWN, //���¹���һ��
	TEXT_EVENT_CHANGE_FONT, //�ı�����
	
	PASSWORD_EVENT_PASS,		// ������֤ͨ��
	PASSWORD_EVENT_INVALID,		// ������֤ʧ��
	PASSWORD_EVENT_UPDATEED,	// �����޸ĳɹ�
	PASSWORD_EVENT_ERROR,		// �����������
	
	CHANNEL_EVENT_CHANGE,		// ͨ�����
	CHANNEL_EVENT_SHOW_CHART,	// �鿴ͨ��ͼ��
} enumViewEvent;

#endif  //__EVENT_H__
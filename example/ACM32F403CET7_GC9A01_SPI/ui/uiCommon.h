#ifndef __UI_COMMON_H__
#define __UI_COMMON_H__

#include <stdint.h>

#ifndef PI
	#define PI               3.14159265358979f
#endif


#define SCREEN_WIDTH    240 //��ʾ�����
#define SCREEN_HEIGHT   240 

#define SCREEN_CENTER_X 120 //��ʾ��Բ��
#define SCREEN_CENTER_Y 120

#define OUTER_RADIUS    120 //Բ����ʾ���⻷�뾶
#define INNER_RADIUS    75 //Բ����ʾ���ڻ��뾶

/**
	��ɫ:
	primary: 0x337ab7(33d6) 	active 0x286090 (2b12)
	success: 0x5cb85c(5dcb) 	active 0x449d44 (44e8)
	warning: 0xf0ad4e(f569) 	active 0xec971f (eca3)
	danger : 0xd9534f(da89) 	active 0xc9302c (c985)
	black  : 0x555555(52aa) 	active 0x333333 (3186)
*/

#define DEFAULT_COLOR			0x52aa 	
#define DEFAULT_ACTIVE_COLOR	0x3186

#define PRIMARY_COLOR			0x33d6 	
#define PRIMARY_ACTIVE_COLOR	0x2b12

#define SUCCESS_COLOR 			0x5dcb
#define SUCCESS_ACTIVE_COLOR 	0x44e8 

#define WARNING_COLOR 			0xf569
#define WARNING_ACTIVE_COLOR 	0xeca3 

#define DANGER_COLOR 			0xda89
#define DANGER_ACTIVE_COLOR 	0xc985 

#define WHITE               	0xFFFF
#define BLACK              	 	0x0000
#define RED                	 	0xF800
#define BLUE                	0x001F
#define GREEN               	0x07E0

//�����С
typedef enum
{
    FONT_SIZE_16 = 16,
    FONT_SIZE_24 = 24,
    FONT_SIZE_32 = 32,
    FONT_SIZE_48 = 48
} enumFontSize;

//�ı����뷽ʽ:����,����,����
typedef enum
{
	ALIGN_LEFT=1,
    ALIGN_CENTER=2,
    ALIGN_RIGHT=3,
} enumTextAlign;

//��
typedef struct{
	uint16_t x;
	uint16_t y;
} uiPoint ;

//��
typedef struct{
	uiPoint pointFrom;
	uiPoint pointTo;
	uint16_t color;
	uint16_t lineWidth;
} uiLine ;

//Բ��
typedef struct{
	uint16_t ox;
	uint16_t oy;
	uint16_t radius;
	uint16_t color;
	uint16_t bgColor;
	uint16_t lineWidth;
} uiRing ;

//Բ��
typedef struct{
	uiPoint center; //Բ��
	uint16_t radius; //�뾶
	uint16_t color; //
	double arcFrom;
	double arcTo;
	uint16_t lineWidth;
} uiArc;

/**
	�ı�����
	�ı���ʾ��ʵ��λ��,����뷽ʽ���ı���������:
		��p.xΪָ���ĺ�����,wΪ�ı���Ŀ��,lΪ�ı��Ŀ��

		����ʱ,p.xΪ�ı�����������,��p���λ��������ʾ�ı�,
		����ʱ,p.x+wΪ�ı����յ������,(p.x + w - l)Ϊ����������ʾ�ı�,
		����ʱ,p.x+w/2Ϊ�ı����е�����,��(p.x +(w - l)/2)Ϊ���������ʾ�ı�,
*/
typedef struct{
	uint8_t align	; //���뷽ʽ,0����(Ĭ��),1����,2����
	uint8_t fontType; //todo ֧�ֶ�������
	uint8_t fontSize; // 16,24,32,48
	
	uint16_t color;
	uint16_t bgColor;
	uint16_t borderColor;
	
	uint16_t left;
	uint16_t top;
	uint16_t width; //�ı���Ŀ��
	uint16_t height; //�ı���ĸ߶�
	
	uint8_t borderWidth;
	uint8_t padding;
	
	uint16_t duration; //һ�����ַ���ʾ, һ���ַ���ʾ����ʱ����ʾ��һ���ַ�,��ʵ�ּ򵥵��˻�Ч��,��λms
	
	uint8_t overflow; //todo��������, 00�ض�,01�Զ�����,10�Զ��쳤,11��ʾ�����ʶ"..."
	uint8_t dataType; //todo��ʾ����, 00�ַ���,01��ֵ,
	
	char * text;
} uiText;


//��������
typedef enum
{
    DATATYPE_UINT8 		= 0u,
    DATATYPE_UINT16 	= 1u,
    DATATYPE_UINT32		= 2u,
    DATATYPE_INT8	 	= 3u,
    DATATYPE_INT16 		= 4u,
    DATATYPE_INT32 		= 5u,
    DATATYPE_FLOAT 		= 6u,
    DATATYPE_STRING 	= 7u
} DateType;


/**
 * ��������
 * */
typedef enum
{
    KEYBOARD_NONE 		= 0u,
    KEYBOARD_BOOL 		= 1u,
    KEYBOARD_SELECT 	= 2u, //��ѡ
    KEYBOARD_PASSWORD	= 3u,
    KEYBOARD_NUMBER 	= 4u,
    KEYBOARD_FLOAT      = 5u,
    KEYBOARD_LETTER		= 8u,
    KEYBOARD_FULL		= 15u
} KeyboardType;

/**
 *
 * �Զ�����Ƽ�����:
 * 	NULL 	0xFF
 *
 *  BACK 	0xF0
 *  CLOSE 	0xF1
 * 	OK 		0xF2
 *  DELETE 	0xF3
 *  CLEAR 	0xF4
 *	CAPS 	0xF5
 *  MINUS 	0x2D
 *  POINT 	0x2E
 * */

typedef enum
{
    BUTTON_BACK = 0xF0,
    BUTTON_CLOSE,
    BUTTON_OK,
    BUTTON_DELETE,
    BUTTON_CLEAR,
    BUTTON_CAPS,
    BUTTON_MINUS,
    BUTTON_POINT
} CtrlButtonType;



typedef enum
{
    MENU_TYPE_MENU=0,
    MENU_TYPE_ACTION=1,
    MENU_TYPE_TEXT=2,
	MENU_TYPE_PIC=3,
    MENU_TYPE_CHART=4,
	MENU_TYPE_CHANNEL=5
} enumMenuType;

typedef struct
{
    uint8_t id;
    uint8_t parentId;
    uint8_t txtId;
    uint8_t iconId;

    //�˵�/����
    uint8_t menuType   		: 4; // ���ͣ�0000 �˵� menu 0001 ���� action�� 0010 �ı��� 0011 ͼƬ, 0100 ͼ��, 0101 ״̬��ѯ
    uint8_t needPassword   	: 1;  // ���뱣�� 0 ��,1�� ����������û�����,����Ա�����볬�������е��κ�һ��
    uint8_t menuReserved  	: 3; //����

    //����ѡ��1 ,ֻ�е� menuType = 1 ����Ч
    uint8_t actReadonly  	: 1;  // ������,ֻ�� 0 ��,1 ��
    uint8_t actConfirm   	: 1;  // �޸ĺ���Ҫȷ��
    uint8_t actSource    	: 3;  // ������Դ,000 ��������,001-111 ��λ��վ�ţ��ɿ���7̨��λ�������offsetAddrʹ��
    uint8_t actDataType  	: 3;  // ��ֵ���� 000:u8 001:u16 010:u32 011:int8 100:int16,101:int32,110:float,111:string

    //����ѡ��2
    uint8_t actDataLength	: 4 ;// �ı���ʾ���� 1-16,��ǰֵ+1;
    uint8_t actReserved		: 4 ;// ����

    //����ѡ��1
    uint8_t kbType 			: 4 ;   // �������� 0000�޼��� 0001���� 0010��ѡ 0011���� 0100:���� ,0101 ��С��ĸ, 1111: ȫ����,����ֵ��Ч,Ĭ��000
    uint8_t kbShowBack   	: 1;  //��ʾ���ؼ�
    uint8_t kbShowOK     	: 1;  //��ʾȷ����
    uint8_t kbShowDelete 	: 1;  //��ʾ�˸�ɾ����
    uint8_t kbShowClear  	: 1;  //��ʾ��ռ�

    //����ѡ��
    uint8_t progress 		: 2 ; //�Ƿ���ʾ������(�ٷֱ�),��minVal,maxVal���ʹ�� ,00 �� 01���ν�����, 10 ˮλ������
    uint8_t feedback		: 2 ; // 00��, 01������, 10�ⷴ��,11���ⷴ��
    uint8_t othOp3			: 4 ; //���� ,�ı�����ʾ,���п�����, �ı����ȵ�

    uint8_t txtOrPicId; //menuType:���ı�����ͼƬ����¼��Ӧ��id

    int16_t minVal; //��Сֵ
    int16_t maxVal; //���ֵ
    uint16_t  address; // actSource==00,��ַΪeflash��ָ��������ҳ
    // actSource==01,��Ϊ��λ��modbus��ַ��Ӧ������, 11 ����ֻ�޸ĵ�ǰ�ڴ��е�����
}  Menu ;


typedef struct
{
    uint8_t menuId;
    char defalutValue[16];
    DateType dataType;
    uint8_t dataLength;
    uint8_t source;
    uint16_t address;
    uint8_t progress;
    uint8_t feedback;
    uint8_t txtId;
	uint8_t readonly;
	uint8_t confirm;
} ActionOption;



typedef struct
{
    uint8_t type       : 2; //00����,01ˮλ , ��������
    uint8_t rotation   : 1; //����: 0��ʱ��,1˳ʱ��
    uint8_t water      : 1; //ˮλ: 0 ���µ���, 1���ϵ���
    uint8_t style      : 2; //��ɺ���,00�޶���,01ֱ�ӹر�, 10 ��ʱ200ms 11 ��˸200ms�ر�;
    uint8_t noTitle    : 1; //���ؽ��ȶȱ���
    uint8_t noPercent  : 1; //���ؽ���
    uint8_t lineWidth ;
    uint16_t color;
} ProgressOption;

#endif  //__UI_COMMON_H__

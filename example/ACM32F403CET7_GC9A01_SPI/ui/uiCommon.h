#ifndef __UI_COMMON_H__
#define __UI_COMMON_H__

#include <stdint.h>

#ifndef PI
	#define PI               3.14159265358979f
#endif


#define SCREEN_WIDTH    240 //显示屏宽高
#define SCREEN_HEIGHT   240 

#define SCREEN_CENTER_X 120 //显示屏圆心
#define SCREEN_CENTER_Y 120

#define OUTER_RADIUS    120 //圆形显示屏外环半径
#define INNER_RADIUS    75 //圆形显示屏内环半径

/**
	颜色:
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

//字体大小
typedef enum
{
    FONT_SIZE_16 = 16,
    FONT_SIZE_24 = 24,
    FONT_SIZE_32 = 32,
    FONT_SIZE_48 = 48
} enumFontSize;

//文本对齐方式:靠左,居中,靠右
typedef enum
{
	ALIGN_LEFT=1,
    ALIGN_CENTER=2,
    ALIGN_RIGHT=3,
} enumTextAlign;

//点
typedef struct{
	uint16_t x;
	uint16_t y;
} uiPoint ;

//线
typedef struct{
	uiPoint pointFrom;
	uiPoint pointTo;
	uint16_t color;
	uint16_t lineWidth;
} uiLine ;

//圆环
typedef struct{
	uint16_t ox;
	uint16_t oy;
	uint16_t radius;
	uint16_t color;
	uint16_t bgColor;
	uint16_t lineWidth;
} uiRing ;

//圆弧
typedef struct{
	uiPoint center; //圆心
	uint16_t radius; //半径
	uint16_t color; //
	double arcFrom;
	double arcTo;
	uint16_t lineWidth;
} uiArc;

/**
	文本属性
	文本显示的实际位置,与对齐方式和文本框宽度有样:
		若p.x为指定的横坐标,w为文本框的宽度,l为文本的宽度

		靠左时,p.x为文本的起点横坐标,以p点的位置向左显示文本,
		靠右时,p.x+w为文本的终点横坐标,(p.x + w - l)为起点的向右显示文本,
		居中时,p.x+w/2为文本的中点坐标,以(p.x +(w - l)/2)为起点向右显示文本,
*/
typedef struct{
	uint8_t align	; //对齐方式,0靠左(默认),1居中,2靠右
	uint8_t fontType; //todo 支持多种字体
	uint8_t fontSize; // 16,24,32,48
	
	uint16_t color;
	uint16_t bgColor;
	uint16_t borderColor;
	
	uint16_t left;
	uint16_t top;
	uint16_t width; //文本框的宽度
	uint16_t height; //文本框的高度
	
	uint8_t borderWidth;
	uint8_t padding;
	
	uint16_t duration; //一个个字符显示, 一个字符显示后延时再显示另一个字符,以实现简单的运画效果,单位ms
	
	uint8_t overflow; //todo超长处理, 00截断,01自动换行,10自动伸长,11显示溢出标识"..."
	uint8_t dataType; //todo显示类型, 00字符串,01数值,
	
	char * text;
} uiText;


//数据类型
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
 * 键盘类型
 * */
typedef enum
{
    KEYBOARD_NONE 		= 0u,
    KEYBOARD_BOOL 		= 1u,
    KEYBOARD_SELECT 	= 2u, //单选
    KEYBOARD_PASSWORD	= 3u,
    KEYBOARD_NUMBER 	= 4u,
    KEYBOARD_FLOAT      = 5u,
    KEYBOARD_LETTER		= 8u,
    KEYBOARD_FULL		= 15u
} KeyboardType;

/**
 *
 * 自定义控制键的码:
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

    //菜单/操作
    uint8_t menuType   		: 4; // 类型，0000 菜单 menu 0001 操作 action， 0010 文本， 0011 图片, 0100 图表, 0101 状态轮询
    uint8_t needPassword   	: 1;  // 密码保护 0 否,1是 密码可以是用户密码,管理员密码与超级密码中的任何一个
    uint8_t menuReserved  	: 3; //保留

    //操作选项1 ,只有当 menuType = 1 是有效
    uint8_t actReadonly  	: 1;  // 操作项,只读 0 否,1 是
    uint8_t actConfirm   	: 1;  // 修改后需要确认
    uint8_t actSource    	: 3;  // 参数来源,000 本机参数,001-111 上位机站号，可控制7台上位机，配合offsetAddr使用
    uint8_t actDataType  	: 3;  // 数值类型 000:u8 001:u16 010:u32 011:int8 100:int16,101:int32,110:float,111:string

    //操作选项2
    uint8_t actDataLength	: 4 ;// 文本显示长度 1-16,当前值+1;
    uint8_t actReserved		: 4 ;// 保留

    //键盘选项1
    uint8_t kbType 			: 4 ;   // 键盘类型 0000无键盘 0001布尔 0010单选 0011密码 0100:数字 ,0101 大小字母, 1111: 全键盘,其它值无效,默认000
    uint8_t kbShowBack   	: 1;  //显示返回键
    uint8_t kbShowOK     	: 1;  //显示确定键
    uint8_t kbShowDelete 	: 1;  //显示退格删除键
    uint8_t kbShowClear  	: 1;  //显示清空键

    //其它选项
    uint8_t progress 		: 2 ; //是否显示进度条(百分比),与minVal,maxVal配合使用 ,00 无 01环形进度条, 10 水位进度条
    uint8_t feedback		: 2 ; // 00无, 01声反馈, 10光反馈,11声光反馈
    uint8_t othOp3			: 4 ; //保留 ,文本框显示,居中靠左靠右, 文本框宽度等

    uint8_t txtOrPicId; //menuType:是文本或者图片，记录对应的id

    int16_t minVal; //最小值
    int16_t maxVal; //最大值
    uint16_t  address; // actSource==00,地址为eflash中指定的数据页
    // actSource==01,则为上位机modbus地址对应的数据, 11 代表只修改当前内存中的数据
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
    uint8_t type       : 2; //00环形,01水位 , 其它保留
    uint8_t rotation   : 1; //环形: 0逆时针,1顺时针
    uint8_t water      : 1; //水位: 0 从下到上, 1从上到下
    uint8_t style      : 2; //完成后动作,00无动作,01直接关闭, 10 延时200ms 11 闪烁200ms关闭;
    uint8_t noTitle    : 1; //隐藏进度度标题
    uint8_t noPercent  : 1; //隐藏进度
    uint8_t lineWidth ;
    uint16_t color;
} ProgressOption;

#endif  //__UI_COMMON_H__

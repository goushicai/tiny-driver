/**
 * 编码器事件

 *
 * */

#ifndef __EVENT_H__
#define __EVENT_H__


//状态枚举
typedef enum
{
    FSM_STARTING = 0x00, //启动页面
    FSM_VIEW_ERROR, //报错页面
    FSM_VIEW_MENU, //菜单页面
    FSM_VIEW_ACTION,//操作页面
    FSM_VIEW_TEXT,//纯文本页面
    FSM_VIEW_PIC, //纯图片页面
	FSM_VIEW_CHART, //图表页面
	FSM_VIEW_CHANNEL, //轮询页面
    FSM_VIEW_IDEL //空闲页面
} FSM_STATE;

/***

#define     EVENT_NONE_KEY       0
#define     EVENT_KEY_CLICK          1
#define     EVENT_KEY_DOUBLE_CLICK    2
#define     EVENT_KEY_PRESS          3
#define     EVENT_KEY_RELEASE        4   // >1.2S

*/

//编码器事件
typedef enum
{
    ENCODER_EVENT_NONE = 0x00,
    ENCODER_EVENT_CLICK,
    ENCODER_EVENT_DOUBLE_CLICK,
    ENCODER_EVENT_PRESS,
    ENCODER_EVENT_RELEASE,
    ENCODER_EVENT_VALUE_UP, //值向上变化
    ENCODER_EVENT_VALUE_DOWN,//值向下变化
    ENCODER_EVENT_REVERSE, //编码器反向
    ENCODER_EVENT_ERROR
} enumEncoderEvent;

//键盘事件
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
	VIEW_EVENT_BACK, //返回上菜单
	VIEW_TABINDEX, //下一个选中项
	VIEW_EVENT_ERROR, //错误
	
    MENU_EVENT_ACTIVE_CHANGE, //激活菜单改变
    MENU_EVENT_FIND_MENU, 	//下级菜单仍是菜单
    MENU_EVENT_FIND_ACTION, //下级菜单是操作页
    MENU_EVENT_FIND_TEXT, 	//发现文本页
	MENU_EVENT_FIND_PIC, 	//发现图片页
    MENU_EVENT_FIND_CHART, 	//发现图表页
	MENU_EVENT_FIND_CHANNEL, //发现通道轮询
	
    ACTION_EVENT_OK, //确认当前值
	
	CHART_EVENT_CLEAR,		// 清除图表
	
    TEXT_EVENT_SCROLL_UP, //向上滚动一行
    TEXT_EVENT_SCROLL_DOWN, //向下滚动一行
	TEXT_EVENT_CHANGE_FONT, //改变字体
	
	PASSWORD_EVENT_PASS,		// 密码验证通过
	PASSWORD_EVENT_INVALID,		// 密码验证失败
	PASSWORD_EVENT_UPDATEED,	// 密码修改成功
	PASSWORD_EVENT_ERROR,		// 密码操作错误
	
	CHANNEL_EVENT_CHANGE,		// 通道变更
	CHANNEL_EVENT_SHOW_CHART,	// 查看通道图表
} enumViewEvent;

#endif  //__EVENT_H__
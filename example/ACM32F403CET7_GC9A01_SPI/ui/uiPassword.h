/**
 * 密码页
 *
 * */
#ifndef __UI_PASSWORD_H__
#define __UI_PASSWORD_H__

#include "keyboard.h"

#define PASSWORD_BG_COLOR				0x3186 	//操作页默认背景色 0x2222
#define PASSWORD_TITLE_COLOR			0xFFDF 	//操作页标题颜色 0xFEFEFE
#define PASSWORD_TITLE_FONT_SIZE		32		//操作页标题字体
#define PASSWORD_TITLE_LEFT				56 		//操作页标题显示坐标,居中显示
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

#define PASSWORD_MAX_LENGTH 			10 //密码最大长度
#define PASSWORD_VERIFIED_TIME 			120 //输入密码后,持续有效时间,超过此时间要重新输入密码,单位秒,0代表一直有效

//密码页面操作类型,密码验证,修改密码
typedef enum
{
    PASSWORD_AUTH, //密码验证
    PASSWORD_UPDATE_USER, //修改用户密码
	PASSWORD_UPDATE_ADMIN, //修改管理员密码
	PASSWORD_UPDATE_SUPER, //修改超级密码
} enumPasswordViewType;


//type = 0 检测密码,type=1,修改密码
void showPasswordView(uint8_t type); 

//获取密码验证通过标识
uint8_t getPasswordAuthFlag();
//清除密码验证通过标识
void clearPasswordAuthFlag();

enumViewEvent getPasswordViewEvent();


#endif  //__UI_PASSWORD_H__
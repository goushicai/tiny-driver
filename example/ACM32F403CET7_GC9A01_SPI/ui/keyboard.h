/**
 * 键盘相关
 *
 * 函数:
 * 		显示键盘
 * 		关闭键盘
 * 		选中下一个键位
 		选中上一个键位
		确认当前键值
		退格删除
		清空输入

    键盘的输入内容在  kbInputText 中实时更新,应用程序读取或者直接显示引用即可
 * */


#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "uiDisplay.h"
#include "encoder.h"
#include "event.h" //事件
#include "progress.h" //反馈


/*****************键盘相关配置 ********************/
#define KEYBOARD_COLOR 				0x0000 		//键盘颜色
#define KEYBOARD_BG_COLOR 			0x3186 		//键盘背景色,即内环颜色
#define KEYBOARD_TEXT_COLOR 		0xFFDF 		//键位颜色
#define KEYBOARD_ACTIVE_TEXT_COLOR 	0xF800 		//键位选中颜色
#define KEYBOARD_BUTTON_MAX_LENGTH 	16 			//键盘显示最大数量
#define KEYBOARD_FONT_SIZE 			24			//键盘文本字体
#define KEYBOARD_MAX_LENGTH		    16			//键盘输入字符数量
#define KEYBOARD_WIDTH 				40 			//环形键盘宽度


/**
 * 键盘选项
 *
 * 键盘支持输入数值与可显示的ascii码
*/
typedef struct
{
    KeyboardType kbType; //键盘类型
    int16_t minVal;
    int16_t maxVal;
    uint8_t kbShowClose  : 1;  //显示关闭键
    uint8_t kbShowBack   : 1;  //显示返回键
    uint8_t kbShowOK     : 1;  //显示确定键
    uint8_t kbShowDelete : 1;  //显示退格删除键
    uint8_t kbShowClear  : 1;  //显示清空键
    uint8_t kbShowCaps   : 1;  //显示大小切换键,仅对字字母键盘有效
    uint8_t kbShowMinus  : 1;  //显示负号
    uint8_t kbShowPoint  : 1;  //显示小数点
} KeyboardOption;

//键位值
typedef struct
{
    uint8_t value; //输出的值
    char text; //显示的文本
} KeyboardButton;


void showKeyboard(KeyboardOption opt);

//读取当前激活的键位
KeyboardButton getKeyboardButton();

//从菜单中获取键盘参数
KeyboardOption getKeyboardOption(Menu menu);

//选中下一个键位
void keyboardNext();

//选中上一个键位
void keyboardPrev();

//输入当前激活的字符
void keyboardAppend(char ch);

//删除最后一个输入的字符
void keyboardDelete();

//清除全部输入
void keyboardClear();

//设置键盘输入内容
void setKeyBoardContent(char *p);

//设置键盘输入范围(包含)
void setKeyboardOptionRange(int16_t minVal,int16_t maxVal);

//读取键盘输入内容
char * getKeyBoardContentString();

//读取键盘输入值 uint8
uint8_t getKeyBoardContentUInt8();

//读取键盘输入值 uint16
uint16_t getKeyBoardContentUInt16();

//读取键盘输入值 uint32
uint32_t getKeyBoardContentUInt32();

//读取键盘输入值 int8
int8_t getKeyBoardContentInt8();

//读取键盘输入值 int16
int16_t getKeyBoardContentInt16();

//读取键盘输入值 int32
int32_t getKeyBoardContentInt32();

//获取键盘事件
enumKeyboardEvent getKeyboardEvent();


#endif  //__KEYBOARD_H__


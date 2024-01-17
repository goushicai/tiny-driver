/**
 * 菜单页
 *
 * 函数:
 *    载入菜单数据
 * 		显示菜单
 * 		选中指定菜单
 * 		选中下一个菜单
 		选中上一个菜单
		确认当前菜单
		返回上级菜单
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
/****************** 菜单页相关配置 ************/
#define MENU_MAX_COUNT          		32 		//菜单数量,一页512B,每项16B,共32个
#define MENU_BG_COLOR           		0x3186 // 菜单页面背景色
#define MENU_RING_WIDTH           		48 		//环形菜单宽度
#define MENU_ITEM_BG_COLOR           	0x0000 	//菜单项未激活背景色
#define MENU_ITEM_ACTIVE_BG_COLOR    	0x52aa 	//菜单项激活时背景色
#define MENU_ITEM_ICON_SIZE          	32		//菜单默认图标字体
#define MENU_ITEM_ICON_COLOR         	0xFFDF 	//菜单项图标默认颜色
#define MENU_ITEM_ACTIVE_ICON_COLOR  	0x07E0 	//菜单项激活图标颜色

#define MENU_TITLE_LEFT       			56 		//菜单标题显示坐标
#define MENU_TITLE_TOP       			100 	//菜单标题显示坐标
#define MENU_TITLE_WIDTH       			128
#define MENU_TITLE_HEIGHT       		32
#define MENU_TITLE_COLOR  				0xFFDF 	////菜单页标题字体颜色
#define MENU_TITLE_FONT_SIZE   			32 		//菜单标题字体大小

//
/**
 * 从 eflash NVR page 1读取数据,并组织成 Menu数组;
 *
 *  正常返回0 ,其它数值为错误
 * */
bool loadMenu();

uint8_t getMenuInitFlag();

void setMenuInitFlag();

void resetMenuData();

//更新菜单
uint8_t writeMenu(uint8_t index, Menu val);

//获取当前层级的所有菜单
uint8_t getMenuList(uint8_t pId);

//在圆形屏幕上显示环形菜单
void showMenuView(Menu menu);

//显示指定菜单下的子菜单
void showSubMenu(uint8_t pMenuId);

//获取当前活跃菜单在fsm中响应编码器事件时使用
Menu getActiveMenu();

//设置当前活跃菜单
void setActiveMenu(uint8_t idx); //同一级菜单,指定序号

//下一个菜单
void menuNext(); //下一个菜单 ,环形菜单,以顺时针方向为正转
//上一个菜单
void menuPrev(); //上一个菜单

//根据menuId获取菜单项
Menu getMenuById(uint8_t mId);

//清除密码验证成功标识
void clearPasswordAuthFlag();

enumViewEvent getMenuViewEvent();

#endif  //__MENU_VIEW_H__

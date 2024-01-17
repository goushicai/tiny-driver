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


#ifndef __MENU_IMG_VIEW_H__
#define __MENU_IMG_VIEW_H__

#include "viewMenu.h"
#include "event.h"
#include "encoder.h"
#include "jpgDecoder.h"
#include "jpg.h"

/****************** 菜单页相关配置 ************/

#define MENU_IMG_BG_COLOR           	0xFFDF  // 菜单页面背景色
#define MENU_IMG_SIZE          			48		//菜单图标大小
#define MENU_IMG_ACTIVE_SIZE      		64		//菜单图标大小
#define MENU_IMG_LEFT      				45		//菜单图标横坐标
#define MENU_IMG_ACTIVE_TOP      		88		//菜单图标纵坐标
#define MENU_IMG_MARGIN      			10		//菜单图标间隔

#define MENU_IMG_TITLE_FONT_SIZE   		24 		//菜单标题字体大小
#define MENU_IMG_TITLE_ACTIVE_FONT_SIZE 32 		//菜单标题字体大小
#define MENU_IMG_TITLE_LEFT       		110 	//菜单标题显示坐标
#define MENU_IMG_TITLE_TOP       		104 	//菜单标题显示坐标
#define MENU_IMG_TITLE_COLOR  			0x3186	//菜单页标题字体颜色
#define MENU_IMG_TITLE_DISABLE_COLOR  	0xAD55	


void showImgMenuView(uint8_t parentId);

//设置当前活跃菜单
void setActiveImgMenu(uint8_t idx); //同一级菜单,指定序号

//下一个菜单
void imgMenuNext(); //下一个菜单 ,环形菜单,以顺时针方向为正转
//上一个菜单
void imgMenuPrev(); //上一个菜单

enumViewEvent getImgMenuViewEvent();

#endif  //__MENU_IMG_VIEW_H__

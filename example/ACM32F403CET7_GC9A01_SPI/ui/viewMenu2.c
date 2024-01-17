/**
 * 图形菜单页
 *
 * */

#include "viewMenu2.h"

//所有菜单, 从eflash中获取,并驻留内存
extern Menu sysMenuList[];
//当前层级菜单列表, 同一级不可超过16个
extern Menu menuList[];

extern uint8_t sysMenuCount;

//当前活跃菜单序号
extern uint8_t menuIndex;

//当前层级菜单数量
extern uint8_t menuCount;

//当前活跃的菜单实例
extern Menu menuInstance;


//显示菜单的标题
void drawImgMenuTitle(uint16_t left,uint16_t top,uint8_t txtId,uint8_t fontSize)
{
	uiText titleOption = getUiTextInstance();
	
	titleOption.align = ALIGN_LEFT;
	titleOption.left = left;
	titleOption.top  = top ;
	
	titleOption.bgColor = MENU_IMG_BG_COLOR;
	titleOption.fontSize = fontSize;
	if(fontSize == MENU_IMG_TITLE_ACTIVE_FONT_SIZE){
		titleOption.color = MENU_IMG_TITLE_COLOR;
	}else{
		titleOption.color = MENU_IMG_TITLE_DISABLE_COLOR;
	}
	titleOption.text = (char *) &hzFontText[txtId][0];
	
	uiShowText(titleOption);
	printfS("\n drawImgMenuTitle: left:%d,top:%d,width:%d",left,top,titleOption.width);
}

unsigned char * getJpgDataById(uint8_t jpgId,uint8_t sizeType){
	unsigned char *p = (unsigned char *)jpg_list48;
	if(sizeType == 48){
		switch(jpgId){
			case JPG_BOOK_48		: p = (unsigned char *)jpg_book48	; break;
			case JPG_CHART_48		: p = (unsigned char *)jpg_chart48	; break;
			case JPG_CLOCK_48		: p = (unsigned char *)jpg_clock48	; break;
			case JPG_COVERT_48		: p = (unsigned char *)jpg_covert48	; break;
			case JPG_FIRE_48		: p = (unsigned char *)jpg_fire48	; break;
			case JPG_ICAST_48		: p = (unsigned char *)jpg_icast48	; break;
			case JPG_LIST_48		: p = (unsigned char *)jpg_list48	; break;
			case JPG_LOG_48			: p = (unsigned char *)jpg_log48	; break;
			case JPG_MESSAGE_48		: p = (unsigned char *)jpg_message48; break;
			case JPG_MIC_48			: p = (unsigned char *)jpg_mic48	; break;
			case JPG_PASSWORD_48	: p = (unsigned char *)jpg_password48; break;
			case JPG_PHONE_48		: p = (unsigned char *)jpg_phone48	; break;
			case JPG_SACN_48		: p = (unsigned char *)jpg_sacn48	; break;
			case JPG_SETTING_48		: p = (unsigned char *)jpg_setting48; break;
			case JPG_USER_48		: p = (unsigned char *)jpg_user48	; break;
			default 				: p = (unsigned char *)jpg_list48	; break;
		}
	}else if(sizeType == 64){
		switch(jpgId){
			case JPG_BOOK_64		: p = (unsigned char *)jpg_book64	; break;
			case JPG_CHART_64		: p = (unsigned char *)jpg_chart64	; break;
			case JPG_CLOCK_64		: p = (unsigned char *)jpg_clock64	; break;
			case JPG_COVERT_64		: p = (unsigned char *)jpg_covert64	; break;
			case JPG_FIRE_64		: p = (unsigned char *)jpg_fire64	; break;
			case JPG_ICAST_64		: p = (unsigned char *)jpg_icast64	; break;
			case JPG_LIST_64		: p = (unsigned char *)jpg_list64	; break;
			case JPG_LOG_64			: p = (unsigned char *)jpg_log64	; break;
			case JPG_MESSAGE_64		: p = (unsigned char *)jpg_message64; break;
			case JPG_MIC_64			: p = (unsigned char *)jpg_mic64	; break;
			case JPG_PASSWORD_64	: p = (unsigned char *)jpg_password64; break;
			case JPG_PHONE_64		: p = (unsigned char *)jpg_phone64	; break;
			case JPG_SACN_64		: p = (unsigned char *)jpg_sacn64	; break;
			case JPG_SETTING_64		: p = (unsigned char *)jpg_setting64; break;
			case JPG_USER_64		: p = (unsigned char *)jpg_user64	; break;
			default 				: p = (unsigned char *)jpg_list64	; break;
		}
	}
	
	return p;
}

//画出当前活跃的菜单项
void setActiveImgMenu(uint8_t idx)
{
	unsigned char *p;
    //修改当前的活跃菜单
    menuIndex = idx;
    menuInstance = menuList[idx];
	
	if(menuCount < 1){
		return;
	}else if(menuCount == 1){
		//当前激活图标
		p = getJpgDataById(menuList[0].iconId,MENU_IMG_ACTIVE_SIZE);
		showJPG(p, MENU_IMG_LEFT,MENU_IMG_ACTIVE_TOP);
		drawImgMenuTitle(MENU_IMG_TITLE_LEFT,MENU_IMG_TITLE_TOP,menuList[idx].txtId,MENU_IMG_TITLE_ACTIVE_FONT_SIZE);
		return;
	}
	
	uiClear(MENU_IMG_BG_COLOR);
	
	if(idx == 0){
		//当前激活图标
		p = getJpgDataById(menuList[idx].iconId,MENU_IMG_ACTIVE_SIZE);
		showJPG(p, MENU_IMG_LEFT,MENU_IMG_ACTIVE_TOP);
		//当前文本
		drawImgMenuTitle(MENU_IMG_TITLE_LEFT,MENU_IMG_TITLE_TOP,menuList[idx].txtId,MENU_IMG_TITLE_ACTIVE_FONT_SIZE);
		
		//下一个图标与文本
		p = getJpgDataById(menuList[idx+1].iconId,MENU_IMG_SIZE);
		showJPG(p, MENU_IMG_LEFT+(MENU_IMG_ACTIVE_SIZE-MENU_IMG_SIZE),MENU_IMG_ACTIVE_TOP + MENU_IMG_ACTIVE_SIZE + MENU_IMG_MARGIN);
		drawImgMenuTitle(MENU_IMG_TITLE_LEFT ,
						MENU_IMG_ACTIVE_TOP + MENU_IMG_ACTIVE_SIZE + MENU_IMG_MARGIN + (MENU_IMG_SIZE-MENU_IMG_TITLE_FONT_SIZE)/2,
						menuList[idx+1].txtId,MENU_IMG_TITLE_FONT_SIZE);
		
	}else if(idx == menuCount - 1){
		//上一个图标与文本
		p = getJpgDataById(menuList[idx - 1].iconId,MENU_IMG_SIZE);
		showJPG(p, MENU_IMG_LEFT+(MENU_IMG_ACTIVE_SIZE-MENU_IMG_SIZE),MENU_IMG_ACTIVE_TOP - MENU_IMG_SIZE - MENU_IMG_MARGIN);
		drawImgMenuTitle(MENU_IMG_TITLE_LEFT,
						MENU_IMG_ACTIVE_TOP - MENU_IMG_TITLE_FONT_SIZE - MENU_IMG_MARGIN - (MENU_IMG_SIZE-MENU_IMG_TITLE_FONT_SIZE)/2,
						menuList[idx-1].txtId,MENU_IMG_TITLE_FONT_SIZE);
		//当前文本与文本
		p = getJpgDataById(menuList[idx].iconId,MENU_IMG_ACTIVE_SIZE);
		showJPG(p, MENU_IMG_LEFT,MENU_IMG_ACTIVE_TOP);
		drawImgMenuTitle(MENU_IMG_TITLE_LEFT,MENU_IMG_TITLE_TOP,menuList[idx].txtId,MENU_IMG_TITLE_ACTIVE_FONT_SIZE);
	}else{
		//上一个图标与文本
		p = getJpgDataById(menuList[idx - 1].iconId,MENU_IMG_SIZE);
		showJPG(p, MENU_IMG_LEFT+(MENU_IMG_ACTIVE_SIZE-MENU_IMG_SIZE),MENU_IMG_ACTIVE_TOP - MENU_IMG_SIZE - MENU_IMG_MARGIN);
		drawImgMenuTitle(MENU_IMG_TITLE_LEFT,
						MENU_IMG_ACTIVE_TOP - MENU_IMG_TITLE_FONT_SIZE - MENU_IMG_MARGIN- (MENU_IMG_SIZE-MENU_IMG_TITLE_FONT_SIZE)/2,
						menuList[idx-1].txtId,MENU_IMG_TITLE_FONT_SIZE);
		
		//当前文本与文本
		p = getJpgDataById(menuList[idx].iconId,MENU_IMG_ACTIVE_SIZE);
		showJPG(p, MENU_IMG_LEFT,MENU_IMG_ACTIVE_TOP);
		drawImgMenuTitle(MENU_IMG_TITLE_LEFT,MENU_IMG_TITLE_TOP,menuList[idx].txtId,MENU_IMG_TITLE_ACTIVE_FONT_SIZE);
		
		//下一个图标与文本
		p = getJpgDataById(menuList[idx+1].iconId,MENU_IMG_SIZE);
		showJPG(p, MENU_IMG_LEFT+(MENU_IMG_ACTIVE_SIZE-MENU_IMG_SIZE),MENU_IMG_ACTIVE_TOP + MENU_IMG_ACTIVE_SIZE + MENU_IMG_MARGIN);
		drawImgMenuTitle(MENU_IMG_TITLE_LEFT ,
						MENU_IMG_ACTIVE_TOP + MENU_IMG_ACTIVE_SIZE + MENU_IMG_MARGIN + (MENU_IMG_SIZE-MENU_IMG_TITLE_FONT_SIZE)/2,
						menuList[idx+1].txtId,MENU_IMG_TITLE_FONT_SIZE);
	}
    
}

//下一个菜单
void imgMenuNext()
{
    if(menuIndex < menuCount-1){
		setActiveImgMenu(menuIndex+1);
	}
}

//上一个菜单
void imgMenuPrev()
{
	if(menuIndex>0){
		setActiveImgMenu(menuIndex-1);
	}
}

//显示图形菜单
void showImgMenuView(uint8_t parentId)
{
	
	getMenuList(parentId);//获取当前层级的 菜单列表
	setActiveImgMenu(0);//显示活跃菜单项
}

enumViewEvent getImgMenuViewEvent()
{
    int8_t encoderValue,encoderEvent;
    enumViewEvent menuEvent = VIEW_EVENT_NONE;
	
    encoderValue = getEncoderVal();
    encoderEvent= getKeyVal();
	
	clrKeyVal();
	clrEncoderVal();

    if(encoderValue > 0)
    {
        imgMenuNext();
        menuEvent = MENU_EVENT_ACTIVE_CHANGE;
    }
    else if(encoderValue < 0)
    {
        imgMenuPrev();
        menuEvent = MENU_EVENT_ACTIVE_CHANGE;
    }

    if(encoderEvent== ENCODER_EVENT_CLICK)
    {
		switch(menuInstance.menuType)
        {
            case MENU_TYPE_ACTION:
                menuEvent = MENU_EVENT_FIND_ACTION;
                break;
            case MENU_TYPE_TEXT:
                menuEvent = MENU_EVENT_FIND_TEXT;
                break;
			case MENU_TYPE_PIC:
                menuEvent = MENU_EVENT_FIND_PIC;
				break;
            case MENU_TYPE_CHART:
                menuEvent = MENU_EVENT_FIND_CHART;
                break;
			case MENU_TYPE_CHANNEL:
                menuEvent = MENU_EVENT_FIND_CHANNEL;
                break;
            default:
                menuEvent = MENU_EVENT_FIND_MENU;
                break;
        }
    }
    else if(encoderEvent== ENCODER_EVENT_DOUBLE_CLICK)       //退回到上级菜单
    {
		menuEvent = VIEW_EVENT_BACK;
		
    }
    return menuEvent;
}

/**
 * �˵�ҳ
 *
 * */

#include "viewMenu.h"

//���в˵�, ��eflash�л�ȡ,��פ���ڴ�
Menu sysMenuList[MENU_MAX_COUNT];
uint8_t sysMenuCount;

//��ǰ�㼶�˵��б�, ͬһ�����ɳ���16��
Menu menuList[MENU_MAX_COUNT/2];

//��ǰ��Ծ�Ĳ˵�ʵ��
Menu menuInstance= {0, 0,0,0,  0,0,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  0,  0,0,0};
//���˵�
Menu parentMenu;

//��ǰ��Ծ�˵����
uint8_t menuIndex=99;

//��ǰ�㼶�˵�����
uint8_t menuCount=0;

/**
	��ʼ���˵�,
	eflash������Ϊ��˴洢,�˵�������Ҫ����Ϊ���,���ߵ�ַ��Ÿ�λ
	*/
void resetMenuData(){
	uint16_t i;
	
	uint32_t menulist[64] = {
		//һ���˵������ã�״̬����־������
		0x01001616, 0x08000000,0x00000000,0x00000000,
		0x0200170c, 0x00000000,0x00000000,0x00000000,
		0x0300180e, 0x00000000,0x00000000,0x00000000,
		0x0400190a, 0x00000000,0x00000000,0x00000000,
		//���ò˵��µĶ����˵���˫�����,����ʱ��,�������
		0x05012200, 0x10824000,0x00000000,0x0000006c,
		0x06012305, 0x10824000,0x00000000,0x00000070,
		0x07012418, 0x10414000,0x70000001,0x00ff0074,
		//״̬�˵��µĶ����˵�����ѹ,����,�¶�,ͨ��
		0x08022c13, 0x10843000,0x0000ffce,0x00320080,
		0x09022d07, 0x10843000,0x7000fff6,0x000a0084,
		0x0a022e17, 0x10013040,0x70000000,0x00640088,
		0x0b022b0b, 0x50012000,0x70000001,0x0010008C,
		//��־�˵��µĶ����˵�����ά��,ͼ��
		0x0c03070e, 0x30000000,0x00000000,0x00000000,
		0x0d032903, 0x40000000,0x00000000,0x00000000,
		//�����˵��µĶ����˵�����˾����,��Ʒ��Ϣ,����˵��
		0x0e043212, 0x20000000,0x00320000,0x00320000,
		0x0f04330e, 0x20000000,0x00320000,0x00330000,
		0x1004340a, 0x20000000,0x00320000,0x00340000
		
	};
	uint32_t addr;
	
	HAL_EFlash_ErasePage(SYSTEM_MENU_PAGE * EFLASH_PAGE_SIZE); 
	for(i = 0;i<64;i++){
		addr = SYSTEM_MENU_PAGE * EFLASH_PAGE_SIZE + (i*4);
		HAL_EFlash_Program_Word(addr, menulist[i]);
		//printfS("\n resetMenuData: i:%d , addr: %d,menu: %08x, flash: %08x, ", i, addr,menulist[i],HAL_EFLASH_READ_WORD(addr));
	}
}


//��ȡ�˵���ʼ����ʶ,�˵�����ҳ��ǰ4���ֽ�,�����ݼ�Ϊ�ѳ�ʼ��
uint8_t getMenuInitFlag(){//
	uint8_t flag = 0;
	uint32_t val = eFlashReadUint32(SYSTEM_MENU_PAGE * EFLASH_PAGE_SIZE);
	if(val == 0x00000000 || val == 0xFFFFFFFF){
		flag = 0;
	}else{
		flag = 1;
	}
	return flag;
}


//
/**
 * �� eflash ���һҳ ��ȡ����,����֯�� Menu����;
 * */
//��ȡһҳ�˵�
Menu readMenuItem(uint8_t idx)
{
    uint8_t tmp  ;
    Menu mItem={0, 0,0,0,  0,0,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  0,  0,0,0};
		
    uint32_t addr = SYSTEM_MENU_PAGE * EFLASH_PAGE_SIZE + (idx* 16);
	//printfS("\n readMenuItem: idx: %d, addr: %d,val: %08x,", idx,addr,HAL_EFLASH_READ_WORD(addr));
	
    mItem.id 		= eFlashReadUint8(addr+3); //�˵�ÿ���ֽ�дһ��,���,���ߵ�ַ����ֽ�
    mItem.parentId 	= eFlashReadUint8(addr+2);
    mItem.txtId 	= eFlashReadUint8(addr+1);
    mItem.iconId 	= eFlashReadUint8(addr+0);
	
	tmp = HAL_EFLASH_READ_BYTE(addr+7);
    mItem.menuType      = tmp >> 4      ; // ����4λ,ȡǰ4λ
    mItem.needPassword  = (tmp & 0x08) >> 3 ; //bit3
    mItem.menuReserved 	= 0;//����

    tmp = HAL_EFLASH_READ_BYTE(addr+6);
    mItem.actReadonly   = tmp  >> 7; 			//bit7
    mItem.actConfirm    = (tmp & 0x40) >> 6; 	//bit6
    mItem.actSource     = (tmp & 0x38) >> 3;	//bit 5,4,3
    mItem.actDataType   = (tmp & 0x07) ;        //bit 2,1,0

    tmp = HAL_EFLASH_READ_BYTE(addr+5);
    mItem.actDataLength  = tmp  >> 4;
    mItem.actReserved    = 0;//����

    tmp = HAL_EFLASH_READ_BYTE(addr+4);
    mItem.kbType   		= tmp  >> 4;
    mItem.kbShowBack    = (tmp & 0x08) >> 3;
    mItem.kbShowOK      = (tmp & 0x04) >> 2;
    mItem.kbShowDelete  = (tmp & 0x02) >> 1;
    mItem.kbShowClear   = (tmp & 0x01) ;

    tmp = HAL_EFLASH_READ_BYTE(addr+11);
    mItem.progress    = tmp  >> 6;
    mItem.feedback    = (tmp & 0x30) >> 4;
    mItem.othOp3      = 0 ;//����

    mItem.txtOrPicId  = HAL_EFLASH_READ_BYTE(addr+10);

    mItem.minVal      = (int16_t)HAL_EFLASH_READ_HALFWORD(addr+8);
    mItem.maxVal      = (int16_t)HAL_EFLASH_READ_HALFWORD(addr+14);
    mItem.address     = HAL_EFLASH_READ_HALFWORD(addr+12);
/*
	printfS("\n\n readMenuItem: %d id:%d, parentId:%d, txtId:%d, iconId:%d, menuType:%d, needPassword:%d",idx,
						mItem.id,mItem.parentId,mItem.txtId,mItem.iconId,mItem.menuType,mItem.needPassword);

	printfS("\n readMenuItem: %d actReadonly:%d, actConfirm:%d, actSource:%d, actDataType:%d, actDataLength:%d",idx,
						mItem.actReadonly,mItem.actConfirm,mItem.actSource,mItem.actDataType,mItem.actDataLength);

	printfS("\n readMenuItem: %d kbType:%d, kbShowBack:%d, kbShowOK:%d, kbShowDelete:%d, kbShowClear:%d ,progress:%d, feedback:%d",idx,
					mItem.kbType,mItem.kbShowBack,mItem.kbShowOK,mItem.kbShowDelete,mItem.kbShowClear,mItem.progress,mItem.feedback);

	printfS("\n readMenuItem: %d txtOrPicId:%02x minVal:%04x, maxVal:%04x, address:%04x",idx,
					mItem.txtOrPicId,mItem.minVal,mItem.maxVal,mItem.address);
					*/
    return mItem;
}

//todo debug
uint8_t writeMenu(uint8_t index, Menu val)
{
    uint32_t addr = (SYSTEM_MENU_PAGE * EFLASH_PAGE_SIZE) + ((uint32_t)index * 16);
    uint32_t m[4];
    uint8_t u0,u1,u2,u3;
    bool flag;

    m[0] = (val.id <<24) | (val.parentId << 16) | (val.txtId <<8) | val.iconId;

    u0 = (val.menuType << 6) | ((val.needPassword & 0x20) <<5)| (val.menuReserved& 0x1F);
    u1 = (val.actReadonly<<7)|((val.actConfirm &0x40)<<6)|((val.actSource & 0x38)<<3)|(val.actDataType & 0x07);
    u2 = (val.actDataLength<<4)|(val.actReserved &0x0F);
    u3 = (val.kbType<<4)|((val.kbShowBack &0x08 )<<3)|((val.kbShowOK & 0x04 )<<2)|((val.kbShowDelete & 0x02 )<<1)|(val.kbShowClear & 0x01);

    m[1] = (u0 <<24) | (u1 << 16) | (u2 <<8) | u3;

    u0 = (val.progress<<6)|((val.feedback & 0x30 )<<4)|(val.othOp3 & 0x0F );

    m[2] = (u0 << 24) | (val.txtOrPicId << 16) | val.minVal;

    m[3] = (val.maxVal << 16)| val.address;

    for(uint8_t i = 0; i<4 ; i++)
    {
        flag = HAL_EFlash_Program_Word(addr+(i * 4), m[i]);

    }
    return flag == true ? 0 : 1;

}

bool loadMenu()
{
    sysMenuCount = 0;
    for(uint8_t i = 0; i < 32; i++)
    {
        Menu m = readMenuItem(i);
        if(m.id == 0x00 || m.id==0xFF)
        {
            break;
        }
		
        sysMenuList[i] = m;
        sysMenuCount ++;
    }
    return sysMenuCount == 0 ? false : true; //sysMenuCount < 1 ���� error
    
/*
    //һ���˵������ã�״̬����־������
	Menu m0 = {1, 0,22,22,  0,1,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  0,  0,0,0};
	Menu m1 = {2, 0,23, 3,  0,0,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  0,  0,0,0};
	Menu m2 = {3, 0,24,14,  0,0,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  1,  0,0,0};
	Menu m3 = {4, 0,25,10,  0,0,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  1,  0,0,0};


	//���ò˵��µĶ����˵���˫�����,����ʱ��,�������
	Menu m4 = {5, 1,34,0,  1,0,0,  1,0,0,2,  4,0,  0,0,0,0,0,  0,0,0,  0,  0,0,0x6C}; 
	Menu m5 = {6, 1,35,5,  1,0,0,  1,0,0,2,  4,0,  0,0,0,0,0,  0,0,0,  0,  0,0,0x70};
	Menu m6 = {7, 1,36,21,  1,0,0,  0,0,0,1,  4,0,  0,0,0,0,0,  1,3,0,  0, 1,600,0x74};
		
	//״̬�˵��µĶ����˵�����ѹ,����,�¶�,ͨ��
	Menu m7 = {8, 2,44,19,  1,0,0,  1,0,0,4,  3,0,  0,0,0,0,0,  0,0,0,  0,  -50,50,0}; 
	Menu m8 = {9, 2,45,7 ,  1,0,0,  1,0,0,4,  3,0,  0,0,0,0,0,  0,0,0,  0,  -10,10,0};
	Menu m9 = {10,2,46,23,  1,0,0,  0,0,0,1,  3,0,  2,0,0,0,0,  1,3,0,  0,  0,100,0};
	Menu m10= {11,2,43,11,  1,0,0,  0,0,0,1,  1,0,  4,0,0,0,0,  1,3,0,  0,  1,16,0};

	//��־�˵��µĶ����˵����ı�,ͼ��
	Menu m11= {12, 3,42,14,  2,0,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  0,  0,0,0}; 
	Menu m12= {13, 3,41,3 ,  3,0,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  0,  0,0,0};

	//�����˵��µĶ����˵�����˾����,��Ʒ��Ϣ,����˵��
	Menu m13= {14, 4,50,18,  2,0,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  50,  0,0,0}; 
	Menu m14= {15, 4,51,14,  2,0,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  51,  0,0,0};
	Menu m15= {16, 4,52,10,  2,0,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  52,  0,0,0};
		
    sysMenuList[0] = m0;
    sysMenuList[1] = m1;
    sysMenuList[2] = m2;
    sysMenuList[3] = m3;
    sysMenuList[4] = m4;
    sysMenuList[5] = m5;
    sysMenuList[6] = m6;
    sysMenuList[7] = m7;
    sysMenuList[8] = m8;
    sysMenuList[9] = m9;
    sysMenuList[10] = m10;
    sysMenuList[11] = m11;
	sysMenuList[12] = m12;
    sysMenuList[13] = m13;
	sysMenuList[14] = m14;
    sysMenuList[15] = m15;
    sysMenuCount = 16;

    return sysMenuCount < 1 ? 1 : 0; //sysMenuCount < 1 ���� error
	*/

}

//����ָ���ĸ�id,��ȡ�˵��б�
uint8_t getMenuList(uint8_t pId)
{
    uint8_t len = sizeof(sysMenuList)/ sizeof(menuInstance);
    menuCount = 0;
    menuIndex = 0;
    for(uint8_t i = 0 ; i < len ; i++)
    {
        if(sysMenuList[i].id>0 && sysMenuList[i].parentId == pId)
        {
            menuList[menuCount] = sysMenuList[i];
            menuCount ++;
        }
    }

    // todo �˵�����δ�ҵ�
    if(menuCount < 1)
    {
        return 2;
    }

    return 0;
}


//��ʾ�˵��ı���
void drawMenuTitle(uint16_t txtColor, uint16_t bgColor)
{
	uiText titleOption = getUiTextInstance();
	
	titleOption.left = MENU_TITLE_LEFT;
	titleOption.top  = MENU_TITLE_TOP ;
	titleOption.color = MENU_TITLE_COLOR;
	titleOption.bgColor = MENU_BG_COLOR;
	titleOption.fontSize = FONT_SIZE_32;
	titleOption.borderColor = MENU_BG_COLOR;
	titleOption.width = MENU_TITLE_WIDTH;
	titleOption.text = (char *) &hzFontText[menuInstance.txtId][0];
	uiShowText(titleOption);
}

//�����˵���������
void drawMenu()
{
	uiClear(MENU_ITEM_BG_COLOR);
	uiFillCircle(SCREEN_CENTER_X, SCREEN_CENTER_Y, OUTER_RADIUS - MENU_RING_WIDTH,MENU_BG_COLOR);
}

//���˵���, ����ֻ��ʾͼ��
void drawMenuIcon()
{
    uint16_t x,y,r = OUTER_RADIUS - (MENU_RING_WIDTH)/2 ; //���ڻ����е�
    double angle,step;
    step =  2*PI / (double) menuCount;

    for(uint8_t i = 0; i < menuCount; i++)
    {
        angle = step * i - PI/2; //��12��λ�ÿ�ʼ
        x = SCREEN_CENTER_X + (r * cos(angle) ) - (MENU_ITEM_ICON_SIZE/2) ;
        y = SCREEN_CENTER_Y + (r * sin(angle) ) - (MENU_ITEM_ICON_SIZE/2) ;
		
		uiShowIcon(x,y, menuList[i].iconId ,24, MENU_ITEM_ICON_COLOR,MENU_ITEM_BG_COLOR);
    }
}

//������ǰ��Ծ�Ĳ˵���
void setActiveMenu(uint8_t idx)
{
    uint16_t x,y,r = OUTER_RADIUS - (MENU_RING_WIDTH)/2 ; //���ڻ����е�
    double angle,step;
    step =  2*PI / (double) menuCount;
	
    //��ԭ�˵�ͼ��
    angle = step * menuIndex - PI/2; //��12��λ�ÿ�ʼ
    x = SCREEN_CENTER_X + (r * cos(angle) ) - (MENU_ITEM_ICON_SIZE/2);
    y = SCREEN_CENTER_Y + (r * sin(angle) ) - (MENU_ITEM_ICON_SIZE/2) ;
	uiShowIcon(x,y, menuInstance.iconId ,24, MENU_ITEM_ICON_COLOR,MENU_ITEM_BG_COLOR);
    
	//�޸ĵ�ǰ�Ļ�Ծ�˵�
    menuIndex = idx;
    menuInstance = menuList[idx];

    //���ǰͼ��
    angle = step * idx - PI/2; //��12��λ�ÿ�ʼ
    x = SCREEN_CENTER_X + (r * cos(angle) ) - (MENU_ITEM_ICON_SIZE/2);
    y = SCREEN_CENTER_Y + (r * sin(angle) ) - (MENU_ITEM_ICON_SIZE/2) ;
    
	uiShowIcon(x,y, menuInstance.iconId  ,28, MENU_ITEM_ACTIVE_ICON_COLOR,MENU_ITEM_BG_COLOR);
	
    //�޸ı���
    drawMenuTitle(MENU_TITLE_COLOR,MENU_BG_COLOR);
}

//��һ���˵�
void menuNext()
{
    setActiveMenu((menuIndex >= menuCount - 1) ? 0 : menuIndex + 1);
}

//��һ���˵�
void menuPrev()
{
	setActiveMenu((menuIndex == 0) ? menuCount - 1 : menuIndex - 1);
}

Menu getActiveMenu()
{
    return menuInstance;
}
//����id���Ҳ˵�,�Ҳ�������id=0�ĸ��˵�(���˵������ݶ���)
Menu getMenuById(uint8_t mId)
{
    Menu mItem = {0, 0,0,0,  0,0,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  0,  0,0,0};;
    for(uint8_t i = 0; i < sysMenuCount; i++)
    {
        if(mId == sysMenuList[i].id)
        {
            mItem = sysMenuList[i];
            break;
        }
    }
    return mItem;
}
//���ݸ��˵�id��ʾ�Ӳ˵�
void showSubMenu(uint8_t pMenuId){
	getMenuList(pMenuId);//��ȡ��ǰ�㼶�� �˵��б�
	
	drawMenu();//���α���
	drawMenuIcon();//��ʾ�˵�ͼ��
	setActiveMenu(0);//��ʾ��Ծ�˵���(ͼ��Ŵ�)
	drawMenuTitle(MENU_TITLE_COLOR,MENU_BG_COLOR);
}
//��ʾ���β˵�
void showMenuView(Menu menu)
{
	parentMenu = menu;
	
	if(menu.needPassword && getPasswordAuthFlag()==0){
		showPasswordView(0);
	}else{
		showSubMenu(menu.id);
	}
}

enumViewEvent getMenuViewEvent()
{
    int8_t encoderValue,encoderEvent;
    enumViewEvent menuEvent = VIEW_EVENT_NONE;
	
	//�������
	if(parentMenu.needPassword && getPasswordAuthFlag()==0){
		menuEvent = getPasswordViewEvent();
		if(menuEvent == PASSWORD_EVENT_PASS){
			//showSubMenu(parentMenu.id);
		}
		return menuEvent;
	}
	
    encoderValue = getEncoderVal();
    encoderEvent= getKeyVal();
	
	clrKeyVal();
	clrEncoderVal();

    if(encoderValue > 0)
    {
        menuNext();
        menuEvent = MENU_EVENT_ACTIVE_CHANGE;
    }
    else if(encoderValue < 0)
    {
        menuPrev();
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
    else if(encoderEvent== ENCODER_EVENT_DOUBLE_CLICK)       //�˻ص��ϼ��˵�
    {
		menuEvent = VIEW_EVENT_BACK;
		
    }
    return menuEvent;
}

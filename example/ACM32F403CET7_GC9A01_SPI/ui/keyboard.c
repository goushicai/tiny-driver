#include "keyboard.h"
//键盘选项
KeyboardOption kbOption;
//键盘输入文本 ascii
char keyboardContent[KEYBOARD_MAX_LENGTH];
//键盘输入文本字符长度
uint8_t keyboardContentLength;
//键盘输入文本光标位置, todo
uint8_t kbCursorLocation;
// 编码器上次数值
uint8_t encoderDirection=0,lastencoderDirection; 

//键盘键位列表
KeyboardButton keyButtonList[KEYBOARD_BUTTON_MAX_LENGTH];
uint8_t keyButtonCount;
uint8_t keyButtonIndex;

//修改范围
void setKeyboardOptionRange(int16_t minVal,int16_t maxVal){
	if(minVal < maxVal ){
		kbOption.minVal = minVal;
		kbOption.maxVal = maxVal;
	}
}

//创建布尔键盘的键值列表
void createBoolKeyboardButtons()
{
    keyButtonCount = 2;
    KeyboardButton key =  {'0','N'};
    KeyboardButton key1 =  {'1','Y'};

    keyButtonList[0]= key;
	
	key.value = '1';
	key.text = 'Y';
    keyButtonList[1]= key;
};

//创建选择键盘的键值列表, 0-9之间
void createSelectKeyBoardButtons(uint8_t fromVal, uint8_t toVal)
{
	KeyboardButton kb={0,0};
	uint8_t tmp ;
    if(fromVal > 9 || toVal > 9)
    {
        return;
    }
    if(fromVal > toVal)
    {
        tmp = fromVal;
        fromVal = toVal;
        toVal = tmp;
    }
	
    keyButtonCount = 0;
    for(uint8_t i=fromVal; i<=toVal; i++)
    {
        kb.value = i + '0';
		kb.text  = i + '0';
        keyButtonList[keyButtonCount ++]= kb;
    }
};

//创建密码键盘的键值列表, 密码值全部为数值,密码值存储为字符串
void createPasswordKeyboardButtons()
{
	KeyboardButton kb={0,0};
    keyButtonCount = 0;
    for(uint8_t i=0; i<=9; i++)
    {
        kb.value = i + '0';
		kb.text  = i + '0';
        keyButtonList[keyButtonCount ++]= kb;
    }
};
//创建整数键盘的键值列表
void createNumberKeyboardButtons(KeyboardOption opt)
{
    keyButtonCount = 0;
	KeyboardButton kb = {0,0}; 
    for(uint8_t i=0; i<=9; i++)
    {
		kb.value = i + '0';
		kb.text  = i + '0';
		
        keyButtonList[keyButtonCount ++]= kb;
    }

    if(opt.kbShowMinus)
    {
		kb.value = '-';
		kb.text  = '-';
        keyButtonList[keyButtonCount ++]= kb;
    }
};
//创建带浮点数键盘的键值列表
void createFloatKeyboardButtons(KeyboardOption opt)
{
    keyButtonCount = 0;
	KeyboardButton kb = {0,0}; 
    for(uint8_t i=0; i<=9; i++)
    {
        kb.text =  i+'0';
		kb.value = i+'0';
        keyButtonList[keyButtonCount ++]= kb;
    }
	
	kb.text = '-';
	kb.value = '-';
	keyButtonList[keyButtonCount ++] = kb;
	
	kb.text = '.';
	kb.value = '.';
	keyButtonList[keyButtonCount ++] = kb;
}

//画出键盘背景
void drawKeyboard(uint16_t bgColor)
{
	uiClear(KEYBOARD_COLOR);//全部涂成键盘颜色
	uiFillCircle(SCREEN_CENTER_X, SCREEN_CENTER_Y, OUTER_RADIUS - KEYBOARD_WIDTH,bgColor);//涂上背景颜色
}

//画键位
void drawKeyboardButton()
{
    uint16_t x,y,r = (OUTER_RADIUS - KEYBOARD_WIDTH/2) ; //外内环的中点
    double angle,step;
    step =  2*PI / (double) keyButtonCount;

    for(uint8_t i = 0; i < keyButtonCount; i++)
    {
        angle = step * i - PI/2; //从12点位置开始
        x = SCREEN_CENTER_X + (r * cos(angle) ) - (KEYBOARD_FONT_SIZE/4) ;
        y = SCREEN_CENTER_Y + (r * sin(angle) ) - (KEYBOARD_FONT_SIZE/2) ;
		
		uiShowAscii(x,y, keyButtonList[i].text, FONT_SIZE_24, KEYBOARD_TEXT_COLOR, KEYBOARD_COLOR);
    }
}

//选中指定的键
void keyboardActive(uint8_t idx)
{
    uint16_t x,y,r = (OUTER_RADIUS - KEYBOARD_WIDTH/2) ; //键盘环的中点
    double angle,step;
	
	//恢复原先的键
    step =  2*PI / (double) keyButtonCount;
    angle = step * keyButtonIndex - PI/2; //从12点位置开始
    x = SCREEN_CENTER_X + (r * cos(angle) ) - (KEYBOARD_FONT_SIZE/4);
    y = SCREEN_CENTER_Y + (r * sin(angle) ) - (KEYBOARD_FONT_SIZE/2) ;
	uiShowAscii(x,y, keyButtonList[keyButtonIndex].text, FONT_SIZE_24, KEYBOARD_TEXT_COLOR, KEYBOARD_COLOR);
	
	//激活当前键
    angle = step * idx - PI/2; //从12点位置开始
    x = SCREEN_CENTER_X + (r * cos(angle) ) - (KEYBOARD_FONT_SIZE/4);
    y = SCREEN_CENTER_Y + (r * sin(angle) ) - (KEYBOARD_FONT_SIZE/2) ;
	uiShowAscii(x,y, keyButtonList[idx].text, FONT_SIZE_24, KEYBOARD_ACTIVE_TEXT_COLOR,KEYBOARD_COLOR);
	
    //修改当前选中
    keyButtonIndex = idx;
}

//激活下一个键
void keyboardNext()
{
	uint8_t idx;
	idx = (keyButtonIndex >= keyButtonCount-1) ? 0 : keyButtonIndex + 1;
    keyboardActive(idx);
}
//激活上一个键
void keyboardPrev()
{
	uint8_t idx;
	idx = keyButtonIndex ==0? keyButtonCount-1 : keyButtonIndex - 1;
    keyboardActive(idx);
}

//输入当前激活字符
void keyboardAppend(char ch)
{
    if(keyboardContentLength < KEYBOARD_MAX_LENGTH)
    {
        keyboardContent[keyboardContentLength++] = ch;
    }
}

//删除最后一个字符
void keyboardDelete()
{
    if(keyboardContentLength > 0){
		keyboardContent[keyboardContentLength--] = '\0' ;
	}
}
//清除键盘输入内容
void keyboardClear()
{
	keyboardContentLength = KEYBOARD_MAX_LENGTH ;
	
	while(keyboardContentLength>0){
		keyboardContentLength--;
		keyboardContent[keyboardContentLength] = '\0' ;
	}
}

void showBoolKeyboard()
{
    createBoolKeyboardButtons();
    drawKeyboard(KEYBOARD_BG_COLOR);
    drawKeyboardButton();
    
    keyboardActive(1);
};

void showSelectKeyboard(KeyboardOption opt)
{
    createSelectKeyBoardButtons(opt.minVal,opt.maxVal);
    drawKeyboard(KEYBOARD_BG_COLOR);
    drawKeyboardButton();
	keyboardActive(0);
};

void showPasswordKeyboard()
{
    createPasswordKeyboardButtons();
    drawKeyboard(KEYBOARD_BG_COLOR);
    drawKeyboardButton();
	lastencoderDirection = getEncoderDir();
    keyboardActive(0);
};

void showNumberKeyboard(KeyboardOption opt)
{
    createNumberKeyboardButtons(opt);
    drawKeyboard(KEYBOARD_BG_COLOR);
    drawKeyboardButton();
    keyboardActive(0);
};

void showFloatKeyboard(KeyboardOption opt)
{
    createFloatKeyboardButtons(opt);
    drawKeyboard(KEYBOARD_BG_COLOR);
    drawKeyboardButton();
    keyboardActive(0);
};

void showLetterKeyboard(KeyboardOption opt)
{
	//todo
    keyboardActive(0);
};

void showFullKeyboard(KeyboardOption opt)
{
	//todo
    keyboardActive(0);
};

void showKeyboard(KeyboardOption opt)
{
    kbOption = opt;
    switch (opt.kbType)
    {
        case KEYBOARD_BOOL :
            showBoolKeyboard();
            break;
        case KEYBOARD_PASSWORD:
            showPasswordKeyboard();
            break;
        case KEYBOARD_SELECT :
            showSelectKeyboard(opt);
            break;
        case KEYBOARD_NUMBER :
            showNumberKeyboard(opt);
            break;
        case KEYBOARD_FLOAT :
            showFloatKeyboard(opt);
            break;
        case KEYBOARD_LETTER :
            showLetterKeyboard(opt);
            break;
        case KEYBOARD_FULL :
            showFullKeyboard(opt);
            break;
        default:
            break;
    }
	keyboardClear();
}

//获取当前键值
KeyboardButton getKeyboardButton()
{
    return keyButtonList[keyButtonIndex];
}

//设置键盘输入内容
void setKeyBoardContent(char *p)
{
    uint8_t i = 0,len=0;
    len = strlen(p);
    len = len > KEYBOARD_MAX_LENGTH ? KEYBOARD_MAX_LENGTH: len;
	KeyboardButton kb;
	
    for(i = 0; i< len; i++)
    {
        keyboardContent[i] = *(p+i);
    }
    keyboardContentLength = len;
}
//读取键盘输入内容
char * getKeyBoardContentString(){
	return keyboardContent;
}

//读取键盘输入值 uint8
uint8_t getKeyBoardContentUInt8(){
	return (int8_t) (atoi((char *)keyboardContent));
}

//读取键盘输入值 uint16
uint16_t getKeyBoardContentUInt16(){
	return (int16_t) (atoi((char *)keyboardContent));
}

//读取键盘输入值 uint32
uint32_t getKeyBoardContentUInt32(){
	return (uint32_t) (atoi((char *)keyboardContent));
}

//读取键盘输入值 int8
int8_t getKeyBoardContentInt8(){
	return (int8_t) (atoi((char *)keyboardContent));
}

//读取键盘输入值 int16
int16_t getKeyBoardContentInt16(){
	return (int16_t) (atoi((char *)keyboardContent));
}

//读取键盘输入值 int32
int32_t getKeyBoardContentInt32(){
	return (int32_t) (atoi((char *)keyboardContent));
}

//当前值 加1
void kbValueInc()
{
    int16_t val = (int16_t) (atoi((char *)keyboardContent));
    if(val < kbOption.maxVal)
    {
        val ++;
        sprintf(( char *)keyboardContent,"%d",val);
    }
    else
    {
        uiDisplayInversionOff();
		System_Delay_MS(200);
		uiDisplayInversionOn();
    }
}
//当前值 减1
void kbValueDec()
{
    int16_t val = (int16_t) (atoi((char *)keyboardContent));
    if(val > kbOption.minVal)
    {
        val --;
        sprintf((char *)keyboardContent,"%d",val);
    }
    else
    {
		uiDisplayInversionOff();
		System_Delay_MS(200);
		uiDisplayInversionOn();
    }
}


//获取键盘参数
KeyboardOption getKeyboardOption(Menu menu)
{
    //从菜单中获取键盘参数
	KeyboardOption keyboardOption;
	
    keyboardOption.kbType = menu.kbType;

    keyboardOption.minVal = menu.minVal;
    keyboardOption.maxVal = menu.maxVal;

    keyboardOption.kbShowBack = menu.kbShowBack;
    keyboardOption.kbShowOK = menu.kbShowOK;
    keyboardOption.kbShowDelete = menu.kbShowDelete;
    keyboardOption.kbShowClear = menu.kbShowClear;

    if(menu.actDataType == DATATYPE_INT8 || menu.actDataType == DATATYPE_INT16 || menu.actDataType ==DATATYPE_INT8)
    {
        keyboardOption.kbShowMinus = 1;
    }

    if(menu.actDataType == DATATYPE_FLOAT)
    {
        keyboardOption.kbShowMinus = 1;
        keyboardOption.kbShowPoint = 1;
    }
    return keyboardOption;
}

//读取键盘事件
enumKeyboardEvent getKeyboardEvent()
{
    int8_t encoderValue,encoderDirChange=0;
    enumEncoderEvent encoderEvent;

    enumKeyboardEvent keyboardEvent = KEYBOARD_EVENT_NONE;

    KeyboardButton btn = getKeyboardButton();

    encoderValue = getEncoderVal();
	clrEncoderVal();
	
    encoderEvent = getKeyVal();
	clrKeyVal();
	
	if(encoderValue!=0){ //编码器数值发生变化后,确认转动方向
		encoderDirection = getEncoderDir();
		if(lastencoderDirection!= encoderDirection){
			lastencoderDirection = encoderDirection;
			encoderDirChange = 1;
		}
	}
	
    //双击退出
    if(encoderEvent == ENCODER_EVENT_DOUBLE_CLICK)
    {
		keyboardClear();//清除键盘输入,以免影响下次使用
		encoderDirChange = 0;
        keyboardEvent = KEYBOARD_EVENT_BACK;//退出
		
    }else if(encoderEvent == ENCODER_EVENT_PRESS)//长按清除输入
    {
        keyboardClear();
		encoderDirChange = 0;
        keyboardEvent = KEYBOARD_EVENT_CHANGE;
    }

    if(kbOption.kbType == KEYBOARD_NONE)
    {
        if(encoderValue>0)
        {
            kbValueInc();
            keyboardEvent = KEYBOARD_EVENT_CHANGE;
        }
        else if(encoderValue<0)
        {
            kbValueDec();
            keyboardEvent = KEYBOARD_EVENT_CHANGE;
        }

        if(encoderEvent == ENCODER_EVENT_CLICK)  //单击确认
        {
            keyboardEvent = KEYBOARD_EVENT_OK;
        }
    }
    else if(kbOption.kbType == KEYBOARD_PASSWORD)
    {
		if(encoderValue>0){
            keyboardNext();
        }else if(encoderValue<0){
            keyboardPrev();
        }
		
		if(encoderDirChange==1){
			printfS("password: dir: %x, %x, char: %x", lastencoderDirection, encoderDirection, btn.value );
			keyboardAppend(btn.value);
            keyboardEvent = KEYBOARD_EVENT_CHANGE;
		}
			
        if(encoderEvent == ENCODER_EVENT_CLICK)  //单击确认
        {
            //keyboardAppend(btn.value);
            keyboardEvent = KEYBOARD_EVENT_OK;
        }
    }
    else
    {
        if(encoderValue>0)
        {
            keyboardNext();
        }
        else if(encoderValue<0)
        {
            keyboardPrev();
        }

        if(encoderEvent == ENCODER_EVENT_CLICK)
        {
            switch(btn.value)
            {
                case BUTTON_BACK:
                    keyboardEvent = KEYBOARD_EVENT_BACK;
                    break;
                case BUTTON_CLOSE:
                    keyboardEvent = KEYBOARD_EVENT_CLOSE;
                    break;
                case BUTTON_OK:
                    keyboardEvent = KEYBOARD_EVENT_OK;
                    break;
                case BUTTON_DELETE:
                    keyboardDelete();
                    keyboardEvent = KEYBOARD_EVENT_CHANGE;
                    break;
                case BUTTON_CLEAR:
                    keyboardClear();
                    keyboardEvent = KEYBOARD_EVENT_CHANGE;
                    break;
                case BUTTON_CAPS:
                    keyboardEvent = KEYBOARD_EVENT_CAPS;
                    break;
                default:
                    keyboardAppend(btn.value);
                    keyboardEvent = KEYBOARD_EVENT_CHANGE;
                    break;
            }
        }
    }

    return keyboardEvent;
}
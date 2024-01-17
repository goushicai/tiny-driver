/**
 * 菜单页
 *
 * */

#include "viewAction.h"

ActionOption actionOption;
KeyboardOption keyboardOption;

Menu curentAction;

uiText inputOption, errorOption;
int8_t encoderlastValue;
int8_t maxCharCount = 0;
int16_t minValue,maxValue;

char errorMsg[13];
char errorMsgLength = 12;

char * getActionValue(uint16_t addr, DateType dType, uint8_t dLen)
{
    return getSystemOption(addr);
}

//获取操作页参数
ActionOption getActionOption(Menu menu)
{
    actionOption.source = menu.actSource;
    actionOption.address = menu.address;
    actionOption.feedback = menu.feedback;
    actionOption.progress = menu.progress;
	actionOption.readonly = menu.actReadonly;
	actionOption.confirm = menu.actConfirm;
	actionOption.source = menu.actSource;
    actionOption.address = menu.address;
    actionOption.txtId = menu.txtId;
	
	if(actionOption.address > 0){
		if(menu.actSource == 0){
			sprintf(actionOption.defalutValue,"%s",getSystemOption(actionOption.address));
		}
		else{
			sprintf(actionOption.defalutValue,"%s",getActionValue(actionOption.address, actionOption.dataType, actionOption.dataLength));
		}
	}

    actionOption.dataType = menu.actDataType;
    switch(actionOption.dataType)
    {
        case DATATYPE_UINT8:
            actionOption.dataLength = 1;
            break;
        case DATATYPE_UINT16:
            actionOption.dataLength = 2;
            break;
        case DATATYPE_UINT32:
            actionOption.dataLength = 4;
            break;
        case DATATYPE_INT8:
            actionOption.dataLength = 1;
            break;
        case DATATYPE_INT16:
            actionOption.dataLength = 2;
            break;
        case DATATYPE_INT32:
            actionOption.dataLength = 4;
            break;
        case DATATYPE_FLOAT:
            actionOption.dataLength = 4;
            break;
        case DATATYPE_STRING:
            actionOption.dataLength = strlen(actionOption.defalutValue);
            break;
        default :
            break;
    }

    return actionOption;
};

void showActionInputError(){
	//inputOption.bgColor = DANGER_ACTIVE_COLOR;
	//uiShowText(inputOption);
	printfS("showActionInputError: before");
	errorOption.text = errorMsg;
	uiShowText(errorOption);
	
	printfS("showActionInputError: after show error");
	//System_Delay_MS(200);
	
	//inputOption.bgColor = ACTION_INPUT_BG_COLOR;
	//uiShowText(inputOption);
}


//显示标题
void showActionTitle(){
	uiText txtOption = getUiTextInstance();
	
	txtOption.left = ACTION_TITLE_LEFT;
	txtOption.top  = ACTION_TITLE_TOP;
	txtOption.width = ACTION_TITLE_WIDTH;
	txtOption.borderWidth=0;
	txtOption.padding=0;
	txtOption.fontSize = ACTION_TITLE_FONT_SIZE;
	txtOption.color = ACTION_TITLE_COLOR;
	txtOption.bgColor = ACTION_BG_COLOR;
	txtOption.borderColor = ACTION_BG_COLOR;
	txtOption.align = ALIGN_CENTER;
	txtOption.text = (char *) &hzFontText[curentAction.txtId][0];
	
	uiShowText(txtOption);
}

void flushActionInput()
{
    int16_t x,y,val;
    uint8_t percent,len;
	char *txt = getKeyBoardContentString();
	
	//inputOption.align = ALIGN_RIGHT;
	inputOption.text = getKeyBoardContentString();
	uiShowText(inputOption);
	
	//printfS("\r\nflushActionInput: strlen(txt) : %d, maxCharCount: %d, %s",strlen(txt), maxCharCount,txt);
	//输入超长
	if(strlen(txt)> maxCharCount){
		sprintf(( char *)errorMsg,"%s","too long");
		showActionInputError();
		return;
	}
	
	//数值超出范围
	val = (int16_t) (atoi(txt));
	//printfS("\r\nflushActionInput: val: %d, minVal : %d, maxVal : %d",val, keyboardOption.minVal,keyboardOption.maxVal);
	
	if(keyboardOption.minVal !=0 && keyboardOption.maxVal !=0 && keyboardOption.maxVal>keyboardOption.minVal){
		if(val > curentAction.maxVal || val < curentAction.minVal){
			sprintf(( char *)errorMsg,"%s","out of range");
			showActionInputError();
			return;
		}
	}
	
	//显示进度条
    if(actionOption.progress >0 &&  keyboardOption.kbType ==KEYBOARD_NONE)
    {
        percent  = (int16_t)((double)(val - keyboardOption.minVal)* 100 /(double) (keyboardOption.maxVal - keyboardOption.minVal)+0.5);
		printfS("\r\nflushActionInput: progress: %d,val: %d, range: %d ",percent, val, keyboardOption.maxVal-keyboardOption.minVal);
        showProgressWater(percent,SUCCESS_ACTIVE_COLOR,ACTION_BG_COLOR);//显示进度条
		showActionTitle();
    }
};

//显示操作页
void showActionView(Menu menu)
{
	
	uiClear(ACTION_BG_COLOR);
	
    actionOption = getActionOption(menu);
    keyboardOption = getKeyboardOption(menu);
	
	curentAction = menu;
	
	inputOption = getUiTextInstance();
	inputOption.left 		= ACTION_INPUT_LEFT;
	inputOption.top  		= ACTION_INPUT_TOP;
	inputOption.fontSize 	= ACTION_INPUT_FONT_SIZE;
	inputOption.color 		= ACTION_INPUT_COLOR;
	inputOption.bgColor 	= ACTION_INPUT_BG_COLOR;
	inputOption.borderColor = ACTION_INPUT_BORDER_COLOR;
	inputOption.borderWidth = ACTION_INPUT_BORDER_WIDTH;
	inputOption.padding 	= ACTION_INPUT_PADDING;
	inputOption.width 		= ACTION_INPUT_WIDTH;
	
	errorOption = getUiTextInstance();
	errorOption.left 		= ACTION_ERROR_LEFT;
	errorOption.top  		= ACTION_ERROR_TOP;
	errorOption.fontSize 	= ACTION_ERROR_FONT_SIZE;
	errorOption.color 		= ACTION_ERROR_COLOR;
	errorOption.bgColor 	= ACTION_ERROR_BG_COLOR;
	errorOption.borderColor = ACTION_ERROR_BORDER_COLOR;
	errorOption.borderWidth = ACTION_ERROR_BORDER_WIDTH;
	errorOption.padding 	= ACTION_ERROR_PADDING;
	errorOption.width 		= ACTION_ERROR_WIDTH;
	
	if(menu.actDataLength>0){
		//inputOption.width = inputOption.fontSize * menu.actDataLength;
		maxCharCount = menu.actDataLength;
	}else{
		//inputOption.width = ACTION_INPUT_WIDTH;
		maxCharCount = ACTION_INPUT_WIDTH/inputOption.fontSize;
	}
	
	if(actionOption.readonly == 0){
		//显示键盘
		showKeyboard(keyboardOption);
	}
	
	//显示标题
    showActionTitle();

    //显示原有值
	printfS("showActionView: defalutValue: %s",actionOption.defalutValue);
    setKeyBoardContent(actionOption.defalutValue);
    inputOption.text = actionOption.defalutValue;
	uiShowText(inputOption);
}

void saveAction()
{
    uint8_t result;
    int32_t val = getKeyBoardContentUInt32();
    if(actionOption.source==0)
    {
        result = setSystemOption(actionOption.txtId, val);
        if(result!=0)
        {
            failTwkinle(ACTION_BG_COLOR);
        }
    }
    else if(actionOption.source == 1)
    {
        result = 0;
        if(result!=0)
        {
            failTwkinle(ACTION_BG_COLOR);
        }
    }
}

//读取操作页事件
enumViewEvent getActionViewEvent()
{
    int8_t encoderValue,encoderEvent;
	
    enumViewEvent actionEvent = VIEW_EVENT_NONE;
    enumKeyboardEvent keyboardEvent ;
	
	if(actionOption.readonly == 1){
		encoderEvent= getKeyVal();
		clrKeyVal();
		if(encoderEvent== ENCODER_EVENT_DOUBLE_CLICK){
			actionEvent = VIEW_EVENT_BACK ;
		}
	}else{
		keyboardEvent = getKeyboardEvent(); //读取键盘事件
		switch(keyboardEvent)
		{
			case KEYBOARD_EVENT_CHANGE:
				flushActionInput() ;
				break;
			case KEYBOARD_EVENT_BACK:
				actionEvent = VIEW_EVENT_BACK ;
				break;
			case KEYBOARD_EVENT_OK:
				saveAction() ;
				actionEvent = VIEW_EVENT_BACK ;
				break;

			default:
				break;
		}
	}

    return actionEvent;
}
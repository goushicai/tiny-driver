/**
 * 密码页
 *
 * */

#include "uiPassword.h"

char userPassword[PASSWORD_MAX_LENGTH];
char adminPassword[PASSWORD_MAX_LENGTH];
char superPassword[PASSWORD_MAX_LENGTH];

enumPasswordViewType verifiedType; //密码验证类型,0 普通验证,1修改密码
uint8_t passwordAuthFlag = 0;// 密码验证通过标识
uiText title, input;

void getUserPassword(){
	sprintf(userPassword,"%s","123456");
}
void getAdminPassword(){
	sprintf(adminPassword,"%s","888888");
}

void getSuperPassword(){
	sprintf(superPassword,"%s","230827");
}
void showPasswordTitle(){
	title.fontSize = PASSWORD_TITLE_FONT_SIZE;
	title.color = PASSWORD_TITLE_COLOR;
	title.bgColor = PASSWORD_BG_COLOR;
	input.bgColor = PASSWORD_INPUT_BG_COLOR;
	
	title.align = ALIGN_CENTER;
	title.width = PASSWORD_TITLE_WIDTH;
	title.left = PASSWORD_TITLE_LEFT;
	title.top = PASSWORD_TITLE_TOP;

	if(verifiedType == 1){
		title.text = (char *) &hzFontText[31][0]; //旧密码
	}else{
		title.text = (char *) &hzFontText[30][0]; //密码
	}
	uiShowText(title);
}
void showPasswordInput(){
	input = getUiTextInstance();
	
	input.fontSize = PASSWORD_INPUT_FONT_SIZE;
	input.color = PASSWORD_INPUT_COLOR;
	input.bgColor = PASSWORD_INPUT_BG_COLOR;
	input.width = PASSWORD_TITLE_WIDTH;
	input.align = ALIGN_CENTER;
	input.borderColor = PASSWORD_INPUT_BORDER_COLOR;
	input.borderWidth = PASSWORD_INPUT_BORDER_WIDTH;
	input.left = PASSWORD_INPUT_LEFT;
	input.top = PASSWORD_INPUT_TOP;
	input.text = "";
	uiShowText(input);
}


void showPasswordView(enumPasswordViewType type){
	uiClear(PASSWORD_BG_COLOR);
	
	verifiedType = type;
	
	clearPasswordAuthFlag();
	
	//显示密码键盘
	KeyboardOption kbOpt ;
	kbOpt.kbType = KEYBOARD_PASSWORD;
	showKeyboard(kbOpt);
	
	//获取密码
	getUserPassword();
	getSuperPassword();
	
	showPasswordTitle();
	showPasswordInput();
}

void showPasswordInputError(){
	input.bgColor = PASSWORD_INPUT_ERROR_COLOR;
	uiShowText(input);
}

void clearPasswordInputError(){
	input.bgColor = PASSWORD_INPUT_BG_COLOR;
	uiShowText(input);
}

void flushPasswordActionInput()
{
	char *txt = getKeyBoardContentString();
	
	//printfS("\r\nflushActionInput: strlen(txt) : %d, maxCharCount: %d, %s",strlen(txt), maxCharCount,txt);
	//输入超长
	if(strlen(txt)> PASSWORD_MAX_LENGTH){
		showPasswordInputError();
		return;
	}
	clearPasswordInputError();
	input.borderColor = PASSWORD_INPUT_BORDER_COLOR;
	input.text = txt;
	uiShowText(input);
}

//检查密码,0x01-0x07值为成功,其它为失败
uint8_t checkPassword(){
	passwordAuthFlag = 0;
	
	//检查用户密码
	if(strcmp(input.text,userPassword)==0 ){
		passwordAuthFlag = 1;
	}else if(strcmp(input.text,adminPassword)==0){
		passwordAuthFlag = 2;
	}else if(strcmp(input.text,superPassword)==0){
		passwordAuthFlag = 4;
	}
	
    return passwordAuthFlag;
}

uint8_t getPasswordAuthFlag(){
	return passwordAuthFlag;
}

void clearPasswordAuthFlag(){
	passwordAuthFlag = 0;
}

//修改密码
uint8_t updatePassword(){
	return 0;
}

enumViewEvent getPasswordViewEvent()
{
    enumViewEvent event = VIEW_EVENT_NONE;
	enumKeyboardEvent keyboardEvent = getKeyboardEvent(); //读取键盘事件
	int8_t encoderEvent= getKeyVal();
	
	if(encoderEvent== ENCODER_EVENT_DOUBLE_CLICK)       //退回到上级菜单
    {
		return VIEW_EVENT_BACK;
    }
	
    switch(keyboardEvent)
    {
        case KEYBOARD_EVENT_CHANGE:
            flushPasswordActionInput() ;
            break;
        case KEYBOARD_EVENT_BACK:
            event = VIEW_EVENT_BACK ;
            break;
        case KEYBOARD_EVENT_OK:
			if(verifiedType == PASSWORD_AUTH){ //验证密码
				if(checkPassword() == 0){
					showPasswordInputError();
					event = PASSWORD_EVENT_INVALID ;
				}else{
					event = PASSWORD_EVENT_PASS ;
					input.borderColor = SUCCESS_COLOR;
					uiShowText(input);
				}
			}else { //todo 修改密码
				if(verifiedType==PASSWORD_UPDATE_USER){//修改用户密码
					if(updatePassword() == 0){
						event = PASSWORD_EVENT_UPDATEED;
					}else{
						event = PASSWORD_EVENT_ERROR ;
						input.bgColor = DANGER_COLOR;
						uiShowText(input);
					}
				}       
            break;
        default:
            break;
		}
	}
	
	return event;
}

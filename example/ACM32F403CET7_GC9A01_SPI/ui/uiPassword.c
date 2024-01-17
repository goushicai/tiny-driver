/**
 * ����ҳ
 *
 * */

#include "uiPassword.h"

char userPassword[PASSWORD_MAX_LENGTH];
char adminPassword[PASSWORD_MAX_LENGTH];
char superPassword[PASSWORD_MAX_LENGTH];

enumPasswordViewType verifiedType; //������֤����,0 ��ͨ��֤,1�޸�����
uint8_t passwordAuthFlag = 0;// ������֤ͨ����ʶ
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
		title.text = (char *) &hzFontText[31][0]; //������
	}else{
		title.text = (char *) &hzFontText[30][0]; //����
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
	
	//��ʾ�������
	KeyboardOption kbOpt ;
	kbOpt.kbType = KEYBOARD_PASSWORD;
	showKeyboard(kbOpt);
	
	//��ȡ����
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
	//���볬��
	if(strlen(txt)> PASSWORD_MAX_LENGTH){
		showPasswordInputError();
		return;
	}
	clearPasswordInputError();
	input.borderColor = PASSWORD_INPUT_BORDER_COLOR;
	input.text = txt;
	uiShowText(input);
}

//�������,0x01-0x07ֵΪ�ɹ�,����Ϊʧ��
uint8_t checkPassword(){
	passwordAuthFlag = 0;
	
	//����û�����
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

//�޸�����
uint8_t updatePassword(){
	return 0;
}

enumViewEvent getPasswordViewEvent()
{
    enumViewEvent event = VIEW_EVENT_NONE;
	enumKeyboardEvent keyboardEvent = getKeyboardEvent(); //��ȡ�����¼�
	int8_t encoderEvent= getKeyVal();
	
	if(encoderEvent== ENCODER_EVENT_DOUBLE_CLICK)       //�˻ص��ϼ��˵�
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
			if(verifiedType == PASSWORD_AUTH){ //��֤����
				if(checkPassword() == 0){
					showPasswordInputError();
					event = PASSWORD_EVENT_INVALID ;
				}else{
					event = PASSWORD_EVENT_PASS ;
					input.borderColor = SUCCESS_COLOR;
					uiShowText(input);
				}
			}else { //todo �޸�����
				if(verifiedType==PASSWORD_UPDATE_USER){//�޸��û�����
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

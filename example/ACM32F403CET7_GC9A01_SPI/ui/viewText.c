#include "viewText.h"

uint16_t viewRows=0,viewCols=0,startRow=0,totalRows=0,textLength=0;
uiText singleLineText;
char textLineBuffer[TEXT_VIEW_MAX_COLS];
uint32_t textAddr;
enumFontSize fontSize = TEXT_VIEW_FONT_SIZE;

void clearTextLineBuffer(){
	uint8_t i=0;
	for(i = 0;i<TEXT_VIEW_MAX_COLS;i++){
		textLineBuffer[i] = '\0';
	}
}

void writeTextLine(char * text){
	singleLineText.text = text;
	//printfS("\r\nwriteTextLine: rows:%d, left: %d, top: %d, text: %s, fontSize: %d",startRow, singleLineText.left,singleLineText.top,text,fontSize);
	uiShowText(singleLineText);
	
	singleLineText.left = TEXT_VIEW_LEFT;
	singleLineText.top += fontSize;
	clearTextLineBuffer();
}


//获取文本的行数
uint16_t getTextRows(char *text, uint8_t colSize){
	
	uint16_t len,idx = 0,rows=0,cols=0;
	len = strlen(text);
	char ch;
	
	while(idx < len){
		ch = *(text + idx) ;
		
		if(ch == '\r' || ch == '\n'){ //换行符
			idx ++;
			cols = 0;
			rows ++;
			continue;
		}
		
		if(ch & 0x80 ){ //汉字
			idx +=2;
			cols +=2;
		}else{
			idx ++;
			cols ++;
			
			if(cols ==1 && ch == ' '){
				cols --; // 删除行首空格
			}
		}
			
		if(cols >=  colSize){ //新的一行
			cols = 0;
			rows++;
		}
	}
	
	if(cols >0){ //最后未满一行的数据
		rows++;
	}
	return rows;
	
}

void showPrevRow(){
	singleLineText.fontSize = FONT_SIZE_24;
	singleLineText.left = 5;
	singleLineText.top = SCREEN_CENTER_Y - singleLineText.fontSize/2;
	singleLineText.color = TEXT_VIEW_COLOR;
	singleLineText.bgColor = TEXT_VIEW_BG_COLOR;
	singleLineText.width = singleLineText.fontSize/2;
	//singleLineText.align = ALIGN_LEFT;
	singleLineText.text = "<";
	
	uiShowText(singleLineText);
}

void showNextRow(){
	singleLineText.fontSize = FONT_SIZE_24;
	singleLineText.left = SCREEN_WIDTH - singleLineText.fontSize/2 - 5;
	singleLineText.top = SCREEN_CENTER_Y - singleLineText.fontSize/2;
	singleLineText.color = TEXT_VIEW_COLOR;
	singleLineText.bgColor = TEXT_VIEW_BG_COLOR;
	singleLineText.width = singleLineText.fontSize/2;
	//singleLineText.align = ALIGN_LEFT;
	singleLineText.text = ">";
	
	uiShowText(singleLineText);
}
void clearPrevRow(){
	uiFillRectangle(10,SCREEN_CENTER_Y - FONT_SIZE_16/2, FONT_SIZE_16/2,FONT_SIZE_16, TEXT_VIEW_BG_COLOR);
}

void clearNextRow(){
	uiFillRectangle(SCREEN_CENTER_X-110,SCREEN_CENTER_Y - FONT_SIZE_16/2, FONT_SIZE_16/2,FONT_SIZE_16, TEXT_VIEW_BG_COLOR);
}

//从指定行起来显示多行文本
void showTextFromRow(uint8_t fromRow){
	char ch;
	char *text = (char *) textAddr;
	uint16_t idx,rows=0,cols=0;
	
	uiClear(TEXT_VIEW_BG_COLOR);
	
	clearTextLineBuffer();
	viewRows = (TEXT_VIEW_WIDTH)/fontSize;
	viewCols = (TEXT_VIEW_HEIGHT)/(fontSize/2);
	
	viewRows = viewRows < 1 ? 1: viewRows; //每页可视行数至少为1
	viewCols = viewCols < 1 ? 2: viewCols; //每页可视列数至少为1
	
	if(viewCols >= TEXT_VIEW_MAX_COLS){ //每页可见列数若大于超过设定的最大值,强制修改为最大值
		viewCols = TEXT_VIEW_MAX_COLS - 1;
	}
	
	totalRows = getTextRows(text, viewCols);
	
	if(fromRow > 0){
		showPrevRow(); //显示上一行的标识
	}else{
		//clearPrevRow();
	}
	
	if(fromRow < totalRows - viewRows){
		showNextRow(); //显示下一行的标识
	}else{
		//clearNextRow();
	}
		
	singleLineText.left = TEXT_VIEW_LEFT;
	singleLineText.top = TEXT_VIEW_TOP;
	singleLineText.width = TEXT_VIEW_WIDTH;
	singleLineText.fontSize = fontSize;
	
	idx = fromRow * viewCols;
	
	while(rows < viewRows){
		ch = *(text + idx) ;
		if(ch == '\r' || ch == '\n'){ //换行符
			writeTextLine(textLineBuffer);
			cols = 0; rows++;
			idx ++;
		}else{
			textLineBuffer[cols ++] =  ch;
			if(ch & 0x80 ){ //汉字
				textLineBuffer[cols ++] =  *(text + idx+1) ;
				idx +=2;
			}else{
				idx +=1;
			}
			
			if(cols ==1 && ch == ' '){
				cols --; // 删除行首空格
			}
			
			if(cols >=  viewCols){ //显示一行
				writeTextLine(textLineBuffer);
				cols = 0;rows++;
			}
		}
		
		if( idx >= textLength){
			if(cols > 0){
				writeTextLine(textLineBuffer);
				cols = 0; rows++;
			}
			break;
		}
	}
}

void scrollUp(){
	//向上滚动,文本总行数大于页面显示行数,且当前行不是首页,可见
	if(totalRows > viewRows && startRow > 0 ){
		startRow --;
		showTextFromRow(startRow);
	}
}

void scrollDown(){ //向下滚动,文本总行数大于页面显示行数,且当前页未显示完,可见
	if(totalRows > viewRows &&  startRow < totalRows - viewRows ){
		startRow ++ ;
		showTextFromRow(startRow);
	}
}

void showTextView(char *text){
	uiClear(TEXT_VIEW_BG_COLOR);
	
	textAddr = (uint32_t )(text);	
	textLength = strlen(text);
	
	singleLineText.left = TEXT_VIEW_LEFT;
	singleLineText.top = TEXT_VIEW_TOP;
	singleLineText.fontSize = fontSize;
	singleLineText.color = TEXT_VIEW_COLOR;
	singleLineText.bgColor = TEXT_VIEW_BG_COLOR;
	singleLineText.width = TEXT_VIEW_WIDTH;
	singleLineText.align = ALIGN_LEFT;
	
	startRow = 0;
	
	
	showTextFromRow(startRow);
}

void TextViewChangeFontSize(){
	if(fontSize == FONT_SIZE_16){
		fontSize = FONT_SIZE_24;
	}else if(fontSize == FONT_SIZE_24){
		fontSize = FONT_SIZE_32;
	}else if(fontSize == FONT_SIZE_32){
		fontSize = FONT_SIZE_16;
	}else{
		fontSize = TEXT_VIEW_FONT_SIZE;
	}
	startRow = 0;
	showTextFromRow(startRow);
}
//获取页页事件
enumViewEvent getTextViewEvent()
{
    int8_t encoderValue,encoderEvent;

    enumViewEvent event = VIEW_EVENT_NONE;
    
	encoderValue = getEncoderVal();
    encoderEvent= getKeyVal();
	
	clrKeyVal();
	clrEncoderVal();
	
	if(encoderEvent== ENCODER_EVENT_DOUBLE_CLICK) {      //退回到上级菜单
		event = VIEW_EVENT_BACK;
    }else if(encoderEvent== ENCODER_EVENT_RELEASE){
		event = TEXT_EVENT_CHANGE_FONT;
	}
	
	if(encoderValue > 0){ //向下滚动
        event = TEXT_EVENT_SCROLL_DOWN;
    }else if(encoderValue < 0){
        event = TEXT_EVENT_SCROLL_UP;
    }
    return event;
}
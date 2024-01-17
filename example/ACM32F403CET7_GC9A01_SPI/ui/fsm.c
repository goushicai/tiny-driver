#include "fsm.h"
/**
	键盘,菜单页,操作页等,各有相应的事件

	事件分组与处理方式
		事件分为两级,组件事件,状态事件
		组件事件在组件中定义,并由在状态中处理
		状态事件在页面中产生,在状态机中处理

*/
uint16_t idelTime = 0; 		//空闲时间
uint8_t isShowView=0; 		//页面是否已经切换
uint8_t ErrorCode = 0; 		//错误代码
uint8_t idelTimeFlag = 0;


FSM_STATE lastState;		//上个状态
FSM_STATE currentState;		//当前状态
enumViewEvent fsmViewEvent;	//页面的事件
Menu currentMenu={0, 0,0,0,  0,0,0,  0,0,0,0,  0,0,  0,0,0,0,0,  0,0,0,  0,  0,0,0};

void setFsmState(FSM_STATE state )
{
    lastState = currentState ;
    currentState = state;

    clrKeyVal();
    clrEncoderVal();

    idelTime = 0; //清除空闲时间
    isShowView = 0; //页面未切换
	
	//currentMenu.parentId = 0;
	printfS("\r\nsetFsmState: from %d  to %d", lastState, currentState);
}

//检查错误标志
void checkError()
{
    if(ErrorCode > 0 && FSM_VIEW_ERROR != currentState)
    {
		setFsmState(FSM_VIEW_ERROR);
    }
}

//检查定时器
void checkTimer(flag)
{	
	if(flag > 0){
        clearRtcFlag();
        idelTime ++;
		idelTimeFlag = 0;
		
		if(idelTime >IDEL_TIMEOUT){
			clearPasswordAuthFlag();
		}
    }
}


void startState()
{	
	char s1[16],s2[16],s3[16];
	
	isShowView = 1;
    //显示初始化界面
    showStartView();
    updateStartCount();
	
	//HAL_EFlash_ErasePage(SYSTEM_OPTION_PAGE * EFLASH_PAGE_SIZE); 
	//HAL_EFlash_ErasePage(SYSTEM_MENU_PAGE * EFLASH_PAGE_SIZE); 
	
	//重置系统参数
	if(getOptionInitFlag()==0){
		printfS("starting: reset system option\n");
		resetSystemOption();
	}
	
	//重置菜单
	if(getMenuInitFlag()==0){
		printfS("starting: reset system menu\n");
		resetMenuData();
	}
	
    if(loadMenu() == true){  //自检成功,转到菜单页面
		//printfS("\nclearSystemOption");
		//clearSystemOption();
		/*
		printfS("\nSetOption: %d,%d,%d", setSystemOption(ADDR_KEY_DOUBLE_CLICK_INTERVAL,501),
									setSystemOption(ADDR_KEY_PRESS_DURATION,602),
									setSystemOption(ADDR_CHART_UPDATE_DURATION,4));
		sprintf(s1,"%s",getSystemOption(ADDR_KEY_DOUBLE_CLICK_INTERVAL));
		sprintf(s2,"%s",getSystemOption(ADDR_KEY_PRESS_DURATION));
		sprintf(s3,"%s",getSystemOption(ADDR_CHART_UPDATE_DURATION));
		printfS("\n GetOption: %s,%s,%s",s1,s2,s3);

		*/
	
        //显示进度条
		showStartProgress();
		setFsmState(FSM_VIEW_MENU);
    }
    else{ //否则转向错误页
        setFsmState(FSM_VIEW_ERROR);
    }
}

void menuState()
{
    if(isShowView == 0)
    {
		showImgMenuView(currentMenu.parentId);
        isShowView = 1;
    }
	
    //fsmViewEvent = getMenuViewEvent();
	fsmViewEvent = getImgMenuViewEvent();
	
    switch(fsmViewEvent)
    {
        case MENU_EVENT_ACTIVE_CHANGE://激活菜单改变
            idelTime = 0; 
            break;

        case MENU_EVENT_FIND_ACTION:
			currentMenu = getActiveMenu();
			setFsmState(FSM_VIEW_ACTION);
		
            break;
		case PASSWORD_EVENT_PASS:
			currentMenu = getActiveMenu();
			if(currentMenu.menuType == 0){
				showSubMenu(currentMenu.id);
				idelTime=0;
			}else if(currentMenu.menuType == 1){
				setFsmState(FSM_VIEW_ACTION);
			}
		
            break;
        case MENU_EVENT_FIND_MENU:
			currentMenu = getActiveMenu();
			//showMenuView(currentMenu);
			showImgMenuView(currentMenu.id);
			idelTime=0;
            break;
			
		case MENU_EVENT_FIND_TEXT:
			currentMenu = getActiveMenu();
            setFsmState(FSM_VIEW_TEXT);
            break;
		case MENU_EVENT_FIND_PIC:
			currentMenu = getActiveMenu();
            setFsmState(FSM_VIEW_PIC);
            break;
        case MENU_EVENT_FIND_CHART:
			currentMenu = getActiveMenu();
			printfS("\nMENU_EVENT_FIND_CHART: menuId: %d ",currentMenu.id);
            setFsmState(FSM_VIEW_CHART);
            break;
		
		case MENU_EVENT_FIND_CHANNEL:
			currentMenu = getActiveMenu();
			printfS("\nMENU_EVENT_FIND_CHANNEL: menuId: %d ",currentMenu.id);
            setFsmState(FSM_VIEW_CHANNEL);
            break;
		
        case VIEW_EVENT_BACK:
			currentMenu = getMenuById(currentMenu.parentId);
            showImgMenuView(currentMenu.parentId);
            break;
        default:
            if(idelTime >= IDEL_TIMEOUT){  //长时间空闲转入空闲页
                setFsmState(FSM_VIEW_IDEL);
            }
            break;
    }
}

void actionState()
{
    if(isShowView == 0)
    {
        showActionView(currentMenu);
        isShowView = 1;
    }
	
    fsmViewEvent = getActionViewEvent();
	
    switch(fsmViewEvent)
    {
        case ACTION_EVENT_OK:
			currentMenu = getMenuById(currentMenu.parentId);
			setFsmState(FSM_VIEW_MENU);
            break;

        case VIEW_EVENT_BACK:
            currentMenu = getMenuById(currentMenu.parentId);
            setFsmState(FSM_VIEW_MENU);
            break;

        case VIEW_EVENT_ERROR:
            setFsmState(FSM_VIEW_ERROR);
            break;

        default:
            if(idelTime >= IDEL_TIMEOUT)  //长时间空闲转入空闲页
            {
                setFsmState(FSM_VIEW_IDEL);
            }
            break;
    }
}
//显示文本
void textState()
{
	
	char str[200];
    if(isShowView == 0)
    {
		sprintf(str,"%s%s%s%s,\r%s%s%s%s,\r%s%s%s%s%s%s%s%s%s%s%s%s", 
													hzFontText[0],hzFontText[1],hzFontText[2],hzFontText[3],
													hzFontText[4],hzFontText[5],hzFontText[6],hzFontText[7],
													hzFontText[8],hzFontText[9],hzFontText[10],hzFontText[11],
													hzFontText[12],hzFontText[13],hzFontText[14],hzFontText[15],
													hzFontText[16],hzFontText[17],hzFontText[18],hzFontText[19]);
        printfS("\r\ncurrentState: textState, %s", str );
        showTextView(str);
        isShowView = 1;
    }
	
	System_Delay_MS(10);
    
	fsmViewEvent = getTextViewEvent();
	switch(fsmViewEvent){
		case TEXT_EVENT_SCROLL_UP: 
			scrollUp();
			break;
		case TEXT_EVENT_SCROLL_DOWN: 
			scrollDown();
			break;
		case TEXT_EVENT_CHANGE_FONT: 
			TextViewChangeFontSize();
			break;
		case VIEW_EVENT_BACK:
			currentMenu = getMenuById(currentMenu.parentId);
            setFsmState(FSM_VIEW_MENU);
		
		default:
            if(idelTime >= IDEL_TIMEOUT){ //长时间空闲转入空闲页
                setFsmState(FSM_VIEW_IDEL);
            }
            break;
	}
}


void picState()
{	
	if(isShowView == 0)
    {
        showPicView();
        isShowView = 1;
		printfS("picState");
    }
	
	System_Delay_MS(10);
	fsmViewEvent = getPicViewEvent();
	
	switch(fsmViewEvent){
		case VIEW_EVENT_BACK:
			currentMenu = getMenuById(currentMenu.parentId);
            setFsmState(FSM_VIEW_MENU);
		default:
            if(idelTime >= IDEL_TIMEOUT){ //长时间空闲转入空闲页
                setFsmState(FSM_VIEW_IDEL);
            }
            break;
	}
}

//空闲状态,内容可以调整,目前显示时钟
void idelState()
{
    if(isShowView == 0)
    {
        showIdelView();
        isShowView = 1;
    }
	
	fsmViewEvent = getIdelViewEvent();
	
	switch(fsmViewEvent){
		case VIEW_EVENT_BACK: 
			setFsmState(lastState);
			break;
		
		default:
            break;
	}
	if(getRtcFlag() == 1){
		showDateTime();
	}
}

void channelState(){
	if(isShowView == 0) {
		showChannelView(0);
        isShowView = 1;
    }
	
	if(idelTimeFlag){
		ChannelTimeInc();
		showChannelText();
	}
	
	fsmViewEvent = getChannelViewEvent();
	switch(fsmViewEvent){
		case VIEW_EVENT_BACK: //返回到菜单页
			currentMenu = getMenuById(currentMenu.parentId);
            setFsmState(FSM_VIEW_MENU);
			break;
		case CHANNEL_EVENT_CHANGE: 
			
			break;
		case CHANNEL_EVENT_SHOW_CHART: 
			setFsmState(FSM_VIEW_CHART);
			break;
		default:
			if(idelTime > 3){
				idelTime = 0;
				nextChannel();
			}
			break;
	}
}
void chartState(){
	int8_t val = 0;
	ChartTypeDef co;
	
	if(isShowView == 0) {
		co.chartType =0;
		co.maxValue = 80;
		co.minValue = -80;
		co.duration = 1; 
		co.xLabel= "T"; 
		co.yLabel = "V";
		co.gridInterval=40;
        showChartView(co);
        isShowView = 1;
    }
	
	fsmViewEvent = getChartViewEvent();
	switch(fsmViewEvent){
		case VIEW_EVENT_BACK: //从图表页返回到菜单页
			currentMenu = getMenuById(currentMenu.parentId);
            setFsmState(FSM_VIEW_MENU);
			break;
		case CHART_EVENT_CLEAR: 
			
			break;
		default: 
			if(co.duration == 0){
				if(idelTime >= IDEL_TIMEOUT){ //长时间空闲转入空闲页
					setFsmState(FSM_VIEW_IDEL);
				}
			}
            break;
	}
	if(co.duration > 0){
		if(idelTimeFlag){
			val = sin((double)idelTime/8) * 80;
			flushLineChart(val);
		}
	}
}


void errorState()
{	
	if(isShowView == 0)
    {
        showErrorCode(ErrorCode);
        isShowView = 1;
    }
	
	System_Delay_MS(10);
	
	if(ErrorCode != 0){
		setFsmState(lastState);
	}
}

void fsmInit(){
	lastState = FSM_STARTING;
    currentState = FSM_STARTING;
	fsmViewEvent = VIEW_EVENT_NONE;
	ErrorCode = 0;
	currentMenu.parentId = 0;
}
void fsmRun()
{
    fsmInit();
	clearRtcFlag();
	
    while(1)
    {
		idelTimeFlag = getRtcFlag();
		
        switch(currentState)
        {
            case FSM_STARTING:
                startState();
                break;

            case FSM_VIEW_MENU:
                menuState();
                break;

            case FSM_VIEW_ACTION:
                actionState();
                break;
			
			case FSM_VIEW_TEXT:
                textState();
                break;
			case FSM_VIEW_PIC:
                picState();
                break;
			case FSM_VIEW_CHART:
                chartState();
                break;
			
			case FSM_VIEW_CHANNEL:
                channelState();
                break;
			
            case FSM_VIEW_IDEL:
                idelState();
                break;

            case FSM_VIEW_ERROR:
                errorState();
                break;

            default:
                break;
        }
        checkTimer(idelTimeFlag);//时间相关, 运行时间,空闲时间等

        checkError();//检查错误标识
    }
}

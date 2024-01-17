/**
 * 状态机
 *
 * 以页面作为状态,通过事件切换状态
 *
 * */

#ifndef __FSM_H__
#define __FSM_H__

#include "viewStart.h"
#include "viewError.h"
#include "viewMenu.h"
#include "viewMenu2.h"
#include "viewAction.h"
#include "viewIdel.h"
#include "viewText.h"
#include "viewPic.h"
#include "viewChart.h"
#include "viewChannel.h"
#include "encoder.h"
#include "timer.h"

void fsmRun();

#endif  //__FSM_H__
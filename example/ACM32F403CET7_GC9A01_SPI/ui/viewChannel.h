#ifndef __VIEW_CHANNEL_H__
#define __VIEW_CHANNEL_H__

#include "uiDisplay.h"
#include "encoder.h"
#include "event.h"
#include "pic.h"
#include "stdlib.h"
#define CHANNEL_DEFAULT_BG_COLOR 	0x1082
#define CHANNEL_ACTIVE_BG_COLOR 	0x44e8 

#define CHANNEL_TITLE_LEFT         60
#define CHANNEL_TITLE_TOP          60
#define CHANNEL_TITLE_WIDTH        96
#define CHANNEL_TITLE_FONT_SIZE    32
#define CHANNEL_TITLE_FONT_COLOR   0xFFFF

#define CHANNEL_TEXT_LEFT          40
#define CHANNEL_TEXT_TOP           100
#define CHANNEL_TEXT_WIDTH         160
#define CHANNEL_TEXT_FONT_SIZE     24
#define CHANNEL_TEXT_FONT_COLOR    0xFFFF

void showChannelView(uint8_t channel);

void showChannelText();

void ChannelTimeInc();

void nextChannel();

void prevChannel();

enumViewEvent getChannelViewEvent();


#endif  //__VIEW_CHANNEL_H__

#ifndef __LED_H__
#define __LED_H__

#include "stm32f1xx_hal.h"
#include "gpio.h"

//led ´ò¿ª
void ledOn(void);
//led ¹Ø±Õ
void ledOff(void);

//ledÉÁË¸
void ledTwinkle(uint16_t count,uint16_t duration);

#endif /*__LED_H__ */


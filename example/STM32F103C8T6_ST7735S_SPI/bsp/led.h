#ifndef __LED_H__
#define __LED_H__

#include "stm32f1xx_hal.h"
#include "gpio.h"

//led ��
void ledOn(void);
//led �ر�
void ledOff(void);

//led��˸
void ledTwinkle(uint16_t count,uint16_t duration);

#endif /*__LED_H__ */


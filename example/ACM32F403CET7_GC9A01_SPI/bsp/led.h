#ifndef __LED_H__
#define __LED_H__

#include "ACM32Fxx_HAL.h"
#include "gpio_config.h"

//led ��
void ledOn(void);
//led �ر�
void ledOff(void);

//led��˸
void ledTwinkle(uint16_t count,uint16_t duration);

#endif /*__LED_H__ */


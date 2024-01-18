#include "led.h"

//led 打开
void ledOn(void){
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_CLEAR);
}
//led 关闭
void ledOff(void){
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
}

//led闪烁
void ledTwinkle(uint16_t count,uint16_t duration){
	//先关闭
	ledOff();
	while(count -- >0){
		ledOn();
		System_Delay_MS(duration);
		ledOff();
		System_Delay_MS(duration);
	}
}

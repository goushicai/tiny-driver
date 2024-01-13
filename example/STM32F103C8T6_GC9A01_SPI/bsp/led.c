#include "led.h"

//led 打开, pa8 低电平有效,正点原子 M48Z
void ledOn(void){
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
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
		HAL_Delay(duration);
		ledOff();
		HAL_Delay(duration);
	}
}

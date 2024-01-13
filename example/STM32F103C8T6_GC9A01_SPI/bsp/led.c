#include "led.h"

//led ��, pa8 �͵�ƽ��Ч,����ԭ�� M48Z
void ledOn(void){
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
}
//led �ر�
void ledOff(void){
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
}

//led��˸
void ledTwinkle(uint16_t count,uint16_t duration){
	//�ȹر�
	ledOff();
	while(count -- >0){
		ledOn();
		HAL_Delay(duration);
		ledOff();
		HAL_Delay(duration);
	}
}

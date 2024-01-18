#include "led.h"

//led ��
void ledOn(void){
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_CLEAR);
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
		System_Delay_MS(duration);
		ledOff();
		System_Delay_MS(duration);
	}
}

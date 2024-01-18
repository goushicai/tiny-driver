#include "gpio.h"

/**
[TO_MODITY]

请根据实际的需要初始化LCD相关的GPIO
*/
void lcdGpioInit(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.Pin = LCD_BLK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Alternate = GPIO_FUNCTION_0;
    HAL_GPIO_Init(LCD_BLK_PORT, &GPIO_InitStruct);
	
    GPIO_InitStruct.Pin = LCD_DC_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Alternate = GPIO_FUNCTION_0;
    HAL_GPIO_Init(LCD_DC_PORT, &GPIO_InitStruct);
/*
	// SPI2_CS 的 GPIO 初始化  在HAL_SPI_MspInit()中
    GPIO_InitStruct.Pin = LCD_CS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Alternate = GPIO_FUNCTION_0;
    HAL_GPIO_Init(LCD_CS_PORT, &GPIO_InitStruct);
*/
    GPIO_InitStruct.Pin = LCD_RST_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Alternate = GPIO_FUNCTION_0;
    HAL_GPIO_Init(LCD_RST_PORT, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(LCD_BLK_PORT, LCD_BLK_PIN, GPIO_PIN_CLEAR);
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_CLEAR);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_CLEAR);
    HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN, GPIO_PIN_SET);
}

void ledGpioInit(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	HAL_GPIO_WritePin(LED_PORT,LED_PIN, GPIO_PIN_CLEAR);
	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Alternate = GPIO_FUNCTION_0;
	
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);	
}

void GPIO_Init(void){
	
    lcdGpioInit();
	
	ledGpioInit();
}

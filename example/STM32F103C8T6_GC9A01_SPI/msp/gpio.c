#include "gpio.h"

/**
[TO_MODITY]

请根据实际的需要初始化LCD相关的GPIO
*/
void lcdGpioInit(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
    if(LCD_BLK_PORT == GPIOA || LCD_DC_PORT == GPIOA || LCD_CS_PORT == GPIOA ||LCD_RST_PORT == GPIOA ){
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }

    if(LCD_BLK_PORT == GPIOA || LCD_DC_PORT == GPIOB || LCD_CS_PORT == GPIOB ||LCD_RST_PORT == GPIOB){
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }

    if(LCD_BLK_PORT == GPIOA || LCD_DC_PORT == GPIOC || LCD_CS_PORT == GPIOC ||LCD_RST_PORT == GPIOC){
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }

    if(LCD_BLK_PORT == GPIOA || LCD_DC_PORT == GPIOD || LCD_CS_PORT == GPIOD ||LCD_RST_PORT == GPIOD){
        __HAL_RCC_GPIOD_CLK_ENABLE();
    }

	HAL_GPIO_WritePin(LCD_BLK_PORT, LCD_BLK_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST_PIN, GPIO_PIN_SET);
	
	GPIO_InitStruct.Pin = LCD_BLK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_BLK_PORT, &GPIO_InitStruct);
	
    GPIO_InitStruct.Pin = LCD_DC_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_DC_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_CS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_CS_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_RST_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_RST_PORT, &GPIO_InitStruct);
	
}

void ledGpioInit(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	if(LED_PORT == GPIOA){
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }

    if(LED_PORT == GPIOB){
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }

    if(LED_PORT == GPIOC){
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }

    if(LED_PORT == GPIOD){
        __HAL_RCC_GPIOD_CLK_ENABLE();
    }
	
	HAL_GPIO_WritePin(LED_PORT,LED_PIN, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	
	
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);	
}

void GPIO_Init(void){
	
    lcdGpioInit();
	
	ledGpioInit();
}

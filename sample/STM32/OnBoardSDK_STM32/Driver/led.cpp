#include "led.h"


void Led_Gpio_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	  	 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       
	GPIO_Init(GPIOC,&GPIO_InitStructure);  

  led_off;	
}


#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h"

#define led_toggle   GPIO_ToggleBits(GPIOC , GPIO_Pin_1);
#define led_off      GPIO_SetBits(GPIOC    , GPIO_Pin_1);

extern void Led_Gpio_Config(void);


#endif
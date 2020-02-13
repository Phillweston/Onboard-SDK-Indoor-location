#ifndef __BUZZER_H
#define __BUZZER_H
#include "stm32f4xx.h"

extern void Buzzer_Init(uint16_t arr, uint16_t psc);
extern void buzzer_on(uint16_t psc, uint16_t pwm);
extern void buzzer_off(void);

#endif

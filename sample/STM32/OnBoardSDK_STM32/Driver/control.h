#ifndef __CONTROL_H
#define __CONTROL_H
#include "stm32f4xx.h"

extern void control_task(void);
extern void calculate_position(void);
extern void control_mode(void);

#endif
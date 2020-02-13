#ifndef __PID_H
#define __PID_H
#include "stm32f4xx.h"
#include "global_variable.h"

extern fp32 Position_Type_PID(Pid_error *sptr, Pid_parameter *PID, fp32 NowData, fp32 Point);

#endif

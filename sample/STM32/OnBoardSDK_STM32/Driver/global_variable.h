#ifndef __GLOBAL_VARIABLE_H
#define __GLOBAL_VARIABLE_H
#include "stm32f4xx.h"


typedef float  fp32;
typedef double fp64;

#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }
		
#define LimitMin(input, min)   \
    {                          \
        if (input < min)       \
        {                      \
            input = min;       \
        }                      \
    }		
		
#define rc_deadline_limit(input, output, dealine)        \
    {                                                    \
        if ((input) > (dealine) || (input) < -(dealine)) \
        {                                                \
            (output) = (input);                          \
        }                                                \
        else                                             \
        {                                                \
            (output) = 0;                                \
        }                                                \
    }
		
#define HISTORY_DATA_LENGTH  20
#define RC_DEAD              1000
#define SDK_MODE             10000          //遥控使用的是LB2，控制SDK模式的杆子打到SDK模式数值是10000，用其他遥控的要自己看下自己的遥控数据
#define REMOTE_MODE          0              //与上面同理，遥控模式是0
#define CONTROL_TIMEOUT      400            
#define REMOTE_TO_ANGLE      1000.0f        //LB2的遥感是-10000 - 10000 ， 把遥控控制飞机姿态角度限制在-10度 - 10度，建议角度限制小一点，比较稳定       
#define REMOTE_TO_VEL        200.0f         //YAW轴的控制是采用角速度，使用角度控制，有点迟钝，可以自己使用角度控制，在模拟器中试试效果，推荐使用角速度控制。
#define REMOTE_TO_VERTICAL   7000.0f        //高度也是采用速度控制，比较灵活，注意API的速度单位是M来着，所以把速度限制在正负一米多内
#define ANGLE_MAX            15.0f          //光流飞行刹车以及定点悬停的最大角度为15度
#define PI                   180
#define RX_BUF_NUM           50u		

typedef struct{
	 unsigned char Loop_Task_1000HZ;
	
	 unsigned char Loop_Task_250HZ;
	
	 unsigned char Loop_Task_100HZ;
	
	 unsigned char Loop_Task_50HZ;
	
	 unsigned char Loop_Task_10HZ;
	
	 unsigned char Loop_Task_1HZ;
	
	 unsigned char Loop_Task_Receiver;
	
}_Task_flag;

typedef struct pid_error
{
	float SumError;
	short int  LastError;	
	short int  PrevError;	
	short int  LastData;	
} Pid_error;


typedef struct pid_parameter
{
	float p;
	float i;
	float d;
	float i_limit;
	float err_limit;
	float output_limit;
}Pid_parameter;

typedef struct _Flow             
{
	bool     DETERMINED;   
	uint8_t  OF_QUALITY;
	uint8_t  SUM;
	uint8_t  OF_STATE; 
	int16_t  OF_DX;
	int16_t  OF_DY;
	int16_t  OF_DX2;
	int16_t  OF_DY2;
	int16_t  OF_DX2FIX;
	int16_t  OF_DY2FIX;
  uint16_t OF_ALT;
	uint16_t OF_ALT2;
	uint16_t HISTORY_OF_ALT[HISTORY_DATA_LENGTH];
	uint16_t TAR_ALT;
	int16_t  ALT_RATE_OF_CHANGE;
	float DISTANCE_X;
	float DISTANCE_Y;
	float TAR_POSITION_X;
	float TAR_POSITION_Y;
	float TAR_SPEED_X;
	float TAR_SPEED_Y;
	float TAR_SPEED_Z;
	float TAR_ANGLE_PITCH;
	float TAR_ANGLE_ROLL;
}_Flow;

extern _Flow  Flow;


#endif
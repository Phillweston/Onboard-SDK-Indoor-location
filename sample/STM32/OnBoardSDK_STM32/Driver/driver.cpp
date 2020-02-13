#include "driver.h"
#include "main.h"

static void Nvic_Init();

void Underlying_initialization()
{
    Nvic_Init();
	  Timer_Condfig();
	  Led_Gpio_Config();
	  Buzzer_Init(200 , 90);
	  Optical_Usart_Init();
	  UsartConfig();
}


void Loop_Task(void)
{
    static uint64_t tick[4] = {0};	  
	  
	  if (v->protocolLayer->getDriver()->getTimeStamp() - tick[0] >= 4)    // 250HZ 控制指令频率需要高点，不然出现飞机迟钝现象
		{
			   control_task();
			   tick[0] = v->protocolLayer->getDriver()->getTimeStamp();
		}

	  if (v->protocolLayer->getDriver()->getTimeStamp() - tick[1] >= 10)   //100HZ
		{
			   calculate_position();
			   tick[1] = v->protocolLayer->getDriver()->getTimeStamp();
		}
		
	  if (v->protocolLayer->getDriver()->getTimeStamp() - tick[2] >= 20)   //50HZ
		{
			   Sub_50HZ_Information_Task();
			   //Communicate_ano(); 
			   tick[2] = v->protocolLayer->getDriver()->getTimeStamp();
		}		
	  
	  if (v->protocolLayer->getDriver()->getTimeStamp() - tick[3] >= 1000)  //1HZ
		{
			   control_mode();
			   tick[3] = v->protocolLayer->getDriver()->getTimeStamp();
		}				
 	
}

static void Nvic_Init()
{						 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
//	  NVIC_InitTypeDef  NVIC_InitStructure_TIM3;
//		NVIC_InitStructure_TIM3.NVIC_IRQChannel                     = TIM3_IRQn;
//		NVIC_InitStructure_TIM3.NVIC_IRQChannelCmd                  = ENABLE;
//		NVIC_InitStructure_TIM3.NVIC_IRQChannelPreemptionPriority   = 0X02;
//		NVIC_InitStructure_TIM3.NVIC_IRQChannelSubPriority          = 0X00;
//		NVIC_Init(&NVIC_InitStructure_TIM3);	
	
	  NVIC_InitTypeDef NVIC_InitStructure_USART1;
		NVIC_InitStructure_USART1.NVIC_IRQChannel                   = USART1_IRQn;
		NVIC_InitStructure_USART1.NVIC_IRQChannelCmd                = ENABLE;
		NVIC_InitStructure_USART1.NVIC_IRQChannelPreemptionPriority = 0X00;
		NVIC_InitStructure_USART1.NVIC_IRQChannelSubPriority        = 0X00;
		NVIC_Init(&NVIC_InitStructure_USART1);	
  
		NVIC_InitTypeDef NVIC_InitStructure_USART3;
		NVIC_InitStructure_USART3.NVIC_IRQChannelPreemptionPriority = 0X03;
		NVIC_InitStructure_USART3.NVIC_IRQChannelSubPriority        = 0X00;
		NVIC_InitStructure_USART3.NVIC_IRQChannel                   = USART3_IRQn;
		NVIC_InitStructure_USART3.NVIC_IRQChannelCmd                = ENABLE;
		NVIC_Init(&NVIC_InitStructure_USART3);

		NVIC_InitTypeDef NVIC_InitStructure_USART2;
		NVIC_InitStructure_USART2.NVIC_IRQChannelPreemptionPriority = 0X01;
		NVIC_InitStructure_USART2.NVIC_IRQChannelSubPriority        = 0X00;
		NVIC_InitStructure_USART2.NVIC_IRQChannel                   = USART2_IRQn;
		NVIC_InitStructure_USART2.NVIC_IRQChannelCmd                = ENABLE;
		NVIC_Init(&NVIC_InitStructure_USART2);	
}


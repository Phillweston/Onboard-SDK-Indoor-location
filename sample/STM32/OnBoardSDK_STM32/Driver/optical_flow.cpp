#include "optical_flow.h"
#include "main.h"


_Flow  Flow;
uint8_t flow_time;
static uint8_t rx_data[RX_BUF_NUM];


void Optical_Usart_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	  DMA_InitTypeDef   DMA_InitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9 , GPIO_AF_USART1); // tx
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); // rx

		USART_InitStructure.USART_BaudRate            = 500000;
		USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits            = USART_StopBits_1;
		USART_InitStructure.USART_Parity              = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;

		USART_Init(USART1, &USART_InitStructure);
		
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
		
		USART_DMACmd(USART1 , USART_DMAReq_Rx , ENABLE);
 
    DMA_DeInit(DMA2_Stream5);
    DMA_InitStructure.DMA_Channel            = DMA_Channel_4;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (USART1->DR);
		DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)rx_data;
		DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralToMemory;
		DMA_InitStructure.DMA_BufferSize         = RX_BUF_NUM;
		DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
   	DMA_InitStructure.DMA_Priority           = DMA_Priority_VeryHigh;
		DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;
		DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_Full;
		DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;
		DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream5 , &DMA_InitStructure);
 
    DMA_ClearFlag(DMA2_Stream5 , DMA_FLAG_TCIF5);
		DMA_ITConfig(DMA2_Stream5 , DMA_IT_TC , ENABLE);
		DMA_Cmd(DMA2_Stream5 , ENABLE);
		USART_Cmd(USART1, ENABLE);
}


//光流数据接收后分析  具体看光流的数据手册
static void optical_data_analysis(uint8_t *data_buf , uint8_t num)
{
    int8_t	Length = num;
	  uint8_t sum = 0;
	  static uint8_t receiver_flow_flag = 0;
	  static uint8_t _data_len = 0;
	  static uint64_t last_time = 0;
	  
	  while(Length > 0)
		{
			  switch(receiver_flow_flag)
				{
				case 0:	
					  if (data_buf[num - Length] == 0xAA && receiver_flow_flag == 0)
						{
						    receiver_flow_flag = 1;
                Length -= 1;							
						}
						else
						{
							  receiver_flow_flag = 0;
						    Length = 0;	
						}
				    break;
				case 1:		
					  if (data_buf[num - Length] == 0x22 && receiver_flow_flag == 1)
						{
							  receiver_flow_flag = 2;
							  Length -= 1;
						}
						else
						{
							  receiver_flow_flag = 0;
						    Length = 0;	
						}
						break;
				case 2:
					  if (receiver_flow_flag == 2)
						{
							  receiver_flow_flag = 3;
							  Length -= 1;
						}					  
            break;
        case 3:
					  if (data_buf[num - Length] == 0X51 && receiver_flow_flag == 3)
						{
							  receiver_flow_flag = 4;  
						}
						else if (data_buf[num - Length] == 0X52 && receiver_flow_flag == 3)
						{
						    receiver_flow_flag = 5;	
						}
						Length -= 1;
            break;
				case 4:
						_data_len = data_buf[num - Length];	
						for (uint8_t i = num - Length	- 4 ; i < num - Length	+ 16 ; i++)
						{
								 sum += data_buf[i];
						}					
						if (!(sum == data_buf[num - Length + _data_len + 1]))		return;	
						Flow.OF_DX2 = (int16_t)((data_buf[num - Length + 3] << 8)| data_buf[num - Length + 4]);	
						Flow.OF_DY2 = (int16_t)((data_buf[num - Length + 5] << 8)| data_buf[num - Length + 6]);	
						Flow.OF_DX2FIX = (int16_t)((data_buf[num - Length + 7] << 8)| data_buf[num - Length + 8]);	
						Flow.OF_DY2FIX = (int16_t)(data_buf[num - Length + 9] << 8| data_buf[num - Length + 10]);	
						Flow.OF_QUALITY = data_buf[num - Length + 15];
						flow_time = (v->protocolLayer->getDriver()->getTimeStamp() - last_time) * 0.001f;
						last_time = v->protocolLayer->getDriver()->getTimeStamp();
						Flow.DISTANCE_X += flow_time * Flow.OF_DX2FIX;
						Flow.DISTANCE_Y += flow_time * Flow.OF_DY2FIX;                								
						Length -= _data_len + 2;
						receiver_flow_flag = 0;
            break;						
				case 5:		
						_data_len = data_buf[num - Length];	
						if (data_buf[num - Length + 1] == 0)
						{
								static uint8_t length = 0;
							  //存历史激光高度数据，求变化率
								Flow.OF_ALT = (uint16_t)(data_buf[num - Length + 2]|data_buf[num - Length + 3]);		
								Flow.HISTORY_OF_ALT[length] = Flow.OF_ALT;
								length ++;
								if (length == HISTORY_DATA_LENGTH)
										length = 0;
								Flow.ALT_RATE_OF_CHANGE = abs(Flow.OF_ALT	- Flow.HISTORY_OF_ALT[length]);										
						}
						else if (data_buf[num - Length + 1] == 1)
						{
								Flow.OF_ALT2 = (uint16_t)(data_buf[num - Length + 2]|data_buf[num - Length + 3]);	
						}
						Length -= _data_len + 2;
						receiver_flow_flag = 0;								
            break;
        default:
					  receiver_flow_flag = 0;
				    Length = 0;
            break;					
				} 				
	  }
}


extern "C" void USART1_IRQHandler(void)
{
	  static uint8_t buff_length = 0;
	  if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
	  {
		    USART_ReceiveData(USART1);
		    USART_ClearFlag(USART1, USART_FLAG_ORE);
	  }
	  if (USART_GetITStatus(USART1 , USART_IT_IDLE) != RESET)
		{
			  DMA_Cmd(DMA2_Stream5 , DISABLE);
			  DMA_ClearFlag(DMA2_Stream5 , DMA_FLAG_TCIF5); 
        buff_length = RX_BUF_NUM - DMA_GetCurrDataCounter(DMA2_Stream5);
			  optical_data_analysis(rx_data , buff_length-1);
			  DMA_SetCurrDataCounter(DMA2_Stream5 , 50);
			  DMA_Cmd(DMA2_Stream5 , ENABLE);
        USART_ReceiveData(USART1);			
		}	
}


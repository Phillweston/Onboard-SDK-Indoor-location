/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
  * 作者   ：匿名科创
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
 * 描述    ：光流数据解析
**********************************************************************************/
#include "Ano_OF.h"
#include "Ano_FcData.h"

/*
OF_STATE :
0bit: 1-高度有效；0-高度无效
1bit: 1-光流有效；0-光流无效
2bit: 1-高度融合有效；0-高度融合无效
3bit: 1-光流融合有效；0-光流融合无效
4:0
7bit: 1
*/

uint8_t		OF_STATE,OF_QUALITY;
int8_t		OF_DX,OF_DY;
int16_t		OF_DX2,OF_DY2,OF_DX2FIX,OF_DY2FIX;
uint16_t	OF_ALT,OF_ALT2;
int16_t		OF_GYR_X,OF_GYR_Y,OF_GYR_Z;
int16_t		OF_GYR_X2,OF_GYR_Y2,OF_GYR_Z2;
int16_t		OF_ACC_X,OF_ACC_Y,OF_ACC_Z;
int16_t		OF_ACC_X2,OF_ACC_Y2,OF_ACC_Z2;
float		OF_ATT_ROL,OF_ATT_PIT,OF_ATT_YAW;
float		OF_ATT_S1,OF_ATT_S2,OF_ATT_S3,OF_ATT_S4;

void AnoOF_DataAnl(uint8_t *data_buf,uint8_t num);

static uint8_t _datatemp[50];
static u8 _data_cnt = 0;
static u8 anoof_data_ok;

void AnoOF_DataAnl_Task(u8 dT_ms)
{
//	if(anoof_data_ok)
//	{
//		anoof_data_ok = 0;
//		AnoOF_DataAnl(_datatemp,_data_cnt+5);
//	}
	
	AnoOF_Check(dT_ms);
}


//AnoOF_GetOneByte是初级数据解析函数，串口每接收到一字节光流数据，调用本函数一次，函数参数就是串口收到的数据
//当本函数多次被调用，最终接收到完整的一帧数据后，会自动调用数据解析函数AnoOF_DataAnl
void AnoOF_GetOneByte(uint8_t data)
{

	static u8 _data_len = 0;
	static u8 state = 0;
	
	if(state==0&&data==0xAA)
	{
		state=1;
		_datatemp[0]=data;
	}
	else if(state==1&&data==0x22)	//源地址
	{
		state=2;
		_datatemp[1]=data;
	}
	else if(state==2)			//目的地址
	{
		state=3;
		_datatemp[2]=data;
	}
	else if(state==3)			//功能字
	{
		state = 4;
		_datatemp[3]=data;
	}
	else if(state==4)			//长度
	{
		state = 5;
		_datatemp[4]=data;
		_data_len = data;
		_data_cnt = 0;
	}
	else if(state==5&&_data_len>0)
	{
		_data_len--;
		_datatemp[5+_data_cnt++]=data;
		if(_data_len==0)
			state = 6;
	}
	else if(state==6)
	{
		state = 0;
		_datatemp[5+_data_cnt]=data;
		AnoOF_DataAnl(_datatemp,_data_cnt+6);//anoof_data_ok = 1 ;//
	}
	else
		state = 0;
}
//AnoOF_DataAnl为光流数据解析函数，可以通过本函数得到光流模块输出的各项数据
//具体数据的意义，请参照匿名光流模块使用手册，有详细的介绍
static u8 of_check_f[2];
static u16 of_check_cnt[2] = { 10000,10000 };
void AnoOF_Check(u8 dT_ms)
{
	for(u8 i=0;i<2;i++)
	{
		if(of_check_f[i] == 0 )
		{
			if(of_check_cnt[i]<10000)
			{
				of_check_cnt[i] += dT_ms;	
			}
		}
		else
		{
			of_check_cnt[i] = 0;
		}
		

		of_check_f[i] = 0;
	}
	
	
	if(of_check_cnt[0] > 1000 || of_check_cnt[1] > 1000)
	{
		sens_hd_check.of_ok = 0;
	}
	else
	{
		sens_hd_check.of_ok = 1;
	}
		

	
}

void AnoOF_DataAnl(uint8_t *data_buf,uint8_t num)
{
	u8 sum = 0;
	for(u8 i=0;i<(num-1);i++)
		sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		return;		
	
	if(*(data_buf+3)==0X51)//光流信息
	{
		if(*(data_buf+5)==0)//原始光流信息
		{
			OF_STATE 		= *(data_buf+6);
			OF_DX  		= *(data_buf+7);
			OF_DY  		= *(data_buf+8);
			OF_QUALITY  	= *(data_buf+9);
		}
		else if(*(data_buf+5)==1)//融合后光流信息
		{
			OF_STATE 		= *(data_buf+6);
			OF_DX2		= (int16_t)(*(data_buf+7)<<8)|*(data_buf+8) ;
			OF_DY2		= (int16_t)(*(data_buf+9)<<8)|*(data_buf+10) ;
			OF_DX2FIX	= (int16_t)(*(data_buf+11)<<8)|*(data_buf+12) ;
			OF_DY2FIX	= (int16_t)(*(data_buf+13)<<8)|*(data_buf+14) ;
			//OF_DIS_X = (int16_t)(*(data_buf+15)<<8)|*(data_buf+16) ;
			//OF_DIS_Y = (int16_t)(*(data_buf+17)<<8)|*(data_buf+18) ;
			OF_QUALITY  	= *(data_buf+19);
			
			of_check_f[0] = 1;
		}
	}
	if(*(data_buf+3)==0X52)//高度信息
	{
		if(*(data_buf+5)==0)//原始高度信息
		{
			OF_ALT = (uint16_t)(*(data_buf+6)<<8)|*(data_buf+7) ;
			of_check_f[1] = 1;
		}
		else if(*(data_buf+5)==1)//融合后高度信息
		{
			OF_ALT2 = (uint16_t)(*(data_buf+6)<<8)|*(data_buf+7) ;
		}
	}
}


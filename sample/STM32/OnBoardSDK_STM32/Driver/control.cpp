#include "control.h"
#include "main.h"


Pid_error err_position_x;
Pid_error err_position_y;
Pid_error err_position_z;
Pid_error err_speed_x;
Pid_error err_speed_y;
Pid_parameter  Pid_position_x = {  1.0   , 0 , 0    , 0  , 45.0       };
Pid_parameter  Pid_position_y = {  1.0   , 0 , 0    , 0  , 45.0       };
Pid_parameter  Pid_position_z = {  0.020 , 0 , 0    , 0  , 10.0       };
Pid_parameter  Pid_speed_x    = {  0.12  , 0 , 0.05 , 0  , 60.0 , 15.0};
Pid_parameter  Pid_speed_y    = {  0.12  , 0 , 0.05 , 0  , 60.0 , 15.0};


//onboard sdk 发送控制飞机位置指令
void control_task()
{    
	  static bool     sdk_mode         = 0;
	  static uint64_t tick             = 0;
	  static fp32     target_angle_yaw = 0.0f;
    //用遥控摇杆开启或者关闭onboard sdk模式	  注意要夺回控制权或者放弃控制权  方便飞机出问题可以用遥控器退出开发者模式  将光流距离清除
	  if (rc_data.mode == SDK_MODE && sdk_mode == false)
		{
		    sdk_mode = true;
			  v->obtainCtrlAuthority();
			  Flow.DISTANCE_X = Flow.DISTANCE_Y = 0;
		}
		else if (rc_data.mode == REMOTE_MODE && sdk_mode == true)
		{
        sdk_mode = false;	
			  v->releaseCtrlAuthority();
		}
		//飞机没有起飞前把当前激光或者超声波高度数据记为目标高度(飞行过程中实际上靠飞机上的气压计，第三方测距只是防止飞机室内飞行)
		if (v->subscribe->getValue<Telemetry::TOPIC_STATUS_FLIGHT>() ==  VehicleStatus::FlightStatus::STOPED)
	  {
        Flow.TAR_ALT = Flow.OF_ALT;
		}
		//动油门遥感后要重新确定第三方测距模块目标高度，方便飞行维持高度稳定
		if ((rc_data.throttle != 0) && v->subscribe->getValue<Telemetry::TOPIC_STATUS_FLIGHT>() !=  VehicleStatus::FlightStatus::STOPED)
		{			
        tick = v->protocolLayer->getDriver()->getTimeStamp();	
        Flow.DETERMINED = false;			
		}
		else
		{
			  //动油门回中一段时间后再记下目标高度，先让飞机垂直方向上的速度降低，不然立马确认高度反应可能有点剧烈
			  if (v->protocolLayer->getDriver()->getTimeStamp() - tick > CONTROL_TIMEOUT && Flow.DETERMINED == false)                                                                                                                                                 
		    {
					  Flow.TAR_ALT = Flow.OF_ALT2;
					  Flow.DETERMINED = true;
				}	
		}
    //控制无人机位置 可以看下控制位置以及高度的API，可以根据自己的需求去修改API，不动方向遥感的时候，水平位置使用光流数据进行闭环控制，不动油门的时候，用激光或者超声波进行垂直方向的速度控制	
		if ((rc_data.pitch != 0 || rc_data.roll != 0) && v->subscribe->getValue<Telemetry::TOPIC_STATUS_FLIGHT>() ==  VehicleStatus::FlightStatus::IN_AIR)
		{
		
         if (rc_data.throttle != 0)			
             v->control->attitudeAndVertPosCtrl( rc_data.roll/REMOTE_TO_ANGLE , -rc_data.pitch/REMOTE_TO_ANGLE , rc_data.yaw/REMOTE_TO_VEL , rc_data.throttle/REMOTE_TO_VERTICAL);	
         else 
 			       v->control->attitudeAndVertPosCtrl( rc_data.roll/REMOTE_TO_ANGLE , -rc_data.pitch/REMOTE_TO_ANGLE,  rc_data.yaw/REMOTE_TO_VEL , Flow.TAR_SPEED_Z);	    					 				 
		}
		else if(v->subscribe->getValue<Telemetry::TOPIC_STATUS_FLIGHT>() ==  VehicleStatus::FlightStatus::IN_AIR)
		{
		    //注意光流最终输出的角度要限制好幅度	包括api其他的角度控制。
			  if (rc_data.throttle != 0)
			       v->control->attitudeAndVertPosCtrl( -Flow.TAR_ANGLE_ROLL , -Flow.TAR_ANGLE_PITCH, rc_data.yaw/REMOTE_TO_VEL , rc_data.throttle/REMOTE_TO_VERTICAL);	
        else
 			       v->control->attitudeAndVertPosCtrl( -Flow.TAR_ANGLE_ROLL , -Flow.TAR_ANGLE_PITCH, rc_data.yaw/REMOTE_TO_VEL , Flow.TAR_SPEED_Z);	    					 
		}
}


void calculate_position(void)
{
    static bool     last_rc_pitch  = false; 	  
	  static bool     last_rc_roll   = false; 
	  static uint64_t tick           = 0;
	  static uint8_t  frequency_50HZ = 0;
	  static bool height_change_flag = false;
	  
	  //sdk模式，遥控不在中间的时候，需要置相关标志位，关掉对应轴向的位置控制，回中时，使用光流数据进行刹车  
	  if (rc_data.pitch!= 0)
			  last_rc_pitch = true;
		
	  if (rc_data.roll != 0)
			  last_rc_roll  = true;	
		
	  /*在处于定位模式下时 Flow.DETERMINED == true 说明已经确定激光目标高度  此时飞行过程中，有可能经过一些不平的地方或者小车从下面经过，
	    导致激光数据突变，如果变化超过一定范围（10cm），削弱激光修正高度的比例,不然飞机高度容易不稳定（激光修正的比例系数不能为0，室内气压定高不好）*/
		if ((Flow.ALT_RATE_OF_CHANGE >= 10) && height_change_flag == false && Flow.DETERMINED == true)
		{
		    height_change_flag = true;	
			  Pid_position_z.p   = 0.01f;
		}	 
		
		/*较长时间下方有车子移动，或者经常在不平的地面飞行，那么飞机因为激光修正的削弱，短时间不会出现掉高现象，当垂直的速度稳定一段时间，
		重新确定当前激光高度为目标高度，并且加大激光修正 ，这样可以防止车子停飞机下端或者飞机飞到一些与当前位置高度不同的地方出现高度变化严重现象
		*/
		if (height_change_flag == true && (Flow.ALT_RATE_OF_CHANGE < 10))
		{
		    if (v->protocolLayer->getDriver()->getTimeStamp() - tick > CONTROL_TIMEOUT/2)
				{
				    Pid_position_z.p = 0.020f;	
						height_change_flag = false;
					  Flow.TAR_ALT = Flow.OF_ALT;
				}
		}
		else
		    tick = v->protocolLayer->getDriver()->getTimeStamp();	 	
		
		//高度环，水平位置环采用50HZ执行频率，水平位置的速度环使用100HZ
		frequency_50HZ++;
		if (frequency_50HZ == 2)
		{
			  frequency_50HZ = 0;
			
				Flow.TAR_SPEED_X = Position_Type_PID(&err_position_x , &Pid_position_x , Flow.DISTANCE_X , Flow.TAR_POSITION_X);
				Flow.TAR_SPEED_Y = Position_Type_PID(&err_position_y , &Pid_position_y , Flow.DISTANCE_Y , Flow.TAR_POSITION_Y);
			  if (rc_data.throttle != 0)
				{
            //改变高度的时候，可以把光流的参数改小点，等高度确定再恢复，因为飞机高度变化，会引起光流数据变化 此处没加，需要的可以自己加
					  Flow.DISTANCE_X = Flow.DISTANCE_Y = 0 ;
				}
		    //油门回中并且目标高度确定，用PID输出控制飞机的垂直方向速度，防止飞机掉高严重
				if (rc_data.throttle == 0 && Flow.DETERMINED == 1)
				{
						Flow.TAR_SPEED_Z = Position_Type_PID(&err_position_z , &Pid_position_z , Flow.OF_ALT, Flow.TAR_ALT        );
				}			
			
			
		}
	  /* 方向杆回中的时候，此时用光流的数据进行刹车并且悬停 ，先让飞机停下来，所以把目标速度设置为0，当飞机水平位置移动变慢时，
		   确定一段时间内速度变慢。这时就可以把当前位置记为目标位置 
		*/
		if (last_rc_pitch == true && rc_data.pitch == 0)
		{
			  static uint64_t tick = 0;
			
				Flow.TAR_ANGLE_PITCH = Position_Type_PID(&err_speed_x , &Pid_speed_x , (fp32)Flow.OF_DX2 , 0);
			  if(Flow.OF_DX2 < 20 && Flow.OF_DX2 > -20)
				{
					  if (v->protocolLayer->getDriver()->getTimeStamp() - tick > CONTROL_TIMEOUT/4)
						{
								Flow.DISTANCE_X = 0;
								last_rc_pitch   = false;
								tick = v->protocolLayer->getDriver()->getTimeStamp();
						}
				}
				else
            tick = v->protocolLayer->getDriver()->getTimeStamp(); 
		}
		else
				Flow.TAR_ANGLE_PITCH = Position_Type_PID(&err_speed_x , &Pid_speed_x , (fp32)Flow.OF_DX2 , Flow.TAR_SPEED_X);
		
		if (last_rc_roll == true && rc_data.roll == 0 )  
		{
			  static uint64_t tick = 0;
			
				Flow.TAR_ANGLE_ROLL = Position_Type_PID(&err_speed_y , &Pid_speed_y , (fp32)Flow.OF_DY2 , 0);
				if(Flow.OF_DY2 < 20 && Flow.OF_DY2 > -20)
				{
					  if (v->protocolLayer->getDriver()->getTimeStamp() - tick > CONTROL_TIMEOUT/4)
						{
							Flow.DISTANCE_Y = 0;
							last_rc_roll = false;
							tick = v->protocolLayer->getDriver()->getTimeStamp();
						}
				}
        else
            tick = v->protocolLayer->getDriver()->getTimeStamp();					
		}
		else
				Flow.TAR_ANGLE_ROLL = Position_Type_PID(&err_speed_y , &Pid_speed_y , (fp32)Flow.OF_DY2 , Flow.TAR_SPEED_Y);		
		
}


//通过灯是否闪烁判断此时飞控处于onboard sdk模式还是遥控模式（此处用的是蜂鸣器，比赛建议用比较显眼的灯，方便飞行手判断此时是否处于sdk模式）
void control_mode()
{
    if (control_device.deviceStatus == 2 && control_device.flightStatus == 1)
		{
				buzzer_on( 90 , 100);
		}
		else
		{
		    //判断飞机的状态，一定要注意不在sdk模式要释放控制权，防止自己写的东西出问题，与N3飞控通讯失败，没释放控制权会导致飞机按照你最后发的指令一直执行，导致后面其他不可描述的事情发生	
			  v->releaseCtrlAuthority();             
				buzzer_off();	 
		}
}


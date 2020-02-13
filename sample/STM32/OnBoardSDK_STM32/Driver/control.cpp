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


//onboard sdk ���Ϳ��Ʒɻ�λ��ָ��
void control_task()
{    
	  static bool     sdk_mode         = 0;
	  static uint64_t tick             = 0;
	  static fp32     target_angle_yaw = 0.0f;
    //��ң��ҡ�˿������߹ر�onboard sdkģʽ	  ע��Ҫ��ؿ���Ȩ���߷�������Ȩ  ����ɻ������������ң�����˳�������ģʽ  �������������
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
		//�ɻ�û�����ǰ�ѵ�ǰ������߳������߶����ݼ�ΪĿ��߶�(���й�����ʵ���Ͽ��ɻ��ϵ���ѹ�ƣ����������ֻ�Ƿ�ֹ�ɻ����ڷ���)
		if (v->subscribe->getValue<Telemetry::TOPIC_STATUS_FLIGHT>() ==  VehicleStatus::FlightStatus::STOPED)
	  {
        Flow.TAR_ALT = Flow.OF_ALT;
		}
		//������ң�к�Ҫ����ȷ�����������ģ��Ŀ��߶ȣ��������ά�ָ߶��ȶ�
		if ((rc_data.throttle != 0) && v->subscribe->getValue<Telemetry::TOPIC_STATUS_FLIGHT>() !=  VehicleStatus::FlightStatus::STOPED)
		{			
        tick = v->protocolLayer->getDriver()->getTimeStamp();	
        Flow.DETERMINED = false;			
		}
		else
		{
			  //�����Ż���һ��ʱ����ټ���Ŀ��߶ȣ����÷ɻ���ֱ�����ϵ��ٶȽ��ͣ���Ȼ����ȷ�ϸ߶ȷ�Ӧ�����е����
			  if (v->protocolLayer->getDriver()->getTimeStamp() - tick > CONTROL_TIMEOUT && Flow.DETERMINED == false)                                                                                                                                                 
		    {
					  Flow.TAR_ALT = Flow.OF_ALT2;
					  Flow.DETERMINED = true;
				}	
		}
    //�������˻�λ�� ���Կ��¿���λ���Լ��߶ȵ�API�����Ը����Լ�������ȥ�޸�API����������ң�е�ʱ��ˮƽλ��ʹ�ù������ݽ��бջ����ƣ��������ŵ�ʱ���ü�����߳��������д�ֱ������ٶȿ���	
		if ((rc_data.pitch != 0 || rc_data.roll != 0) && v->subscribe->getValue<Telemetry::TOPIC_STATUS_FLIGHT>() ==  VehicleStatus::FlightStatus::IN_AIR)
		{
		
         if (rc_data.throttle != 0)			
             v->control->attitudeAndVertPosCtrl( rc_data.roll/REMOTE_TO_ANGLE , -rc_data.pitch/REMOTE_TO_ANGLE , rc_data.yaw/REMOTE_TO_VEL , rc_data.throttle/REMOTE_TO_VERTICAL);	
         else 
 			       v->control->attitudeAndVertPosCtrl( rc_data.roll/REMOTE_TO_ANGLE , -rc_data.pitch/REMOTE_TO_ANGLE,  rc_data.yaw/REMOTE_TO_VEL , Flow.TAR_SPEED_Z);	    					 				 
		}
		else if(v->subscribe->getValue<Telemetry::TOPIC_STATUS_FLIGHT>() ==  VehicleStatus::FlightStatus::IN_AIR)
		{
		    //ע�������������ĽǶ�Ҫ���ƺ÷���	����api�����ĽǶȿ��ơ�
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
	  
	  //sdkģʽ��ң�ز����м��ʱ����Ҫ����ر�־λ���ص���Ӧ�����λ�ÿ��ƣ�����ʱ��ʹ�ù������ݽ���ɲ��  
	  if (rc_data.pitch!= 0)
			  last_rc_pitch = true;
		
	  if (rc_data.roll != 0)
			  last_rc_roll  = true;	
		
	  /*�ڴ��ڶ�λģʽ��ʱ Flow.DETERMINED == true ˵���Ѿ�ȷ������Ŀ��߶�  ��ʱ���й����У��п��ܾ���һЩ��ƽ�ĵط�����С�������澭����
	    ���¼�������ͻ�䣬����仯����һ����Χ��10cm�����������������߶ȵı���,��Ȼ�ɻ��߶����ײ��ȶ������������ı���ϵ������Ϊ0��������ѹ���߲��ã�*/
		if ((Flow.ALT_RATE_OF_CHANGE >= 10) && height_change_flag == false && Flow.DETERMINED == true)
		{
		    height_change_flag = true;	
			  Pid_position_z.p   = 0.01f;
		}	 
		
		/*�ϳ�ʱ���·��г����ƶ������߾����ڲ�ƽ�ĵ�����У���ô�ɻ���Ϊ������������������ʱ�䲻����ֵ������󣬵���ֱ���ٶ��ȶ�һ��ʱ�䣬
		����ȷ����ǰ����߶�ΪĿ��߶ȣ����ҼӴ󼤹����� ���������Է�ֹ����ͣ�ɻ��¶˻��߷ɻ��ɵ�һЩ�뵱ǰλ�ø߶Ȳ�ͬ�ĵط����ָ߶ȱ仯��������
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
		
		//�߶Ȼ���ˮƽλ�û�����50HZִ��Ƶ�ʣ�ˮƽλ�õ��ٶȻ�ʹ��100HZ
		frequency_50HZ++;
		if (frequency_50HZ == 2)
		{
			  frequency_50HZ = 0;
			
				Flow.TAR_SPEED_X = Position_Type_PID(&err_position_x , &Pid_position_x , Flow.DISTANCE_X , Flow.TAR_POSITION_X);
				Flow.TAR_SPEED_Y = Position_Type_PID(&err_position_y , &Pid_position_y , Flow.DISTANCE_Y , Flow.TAR_POSITION_Y);
			  if (rc_data.throttle != 0)
				{
            //�ı�߶ȵ�ʱ�򣬿��԰ѹ����Ĳ�����С�㣬�ȸ߶�ȷ���ٻָ�����Ϊ�ɻ��߶ȱ仯��������������ݱ仯 �˴�û�ӣ���Ҫ�Ŀ����Լ���
					  Flow.DISTANCE_X = Flow.DISTANCE_Y = 0 ;
				}
		    //���Ż��в���Ŀ��߶�ȷ������PID������Ʒɻ��Ĵ�ֱ�����ٶȣ���ֹ�ɻ���������
				if (rc_data.throttle == 0 && Flow.DETERMINED == 1)
				{
						Flow.TAR_SPEED_Z = Position_Type_PID(&err_position_z , &Pid_position_z , Flow.OF_ALT, Flow.TAR_ALT        );
				}			
			
			
		}
	  /* ����˻��е�ʱ�򣬴�ʱ�ù��������ݽ���ɲ��������ͣ �����÷ɻ�ͣ���������԰�Ŀ���ٶ�����Ϊ0�����ɻ�ˮƽλ���ƶ�����ʱ��
		   ȷ��һ��ʱ�����ٶȱ�������ʱ�Ϳ��԰ѵ�ǰλ�ü�ΪĿ��λ�� 
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


//ͨ�����Ƿ���˸�жϴ�ʱ�ɿش���onboard sdkģʽ����ң��ģʽ���˴��õ��Ƿ����������������ñȽ����۵ĵƣ�����������жϴ�ʱ�Ƿ���sdkģʽ��
void control_mode()
{
    if (control_device.deviceStatus == 2 && control_device.flightStatus == 1)
		{
				buzzer_on( 90 , 100);
		}
		else
		{
		    //�жϷɻ���״̬��һ��Ҫע�ⲻ��sdkģʽҪ�ͷſ���Ȩ����ֹ�Լ�д�Ķ��������⣬��N3�ɿ�ͨѶʧ�ܣ�û�ͷſ���Ȩ�ᵼ�·ɻ���������󷢵�ָ��һֱִ�У����º��������������������鷢��	
			  v->releaseCtrlAuthority();             
				buzzer_off();	 
		}
}


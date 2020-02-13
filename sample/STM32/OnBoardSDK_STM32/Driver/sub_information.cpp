#include "sub_information.h"
#include "main.h"


static uint8_t pkgIndex;	
static uint8_t pkgIndex1;	
fp32 pitch , roll, yaw;
Telemetry::TypeMap<Telemetry::TOPIC_RC>::type                 rc_data;
Telemetry::TypeMap<Telemetry::TOPIC_QUATERNION>::type         quaternion;
Telemetry::TypeMap<Telemetry::TOPIC_STATUS_FLIGHT>::type      status_flight;
Telemetry::TypeMap<Telemetry::TOPIC_HEIGHT_FUSION>::type      height_fusion;
Telemetry::TypeMap<Telemetry::TOPIC_ACCELERATION_BODY>::type  accel_body;
Telemetry::TypeMap<Telemetry::TOPIC_CONTROL_DEVICE>::type     control_device;
Telemetry::TypeMap<Telemetry::TOPIC_HEIGHT_HOMEPOINT>::type   height_homepoint;
Telemetry::TypeMap<Telemetry::TOPIC_ALTITUDE_FUSIONED>::type  altitude_fusioned;
Telemetry::TypeMap<Telemetry::TOPIC_ALTITUDE_BAROMETER>::type altitude_barometer;
static bool Sub_50HZ_Information_Init();  
static bool Sub_1000HZ_Information_Init();



//订阅N3飞控信息，具体订阅频率看DJI Assistant，可以通过上位机配置订阅信息频率
void Sub_50HZ_Information_Task(void)
{
	  static bool init_ready = false;
	  static bool init_flag  = false;
	  if (init_flag == false)
		{
			 init_ready = Sub_50HZ_Information_Init();
			 init_flag  = true;
		}
	
	  if (init_ready != false)
       //! Start listening to subscribed packages
        v->subscribe->startPackage(pkgIndex);	
		
		rc_data            =  v->subscribe->getValue<Telemetry::TOPIC_RC>();
		height_fusion      = v->subscribe->getValue<Telemetry::TOPIC_HEIGHT_FUSION>();
		altitude_barometer = v->subscribe->getValue<Telemetry::TOPIC_ALTITUDE_BAROMETER>();
		altitude_fusioned  =  v->subscribe->getValue<Telemetry::TOPIC_ALTITUDE_FUSIONED>();
		quaternion         = v->subscribe->getValue<Telemetry::TOPIC_QUATERNION>();	  
		status_flight      = v->subscribe->getValue<Telemetry::TOPIC_STATUS_FLIGHT>();		
		control_device     = v->subscribe->getValue<Telemetry::TOPIC_CONTROL_DEVICE>();
		
		rc_deadline_limit(rc_data.throttle , rc_data.throttle , RC_DEAD);
		rc_deadline_limit(rc_data.pitch    , rc_data.pitch    , RC_DEAD);
		rc_deadline_limit(rc_data.roll     , rc_data.roll     , RC_DEAD);
		rc_deadline_limit(rc_data.yaw      , rc_data.yaw      , RC_DEAD);
		yaw   = toEulerAngle((static_cast<void*>(&quaternion))).z * 57.3f;
  	pitch = toEulerAngle((static_cast<void*>(&quaternion))).x * 57.3f;
	  roll  = toEulerAngle((static_cast<void*>(&quaternion))).y * 57.3f;
}



void Sub_1000HZ_Information_Task(void)
{
	  static bool init_ready = false;
	  static bool init_flag  = false;
	
	  if (init_flag == false)
		{
			 init_ready = Sub_1000HZ_Information_Init();
			 init_flag  = true;
		}
	
	  if (init_ready != false)
       //! Start listening to subscribed packages
        v->subscribe->startPackage(pkgIndex1);		
		
		control_device = v->subscribe->getValue<Telemetry::TOPIC_CONTROL_DEVICE>();
		status_flight  = v->subscribe->getValue<Telemetry::TOPIC_STATUS_FLIGHT>();
}


static bool Sub_50HZ_Information_Init()
{
		if (v->getFwVersion() != Version::M100_31)
		{	
				// Telemetry: Subscribe freq 50 Hz
				pkgIndex                             = 0;
				int                  freq            = 50;
				Telemetry::TopicName topicList50Hz[] = {
					Telemetry::TOPIC_RC , Telemetry::TOPIC_HEIGHT_FUSION ,Telemetry::TOPIC_ALTITUDE_BAROMETER , 
					Telemetry::TOPIC_ALTITUDE_FUSIONED,Telemetry::TOPIC_QUATERNION,Telemetry::TOPIC_STATUS_FLIGHT,
					Telemetry::TOPIC_CONTROL_DEVICE
				};
				int  numTopic        = sizeof(topicList50Hz) / sizeof(topicList50Hz[0]);
				bool enableTimestamp = false;

				bool pkgStatus = v->subscribe->initPackageFromTopicList(
					pkgIndex, numTopic, topicList50Hz, enableTimestamp, freq);
				if (!(pkgStatus))
				{
					return pkgStatus;
				}			
		}
}

	
static bool Sub_1000HZ_Information_Init()
{
		if (v->getFwVersion() != Version::M100_31)
		{	
				// Telemetry: Subscribe to flight status and mode at freq 10 Hz
				pkgIndex                             = 0;
				int                  freq            = 10;
				Telemetry::TopicName topicList1000Hz[] = {
					 Telemetry::TOPIC_STATUS_FLIGHT , Telemetry::TOPIC_CONTROL_DEVICE
				};
				int  numTopic        = sizeof(topicList1000Hz) / sizeof(topicList1000Hz[0]);
				bool enableTimestamp = false;

				bool pkgStatus = v->subscribe->initPackageFromTopicList(
					pkgIndex1, numTopic, topicList1000Hz, enableTimestamp, freq);
				if (!(pkgStatus))
				{
				    return pkgStatus;
				}			
		}	
}

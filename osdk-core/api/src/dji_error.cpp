/** @file dji_error.cpp
 *  @version 3.3
 *  @date April 2017
 *
 *  @brief All DJI OSDK OpenProtocol ACK Error Codes
 *
 *  @Copyright (c) 2016-2017 DJI
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "dji_error.hpp"
// clang-format off
const uint16_t DJI::OSDK::ErrorCode::CommonACK::SUCCESS                = 0x0000;
const uint16_t DJI::OSDK::ErrorCode::CommonACK::KEY_ERROR              = 0xFF00;
const uint16_t DJI::OSDK::ErrorCode::CommonACK::NO_AUTHORIZATION_ERROR = 0xFF01;
const uint16_t DJI::OSDK::ErrorCode::CommonACK::NO_RIGHTS_ERROR        = 0xFF02;
const uint16_t DJI::OSDK::ErrorCode::CommonACK::NO_RESPONSE_ERROR      = 0xFFFF;
const uint8_t  DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_NONE        = 0;
const uint8_t  DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_COMPASS_ABNORMAL = 1;
const uint8_t  DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_ASSISTANT_PROTECTED = 2;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_DEVICE_LOCKED = 3;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_IMU_NEED_ADV_CALIBRATION = 5;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_IMU_SN_ERROR   = 6;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_IMU_PREHEATING = 7;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_COMPASS_CALIBRATING = 8;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_IMU_NO_ATTITUDE = 9;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_NO_GPS_IN_NOVICE_MODE = 10;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_BATTERY_CELL_ERROR = 11;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_BATTERY_COMMUNICATION_ERROR = 12;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_BATTERY_VOLTAGE_TOO_LOW = 13;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_BATTERY_USER_LOW_LAND = 14;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_BATTERY_MAIN_VOL_LOW = 15;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_BATTERY_TEMP_VOL_LOW = 16;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_BATTERY_SMART_LOW_LAND = 17;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_BATTERY_NOT_READY = 18;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RUNNING_SIMULATOR = 19;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_PACK_MODE        = 20;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_IMU_ATTI_LIMIT   = 21;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_NOT_ACTIVATED    = 22;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_IN_FLYLIMIT_AREA = 23;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_IMU_BIAS_LIMIT   = 24;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_ESC_ERROR        = 25;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_IMU_INITING      = 26;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_UPGRADING        = 27;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_HAVE_RUN_SIM     = 28;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_IMU_CALIBRATING  = 29;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_TAKEOFF_TILT_TOO_LARGE = 30;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_31      = 31;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_32      = 32;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_33      = 33;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_34      = 34;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_35      = 35;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_36      = 36;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_37      = 37;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_38      = 38;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_39      = 39;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_40      = 40;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_INVALID_SN       = 41;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_42      = 42;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_43      = 43;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_FLASH_OPERATING  = 44;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GPS_DISCONNECT   = 45;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_INTERNAL_46      = 46;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RECORDER_ERROR   = 47;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_INVALID_PRODUCT  = 48;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_49      = 49;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_50      = 50;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_51      = 51;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_52      = 52;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_53      = 53;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_54      = 54;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_55      = 55;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_56      = 56;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_57      = 57;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_58      = 58;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_59      = 59;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_60      = 60;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_IMU_DISCONNECTED = 61;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RC_CALIBRATING   = 62;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RC_CALI_DATA_OUT_RANGE = 63;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RC_QUIT_CALI = 64;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RC_CENTER_OUT_RANGE = 65;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RC_MAP_ERROR = 66;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_WRONG_AIRCRAFT_TYPE = 67;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_SOME_MODULE_NOT_CONFIGURED = 68;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_69 = 69;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_70 = 70;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_71 = 71;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_72 = 72;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_73 = 73;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_NS_ABNORMAL = 74;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_TOPOLOGY_ABNORMAL = 75;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RC_NEED_CALI     = 76;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_INVALID_FLOAT    = 77;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_M600_BAT_TOO_FEW = 78;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_M600_BAT_AUTH_ERR = 79;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_M600_BAT_COMM_ERR = 80;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_M600_BAT_DIF_VOLT_LARGE_1 = 81;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_BATTERY_BOLTAHGE_DIFF_82 = 82;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_INVALID_VERSION = 83;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GIMBAL_GYRO_ABNORMAL = 84;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GIMBAL_ESC_PITCH_NO_DATA = 85;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GIMBAL_ESC_ROLL_NO_DATA = 86;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GIMBAL_ESC_YAW_NO_DATA = 87;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GIMBAL_FIRM_IS_UPDATING = 88;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GIMBAL_OUT_OF_CONTROL = 89;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GIMBAL_PITCH_SHOCK = 90;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GIMBAL_ROLL_SHOCK = 91;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GIMBAL_YAW_SHOCK = 92;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_IMU_CALI_SUCCESS = 93;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_TAKEOFF_EXCEPTION = 94;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_ESC_STALL_NEAR_GOUND = 95;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_ESC_UNBALANCE_ON_GRD = 96;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_ESC_PART_EMPTY_ON_GRD = 97;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_ENGINE_START_FAILED = 98;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_AUTO_TAKEOFF_LAUNCH_FAILED = 99;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_ROLL_OVER_ON_GRD = 100;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_BAT_VERSION_ERR = 101;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RTK_INITING     = 102;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RTK_FAIL_TO_INIT = 103;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_104 = 104;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_105 = 105;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_106 = 106;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_107 = 107;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_108 = 108;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_RESERVED_109 = 109;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::START_MOTOR_FAIL_MOTOR_STARTED = 110;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_INTERNAL_111    = 111;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_ESC_CALIBRATING = 112;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GPS_SIGNATURE_INVALID = 113;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GIMBAL_CALIBRATING = 114;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_FORCE_DISABLE = 115;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::TAKEOFF_HEIGHT_EXCEPTION = 116;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_ESC_NEED_UPGRADE = 117;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_GYRO_DATA_NOT_MATCH = 118;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_APP_NOT_ALLOW = 119;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_COMPASS_IMU_MISALIGN = 120;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_FLASH_UNLOCK  = 121;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_ESC_SCREAMING = 122;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_ESC_TEMP_HIGH = 123;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_BAT_ERR       = 124;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::IMPACT_IS_DETECTED       = 125;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_MODE_FAILURE  = 126;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_CRAFT_FAIL_LATELY = 127;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::KILL_SWITCH_ON           = 135;
const uint8_t DJI::OSDK::ErrorCode::CommonACK::MOTOR_FAIL_MOTOR_CODE_ERROR = 255;
const uint16_t DJI::OSDK::ErrorCode::ActivationACK::SUCCESS          = 0x0000;
const uint16_t DJI::OSDK::ErrorCode::ActivationACK::PARAMETER_ERROR  = 0x0001;
const uint16_t DJI::OSDK::ErrorCode::ActivationACK::ENCODE_ERROR     = 0x0002;
const uint16_t DJI::OSDK::ErrorCode::ActivationACK::NEW_DEVICE_ERROR = 0x0003;
const uint16_t DJI::OSDK::ErrorCode::ActivationACK::DJIGO_APP_NOT_CONNECTED = 0x0004;
const uint16_t DJI::OSDK::ErrorCode::ActivationACK::NETWORK_ERROR = 0x0005;
const uint16_t DJI::OSDK::ErrorCode::ActivationACK::SERVER_ACCESS_REFUSED = 0x0006;
const uint16_t DJI::OSDK::ErrorCode::ActivationACK::ACCESS_LEVEL_ERROR = 0x0007;
const uint16_t DJI::OSDK::ErrorCode::ActivationACK::OSDK_VERSION_ERROR = 0x0008;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::SetControl::RC_MODE_ERROR = 0x0000;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::SetControl::RELEASE_CONTROL_SUCCESS = 0x0001;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::SetControl::OBTAIN_CONTROL_SUCCESS = 0x0002;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::SetControl::OBTAIN_CONTROL_IN_PROGRESS = 0x0003;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::SetControl::RELEASE_CONTROL_IN_PROGRESS = 0x0004;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::SetControl::RC_NEED_MODE_F = 0x0006;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::SetControl::RC_NEED_MODE_P = 0x0005;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::SetControl::IOC_OBTAIN_CONTROL_ERROR = 0x00C9;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::SUCCESS      = 0x0000;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::MOTOR_ON     = 0x0001;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::MOTOR_OFF    = 0x0002;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::IN_AIR       = 0x0003;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::NOT_IN_AIR   = 0x0004;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::NO_HOMEPOINT = 0x0005;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::BAD_GPS      = 0x0006;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::IN_SIMULATOR_MODE = 0x0007;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::ALREADY_RUNNING = 0x0008;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::NOT_RUNNING     = 0x0009;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::INVAILD_COMMAND = 0x0010;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::NO_LANDING_GEAR = 0x0011;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::GIMBAL_MOUNTED  = 0x0012;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::BAD_SENSOR      = 0x0013;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::ALREADY_PACKED  = 0x0014;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::NO_PACKED       = 0x0015;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::LegacyTask::SUCCESS  = 0x0002;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::LegacyTask::FAIL     = 0x0001;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::Task::PACKED_MODE_NOT_SUPPORTED = 0x0016;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::SetArm::AIRCRAFT_IN_AIR_ERROR       = 0x0003;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::SetArm::ALREADY_ARMED_ERROR 	     = 0x0002;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::SetArm::OBTAIN_CONTROL_NEEDED_ERROR = 0x0001;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::SetArm::SUCCESS 		     = 0x0000;
const uint16_t DJI::OSDK::ErrorCode::ControlACK::KillSwitch::SUCCESS 		 = 0x00;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::SUCCESS                = 0x00;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::ILLEGAL_DATA_LENGTH    = 0x01;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::VERSION_DOES_NOT_MATCH = 0x02;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::PACKAGE_OUT_OF_RANGE   = 0x03;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::PACKAGE_ALREADY_EXISTS = 0x04;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::PACKAGE_DOES_NOT_EXIST = 0x05;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::ILLEGAL_FREQUENCY      = 0x06;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::PACKAGE_TOO_LARGE      = 0x07;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::PIPELINE_OVERFLOW      = 0x08;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::INTERNAL_ERROR_0X09    = 0x09;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::PACKAGE_EMPTY          = 0x20;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::INCORRECT_NUM_OF_TOPICS = 0x21;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::ILLEGAL_UID          = 0x22;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::PERMISSION_DENY      = 0x23;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::MULTIPLE_SUBSCRIBE   = 0x24;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::SOURCE_DEVICE_OFFLINE = 0x25;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::PAUSED               = 0x48;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::RESUMED              = 0x49;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::INTERNAL_ERROR_0X4A  = 0x4A;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::FAILED_AUTHENTICATION  = 0x50;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::VERSION_VERSION_TOO_FAR = 0x51;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::VERSION_UNKNOWN_ERROR = 0x59;
const uint8_t DJI::OSDK::ErrorCode::SubscribeACK::INTERNAL_ERROR_0XFF   = 0xFF;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::SUCCESS         = 0x00;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::WRONG_WAYPOINT_INDEX = 0x01;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::RC_NOT_IN_MODE_F = 0xD0;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::OBTAIN_CONTROL_REQUIRED = 0xD1;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::CLOSE_IOC_REQUIRED = 0xD2;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::NOT_INITIALIZED = 0xD3;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::NOT_RUNNING     = 0xD4;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::IN_PROGRESS     = 0xD5;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::TASK_TIMEOUT    = 0xD6;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::OTHER_MISSION_RUNNING = 0xD7;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::BAD_GPS     = 0xD8;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::RTK_NOT_READY     = 0xCD;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::LOW_BATTERY = 0xD9;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::VEHICLE_DID_NOT_TAKE_OFF = 0xDA;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::INVALID_PARAMETER = 0xDB;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::CONDITIONS_NOT_SATISFIED = 0xDC;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::CROSSING_NO_FLY_ZONE = 0xDD;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::UNRECORDED_HOME = 0xDE;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::AT_NO_FLY_ZONE  = 0xDF;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::TOO_HIGH        = 0xC0;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::TOO_LOW         = 0xC1;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::TOO_FAR_FROM_HOME = 0xC7;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::NOT_SUPPORTED = 0xC8;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::TOO_FAR_FROM_CURRENT_POSITION = 0xC9;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::BEGGINER_MODE_NOT_SUPPORTED = 0xCA;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::TAKE_OFF_IN_PROGRESS = 0xF0;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::LANDING_IN_PROGRESS = 0xF1;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::RRETURN_HOME_IN_PROGRESS = 0xF2;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::START_MOTORS_IN_PROGRESS = 0xF3;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::INVALID_COMMAND = 0xF4;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Common::UNKNOWN_ERROR   = 0xFF;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Follow::TOO_FAR_FROM_YOUR_POSITION_LACK_OF_RADIO_CONNECTION = 0xB0;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Follow::CUTOFF_TIME_OVERFLOW = 0xB1;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::Follow::GIMBAL_PITCH_ANGLE_OVERFLOW = 0xB2;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::HotPoint::INVALID_RADIUS = 0xC2;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::HotPoint::YAW_RATE_OVERFLOW = 0xC3;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::HotPoint::INVALID_START_POINT = 0xC4;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::HotPoint::INVALID_YAW_MODE = 0xC5;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::HotPoint::TOO_FAR_FROM_HOTPOINT = 0xC6;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::HotPoint::INVALID_PAREMETER = 0xA2;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::HotPoint::INVALID_LATITUDE_OR_LONGITUTE = 0xA3;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::HotPoint::INVALID_DIRECTION = 0xA6;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::HotPoint::IN_PAUSED_MODE = 0xA9;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::HotPoint::FAILED_TO_PAUSE = 0xAA;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::INVALID_DATA = 0xE0;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::INVALID_POINT_DATA = 0xE1;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::TRACE_TOO_LONG = 0xE2; /*!< This is the distance from WP1 to WPn. Newer A3/N3 FW > 60km; all others > 30km >*/
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::TOTAL_DISTANCE_TOO_LONG        = 0xE3; /*!< This is the distance from WP1 to WPn, plus distance from homepoint to WP1 and the distance from WPn back to the homepoint. Newer A3/N3 FW > 100km; all others > 60km >*/
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::POINT_OVERFLOW = 0xE4;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::POINTS_TOO_CLOSE = 0xE5;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::POINTS_TOO_FAR = 0xE6;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::CHECK_FAILED   = 0xE7;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::INVALID_ACTION = 0xE8;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::POINT_DATA_NOT_ENOUGH = 0xE9;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::DATA_NOT_ENOUGH = 0xEA;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::POINTS_NOT_ENOUGH = 0xEB;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::IN_PROGRESS = 0xEC;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::NOT_IN_PROGRESS = 0xED;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::WayPoint::INVALID_VELOCITY = 0xEE;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::IOC::TOO_CLOSE_TO_HOME  = 0xA0;
const uint8_t DJI::OSDK::ErrorCode::MissionACK::IOC::UNKNOWN_TYPE       = 0xA1;
const uint8_t DJI::OSDK::ErrorCode::MFIOACK::init::SUCCESS              = 0x00;
const uint8_t DJI::OSDK::ErrorCode::MFIOACK::init::UNKNOWN_ERROR        = 0x01;
const uint8_t DJI::OSDK::ErrorCode::MFIOACK::init::PORT_NUMBER_ERROR    = 0x02;
const uint8_t DJI::OSDK::ErrorCode::MFIOACK::init::PORT_MODE_ERROR      = 0x03;
const uint8_t DJI::OSDK::ErrorCode::MFIOACK::init::PORT_DATA_ERROR      = 0x04;
const uint8_t DJI::OSDK::ErrorCode::MFIOACK::set::SUCCESS               = 0x00;
const uint8_t DJI::OSDK::ErrorCode::MFIOACK::set::CHANNEL_ERROR         = 0x01;
const uint8_t DJI::OSDK::ErrorCode::MFIOACK::set::PORT_NOT_MAPPED_ERROR = 0x02;
const uint8_t DJI::OSDK::ErrorCode::MFIOACK::get::SUCCESS               = 0x00;
// clang-format on


// Backward compatibility

const uint8_t& DJI::OSDK::ErrorCode::MissionACK::WayPoint::DISTANCE_OVERFLOW = DJI::OSDK::ErrorCode::MissionACK::WayPoint::TRACE_TOO_LONG;
const uint8_t& DJI::OSDK::ErrorCode::MissionACK::WayPoint::TIMEOUT = DJI::OSDK::ErrorCode::MissionACK::WayPoint::TOTAL_DISTANCE_TOO_LONG;

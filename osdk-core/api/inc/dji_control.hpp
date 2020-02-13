/** @file dji_control.hpp
 *  @version 3.3
 *  @date April 2017
 *
 *  @brief
 *  Control API for DJI OSDK library
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

#ifndef DJI_CONTROL_H
#define DJI_CONTROL_H

#include "dji_ack.hpp"
#include "dji_open_protocol.hpp"
#include "dji_type.hpp"
#include "dji_vehicle_callback.hpp"

namespace DJI
{
namespace OSDK
{

// Forward Declarations
class Vehicle;

/*! @brief Flight control API: high-level actions and low-level control modes
 *
 */
class Control
{

public:
  /*! @brief Flight control commands
   */
  class FlightCommand
  {
  public:
    /*
     * @note Matrice 100 flight commands
     */
    typedef struct LegacyCMD
    {
      const static int goHome  = 1;
      const static int takeOff = 4;
      const static int landing = 6;
    } LegacyCMD;

    /*
     * @note OSDK release 3.3
     */
    const static int takeOff = 1; /*!< vehicle takeoff*/
    const static int landing = 2; /*!< vehicle landing*/
    //! @note independent mode courseLock,
    //! cannot be controlled through SDK
    const static int courseLock       = 5;
    const static int goHome           = 6; /*!< vehicle return home position*/
    const static int startMotor       = 7;
    const static int stopMotor        = 8;
    const static int calibrateCompass = 9;
    const static int exitGoHome       = 12;
    const static int exitTakeOff      = 13;
    const static int exitLanding      = 14;
    const static int exitCalibrateCompass = 21;
    const static int landingGearDown      = 28;
    const static int landingGearUp        = 29;
  };
  // clang-format off
  /*! @brief bit 5:4 of the 8-bit (7:0) CtrlData.flag
   *我们建议开发人员在您的无人机飞行高度大于3米时不要在室内使用VERTICAL_POSITION控制模式。
	 *这是因为在室内环境中，气压计可能不准确，并且垂直控制器可能无法保持UAV的高度。
   *  We suggest developers do not use VERTICAL_POSITION control mode indoor
   * when your UAV
   *  flight height is larger than 3 meters.
   *  This is because in indoor environments, barometer can be inaccurate, and
   * the
   *  vertical controller may fail to keep the height of the UAV.
   */
  enum VerticalLogic
  {
    /*!
     - Set the control-mode to control the vertical   设置控制模式以控制无人机的垂直速度，向上为正
       speed of UAV, upward is positive
     - Limit: -5 to 5 m/s                             限制：-5至5米/秒 
     */
    VERTICAL_VELOCITY = 0x00,
    /*!
     - Set the control-mode to control the height of UAV  设置控制模式以控制UAV的高度
     - Limit: 0 to 120 m                                  限制：0至120米
     */
    VERTICAL_POSITION = 0x10,
    /*!
     - Set the control-mode to directly control the thrust  设置控制模式以直接控制推力
     - Range: 0% to 100%                                    范围：0％至100％
     */
    VERTICAL_THRUST = 0x20,
  };

  /*! @brief bit 7:6 of the 8-bit (7:0) CtrlData.flag
   *
   *  @note
	 * 仅当GPS信号良好（health_flag> = 3）时，才能使用水平位置控制（HORIZONTAL_POSITION）相关的控制模式。
   *        - Only when the GPS signal is good (health_flag >=3)，horizontal
   * position control (HORIZONTAL_POSITION) related control modes can be used.
	 * 仅当GPS信号良好（health_flag> = 3）或AdvancedSensing系统与自动驾驶仪正常工作时，
	 * 才能使用水平速度控制（HORIZONTAL_VELOCITY）相关的控制模式。
   *        - Only when GPS signal is good (health_flag >=3)，or when AdvancedSensing
   * system is working properly with Autopilot，
   *          horizontal velocity control（HORIZONTAL_VELOCITY）related control
   * modes can be used.
   */
  enum HorizontalLogic
  {
    /*!
     - Set the control-mode to control pitch & roll
     angle of the vehicle.                                   设置控制模式以控制车辆的俯仰角和侧倾角。
     - Need to be referenced to either the ground or         需要通过Horizo​​ntalCoordinate设置引用地面或主体框架
     body frame by HorizontalCoordinate setting.        
     - Limit: 35 degree                                      限制：35度 
     */
    HORIZONTAL_ANGLE = 0x00,
    /*!
     - Set the control-mode to control horizontal           
     vehicle velocities.                                     设置控制模式以控制水平车速。
     - Need to be referenced to either the ground
     or body frame by HorizontalCoordinate setting.          需要通过Horizo​​ntalCoordinate设置引用地面或主体框架
     - Limit: 30 m/s                                         限制：30米/秒 
     */
    HORIZONTAL_VELOCITY = 0x40,
    /*!
     - Set the control-mode to control position
     offsets of pitch & roll directions                      设置控制模式以控制俯仰和滚转方向的位置偏移
     - Need to be referenced to either the ground 
     or body frame by HorizontalCoordinate setting.          需要通过Horizo​​ntalCoordinate设置引用地面或主体框架
     - Limit: N/A                                            限制：N / A. 
     */
    HORIZONTAL_POSITION = 0x80,
    /*!
     - Set the control-mode to control rate of
     change of the vehicle's attitude                        设置控制模式以控制车辆姿态的变化率
     - Need to be referenced to either the ground
     or body frame by HorizontalCoordinate setting.          需要通过Horizo​​ntalCoordinate设置引用地面或主体框架
     - Limit: 150.0 deg/s                                    限制：150.0度/秒 
     */
    HORIZONTAL_ANGULAR_RATE = 0xC0
  };
  /*! @brief bit 3 of the 8-bit (7:0) CtrlData.flag
   */
  enum YawLogic
  {
    /*!
     - Set the control-mode to control yaw angle.                          设置控制模式以控制偏航角。
     - Yaw angle is referenced to the ground frame.                        偏航角以地面框架为参考
     - In this control mode, Ground frame is enforeced in Autopilot.       在此控制模式下，地面框架在自动驾驶仪中进行。
     */
    YAW_ANGLE = 0x00,
    /*!
     - Set the control-mode to control yaw angular velocity.               设置控制模式以控制偏航角速度
     - Same reference frame as YAW_ANGLE.                                  与YAW_ANGLE相同的参考框架
     - Limite: 150 deg/s                                                   限制：150度/秒
     */
    YAW_RATE = 0x08
  };

  /*! @brief bit 2:1 of the 8-bit (7:0) CtrlData.flag
   */
  enum HorizontalCoordinate
  {
    /*! Set the x-y of ground frame as the horizontal frame (NEU) */     //将地面框架的xy设置为水平框架（NEU）
    HORIZONTAL_GROUND = 0x00,
    /*! Set the x-y of body frame as the horizontal frame (FRU) */       //将body框架的xy设置为水平框架（FRU）
    HORIZONTAL_BODY = 0x02
  };

  /*!
   * @brief bit 0 of the 8-bit (7:0) CtrlData.flag.
   *仅适用于水平速度控制模式在速度稳定模式下，一旦输入命令为零，无人机将制动并悬停在一个位置。
	 *在悬停状态下，无人机将尝试保持原位。
   *
   *在速度非稳定模式下，无人机将遵循速度命令，并且在命令为零时不会悬停。这就是说无人机将随风飘荡
   * Drone will try to hold at current position if enable
   */
  enum StableMode
  {
    STABLE_DISABLE = 0x00, /*!< Disable the stable mode */                //禁用稳定模式
    STABLE_ENABLE  = 0x01  /*!< Enable the stable mode */                 //启用稳定模式 
  };

  /*!
   * @brief turn on or off the motors for emergency reasons
	 *        出于紧急原因打开或关闭电机
   */
  enum KillSwitch
  {
    ENABLE  = 0x01, /*!< Enable the killswitch */                         //启用killswitch
    DISABLE = 0x02  /*!< Disable the killswitch */                        //禁用killswitch
  };
// clang-format on

/*! The struct for CtrlData

 */
#pragma pack(1)
  /*! @brief CtrlData used for flight control.
    *
    */
  typedef struct CtrlData
  {
    uint8_t flag;  /*!< control data flag consists of 8 bits.                        控制数据标志由8位组成
 
                      - CtrlData.flag = ( DJI::OSDK::Control::HorizontalLogic |
                      DJI::OSDK::Control::VerticalLogic |
                      DJI::OSDK::Control::YawLogic |
                      DJI::OSDK::Control::HorizontalCoordinate |
                      DJI::OSDK::Control::StableMode)
                   */
    float32_t x;   /*!< Control with respect to the x axis of the
                      DJI::OSDK::Control::HorizontalCoordinate.*/
    float32_t y;   /*!< Control with respect to the y axis of the
                      DJI::OSDK::Control::HorizontalCoordinate.*/
    float32_t z;   /*!< Control with respect to the z axis, up is positive. */     //控制相对于z轴，向上为正。 
    float32_t yaw; /*!< Yaw position/velocity control w.r.t. the ground frame.*/   //偏航位置/速度控制与地面框架相对应。

    /*!
     * \brief CtrlData initialize the CtrlData variable.
     * \param in_flag   See CtrlData.flag
     * \param in_x      See CtrlData.x
     * \param in_y      See CtrlData.y
     * \param in_z      See CtrlData.z
     * \param in_yaw    See CtrlData.yaw
     */
    CtrlData(uint8_t in_flag, float32_t in_x, float32_t in_y, float32_t in_z,
             float32_t in_yaw);
  } CtrlData; // pack(1)

  /*! @brief AdvancedCtrlData
   *
   *  @note for flag, x, y, z, yaw definition see CtrlData.
   */
  typedef struct AdvancedCtrlData
  {
    uint8_t   flag;
    uint8_t   advFlag;
    float32_t x;
    float32_t y;
    float32_t z;
    float32_t yaw;
    float32_t xFeedforward;
    float32_t yFeedforward;

    AdvancedCtrlData(uint8_t in_flag, float32_t in_x, float32_t in_y,
                     float32_t in_z, float32_t in_yaw, float32_t x_forw,
                     float32_t y_forw);
  } AdvancedCtrlData; // pack(1)

  // CMD data supported in Matrice 100
  typedef struct LegacyCMDData
  {
    uint8_t sequence;
    uint8_t cmd;
  } LegacyCMDData; // pack (1)

  typedef struct KillSwitchData
  {
    uint8_t high_version;    /*!< version # for FW version match */
    uint8_t low_version;     /*!< version # for protocol compatibility */
    uint8_t debug_description[10]; /*!< insert reasons for emergency stop for debugging purpose */
    uint8_t cmd : 2;  /*!< 0: no action, 1: motor stop with protection, 2: disarm protection */
    uint8_t reserved : 6;
  } KillSwitchData; // pack(1)


#pragma pack()

  /*! @note
   *
   *  Basically control class provide two functions:
   *  1. action() which implements CMD_ID_TASK
   *  2. modeCtrl() which implements CMD_ID_CONTROL
   *
   *  The rest of the functions are just wrapper functions
   *  that provide commonly used control functions
   *  EX: takeoff, landing, and position control mode
   */
private:
  const int wait_timeout;

public:
  Control(Vehicle* vehicle = 0);
  ~Control();

  Vehicle* vehicle;

  /*! @brief Basic action command for the vehicle, see FlightCommand for cmd
   * choices                                             车辆的基本操作命令，请参阅Flight命令以获取cmd选项。
   *
   *  @param cmd action command from FlightCommand       FlightCommand的动作命令
   *  @param callback callback function                  回调函数             
   *  @param userData user data (void ptr)               用户数据（void ptr）
   */
  void action(const int cmd, VehicleCallBack callback = 0,
              UserData userData = 0);
  /*! @brief Control the vehicle using user-specified mode, see FlightCommand
   * for cmd choices
   *
   *  @param cmd action command from FlightCommand    FlightCommand的动作命令
   *  @param timeout timeout to wait for ACK          等待ACK的超时 
   *  @return ErrorCode                               返回错误代码
   */
  ACK::ErrorCode action(const int cmd, int timeout);

  /*! @brief Wrapper function for arming the motors                                     包裹功能用于布防电机
   *
   *  @return ACK::ErrorCode struct with the acknowledgement from the FC                ACK :: ErrorCode结构，带有来自FC的确认
   */
  ACK::ErrorCode armMotors(int wait_timeout);
  /*! @brief Wrapper function for arming the motors                                     包裹功能用于布防电机
   *
   *  @note If user does not provide his/her own callback, default callback             如果用户没有提供他/她自己的回调，则将执行默认回调
   *  will be executed
   */
  void armMotors(VehicleCallBack callback = 0, UserData userData = 0);

  /*! @brief Wrapper function for disarming the motors                                  包裹功能用于撤防电机
   *
   *  @return ACK::ErrorCode struct with the acknowledgement from the FC                ACK :: ErrorCode结构，带有来自FC的确认
   */
  ACK::ErrorCode disArmMotors(int wait_timeout);
  /*! @brief Wrapper function for disarming the motors                                  包裹功能用于撤防电机
   *
   *  @note If user does not provide his/her own callback, default callback             如果用户没有提供他/她自己的回调，则将执行默认回调
   *  will be executed
   */
  void disArmMotors(VehicleCallBack callback = 0, UserData userData = 0);

  /*! @brief Wrapper function for take off                                              包装功能起飞
   *
   *  @return ACK::ErrorCode struct with the acknowledgement from the FC                ACK :: ErrorCode结构，带有来自FC的确认
   */
  ACK::ErrorCode takeoff(int wait_timeout);
  /*! @brief Wrapper function for take off                                              包装功能起飞。
   *
   *  @note If user does not provide his/her own callback, default callback             如果用户没有提供他/她自己的回调，则将执行默认回调
   *  will be executed
   */
  void takeoff(VehicleCallBack callback = 0, UserData userData = 0);

  /*! @brief Wrapper function for go Home                                               回家的包装功能
   *
   *  @return ACK::ErrorCode struct with the acknowledgement from the FC                ACK :: ErrorCode结构，带有来自FC的确认
   */
  ACK::ErrorCode goHome(int wait_timeout);
  /*! @brief Wrapper function for go Home                                               回家的包装功能
   *
   *  @note If user does not provide his/her own callback, default callback             如果用户没有提供他/她自己的回调，则将执行默认回调
   *  will be executed
   */
  void goHome(VehicleCallBack callback = 0, UserData userData = 0);

  /*! @brief Wrapper function for landing                                               用于着陆的包装功能
   *
   *  @return ACK::ErrorCode struct with the acknowledgement from the FC                ACK :: ErrorCode结构，带有来自FC的确认
   */
  ACK::ErrorCode land(int wait_timeout);
  /*! @brief Wrapper function for landing                                               用于着陆的包装功能
   *
   *  @note If user does not provide his/her own callback, default callback             如果用户没有提供他/她自己的回调，则将执行默认回调
   *  will be executed
   */
  void land(VehicleCallBack callback = 0, UserData userData = 0);

  /*! @brief Control the vehicle using user-specified mode                              使用用户指定的模式控制车辆。
   *
   *  @param data control set-points and flags                                          控制设定点和标志
   */
  void flightCtrl(CtrlData data);

  /*! @brief Control the vehicle using user-specified mode (overloaded)                 使用用户指定的模式控制车辆（超载）             
   *
   *  @note this mode only works in HORIZONTAL_VELOCITY and the unit of                 此模式仅适用于HORIZONTAL_VELOCITY，前馈项的单位为m / s ^ 2
   *  feedforward term is m/s^2
   *
   *  @param data control set-points and flags                                          数据	控制设定点和标志
   */
  void flightCtrl(AdvancedCtrlData data);
 
  /*! @brief Control the position and yaw angle of the vehicle.                         控制车辆的位置和偏航角度。
   *  The reference frame is the DJI::OSDK::Control::HORIZONTAL_GROUND (NEU).           参考帧是DJI :: OSDK :: Control :: HORIZONTAL_GROUND（NEU）。
   *
   *  @param x position set-point in x axis of ground frame (m)                         地面框架x轴的位置设定点（m） 
   *  @param y position set-point in y axis of ground frame (m)                         地面框架y轴的位置设定点（m）
   *  @param z position set-point in z axis of ground frame (m), input limit see        地面框架（m）的z轴位置设定点，
   * DJI::OSDK::Control::VERTICAL_POSITION                                              输入限制见DJI :: OSDK :: Control :: VERTICAL_POSITION 
   *  @param yaw yaw set-point (deg)                                                    偏航设定点（度）
   */
  void positionAndYawCtrl(float32_t x, float32_t y, float32_t z, float32_t yaw);

  /*! @brief Control the velocity and yaw rate of the vehicle.                          控制车辆的速度和横摆率。
   *  The reference frame is the DJI::OSDK::Control::HORIZONTAL_GROUND (NEU).           参考帧是DJI :: OSDK :: Control :: HORIZONTAL_GROUND（NEU）。
   *
   *  @param Vx velocity set-point in x axis of ground frame (m/s), input limit         地面框架x轴的速度设定点（m / s）
   * see DJI::OSDK::Control::HORIZONTAL_VELOCITY
   *  @param Vy velocity set-point in y axis of ground frame (m/s), input limit         地面框架y轴的速度设定点（m / s）
   * see DJI::OSDK::Control::HORIZONTAL_VELOCITY
   *  @param Vz velocity set-point in z axis of ground frame (m/s), input limit         地面框架z轴的速度设定点（m / s）
   * see DJI::OSDK::Control::VERTICAL_VELOCITY
   *  @param yawRate yawRate set-point (deg/s)                                          yawRate设定点（deg / s）
   */
  void velocityAndYawRateCtrl(float32_t Vx, float32_t Vy, float32_t Vz,
                              float32_t yawRate);

	void velocityAndYawRateCtrl(float32_t Vz,
                              float32_t yawRate);                                       //重载函数，只控制高度速度还有YAW的角速度
  /*! @brief Control the attitude and vertical position of the vehicle                  控制车辆的姿态和垂直位置。
   *
   *  @param roll   attitude set-point in x axis of body frame (FRU) (deg),
   * input limit see DJI::OSDK::Control::HORIZONTAL_ANGLE
   *  @param pitch  attitude set-point in y axis of body frame (FRU) (deg),
   * input limit see DJI::OSDK::Control::HORIZONTAL_ANGLE
   *  @param z      z position set-point in z axis of ground frame (NED) (m),
   * input limit see DJI::OSDK::Control::VERTICAL_POSITION
   *  @param yaw    attitude set-point in z axis of ground frame (NED) (deg)
   */
  void attitudeAndVertPosCtrl(float32_t roll, float32_t pitch, float32_t yaw,
                              float32_t z);
	
	void attitudeAndVertPosCtrl(float32_t roll, float32_t pitch);                         //重载函数  只控制roll pitch

  /*! @brief Control the attitude rate and vertical position of the vehicle             控制车辆的姿态速度和垂直位置。
   *
   *  @param rollRate   attitude rate set-point in x axis of body frame (FRU)
   * (deg/s)
   *  @param pitchRate  attitude rate set-point in y axis of body frame (FRU)
   * (deg/s)
   *  @param yawRate    attitude rate set-point in z axis of body frame (FRU)
   * (deg/s), input limit see DJI::OSDK::Control::YAW_RATE
   *  @param z          z position set-point in z axis of ground frame (NED)
   * (m), input limit see DJI::OSDK::Control::VERTICAL_POSITION
   */
  void angularRateAndVertPosCtrl(float32_t rollRate, float32_t pitchRate,
                                 float32_t yawRate, float32_t z);

  /*! @brief Stop the vehicle in horiz velocity, vert velocity, yaw rate mode          在水平速度，垂直速度，偏航率模式（车身框架）中停车
   * (body frame)                          
   *
   */
  void emergencyBrake();

  /*! @brief A callback function for action non-blocking calls                         用于操作非阻塞调用的回调函数。
   *
   *  @param recvFrame the data comes with the callback function                       数据附带回调函数 
   *  @param userData a void ptr that user can manipulate inside the callback          用户可以在回调内操作的void ptr 
   *
   */
  static void actionCallback(Vehicle* vehiclePtr, RecvContainer recvFrame,
                             UserData userData);

  /*! @brief Turn on or off the kill switch                                            打开或关闭终止开关
   *
   *  @param cmd enable or disable the kill switch                                     启用或禁用kill开关 
   *  @param wait_timeout timeout for blocking call                                    阻止呼叫超时
   *  @param debugMsg inject debug message to flight control FW for logging, size limit: 10 bytes   将调试消息注入飞行控制FW进行记录，大小限制：10个字节
   *
   *  @return ACK::ErrorCode struct with the acknowledgement from the FC               ACK :: ErrorCode结构，带有来自FC的确认
   */
  ACK::ErrorCode killSwitch(KillSwitch cmd, int wait_timeout = 10, char debugMsg[10] = (char *)"OSDK_API");
  /*! @brief Turn on or off the kill switch                                            打开或关闭终止开关                  
   *
   *  @param cmd enable or disable the kill switch                                     启用或禁用kill开关
   *  @param debugMsg inject debug message to flight control FW for logging, size limit: 10 bytes    将调试消息注入飞行控制FW进行记录，大小限制：10个字节
   *  @param callback callback function you want called upon ACK                                     你想要在ACK上调用的回调函数
   *  @param userData additional data you want the callback function to have access to               您希望回调函数可以访问的其他数据
   *
   *  @note If user does not provide his/her own callback, default callback                          如果用户没有提供他/她自己的回调，则将执行默认回调
   *  will be executed
   */
  void killSwitch(KillSwitch cmd, char debugMsg[10] = (char *)"OSDK_API", VehicleCallBack callback = 0, UserData userData = 0);

private:
  /*! @brief Wrapper function for arming/disarming the motors
   *  @note Supported in Matrice 100
   *  @return ACK::ErrorCode struct with the acknowledgment from the FC
   */
  ACK::ErrorCode setArm(bool armSetting, int timeout);
  /*! @brief Wrapper function for arming/disarming the motors
   *  @note Supported on Matrice 100. If user does not provide his/her
   *  own callback, default callback will be executed.
   */
  void setArm(bool armSetting, VehicleCallBack callback = 0,
              UserData userData = 0);

  /*
   * Task CMD data to send to the flight controller (supported in Matrice 100)
   */
  LegacyCMDData legacyCMDData;
}; // class Control

} // OSDK
} // DJI

#endif // DJI_CONTROL_H

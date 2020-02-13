/*! @file main.cpp
*  @version 3.1.8
 *  @date Aug 05 2016
 *
 *  @brief
 *  An exmaple program of DJI-onboard-SDK portable for stm32
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

#ifndef MAIN_H
#define MAIN_H

#include "Activate.h"
#include "BspUsart.h"
#include "CameraGimbalSample.h"
#include "FlightControlSample.h"
#include "MissionSample.h"
#include "MobileSample.h"
#include "PayloadSample.h"
#include "Receive.h"
#include "TelemetrySample.h"
#include "TimeSyncSample.h"
#include "bsp.h"
#include "cppforstm32.h"
#include "dji_vehicle.hpp"
#include "stm32f4xx_conf.h"
#include "timer.h"
#include "stm32f4xx.h"
#include "misc.h"
#include "dji_vehicle.hpp"
#include "string.h"



#include "led.h"
#include "driver.h"
#include "buzzer.h"
#include "sub_information.h"
#include "global_variable.h"
#include "math.h"
#include "time.h"
#include "control.h"
#include "optical_flow.h"
#include "pid.h"
#include "comunication.h"


extern Vehicle* v;
extern uint8_t flow_time;
extern uint32_t tick; // tick is the time stamp,which record how many ms since u
                      // initialize the system.
// warnning: after 49 days of non-reset running, tick will RESET to ZERO.
extern fp32 pitch , roll, yaw;
extern Vehicle  vehicle;
extern Control  control;
extern RecvContainer  receivedFramie;
extern RecvContainer* rFrame;
extern uint8_t come_data;
extern uint8_t Rx_length;
extern int32_t Rx_adr;
extern int32_t Rx_Handle_Flag;
extern uint8_t Rx_buff[];
extern int32_t Rx_Handle_Flag;
//extern TerminalCommand myTerminal;
extern bool    isFrame;
extern DJI::OSDK::ACK::ErrorCode waitForACK();
extern Telemetry::TypeMap<Telemetry::TOPIC_RC>::type rc_data;
extern Telemetry::TypeMap<Telemetry::TOPIC_ACCELERATION_BODY>::type accel_body;
extern Telemetry::TypeMap<Telemetry::TOPIC_QUATERNION>::type quat;
extern Telemetry::TypeMap<Telemetry::TOPIC_HEIGHT_FUSION>::type height_fusion;
extern Telemetry::TypeMap<Telemetry::TOPIC_ALTITUDE_FUSIONED>::type altitude_fusioned;
extern Telemetry::TypeMap<Telemetry::TOPIC_ALTITUDE_BAROMETER>::type altitude_barometer;
extern Telemetry::TypeMap<Telemetry::TOPIC_CONTROL_DEVICE>::type control_device; 


#endif // MAIN_H

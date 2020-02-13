/*! @file main.cpp
 *  @version 3.3
 *  @date May 2017
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
 *
 *
 *******************************************************************************
 *                                                                             *
 *          --------               --------                 --------           *
 *         |        |   USART3    |        |    USART2     |        |          *
 *         |   PC   | <---------> | stm32  |  <----------> |  M100  |          *
 *         |        | (USB-TTL)   |        |               |        |          *
 *         |        |             |        |               |        |          *
 *          --------               --------                 --------           *
 *                                                                             *
 *                                                                             *
 *******************************************************************************
 * User文件夹中是大疆sdk的例子，可以在模拟器中跑一下
 */

#include "main.h"

/*-----------------------DJI_LIB VARIABLE-----------------------------*/
using namespace DJI::OSDK;
bool           threadSupport = false;
bool           isFrame       = false;
RecvContainer  receivedFrame;
RecvContainer* rFrame  = &receivedFrame;
Vehicle        vehicle = Vehicle(threadSupport);
Vehicle*       v       = &vehicle;
extern TerminalCommand myTerminal;

int main()
{
	
  uint8_t runOnce = 1;
	SystickConfig();
	//等待N3飞控启动成功，需要延时
	delay_nms(30000);	
	Underlying_initialization();
  printf("STM32F4 Board initialization finished!\r\n");
  while (1)
  {
    // One time automatic activation
    if (runOnce)
    {
      runOnce = 0;
      // Check USART communication
      if (!v->protocolLayer->getDriver()->getDeviceStatus())
      {
      printf("USART communication is not working.\r\n");
        delete (v);
        return -1;
      }

      printf("Sample App for STM32F4Discovery Board:\r\n");
      delay_nms(30);
			
      printf("\nPrerequisites:\r\n");
      printf("1. Vehicle connected to the Assistant and simulation is ON\r\n");
      printf("2. Battery fully chanrged\r\n");
      printf("3. DJIGO App connected (for the first time run)\r\n");
      printf("4. Gimbal mounted if needed\r\n");
      delay_nms(30);
      //! Initialize functional Vehicle components like
      //! Subscription, Broabcast, Control, Camera, etc
      v->functionalSetUp();
      delay_nms(500);

      // Check if the firmware version is compatible with this OSDK version
      if (v->getFwVersion() > 0 &&
				v->getFwVersion() < extendedVersionBase &&
	      v->getFwVersion() != Version::M100_31)
      {
        printf("Upgrade firmware using Assistant software!\n");
        delete (v);
        return -1;
      }

      userActivate();
      delay_nms(500);
      /*ACK::ErrorCode ack = waitForACK();
      if(ACK::getError(ack))
      {
        ACK::getErrorCodeMessage(ack, func);
      }*/

      // Verify subscription
      if (v->getFwVersion() != Version::M100_31)
      {
        v->subscribe->verify();
        delay_nms(500);
      }
			
      // Obtain Control Authority
      v->obtainCtrlAuthority();
      delay_nms(1000);
    }

	  Loop_Task();		
  }
}

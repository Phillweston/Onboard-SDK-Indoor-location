/*! @file dji_linux_helpers.hpp
 *  @version 3.3
 *  @date Jun 05 2017
 *
 *  @brief
 *  Helper functions to handle user configuration parsing, version query and
 * activation.
 *
 *  @Copyright (c) 2017 DJI
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

#ifndef ONBOARDSDK_HELPERS_H
#define ONBOARDSDK_HELPERS_H

#include <fstream>
#include <dji_linux_environment.hpp>
#include <dji_vehicle.hpp>

class LinuxSetup
{
public:
  LinuxSetup(int argc, char **argv, bool enableAdvancedSensing = false);
  ~LinuxSetup();

public:
  void setupEnvironment(int argc, char** argv);
  void initVehicle();
  bool validateSerialPort();

public:
  void setTestSerialDevice(DJI::OSDK::LinuxSerialDevice* serialDevice);
  DJI_Environment* getEnvironment()
  {
    return this->environment;
  }
  DJI::OSDK::Vehicle* getVehicle()
  {
    return this->vehicle;
  }
  DJI::OSDK::Vehicle::ActivateData* getActivateData()
  {
    return &activateData;
  }

private:
  DJI::OSDK::Vehicle*              vehicle;
  DJI::OSDK::LinuxSerialDevice*    testSerialDevice;
  DJI_Environment*                 environment;
  DJI::OSDK::Vehicle::ActivateData activateData;
  int                              functionTimeout; // seconds
  bool                             useAdvancedSensing;
};

#endif // ONBOARDSDK_HELPERS_H

/*! @file dji_linux_environment.hpp
 *  @version 3.3
 *  @date Jun 05 2017
 *
 *  @brief
 *  Helper functions to handle user configuration parsing
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

#ifndef ONBOARDSDK_DJI_ENVIRONMENT_H
#define ONBOARDSDK_DJI_ENVIRONMENT_H

#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <unistd.h>

class DJI_Environment
{
public:
  DJI_Environment(const std::string& config_file_path);
  ~DJI_Environment();

  static std::string findFile(std::string file);
  int                getApp_id() const;
  const std::string& getEnc_key() const;
  const std::string& getDevice() const;
  unsigned int       getBaudrate() const;
  bool               getConfigResult() const;
  bool parse(std::string config_file_path);
  const std::string& getDeviceAcm() const;
  void setDeviceAcm(std::string dev_path);

private:
  std::string  config_file_path;
  int          app_id;
  std::string  enc_key;
  std::string  device;
  unsigned int baudrate;
  bool         config_read_result;
  std::string  device_acm;
};

#endif // ONBOARDSDK_DJI_ENVIRONMENT_H

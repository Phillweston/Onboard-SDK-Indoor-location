/*! @file Receive.h
 *
 *  @version 3.3
 *  @date Jun 2017
 *
 *  @brief
 *  This function parses Rx buffer and execute commands sent from computer.
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

#ifndef RECEIVE_H
#define RECEIVE_H
#include "main.h"

#define MAX_RECEIVE 32

class TerminalCommand
{
public:
  uint32_t cmdReadyFlag;       // Rx_Handle_Flag
  uint8_t  cmdIn[MAX_RECEIVE]; // Rx_buff
  int32_t  rxIndex;            // Rx_adr
  int32_t  rxLength;           // Rx_length

  void terminalCommandHandler(Vehicle* vehicle);
  TerminalCommand()
    : cmdReadyFlag(0)
    , rxIndex(0)
    , rxLength(0)
  {
    ;
  }
};

#endif // RECEIVE_H

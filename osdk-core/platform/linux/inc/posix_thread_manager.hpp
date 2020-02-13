/*! @file posix_thread_manager.hpp
 *  @version 3.3
 *  @date Jun 15 2017
 *
 *  @brief
 *  Thread safety and data protection for DJI Onboard SDK on linux platforms
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

#ifndef POSIXTHREADMANAGER_H
#define POSIXTHREADMANAGER_H

#include "dji_thread_manager.hpp"
#include "pthread.h"

namespace DJI
{
namespace OSDK
{

/*! @brief POSIX-Compatible Data Protection and Condition Variables for *NIX
 * platforms
 *
 */
class PosixThreadManager : public ThreadAbstract
{
public:
  PosixThreadManager()
  {
  }
  ~PosixThreadManager();

  void init();

  //! Implementing virtual functions from ThreadManager
public:
  void lockRecvContainer();
  void freeRecvContainer();

  void lockMSG();
  void freeMSG();

  void lockACK();
  void freeACK();

  void lockProtocolHeader();
  void freeProtocolHeader();

  void lockNonBlockCBAck();
  void freeNonBlockCBAck();

  void lockStopCond();
  void freeStopCond();

  void lockFrame();
  void freeFrame();

  void notify();
  void notifyNonBlockCBAckRecv();
  void wait(int timeoutInSeconds);
  void nonBlockWait();

private:
  pthread_mutex_t m_memLock;
  pthread_mutex_t m_msgLock;
  pthread_mutex_t m_ackLock;
  pthread_cond_t  m_ackRecvCv;

  pthread_mutex_t m_headerLock;
  pthread_mutex_t m_nbAckLock;
  pthread_cond_t  m_nbAckRecv;

  //! Thread protection for setting stop condition for threads
  pthread_mutex_t m_stopCondLock;

  //! Thread protection for last received frame storage
  pthread_mutex_t m_frameLock;
};

} // namespace OSDK
} // namespace DJI

#endif // POSIXTHREADMANAGER_H

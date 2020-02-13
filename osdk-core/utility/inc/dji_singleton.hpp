/** @file dji_singleton.hpp
 *  @version 3.3
 *  @date Jun 2017
 *
 *  @brief Singleton Template Class implementation for use with the DJI OSDK
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

#ifndef SINGLETON_H
#define SINGLETON_H

namespace DJI
{
namespace OSDK
{

template <class T>
class Singleton
{
public:
  typedef T type;

protected:
  Singleton();

public:
  virtual ~Singleton()
  {
  }

public:
  static T& instance();
  static T* instancePTR();

protected:
  static T* singleInstance;
}; // class Singleton<T>

// template implementation
template <class T>
Singleton<T>::Singleton()
{
}

template <class T>
T&
Singleton<T>::instance()
{
  return *Singleton<T>::singleInstance;
}

template <class T>
T*
Singleton<T>::instancePTR()
{
  return Singleton<T>::singleInstance;
}

template <class T>
T* Singleton<T>::singleInstance = new T();

} // namespace OSDK
} // namespace DJI

#endif // SINGLETON_H

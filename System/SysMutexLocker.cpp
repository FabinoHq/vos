////////////////////////////////////////////////////////////////////////////////
//     _______                       ____________________________________     //
//     \\ .   \            _________/ . . . . . . . . . . . . . . . .   /     //
//      \\ .   \       ___/ . . . . .    ______________________________/      //
//       \\ .   \   __/. . .   _________/     /    // .  __________/          //
//        \\ .   \_//      ___/ .  _____     /    // .  /______               //
//         \\ .   \/     _/ // .  /    \\    |    \\  .        \              //
//          \\ .        /   || .  |    ||    |     \\______     \             //
//           \\ .      /    || .  \____//    |  _________//     /             //
//            \\ .    /     //  .            / // . . . .      /              //
//             \\____/     //_______________/ //______________/               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//   This is free and unencumbered software released into the public domain.  //
//                                                                            //
//   Anyone is free to copy, modify, publish, use, compile, sell, or          //
//   distribute this software, either in source code form or as a compiled    //
//   binary, for any purpose, commercial or non-commercial, and by any        //
//   means.                                                                   //
//                                                                            //
//   In jurisdictions that recognize copyright laws, the author or authors    //
//   of this software dedicate any and all copyright interest in the          //
//   software to the public domain. We make this dedication for the benefit   //
//   of the public at large and to the detriment of our heirs and             //
//   successors. We intend this dedication to be an overt act of              //
//   relinquishment in perpetuity of all present and future rights to this    //
//   software under copyright law.                                            //
//                                                                            //
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          //
//   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       //
//   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   //
//   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR        //
//   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,    //
//   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR    //
//   OTHER DEALINGS IN THE SOFTWARE.                                          //
//                                                                            //
//   For more information, please refer to <http://unlicense.org>             //
////////////////////////////////////////////////////////////////////////////////
//    VOS : Virtual Operating System                                          //
//     System/SysMutexLocker.cpp : System Mutex locker management             //
////////////////////////////////////////////////////////////////////////////////
#include "SysMutexLocker.h"


////////////////////////////////////////////////////////////////////////////////
//  SysMutexLocker constructor                                                //
////////////////////////////////////////////////////////////////////////////////
SysMutexLocker::SysMutexLocker(SysMutex& mutex) :
m_mutex(mutex),
m_lock(0)
{

}

////////////////////////////////////////////////////////////////////////////////
//  SysMutexLocker destructor                                                 //
////////////////////////////////////////////////////////////////////////////////
SysMutexLocker::~SysMutexLocker()
{
    // Delete eventual locker
    if (m_lock)
    {
        delete m_lock;
        m_lock = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
//  lock : lock the associated mutex                                          //
//  Return : True if the mutex is locked, false otherwise                     //
////////////////////////////////////////////////////////////////////////////////
bool SysMutexLocker::lock()
{
    if (m_lock)
    {
        // Mutex is already locked
        return true;
    }

    try
    {
        // Lock the mutex
        m_lock = new std::lock_guard<std::mutex>(m_mutex.m_mutex);
    }
    catch (const std::bad_alloc&)
    {
        // Memory allocation error
        return false;
    }
    catch (...)
    {
        // Unknown error
        return false;
    }

    if (!m_lock)
    {
        // Memory allocation error
        return false;
    }

    // Mutex successfully locked
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  unlock : Unlock the associated mutex                                      //
////////////////////////////////////////////////////////////////////////////////
void SysMutexLocker::unlock()
{
    // Delete eventual locker
    if (m_lock)
    {
        delete m_lock;
        m_lock = 0;
    }
}

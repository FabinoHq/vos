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
//     System/SysMutex.cpp : System Mutex management                          //
////////////////////////////////////////////////////////////////////////////////
#include "SysMutex.h"


////////////////////////////////////////////////////////////////////////////////
//  SysMutex default constructor                                              //
////////////////////////////////////////////////////////////////////////////////
SysMutex::SysMutex() :
m_mutex()
{

}

////////////////////////////////////////////////////////////////////////////////
//  SysMutex destructor                                                       //
////////////////////////////////////////////////////////////////////////////////
SysMutex::~SysMutex()
{

}


////////////////////////////////////////////////////////////////////////////////
//  Lock the mutex, wait until the mutex is locked                            //
//  return : True if the mutex is locked, false otherwise                     //
////////////////////////////////////////////////////////////////////////////////
bool SysMutex::lock()
{
    bool locked = false;
    unsigned int lockAttempts = 0;
    do
    {
        locked = true;
        ++lockAttempts;
        try
        {
            // Lock the mutex
            m_mutex.lock();
        }
        catch (const std::system_error&)
        {
            // Mutex system error
            locked = false;
        }
        catch (...)
        {
            // Unknown error
            locked = false;
        }
    } while ((!locked) && (lockAttempts <= SysMutexMaxLockAttempts));

    // Mutex locked state
    return locked;
}

////////////////////////////////////////////////////////////////////////////////
//  Try to lock the mutex without waiting                                     //
//  return : True if the mutex is locked, false otherwise                     //
////////////////////////////////////////////////////////////////////////////////
bool SysMutex::trylock()
{
    // Try to lock the mutex
    return m_mutex.try_lock();
}

////////////////////////////////////////////////////////////////////////////////
//  Unlock the mutex                                                          //
////////////////////////////////////////////////////////////////////////////////
void SysMutex::unlock()
{
    m_mutex.unlock();
}

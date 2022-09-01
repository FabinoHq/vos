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
//   For more information, please refer to <https://unlicense.org>            //
////////////////////////////////////////////////////////////////////////////////
//    VOS : Virtual Operating System                                          //
//     System/SysMutexLocker.h : System Mutex locker management               //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_SYSMUTEXLOCKER_HEADER
#define VOS_SYSTEM_SYSMUTEXLOCKER_HEADER

    #include "System.h"
    #include "SysMutex.h"

    #include <thread>
    #include <mutex>
    #include <new>


    ////////////////////////////////////////////////////////////////////////////
    //  SysMutexLocker class definition                                       //
    ////////////////////////////////////////////////////////////////////////////
    class SysMutexLocker
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SysMutexLocker constructor                                    //
            ////////////////////////////////////////////////////////////////////
            SysMutexLocker(SysMutex& mutex);

            ////////////////////////////////////////////////////////////////////
            //  SysMutexLocker destructor                                     //
            ////////////////////////////////////////////////////////////////////
            ~SysMutexLocker();


            ////////////////////////////////////////////////////////////////////
            //  Relock the associated mutex                                   //
            //  return : True if the mutex is locked, false otherwise         //
            ////////////////////////////////////////////////////////////////////
            bool lock();

            ////////////////////////////////////////////////////////////////////
            //  Unlock the associated mutex                                   //
            ////////////////////////////////////////////////////////////////////
            void unlock();


        private:
            ////////////////////////////////////////////////////////////////////
            //  SysMutexLocker private copy constructor : Not copyable        //
            ////////////////////////////////////////////////////////////////////
            SysMutexLocker(const SysMutexLocker&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SysMutexLocker private copy operator : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            SysMutexLocker& operator=(const SysMutexLocker&) = delete;


        private:
            SysMutex&                       m_mutex;    // Associated mutex
            std::lock_guard<std::mutex>*    m_lock;     // Lock guard
    };

#endif // VOS_SYSTEM_SYSMUTEXLOCKER_HEADER

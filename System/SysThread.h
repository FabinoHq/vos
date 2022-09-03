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
//     System/SysThread.h : System Thread management                          //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_SYSTHREAD_HEADER
#define VOS_SYSTEM_SYSTHREAD_HEADER

    #include "System.h"
    #include "SysSleep.h"
    #include "SysMutex.h"
    #include "SysMutexLocker.h"

    #include <thread>
    #include <new>


    ////////////////////////////////////////////////////////////////////////////
    //  SysThread standby sleep time : 10 ms                                  //
    ////////////////////////////////////////////////////////////////////////////
    const double SysThreadStandbySleepTime = 0.01;


    ////////////////////////////////////////////////////////////////////////////
    //  SysThread class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class SysThread
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SysThread default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            SysThread();

            ////////////////////////////////////////////////////////////////////
            //  SysThread virtual destructor                                  //
            ////////////////////////////////////////////////////////////////////
            virtual ~SysThread();


            ////////////////////////////////////////////////////////////////////
            //  Start the thread                                              //
            ////////////////////////////////////////////////////////////////////
            bool start();

            ////////////////////////////////////////////////////////////////////
            //  Stop the thread                                               //
            ////////////////////////////////////////////////////////////////////
            void stop();

            ////////////////////////////////////////////////////////////////////
            //  Set the thread's standby mode                                 //
            ////////////////////////////////////////////////////////////////////
            void standby(bool standbyMode);

            ////////////////////////////////////////////////////////////////////
            //  Thread virtual process                                        //
            ////////////////////////////////////////////////////////////////////
            virtual void process();


        private:
            ////////////////////////////////////////////////////////////////////
            //  SysThread private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            SysThread(const SysThread&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SysThread private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            SysThread& operator=(const SysThread&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SysThread subroutine                                          //
            ////////////////////////////////////////////////////////////////////
            void run();


        private:
            std::thread*    m_thread;       // System thread
            SysMutex        m_mutex;        // Thread states mutex
            bool            m_running;      // Thread running state
            bool            m_standby;      // Thread standby mode
    };


#endif // VOS_SYSTEM_SYSTHREAD_HEADER

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
//     System/SysMutex.h : System Mutex management                            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_SYSMUTEX_HEADER
#define VOS_SYSTEM_SYSMUTEX_HEADER

    #include <exception>
    #include <thread>
    #include <mutex>


    // SysMutex max lock attempts
    const unsigned int SysMutexMaxLockAttempts = 20;
    
    
    ////////////////////////////////////////////////////////////////////////////
    //  SysMutex class definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    class SysMutex
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  SysMutex default constructor                                  //
            ////////////////////////////////////////////////////////////////////
            SysMutex();

            ////////////////////////////////////////////////////////////////////
            //  SysMutex virtual destructor                                   //
            ////////////////////////////////////////////////////////////////////
            virtual ~SysMutex();


            ////////////////////////////////////////////////////////////////////
            //  Lock the mutex, wait until the mutex is locked                //
            //  return : True if the mutex is locked, false otherwise         //
            ////////////////////////////////////////////////////////////////////
            bool lock();

            ////////////////////////////////////////////////////////////////////
            //  Try to lock the mutex without waiting                         //
            //  return : True if the mutex is locked, false otherwise         //
            ////////////////////////////////////////////////////////////////////
            bool trylock();

            ////////////////////////////////////////////////////////////////////
            //  Unlock the mutex                                              //
            ////////////////////////////////////////////////////////////////////
            void unlock();


        private:
            ////////////////////////////////////////////////////////////////////
            //  SysMutex private copy constructor : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            SysMutex(const SysMutex&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  SysMutex private copy operator : Not copyable                 //
            ////////////////////////////////////////////////////////////////////
            SysMutex& operator=(const SysMutex&) = delete;


        private:
            friend class    SysMutexLocker; // Give MutexLocker access to mutex
            std::mutex      m_mutex;        // System mutex
    };

#endif // VOS_SYSTEM_SYSMUTEX_HEADER

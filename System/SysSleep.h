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
//     System/SysSleep.h : System thread sleep management                     //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_SYSTEM_SYSSLEEP_HEADER
#define VOS_SYSTEM_SYSSLEEP_HEADER

    #include "System.h"

    #include <thread>
    #include <chrono>


    ////////////////////////////////////////////////////////////////////////////
    //  Put current thread to sleep for given time in seconds                 //
    ////////////////////////////////////////////////////////////////////////////
    inline void SysSleep(double seconds)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(
            static_cast<long long int>(seconds*1000000)
        ));
    }

    ////////////////////////////////////////////////////////////////////////////
    //  Put current thread to sleep for given time in seconds                 //
    ////////////////////////////////////////////////////////////////////////////
    inline void SysSleep(float seconds)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(
            static_cast<long long int>(seconds*1000000)
        ));
    }

    ////////////////////////////////////////////////////////////////////////////
    //  Release some CPU                                                      //
    ////////////////////////////////////////////////////////////////////////////
    inline void SysYield()
    {
        std::this_thread::yield();
    }


#endif // VOS_SYSTEM_SYSSLEEP_HEADER

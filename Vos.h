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
//     Vos.h : VOS Main class management                                      //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_VOS_HEADER
#define VOS_VOS_HEADER

    #include "System/System.h"
    #include "System/SysCPU.h"
    #include "System/SysMemory.h"
    #include "System/SysVkMemory.h"
    #include "System/SysEvent.h"
    #include "System/SysMouse.h"
    #include "System/SysKeys.h"
    #include "System/SysMessage.h"
    #include "System/SysWindow.h"
    #include "System/SysClock.h"
    #include "System/SysSleep.h"
    #include "System/SysSettings.h"

    #include "Renderer/Renderer.h"
    #include "Resources/Resources.h"
    #include "Physics/Physics.h"
    #include "Softwares/Softwares.h"

    #include <cstddef>
    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  VOS main class definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    class Vos
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Vos default constructor                                       //
            ////////////////////////////////////////////////////////////////////
            Vos();

            ////////////////////////////////////////////////////////////////////
            //  Vos destructor                                                //
            ////////////////////////////////////////////////////////////////////
            ~Vos();


            ////////////////////////////////////////////////////////////////////
            //  Launch VOS                                                    //
            //  return : True if VOS successfully started, false otherwise    //
            ////////////////////////////////////////////////////////////////////
            bool launch();

            ////////////////////////////////////////////////////////////////////
            //  Run VOS                                                       //
            ////////////////////////////////////////////////////////////////////
            void run();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Vos private copy constructor : Not copyable                   //
            ////////////////////////////////////////////////////////////////////
            Vos(const Vos&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Vos private copy operator : Not copyable                      //
            ////////////////////////////////////////////////////////////////////
            Vos& operator=(const Vos&) = delete;


        private:
            bool            m_running;          // VOS running state
            SysClock        m_clock;            // VOS clock
            SysClock        m_frameClock;       // VOS frame clock
            double          m_clockTime;        // VOS clock time
    };


#endif // VOS_VOS_HEADER

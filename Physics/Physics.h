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
//     Physics/Physics.h : Physics management                                 //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_PHYSICS_PHYSICS_HEADER
#define VOS_PHYSICS_PHYSICS_HEADER

    #include "../System/System.h"
    #include "../System/SysThread.h"
    #include "../System/SysMutex.h"
    #include "../Math/Math.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Physics to Renderer conversions                                       //
    ////////////////////////////////////////////////////////////////////////////
    const int64_t RendererToPhysics = Math::OneInt;
    const float PhysicsToRenderer = (1.0f / Math::OneInt);
    const float PhysicsAngleToRenderer = (Math::Pi / (Math::PiInt*1.0f));

    ////////////////////////////////////////////////////////////////////////////
    //  Physics solver settings                                               //
    ////////////////////////////////////////////////////////////////////////////
    const int64_t PhysicsMinEntityHalfSize = (Math::OneInt / 200);
    const int64_t PhysicsMaxSmallStepsIterations = 40;
    const double PhysicsIdleSleepTime = 0.01;
    const double PhysicsErrorSleepTime = 0.1;
    const double PhysicsWaitSleepTime = 0.02;


    ////////////////////////////////////////////////////////////////////////////
    //  PhysicsState enumeration                                              //
    ////////////////////////////////////////////////////////////////////////////
    enum PhysicsState
    {
        PHYSICS_STATE_NONE = 0,
        PHYSICS_STATE_INIT = 1,

        PHYSICS_STATE_IDLE = 2,

        PHYSICS_STATE_ERROR = 3
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Physics class definition                                              //
    ////////////////////////////////////////////////////////////////////////////
    class Physics : public SysThread
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Physics default constructor                                   //
            ////////////////////////////////////////////////////////////////////
            Physics();

            ////////////////////////////////////////////////////////////////////
            //  Physics virtual destructor                                    //
            ////////////////////////////////////////////////////////////////////
            virtual ~Physics();


            ////////////////////////////////////////////////////////////////////
            //  Physics solver thread process                                 //
            ////////////////////////////////////////////////////////////////////
            virtual void process();


            ////////////////////////////////////////////////////////////////////
            //  Init physics solver                                           //
            //  return : True if the physics solver is successfully loaded    //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Get physics solver state                                      //
            //  return : Current physics solver state                         //
            ////////////////////////////////////////////////////////////////////
            PhysicsState getState();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Physics private copy constructor : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            Physics(const Physics&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Physics private copy operator : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            Physics& operator=(const Physics&) = delete;


        private:
            PhysicsState            m_state;            // Physics solver state
            SysMutex                m_stateMutex;       // State mutex
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Physics global instance                                               //
    ////////////////////////////////////////////////////////////////////////////
    extern Physics GPhysics;


#endif // VOS_PHYSICS_PHYSICS_HEADER

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
//     Physics/PhysicsTransform2.h : 2D physics transformations               //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_PHYSICS_PHYSICSTRANSFORM2_HEADER
#define VOS_PHYSICS_PHYSICSTRANSFORM2_HEADER

    #include "../System/System.h"
    #include "../Math/Math.h"
    #include "../Math/Vector2.h"
    #include "../Math/Vector2i.h"
    #include "Physics.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  PhysicsTransform2 class definition                                    //
    ////////////////////////////////////////////////////////////////////////////
    class PhysicsTransform2
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  PhysicsTransform2 default constructor                         //
            ////////////////////////////////////////////////////////////////////
            PhysicsTransform2();

            ////////////////////////////////////////////////////////////////////
            //  PhysicsTransform2 destructor                                  //
            ////////////////////////////////////////////////////////////////////
            ~PhysicsTransform2();


            ////////////////////////////////////////////////////////////////////
            //  Reset physics transformations                                 //
            ////////////////////////////////////////////////////////////////////
            void reset();

            ////////////////////////////////////////////////////////////////////
            //  Precompute physics transforms (thread sync)                   //
            ////////////////////////////////////////////////////////////////////
            void prephysics(const Vector2i& physicsPos, int32_t physicsAngle);

            ////////////////////////////////////////////////////////////////////
            //  Precompute physics isometric transforms (thread sync)         //
            ////////////////////////////////////////////////////////////////////
            void prephysicsIso(
                const Vector2i& physicsPos, int32_t physicsAngle);

            ////////////////////////////////////////////////////////////////////
            //  Offset previous transforms position                           //
            ////////////////////////////////////////////////////////////////////
            void offsetPrevPos(const Vector2i& offset);

            ////////////////////////////////////////////////////////////////////
            //  Offset previous isometric transforms position                 //
            ////////////////////////////////////////////////////////////////////
            void offsetPrevPosIso(const Vector2i& offset);


        private:
            ////////////////////////////////////////////////////////////////////
            //  PhysicsTransform2 private copy constructor : Not copyable     //
            ////////////////////////////////////////////////////////////////////
            PhysicsTransform2(const PhysicsTransform2&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  PhysicsTransform2 private copy operator : Not copyable        //
            ////////////////////////////////////////////////////////////////////
            PhysicsTransform2& operator=(const PhysicsTransform2&) = delete;


        public:
            Vector2         pos;            // Current position
            Vector2         prevPos;        // Previous position
            float           angle;          // Current angle
            float           prevAngle;      // Previous angle
    };


#endif // VOS_PHYSICS_PHYSICSTRANSFORM2_HEADER

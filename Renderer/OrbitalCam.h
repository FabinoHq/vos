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
//     Renderer/OrbitalCam.h : Orbital camera management                      //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_ORBITALCAM_HEADER
#define VOS_RENDERER_ORBITALCAM_HEADER

    #include "../System/System.h"
    #include "../System/SysEvent.h"
    #include "../System/SysMouse.h"
    #include "../System/SysKeys.h"

    #include "../Math/Math.h"
    #include "../Math/Vector3.h"
    #include "../Math/Vector3i.h"
    #include "../Math/Matrix4x4.h"

    #include "../Physics/Physics.h"
    #include "../Physics/PhysicsTransform3.h"

    #include "Camera.h"

    #include <cstdint>
    #include <cstring>


    ////////////////////////////////////////////////////////////////////////////
    //  Orbital camera default settings                                       //
    ////////////////////////////////////////////////////////////////////////////
    const float OrbitalCameraMouseFactor = 0.004f;
    const float OrbitalCameraMinAngle = -(Math::PiHalf-0.001f);
    const float OrbitalCameraMaxAngle = (Math::PiHalf-0.001f);
    const int32_t OrbitalCameraMinDistance = 0;
    const int32_t OrbitalCameraMaxDistance = 50000;


    ////////////////////////////////////////////////////////////////////////////
    //  OrbitalCam class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class OrbitalCam : public Camera
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  OrbitalCam default constructor                                //
            ////////////////////////////////////////////////////////////////////
            OrbitalCam();

            ////////////////////////////////////////////////////////////////////
            //  OrbitalCam virtual destructor                                 //
            ////////////////////////////////////////////////////////////////////
            virtual ~OrbitalCam();


            ////////////////////////////////////////////////////////////////////
            //  Precompute orbital camera physics (thread sync)               //
            ////////////////////////////////////////////////////////////////////
            void prephysics();

            ////////////////////////////////////////////////////////////////////
            //  Compute orbital camera physics (threaded)                     //
            ////////////////////////////////////////////////////////////////////
            void physics();

            ////////////////////////////////////////////////////////////////////
            //  Precompute orbital camera renderer interpolations             //
            ////////////////////////////////////////////////////////////////////
            void precompute(float physicstime);

            ////////////////////////////////////////////////////////////////////
            //  Compute orbital camera                                        //
            //  return : True if the orbital camera is successfully computed  //
            ////////////////////////////////////////////////////////////////////
            virtual bool compute(float ratio);

            ////////////////////////////////////////////////////////////////////
            //  Compute orbital camera from another orbital camera            //
            //  return : True if the orbital camera is successfully computed  //
            ////////////////////////////////////////////////////////////////////
            bool compute(float ratio, OrbitalCam& orbitalCam);


            ////////////////////////////////////////////////////////////////////
            //  Set orbital camera target                                     //
            ////////////////////////////////////////////////////////////////////
            void setTarget(const Vector3i& target);

            ////////////////////////////////////////////////////////////////////
            //  Set orbital camera target                                     //
            ////////////////////////////////////////////////////////////////////
            void setTarget(int32_t targetX, int32_t targetY, int32_t targetZ);

            ////////////////////////////////////////////////////////////////////
            //  Set orbital camera distance from target                       //
            ////////////////////////////////////////////////////////////////////
            void setDistance(int32_t distance);


        private:
            ////////////////////////////////////////////////////////////////////
            //  OrbitalCam private copy constructor : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            OrbitalCam(const OrbitalCam&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  OrbitalCam private copy operator : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            OrbitalCam& operator=(const OrbitalCam&) = delete;


        private:
            PhysicsTransform3       m_transforms;       // Orbitalcam transforms
            Vector3i                m_boundingPos;      // Orbitalcam position
            Vector3i                m_boundingAngles;   // Orbitalcam angles
            Vector3i                m_physicsTarget;    // Orbitalcam target
            int32_t                 m_distance;         // Orbitalcam distance
    };


#endif // VOS_RENDERER_ORBITALCAM_HEADER

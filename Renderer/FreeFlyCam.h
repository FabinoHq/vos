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
//     Renderer/FreeFlyCam.h : Free fly camera management                     //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_FREEFLYCAM_HEADER
#define VOS_RENDERER_FREEFLYCAM_HEADER

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
    //  FreeFlyCam class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class FreeFlyCam : public Camera
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  FreeFlyCam default constructor                                //
            ////////////////////////////////////////////////////////////////////
            FreeFlyCam();

            ////////////////////////////////////////////////////////////////////
            //  FreeFlyCam virtual destructor                                 //
            ////////////////////////////////////////////////////////////////////
            virtual ~FreeFlyCam();


            ////////////////////////////////////////////////////////////////////
            //  Precompute freefly camera physics (thread sync)               //
            ////////////////////////////////////////////////////////////////////
            void prephysics();

            ////////////////////////////////////////////////////////////////////
            //  Compute freefly camera physics (threaded)                     //
            ////////////////////////////////////////////////////////////////////
            void physics();

            ////////////////////////////////////////////////////////////////////
            //  Precompute freefly camera renderer interpolations             //
            ////////////////////////////////////////////////////////////////////
            void precompute(float physicstime);

            ////////////////////////////////////////////////////////////////////
            //  Compute freefly camera                                        //
            //  return : True if the freefly camera is successfully computed  //
            ////////////////////////////////////////////////////////////////////
            virtual bool compute(float ratio);

            ////////////////////////////////////////////////////////////////////
            //  Compute freefly camera from another freefly camera            //
            //  return : True if the freefly camera is successfully computed  //
            ////////////////////////////////////////////////////////////////////
            bool compute(float ratio, FreeFlyCam& freeFlyCam);


            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera bounding position                          //
            ////////////////////////////////////////////////////////////////////
            inline void setBoundingPosition(const Vector3i& boundingPosition)
            {
                m_boundingPos = boundingPosition;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera bounding position                          //
            ////////////////////////////////////////////////////////////////////
            inline void setBoundingPosition(int32_t x, int32_t y, int32_t z)
            {
                m_boundingPos.vec[0] = x;
                m_boundingPos.vec[1] = y;
                m_boundingPos.vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera bounding X position                        //
            ////////////////////////////////////////////////////////////////////
            inline void setBoundingX(int32_t x)
            {
                m_boundingPos.vec[0] = x;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera bounding Y position                        //
            ////////////////////////////////////////////////////////////////////
            inline void setBoundingY(int32_t y)
            {
                m_boundingPos.vec[1] = y;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera bounding Z position                        //
            ////////////////////////////////////////////////////////////////////
            inline void setBoundingZ(int32_t z)
            {
                m_boundingPos.vec[2] = z;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera bounding angles                            //
            ////////////////////////////////////////////////////////////////////
            inline void setBoundingAngles(const Vector3i& boundingAngles)
            {
                m_boundingAngles = boundingAngles;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera bounding angles                            //
            ////////////////////////////////////////////////////////////////////
            inline void setBoundingAngles(
                int32_t angleX, int32_t angleY, int32_t angleZ)
            {
                m_boundingAngles.vec[0] = angleX;
                m_boundingAngles.vec[1] = angleY;
                m_boundingAngles.vec[2] = angleZ;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera bounding X position                        //
            ////////////////////////////////////////////////////////////////////
            inline void setBoundingAngleX(int32_t angleX)
            {
                m_boundingAngles.vec[0] = angleX;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera bounding Y position                        //
            ////////////////////////////////////////////////////////////////////
            inline void setBoundingAngleY(int32_t angleY)
            {
                m_boundingAngles.vec[1] = angleY;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera bounding Z position                        //
            ////////////////////////////////////////////////////////////////////
            inline void setBoundingAngleZ(int32_t angleZ)
            {
                m_boundingAngles.vec[2] = angleZ;
            }


        private:
            ////////////////////////////////////////////////////////////////////
            //  FreeFlyCam private copy constructor : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            FreeFlyCam(const FreeFlyCam&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  FreeFlyCam private copy operator : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            FreeFlyCam& operator=(const FreeFlyCam&) = delete;


        private:
            PhysicsTransform3       m_transforms;       // Camera transforms
            Vector3i                m_boundingPos;      // Camera position
            Vector3i                m_boundingAngles;   // Camera angles
            Vector3                 m_cross;            // Cross product
    };


#endif // VOS_RENDERER_FREEFLYCAM_HEADER

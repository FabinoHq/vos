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
//     Renderer/Camera.h : Free fly camera management                         //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_FREEFLYCAM_HEADER
#define VOS_RENDERER_FREEFLYCAM_HEADER

    #include "../System/System.h"
    #include "Vulkan/Vulkan.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/UniformBuffer.h"
    #include "../Math/Math.h"
    #include "../Math/Vector3.h"
    #include "../Math/Matrix4x4.h"
    #include "Camera.h"

    #include <cstdint>
    #include <cstring>


    ////////////////////////////////////////////////////////////////////////////
    //  Freefly camera default settings                                       //
    ////////////////////////////////////////////////////////////////////////////
    const float FreeflyCameraMouseFactor = 0.004f;
    const float FreeflyCameraMinAngle = -(Math::PiTwo-0.001f);
    const float FreeflyCameraMaxAngle = (Math::PiTwo-0.001f);


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


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
            //  Compute freefly camera                                        //
            ////////////////////////////////////////////////////////////////////
            virtual void compute(Renderer& renderer, float frametime);


            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera speed                                      //
            ////////////////////////////////////////////////////////////////////
            void setSpeed(float speed);

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera forward key state                          //
            ////////////////////////////////////////////////////////////////////
            void setForward(bool forward);

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera backward key state                         //
            ////////////////////////////////////////////////////////////////////
            void setBackward(bool backward);

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera leftward key state                         //
            ////////////////////////////////////////////////////////////////////
            void setLeftward(bool leftward);

            ////////////////////////////////////////////////////////////////////
            //  Set freefly camera rightward key state                        //
            ////////////////////////////////////////////////////////////////////
            void setRightward(bool rightward);

            ////////////////////////////////////////////////////////////////////
            //  Handle mouse move event                                       //
            ////////////////////////////////////////////////////////////////////
            void mouseMove(float mouseDx, float mouseDy);


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
            Vector3     m_cross;        // Freeflycam cross product

            float       m_speed;        // Freeflycam speed

            bool        m_forward;      // Forward key state
            bool        m_backward;     // Backward key state
            bool        m_leftward;     // Leftward key state
            bool        m_rightward;    // Rightward key state
    };


#endif // VOS_RENDERER_FREEFLYCAM_HEADER

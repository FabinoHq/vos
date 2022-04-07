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
//     Renderer/Camera.h : Camera management                                  //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_CAMERA_HEADER
#define VOS_RENDERER_CAMERA_HEADER

    #include "Vulkan/Vulkan.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/UniformBuffer.h"
    #include "../Math/Math.h"
    #include "../Math/Vector3.h"
    #include "../Math/Matrix4x4.h"
    #include "../Math/Transform3.h"

    #include <cstdint>
    #include <cstring>


    ////////////////////////////////////////////////////////////////////////////
    //  Camera default settings                                               //
    ////////////////////////////////////////////////////////////////////////////
    const float CameraDefaultFovy = Math::PiTwo;
    const float CameraDefaultNearPlane = 0.01f;
    const float CameraDefaultFarPlane = 100.0f;


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  Camera class definition                                               //
    ////////////////////////////////////////////////////////////////////////////
    class Camera : public Transform3
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Camera default constructor                                    //
            ////////////////////////////////////////////////////////////////////
            Camera();

            ////////////////////////////////////////////////////////////////////
            //  Camera virtual destructor                                     //
            ////////////////////////////////////////////////////////////////////
            virtual ~Camera();


            ////////////////////////////////////////////////////////////////////
            //  Init camera                                                   //
            //  return : True if the camera is successfully created           //
            ////////////////////////////////////////////////////////////////////
            bool init(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Destroy camera                                                //
            ////////////////////////////////////////////////////////////////////
            void destroyCamera(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Compute camera                                                //
            ////////////////////////////////////////////////////////////////////
            virtual void compute(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Bind camera                                                   //
            //  return : True if the camera is successfully binded            //
            ////////////////////////////////////////////////////////////////////
            bool bind(Renderer& renderer);


            ////////////////////////////////////////////////////////////////////
            //  Set camera fovy angle                                         //
            ////////////////////////////////////////////////////////////////////
            void setFovy(float fovy);

            ////////////////////////////////////////////////////////////////////
            //  Set camera near plane                                         //
            ////////////////////////////////////////////////////////////////////
            void setNearPlane(float nearPlane);

            ////////////////////////////////////////////////////////////////////
            //  Set camera far plane                                          //
            ////////////////////////////////////////////////////////////////////
            void setFarPlane(float farPlane);


            ////////////////////////////////////////////////////////////////////
            //  Get camera fovy angle                                         //
            ////////////////////////////////////////////////////////////////////
            float getFovy();

            ////////////////////////////////////////////////////////////////////
            //  Get camera near plane                                         //
            ////////////////////////////////////////////////////////////////////
            float getNearPlane();

            ////////////////////////////////////////////////////////////////////
            //  Get camera far plane                                          //
            ////////////////////////////////////////////////////////////////////
            float getFarPlane();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Camera private copy constructor : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            Camera(const Camera&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Camera private copy operator : Not copyable                   //
            ////////////////////////////////////////////////////////////////////
            Camera& operator=(const Camera&) = delete;


        protected:
            VkDescriptorSet     m_descriptorSets[RendererMaxSwapchainFrames];
            UniformBuffer       m_uniformBuffers[RendererMaxSwapchainFrames];
            Matrix4x4           m_projMatrix;       // Projection matrix
            Matrix4x4           m_projViewMatrix;   // Projview matrix

            Vector3             m_target;           // Camera target vector
            Vector3             m_upward;           // Camera upward vector
            float               m_fovy;             // Camera fovy
            float               m_nearPlane;        // Camera near plane
            float               m_farPlane;         // Camera far plane
    };


#endif // VOS_RENDERER_CAMERA_HEADER

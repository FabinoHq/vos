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

    #include <cstdint>
    #include <cstring>

    #include "Vulkan/Vulkan.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/UniformBuffer.h"
    #include "../Math/Math.h"
    #include "../Math/Vector3.h"
    #include "../Math/Matrix4x4.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Camera default settings                                               //
    ////////////////////////////////////////////////////////////////////////////
    const float CameraDefaultFovy = 90.0f;
    const float CameraDefaultNearPlane = 0.1f;
    const float CameraDefaultFarPlane = 100.0f;


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  Camera class definition                                               //
    ////////////////////////////////////////////////////////////////////////////
    class Camera
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Camera default constructor                                    //
            ////////////////////////////////////////////////////////////////////
            Camera();

            ////////////////////////////////////////////////////////////////////
            //  Camera destructor                                             //
            ////////////////////////////////////////////////////////////////////
            ~Camera();


            ////////////////////////////////////////////////////////////////////
            //  Init camera                                                   //
            //  return : True if the camera is successfully created           //
            ////////////////////////////////////////////////////////////////////
            bool init(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Bind camera                                                   //
            ////////////////////////////////////////////////////////////////////
            bool bind(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Destroy camera                                                //
            ////////////////////////////////////////////////////////////////////
            void destroyCamera(Renderer& renderer);


            ////////////////////////////////////////////////////////////////////
            //  Set camera position                                           //
            ////////////////////////////////////////////////////////////////////
            void setPosition(float x, float y, float z);

            ////////////////////////////////////////////////////////////////////
            //  Set camera position                                           //
            ////////////////////////////////////////////////////////////////////
            void setPosition(Vector3& position);

            ////////////////////////////////////////////////////////////////////
            //  Set camera X position                                         //
            ////////////////////////////////////////////////////////////////////
            void setX(float x);

            ////////////////////////////////////////////////////////////////////
            //  Set camera Y position                                         //
            ////////////////////////////////////////////////////////////////////
            void setY(float y);

            ////////////////////////////////////////////////////////////////////
            //  Set camera Z position                                         //
            ////////////////////////////////////////////////////////////////////
            void setZ(float z);

            ////////////////////////////////////////////////////////////////////
            //  Translate camera                                              //
            ////////////////////////////////////////////////////////////////////
            void move(float x, float y, float z);

            ////////////////////////////////////////////////////////////////////
            //  Translate camera                                              //
            ////////////////////////////////////////////////////////////////////
            void move(Vector3& vector);

            ////////////////////////////////////////////////////////////////////
            //  Translate camera on X axis                                    //
            ////////////////////////////////////////////////////////////////////
            void moveX(float x);

            ////////////////////////////////////////////////////////////////////
            //  Translate camera on Y axis                                    //
            ////////////////////////////////////////////////////////////////////
            void moveY(float y);

            ////////////////////////////////////////////////////////////////////
            //  Translate camera on Z axis                                    //
            ////////////////////////////////////////////////////////////////////
            void moveZ(float z);

            ////////////////////////////////////////////////////////////////////
            //  Set camera angles                                             //
            ////////////////////////////////////////////////////////////////////
            void setAngles(float angleX, float angleY, float angleZ);

            ////////////////////////////////////////////////////////////////////
            //  Set camera angles                                             //
            ////////////////////////////////////////////////////////////////////
            void setAngles(Vector3& angles);

            ////////////////////////////////////////////////////////////////////
            //  Set camera X angle                                            //
            ////////////////////////////////////////////////////////////////////
            void setAngleX(float angleX);

            ////////////////////////////////////////////////////////////////////
            //  Set camera Y angle                                            //
            ////////////////////////////////////////////////////////////////////
            void setAngleY(float angleY);

            ////////////////////////////////////////////////////////////////////
            //  Set camera Z angle                                            //
            ////////////////////////////////////////////////////////////////////
            void setAngleZ(float angleZ);

            ////////////////////////////////////////////////////////////////////
            //  Rotate camera                                                 //
            ////////////////////////////////////////////////////////////////////
            void rotate(float angleX, float angleY, float angleZ);

            ////////////////////////////////////////////////////////////////////
            //  Rotate camera                                                 //
            ////////////////////////////////////////////////////////////////////
            void rotate(Vector3& angles);

            ////////////////////////////////////////////////////////////////////
            //  Rotate camera around the X axis                               //
            ////////////////////////////////////////////////////////////////////
            void rotateX(float angleX);

            ////////////////////////////////////////////////////////////////////
            //  Rotate camera around the Y axis                               //
            ////////////////////////////////////////////////////////////////////
            void rotateY(float angleY);

            ////////////////////////////////////////////////////////////////////
            //  Rotate camera around the Z axis                               //
            ////////////////////////////////////////////////////////////////////
            void rotateZ(float angleZ);

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


        private:
            ////////////////////////////////////////////////////////////////////
            //  Camera private copy constructor : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            Camera(const Camera&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Camera private copy operator : Not copyable                   //
            ////////////////////////////////////////////////////////////////////
            Camera& operator=(const Camera&) = delete;


        private:
            VkDescriptorSet     m_descriptorSets[RendererMaxSwapchainFrames];
            UniformBuffer       m_uniformBuffers[RendererMaxSwapchainFrames];
            Matrix4x4           m_projMatrix;       // Projection matrix
            Matrix4x4           m_viewMatrix;       // View matrix
            Matrix4x4           m_projViewMatrix;   // Projview matrix

            Vector3             m_position;         // Camera position
            Vector3             m_angles;           // Camera angles
            Vector3             m_target;           // Camera target vector
            Vector3             m_upward;           // Camera upward vector
            float               m_fovy;             // Camera fovy
            float               m_nearPlane;        // Camera near plane
            float               m_farPlane;         // Camera far plane
    };


#endif // VOS_RENDERER_CAMERA_HEADER

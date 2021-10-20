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
//     Renderer/View.h : View management                                      //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VIEW_HEADER
#define VOS_RENDERER_VIEW_HEADER

    #include <cstdint>
    #include <cstring>

    #include "Vulkan/Vulkan.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/UniformBuffer.h"
    #include "../Math/Math.h"
    #include "../Math/Vector2.h"
    #include "../Math/Matrix4x4.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


    ////////////////////////////////////////////////////////////////////////////
    //  View class definition                                                 //
    ////////////////////////////////////////////////////////////////////////////
    class View
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  View default constructor                                      //
            ////////////////////////////////////////////////////////////////////
            View();

            ////////////////////////////////////////////////////////////////////
            //  View destructor                                               //
            ////////////////////////////////////////////////////////////////////
            ~View();


            ////////////////////////////////////////////////////////////////////
            //  Init view                                                     //
            //  return : True if the view is successfully created             //
            ////////////////////////////////////////////////////////////////////
            bool init(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Bind view                                                     //
            ////////////////////////////////////////////////////////////////////
            bool bind(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Destroy view                                                  //
            ////////////////////////////////////////////////////////////////////
            void destroyView(Renderer& renderer);


            ////////////////////////////////////////////////////////////////////
            //  Set view position                                             //
            ////////////////////////////////////////////////////////////////////
            void setPosition(float x, float y);

            ////////////////////////////////////////////////////////////////////
            //  Set view position                                             //
            ////////////////////////////////////////////////////////////////////
            void setPosition(Vector2& position);

            ////////////////////////////////////////////////////////////////////
            //  Set view X position                                           //
            ////////////////////////////////////////////////////////////////////
            void setX(float x);

            ////////////////////////////////////////////////////////////////////
            //  Set view Y position                                           //
            ////////////////////////////////////////////////////////////////////
            void setY(float y);

            ////////////////////////////////////////////////////////////////////
            //  Translate view                                                //
            ////////////////////////////////////////////////////////////////////
            void move(float x, float y);

            ////////////////////////////////////////////////////////////////////
            //  Translate view                                                //
            ////////////////////////////////////////////////////////////////////
            void move(Vector2& vector);

            ////////////////////////////////////////////////////////////////////
            //  Translate view on X axis                                      //
            ////////////////////////////////////////////////////////////////////
            void moveX(float x);

            ////////////////////////////////////////////////////////////////////
            //  Translate view on Y axis                                      //
            ////////////////////////////////////////////////////////////////////
            void moveY(float y);

            ////////////////////////////////////////////////////////////////////
            //  Set view size                                                 //
            ////////////////////////////////////////////////////////////////////
            void setSize(float width, float height);

            ////////////////////////////////////////////////////////////////////
            //  Set view size                                                 //
            ////////////////////////////////////////////////////////////////////
            void setSize(Vector2& size);

            ////////////////////////////////////////////////////////////////////
            //  Set view width                                                //
            ////////////////////////////////////////////////////////////////////
            void setWidth(float width);

            ////////////////////////////////////////////////////////////////////
            //  Set view height                                               //
            ////////////////////////////////////////////////////////////////////
            void setHeight(float height);

            ////////////////////////////////////////////////////////////////////
            //  Set view rotation angle                                       //
            ////////////////////////////////////////////////////////////////////
            void setAngle(float angle);

            ////////////////////////////////////////////////////////////////////
            //  Rotate view                                                   //
            ////////////////////////////////////////////////////////////////////
            void rotate(float angle);


        private:
            ////////////////////////////////////////////////////////////////////
            //  View private copy constructor : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            View(const View&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  View private copy operator : Not copyable                     //
            ////////////////////////////////////////////////////////////////////
            View& operator=(const View&) = delete;


        private:
            VkDescriptorSet     m_descriptorSets[RendererMaxSwapchainFrames];
            UniformBuffer       m_uniformBuffers[RendererMaxSwapchainFrames];
            Matrix4x4           m_projMatrix;       // Projection matrix
            Matrix4x4           m_viewMatrix;       // View matrix
            Matrix4x4           m_projViewMatrix;   // Projview matrix
            Vector2             m_position;         // View position
            Vector2             m_size;             // View size
            float               m_angle;            // View angle
    };


#endif // VOS_RENDERER_VIEW_HEADER

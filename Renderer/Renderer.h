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
//     Renderer/Renderer.h : Renderer management                              //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_RENDERER_HEADER
#define VOS_RENDERER_RENDERER_HEADER

    #include "../System/System.h"
    #include "../System/SysMessage.h"
    #include "../System/SysWindow.h"
    #include "../System/SysVulkan.h"
    #include "Vulkan/Vulkan.h"
    #include "Vulkan/VulkanMemory.h"
    #include "Vulkan/VulkanQueue.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/VulkanBuffer.h"
    #include "Vulkan/VertexBuffer.h"
    #include "Vulkan/UniformBuffer.h"
    #include "Vulkan/GraphicsLayout.h"
    #include "Vulkan/Pipeline.h"
    #include "Vulkan/Shader.h"
    #include "Vulkan/Texture.h"
    #include "Vulkan/CubeMap.h"
    #include "BackRenderer.h"
    #include "View.h"
    #include "Camera.h"
    #include "FreeFlyCam.h"
    #include "OrbitalCam.h"
    #include "Sprite.h"
    #include "../Math/Math.h"
    #include "../Math/Vector2.h"
    #include "../Math/Matrix4x4.h"

    #include "Shaders/Default.h"
    #include "Shaders/DefaultProc.h"
    #include "Shaders/NinePatch.h"
    #include "Shaders/Rectangle.h"
    #include "Shaders/Ellipse.h"
    #include "Shaders/PxText.h"
    #include "Shaders/SkyBox.h"
    #include "Shaders/StaticMesh.h"
    #include "Shaders/StaticProc.h"
    #include "Shaders/HeightMap.h"

    #include "../Resources/Resources.h"

    #include <cstddef>
    #include <cstdint>
    #include <vector>


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer clear color                                                  //
    ////////////////////////////////////////////////////////////////////////////
    const VkClearColorValue RendererClearColor = {0.0f, 0.0f, 0.0f, 1.0f};

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer compositing quad offset                                      //
    ////////////////////////////////////////////////////////////////////////////
    const float RendererCompositingQuadOffset = 0.00001f;

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer max uniforms descriptor sets                                 //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t RendererMaxUniformsDesc = 256;

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer max textures descriptor sets                                 //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t RendererMaxTexturesDesc = 2048;


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Renderer default constructor                                  //
            ////////////////////////////////////////////////////////////////////
            Renderer();

            ////////////////////////////////////////////////////////////////////
            //  Renderer destructor                                           //
            ////////////////////////////////////////////////////////////////////
            ~Renderer();


            ////////////////////////////////////////////////////////////////////
            //  Init renderer                                                 //
            //  return : True if the renderer is successfully loaded          //
            ////////////////////////////////////////////////////////////////////
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Init renderer pipelines                                       //
            //  return : True if the renderer pipelines are ready             //
            ////////////////////////////////////////////////////////////////////
            bool initPipelines();

            ////////////////////////////////////////////////////////////////////
            //  Start rendering frame                                         //
            //  return : True if the rendering frame is ready                 //
            ////////////////////////////////////////////////////////////////////
            bool startFrame();

            ////////////////////////////////////////////////////////////////////
            //  End rendering frame                                           //
            //  return : True if the frame is rendering                       //
            ////////////////////////////////////////////////////////////////////
            bool endFrame();

            ////////////////////////////////////////////////////////////////////
            //  Start render pass                                             //
            ////////////////////////////////////////////////////////////////////
            void startRenderPass();

            ////////////////////////////////////////////////////////////////////
            //  End render pass                                               //
            ////////////////////////////////////////////////////////////////////
            void endRenderPass();

            ////////////////////////////////////////////////////////////////////
            //  Start final render pass                                       //
            ////////////////////////////////////////////////////////////////////
            void startFinalPass();

            ////////////////////////////////////////////////////////////////////
            //  End final render pass                                         //
            ////////////////////////////////////////////////////////////////////
            void endFinalPass();

            ////////////////////////////////////////////////////////////////////
            //  Wait renderer device for idle state                           //
            //  return : True if the renderer device is in idle state         //
            ////////////////////////////////////////////////////////////////////
            bool waitDeviceIdle();

            ////////////////////////////////////////////////////////////////////
            //  Destroy renderer                                              //
            ////////////////////////////////////////////////////////////////////
            void destroyRenderer();


            ////////////////////////////////////////////////////////////////////
            //  Bind renderer pipeline                                        //
            ////////////////////////////////////////////////////////////////////
            void bindPipeline(RendererPipeline rendererPipeline);

            ////////////////////////////////////////////////////////////////////
            //  Bind renderer default vertex buffer                           //
            ////////////////////////////////////////////////////////////////////
            void bindDefaultVertexBuffer();


            ////////////////////////////////////////////////////////////////////
            //  Set renderer default view                                     //
            //  return : True if the default view is successfully set         //
            ////////////////////////////////////////////////////////////////////
            bool setDefaultView();

            ////////////////////////////////////////////////////////////////////
            //  Set renderer view                                             //
            //  return : True if the view is successfully set                 //
            ////////////////////////////////////////////////////////////////////
            bool setView(View& view);

            ////////////////////////////////////////////////////////////////////
            //  Set renderer camera                                           //
            //  return : True if the camera is successfully set               //
            ////////////////////////////////////////////////////////////////////
            bool setCamera(Camera& camera);


            ////////////////////////////////////////////////////////////////////
            //  Get renderer ready state                                      //
            //  return : True if the renderer is ready, false otherwise       //
            ////////////////////////////////////////////////////////////////////
            bool isReady();

            ////////////////////////////////////////////////////////////////////
            //  Get renderer width                                            //
            //  return : Renderer width                                       //
            ////////////////////////////////////////////////////////////////////
            uint32_t getWidth();

            ////////////////////////////////////////////////////////////////////
            //  Get renderer height                                           //
            //  return : Renderer height                                      //
            ////////////////////////////////////////////////////////////////////
            uint32_t getHeight();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Renderer private copy constructor : Not copyable              //
            ////////////////////////////////////////////////////////////////////
            Renderer(const Renderer&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Renderer private copy operator : Not copyable                 //
            ////////////////////////////////////////////////////////////////////
            Renderer& operator=(const Renderer&) = delete;


            ////////////////////////////////////////////////////////////////////
            //  Create Vulkan instance                                        //
            //  return : True if Vulkan instance is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool createVulkanInstance();

            ////////////////////////////////////////////////////////////////////
            //  Select Vulkan device                                          //
            //  return : True if Vulkan device is successfully selected       //
            ////////////////////////////////////////////////////////////////////
            bool selectVulkanDevice();

            ////////////////////////////////////////////////////////////////////
            //  Resize renderer frame                                         //
            //  return : True if the renderer is successfully resized         //
            ////////////////////////////////////////////////////////////////////
            bool resize();


        public:
            bool                m_rendererReady;        // Renderer ready state
            uint32_t            m_frameIndex;           // Current frame index
            VulkanQueue         m_graphicsQueue;        // Graphics queue
            VulkanQueue         m_surfaceQueue;         // Surface queue
            VkDescriptorPool    m_uniformsDescPool;     // Uniforms desc pool
            VkDescriptorPool    m_texturesDescPool;     // Textures desc pool

            BackRenderer        m_mainRenderer;         // Main renderer
            Sprite              m_mainSprite;           // Main sprite

            Pipeline*           m_pipelines;            // Pipelines

            View                m_view;                 // Default view
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer global instance                                              //
    ////////////////////////////////////////////////////////////////////////////
    extern Renderer GRenderer;


#endif // VOS_RENDERER_RENDERER_HEADER

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
//     Renderer/Renderer.h : Renderer management                              //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_RENDERER_HEADER
#define VOS_RENDERER_RENDERER_HEADER

    #include "../System/SysWindow.h"
    #include "../System/SysVulkan.h"
    #include "Vulkan.h"
    #include "VulkanQueue.h"
    #include "Swapchain.h"
    #include "VulkanBuffer.h"
    #include "VertexBuffer.h"
    #include "UniformBuffer.h"
    #include "Texture.h"
    #include "Shader.h"
    #include "../Math/Math.h"
    #include "../Math/Matrix4x4.h"

    #include <vector>


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer clear color                                                  //
    ////////////////////////////////////////////////////////////////////////////
    const VkClearValue RendererClearColor = {0.0f, 0.0f, 0.0f, 1.0f};


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
            bool init(SysWindow* sysWindow);

            ////////////////////////////////////////////////////////////////////
            //  Render frame                                                  //
            ////////////////////////////////////////////////////////////////////
            void render();

            ////////////////////////////////////////////////////////////////////
            //  Cleanup renderer                                              //
            ////////////////////////////////////////////////////////////////////
            void cleanup();


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
            //  Create descriptor set layout                                  //
            //  return : True if descriptor layout is successfully created    //
            ////////////////////////////////////////////////////////////////////
            bool createDescriptorSetLayout();

            ////////////////////////////////////////////////////////////////////
            //  Create pipeline layout                                        //
            //  return : True if pipeline layout is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool createPipelineLayout();

            ////////////////////////////////////////////////////////////////////
            //  Create pipeline                                               //
            //  return : True if pipeline is successfully created             //
            ////////////////////////////////////////////////////////////////////
            bool createPipeline();

            ////////////////////////////////////////////////////////////////////
            //  Create descriptor pool                                        //
            //  return : True if descriptor pool is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool createDescriptorPool();

            ////////////////////////////////////////////////////////////////////
            //  Resize renderer frame                                         //
            //  return : True if the renderer is successfully resized         //
            ////////////////////////////////////////////////////////////////////
            bool resize();


        private:
            bool                m_rendererReady;        // Renderer ready state
            SysWindow*          m_sysWindow;            // SysWindow pointer
            VulkanLibHandle     m_vulkanLibHandle;      // Vulkan library handle
            VkInstance          m_vulkanInstance;       // Vulkan instance
            VkSurfaceKHR        m_vulkanSurface;        // Vulkan surface
            VkPhysicalDevice    m_physicalDevice;       // Physical device
            VkDevice            m_vulkanDevice;         // Vulkan device
            VulkanQueue         m_graphicsQueue;        // Graphics queue
            VulkanQueue         m_surfaceQueue;         // Surface queue
            VulkanQueue         m_transferQueue;        // Transfer queue
            VkCommandPool       m_transferCommandPool;  // Transfer command pool

            Swapchain               m_swapchain;            // Swapchain
            VkDescriptorSetLayout   m_descriptorSetLayout;  // Descriptor layout
            VkPipelineLayout        m_pipelineLayout;       // Pipeline layout
            VkPipeline              m_pipeline;             // Graphics pipeline
            VertexBuffer            m_vertexBuffer;         // Vertex buffer
            Texture                 m_texture;              // Test texture
            Shader                  m_shader;               // Default shader

            UniformBuffer       m_uniformBuffer[RendererMaxSwapchainFrames];
            VkDescriptorPool    m_descriptorPool[RendererMaxSwapchainFrames];
            VkDescriptorSet     m_descriptorSet[RendererMaxSwapchainFrames];
    };


#endif // VOS_RENDERER_RENDERER_HEADER

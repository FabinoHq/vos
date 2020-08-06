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

    #include <vector>


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer clear color                                                  //
    ////////////////////////////////////////////////////////////////////////////
    const VkClearColorValue RendererClearColor = {0.0f, 0.0f, 0.0f, 1.0f};


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanImage data structure                                            //
    ////////////////////////////////////////////////////////////////////////////
    struct VulkanImage
    {
        VulkanImage()
        {
            handle = 0;
            view = 0;
            sampler = 0;
            memory = 0;
        }

        VkImage         handle;     // Image handle
        VkImageView     view;       // Image view
        VkSampler       sampler;    // Image sampler
        VkDeviceMemory  memory;     // Image memory
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VulkanSwapchain data structure                                        //
    ////////////////////////////////////////////////////////////////////////////
    struct VulkanSwapchain
    {
        VulkanSwapchain()
        {
            handle = 0;
            format = VK_FORMAT_UNDEFINED;
            extent.width = 0;
            extent.height = 0;
            imagesCnt = 0;
        }

        VkSwapchainKHR              handle;     // Swapchain handle
        VkFormat                    format;     // Swapchain format
        VkExtent2D                  extent;     // Swapchain extent
        uint32_t                    imagesCnt;  // Swapchain images count
        std::vector<VulkanImage>    images;     // Swapchain images
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VulkanCommands data structure                                         //
    ////////////////////////////////////////////////////////////////////////////
    struct VulkanCommands
    {
        VulkanCommands()
        {
            pool = 0;
        }

        VkCommandPool                   pool;       // Commands pool
        std::vector<VkCommandBuffer>    buffers;    // Commands buffers
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VulkanSemaphores data structure                                       //
    ////////////////////////////////////////////////////////////////////////////
    struct VulkanSemaphores
    {
        VulkanSemaphores()
        {
            imageAvailable = 0;
            renderFinished = 0;
        }

        VkSemaphore     imageAvailable;
        VkSemaphore     renderFinished;
    };


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
            //  Close renderer                                                //
            ////////////////////////////////////////////////////////////////////
            void close();


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
            //  Get Vulkan queues handles                                     //
            //  return : True if queues handles are valid                     //
            ////////////////////////////////////////////////////////////////////
            bool getQueuesHandles();

            ////////////////////////////////////////////////////////////////////
            //  Create Vulkan swapchain                                       //
            //  return : True if Vulkan swapchain is successfully created     //
            ////////////////////////////////////////////////////////////////////
            bool createVulkanSwapchain();

            ////////////////////////////////////////////////////////////////////
            //  Create render pass                                            //
            //  return : True if render pass is successfully created          //
            ////////////////////////////////////////////////////////////////////
            bool createRenderPass();

            ////////////////////////////////////////////////////////////////////
            //  Create command buffers                                        //
            //  return : True if command buffers are successfully created     //
            ////////////////////////////////////////////////////////////////////
            bool createCommandBuffers();

            ////////////////////////////////////////////////////////////////////
            //  Create semaphores                                             //
            //  return : True if semaphores are successfully created          //
            ////////////////////////////////////////////////////////////////////
            bool createSemaphores();

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

            uint32_t            m_graphicsQueueIndex;   // Graphics queue index
            VkQueue             m_graphicsQueueHandle;  // Graphics queue handle
            uint32_t            m_surfaceQueueIndex;    // Surface queue index
            VkQueue             m_surfaceQueueHandle;   // Surface queue handle

            VulkanSwapchain     m_swapchain;            // Vulkan swapchain
            VkRenderPass        m_renderPass;           // Render pass
            VulkanCommands      m_commands;             // Commands
            VulkanSemaphores    m_semaphores;           // Semaphores
    };


#endif // VOS_RENDERER_RENDERER_HEADER

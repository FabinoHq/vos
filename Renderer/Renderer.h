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

    #include "../SysWindow.h"
    #include "../Vulkan.h"

    #include <vector>


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
        }

        VkSwapchainKHR              handle;     // Swapchain handle
        VkFormat                    format;     // Swapchain format
        VkExtent2D                  extent;     // Swapchain extent
        std::vector<VulkanImage>    images;     // Swapchain images
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
            //  Clear renderer frame                                          //
            ////////////////////////////////////////////////////////////////////
            void clear();


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
    };


#endif // VOS_RENDERER_RENDERER_HEADER

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
    //  Renderer default vertex shader                                        //
    ////////////////////////////////////////////////////////////////////////////
    const size_t DefaultVertexShaderSize = 1792;
    const uint32_t DefaultVertexShader[] =
    {
        0x03022307, 0x00000100, 0x00000800, 0x26000000,
        0x00000000, 0x11000200, 0x01000000, 0x0B000600,
        0x01000000, 0x474C534C, 0x2E737464, 0x2E343530,
        0x00000000, 0x0E000300, 0x00000000, 0x01000000,
        0x0F000700, 0x00000000, 0x04000000, 0x6D61696E,
        0x00000000, 0x17000000, 0x1B000000, 0x03000300,
        0x02000000, 0xC2010000, 0x05000400, 0x04000000,
        0x6D61696E, 0x00000000, 0x05000300, 0x0C000000,
        0x706F7300, 0x05000600, 0x15000000, 0x676C5F50,
        0x65725665, 0x72746578, 0x00000000, 0x06000600,
        0x15000000, 0x00000000, 0x676C5F50, 0x6F736974,
        0x696F6E00, 0x05000300, 0x17000000, 0x00000000,
        0x05000600, 0x1B000000, 0x676C5F56, 0x65727465,
        0x78496E64, 0x65780000, 0x48000500, 0x15000000,
        0x00000000, 0x0B000000, 0x00000000, 0x47000300,
        0x15000000, 0x02000000, 0x47000400, 0x1B000000,
        0x0B000000, 0x2A000000, 0x13000200, 0x02000000,
        0x21000300, 0x03000000, 0x02000000, 0x16000300,
        0x06000000, 0x20000000, 0x17000400, 0x07000000,
        0x06000000, 0x02000000, 0x15000400, 0x08000000,
        0x20000000, 0x00000000, 0x2B000400, 0x08000000,
        0x09000000, 0x03000000, 0x1C000400, 0x0A000000,
        0x07000000, 0x09000000, 0x20000400, 0x0B000000,
        0x07000000, 0x0A000000, 0x2B000400, 0x06000000,
        0x0D000000, 0x333333BF, 0x2B000400, 0x06000000,
        0x0E000000, 0x3333333F, 0x2C000500, 0x07000000,
        0x0F000000, 0x0D000000, 0x0E000000, 0x2C000500,
        0x07000000, 0x10000000, 0x0E000000, 0x0E000000,
        0x2B000400, 0x06000000, 0x11000000, 0x00000000,
        0x2C000500, 0x07000000, 0x12000000, 0x11000000,
        0x0D000000, 0x2C000600, 0x0A000000, 0x13000000,
        0x0F000000, 0x10000000, 0x12000000, 0x17000400,
        0x14000000, 0x06000000, 0x04000000, 0x1E000300,
        0x15000000, 0x14000000, 0x20000400, 0x16000000,
        0x03000000, 0x15000000, 0x3B000400, 0x16000000,
        0x17000000, 0x03000000, 0x15000400, 0x18000000,
        0x20000000, 0x01000000, 0x2B000400, 0x18000000,
        0x19000000, 0x00000000, 0x20000400, 0x1A000000,
        0x01000000, 0x18000000, 0x3B000400, 0x1A000000,
        0x1B000000, 0x01000000, 0x20000400, 0x1D000000,
        0x07000000, 0x07000000, 0x2B000400, 0x06000000,
        0x20000000, 0x0000803F, 0x20000400, 0x24000000,
        0x03000000, 0x14000000, 0x36000500, 0x02000000,
        0x04000000, 0x00000000, 0x03000000, 0xF8000200,
        0x05000000, 0x3B000400, 0x0B000000, 0x0C000000,
        0x07000000, 0x3E000300, 0x0C000000, 0x13000000,
        0x3D000400, 0x18000000, 0x1C000000, 0x1B000000,
        0x41000500, 0x1D000000, 0x1E000000, 0x0C000000,
        0x1C000000, 0x3D000400, 0x07000000, 0x1F000000,
        0x1E000000, 0x51000500, 0x06000000, 0x21000000,
        0x1F000000, 0x00000000, 0x51000500, 0x06000000,
        0x22000000, 0x1F000000, 0x01000000, 0x50000700,
        0x14000000, 0x23000000, 0x21000000, 0x22000000,
        0x11000000, 0x20000000, 0x41000500, 0x24000000,
        0x25000000, 0x17000000, 0x19000000, 0x3E000300,
        0x25000000, 0x23000000, 0xFD000100, 0x38000100
    };

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer default fragment shader                                      //
    ////////////////////////////////////////////////////////////////////////////
    const size_t DefaultFragmentShaderSize = 736;
    const uint32_t DefaultFragmentShader[] =
    {
        0x03022307, 0x00000100, 0x00000800, 0x0E000000,
        0x00000000, 0x11000200, 0x01000000, 0x0B000600,
        0x01000000, 0x474C534C, 0x2E737464, 0x2E343530,
        0x00000000, 0x0E000300, 0x00000000, 0x01000000,
        0x0F000600, 0x04000000, 0x04000000, 0x6D61696E,
        0x00000000, 0x09000000, 0x10000300, 0x04000000,
        0x07000000, 0x03000300, 0x02000000, 0xC2010000,
        0x05000400, 0x04000000, 0x6D61696E, 0x00000000,
        0x05000500, 0x09000000, 0x6F75745F, 0x436F6C6F,
        0x72000000, 0x47000400, 0x09000000, 0x1E000000,
        0x00000000, 0x13000200, 0x02000000, 0x21000300,
        0x03000000, 0x02000000, 0x16000300, 0x06000000,
        0x20000000, 0x17000400, 0x07000000, 0x06000000,
        0x04000000, 0x20000400, 0x08000000, 0x03000000,
        0x07000000, 0x3B000400, 0x08000000, 0x09000000,
        0x03000000, 0x2B000400, 0x06000000, 0x0A000000,
        0x00000000, 0x2B000400, 0x06000000, 0x0B000000,
        0xCDCCCC3E, 0x2B000400, 0x06000000, 0x0C000000,
        0x0000803F, 0x2C000700, 0x07000000, 0x0D000000,
        0x0A000000, 0x0B000000, 0x0C000000, 0x0C000000,
        0x36000500, 0x02000000, 0x04000000, 0x00000000,
        0x03000000, 0xF8000200, 0x05000000, 0x3E000300,
        0x09000000, 0x0D000000, 0xFD000100, 0x38000100
    };


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
            //  Create framebuffers                                           //
            //  return : True if framebuffers are successfully created        //
            ////////////////////////////////////////////////////////////////////
            bool createFramebuffers();

            ////////////////////////////////////////////////////////////////////
            //  Create default shaders                                        //
            //  return : True if default shaders are successfully created     //
            ////////////////////////////////////////////////////////////////////
            bool createDefaultShaders();

            ////////////////////////////////////////////////////////////////////
            //  Create pipeline layout                                        //
            //  return : True if pipeline layout successfully created         //
            ////////////////////////////////////////////////////////////////////
            bool createPipelineLayout();

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
            std::vector<VkFramebuffer>  m_framebuffers; // Framebuffers
            VkShaderModule      m_vertexShader;         // Vertex shader
            VkShaderModule      m_fragmentShader;       // Fragment shader
            VkPipelineLayout    m_pipelineLayout;       // Pipeline layout
            VulkanCommands      m_commands;             // Commands
            VulkanSemaphores    m_semaphores;           // Semaphores
    };


#endif // VOS_RENDERER_RENDERER_HEADER

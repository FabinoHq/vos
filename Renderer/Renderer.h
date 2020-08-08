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
    const VkClearValue RendererClearColor = {0.0f, 0.0f, 0.0f, 1.0f};

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer default vertex shader                                        //
    ////////////////////////////////////////////////////////////////////////////
    const size_t DefaultVertexShaderSize = 896;
    const uint32_t DefaultVertexShader[] =
    {
        0x07230203u, 0x00010000u, 0x00080000u, 0x00000026u,
        0x00000000u, 0x00020011u, 0x00000001u, 0x0006000Bu,
        0x00000001u, 0x4C534C47u, 0x6474732Eu, 0x3035342Eu,
        0x00000000u, 0x0003000Eu, 0x00000000u, 0x00000001u,
        0x0007000Fu, 0x00000000u, 0x00000004u, 0x6E69616Du,
        0x00000000u, 0x00000017u, 0x0000001Bu, 0x00030003u,
        0x00000002u, 0x000001C2u, 0x00040005u, 0x00000004u,
        0x6E69616Du, 0x00000000u, 0x00030005u, 0x0000000Cu,
        0x00736F70u, 0x00060005u, 0x00000015u, 0x505F6C67u,
        0x65567265u, 0x78657472u, 0x00000000u, 0x00060006u,
        0x00000015u, 0x00000000u, 0x505F6C67u, 0x7469736Fu,
        0x006E6F69u, 0x00030005u, 0x00000017u, 0x00000000u,
        0x00060005u, 0x0000001Bu, 0x565F6C67u, 0x65747265u,
        0x646E4978u, 0x00007865u, 0x00050048u, 0x00000015u,
        0x00000000u, 0x0000000Bu, 0x00000000u, 0x00030047u,
        0x00000015u, 0x00000002u, 0x00040047u, 0x0000001Bu,
        0x0000000Bu, 0x0000002Au, 0x00020013u, 0x00000002u,
        0x00030021u, 0x00000003u, 0x00000002u, 0x00030016u,
        0x00000006u, 0x00000020u, 0x00040017u, 0x00000007u,
        0x00000006u, 0x00000002u, 0x00040015u, 0x00000008u,
        0x00000020u, 0x00000000u, 0x0004002Bu, 0x00000008u,
        0x00000009u, 0x00000003u, 0x0004001Cu, 0x0000000Au,
        0x00000007u, 0x00000009u, 0x00040020u, 0x0000000Bu,
        0x00000007u, 0x0000000Au, 0x0004002Bu, 0x00000006u,
        0x0000000Du, 0xBF333333u, 0x0004002Bu, 0x00000006u,
        0x0000000Eu, 0x3F333333u, 0x0005002Cu, 0x00000007u,
        0x0000000Fu, 0x0000000Du, 0x0000000Eu, 0x0005002Cu,
        0x00000007u, 0x00000010u, 0x0000000Eu, 0x0000000Eu,
        0x0004002Bu, 0x00000006u, 0x00000011u, 0x00000000u,
        0x0005002Cu, 0x00000007u, 0x00000012u, 0x00000011u,
        0x0000000Du, 0x0006002Cu, 0x0000000Au, 0x00000013u,
        0x0000000Fu, 0x00000010u, 0x00000012u, 0x00040017u,
        0x00000014u, 0x00000006u, 0x00000004u, 0x0003001Eu,
        0x00000015u, 0x00000014u, 0x00040020u, 0x00000016u,
        0x00000003u, 0x00000015u, 0x0004003Bu, 0x00000016u,
        0x00000017u, 0x00000003u, 0x00040015u, 0x00000018u,
        0x00000020u, 0x00000001u, 0x0004002Bu, 0x00000018u,
        0x00000019u, 0x00000000u, 0x00040020u, 0x0000001Au,
        0x00000001u, 0x00000018u, 0x0004003Bu, 0x0000001Au,
        0x0000001Bu, 0x00000001u, 0x00040020u, 0x0000001Du,
        0x00000007u, 0x00000007u, 0x0004002Bu, 0x00000006u,
        0x00000020u, 0x3F800000u, 0x00040020u, 0x00000024u,
        0x00000003u, 0x00000014u, 0x00050036u, 0x00000002u,
        0x00000004u, 0x00000000u, 0x00000003u, 0x000200F8u,
        0x00000005u, 0x0004003Bu, 0x0000000Bu, 0x0000000Cu,
        0x00000007u, 0x0003003Eu, 0x0000000Cu, 0x00000013u,
        0x0004003Du, 0x00000018u, 0x0000001Cu, 0x0000001Bu,
        0x00050041u, 0x0000001Du, 0x0000001Eu, 0x0000000Cu,
        0x0000001Cu, 0x0004003Du, 0x00000007u, 0x0000001Fu,
        0x0000001Eu, 0x00050051u, 0x00000006u, 0x00000021u,
        0x0000001Fu, 0x00000000u, 0x00050051u, 0x00000006u,
        0x00000022u, 0x0000001Fu, 0x00000001u, 0x00070050u,
        0x00000014u, 0x00000023u, 0x00000021u, 0x00000022u,
        0x00000011u, 0x00000020u, 0x00050041u, 0x00000024u,
        0x00000025u, 0x00000017u, 0x00000019u, 0x0003003Eu,
        0x00000025u, 0x00000023u, 0x000100FDu, 0x00010038u
    };

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer default fragment shader                                      //
    ////////////////////////////////////////////////////////////////////////////
    const size_t DefaultFragmentShaderSize = 368;
    const uint32_t DefaultFragmentShader[] =
    {
        0x07230203u, 0x00010000u, 0x00080000u, 0x0000000Eu,
        0x00000000u, 0x00020011u, 0x00000001u, 0x0006000Bu,
        0x00000001u, 0x4C534C47u, 0x6474732Eu, 0x3035342Eu,
        0x00000000u, 0x0003000Eu, 0x00000000u, 0x00000001u,
        0x0006000Fu, 0x00000004u, 0x00000004u, 0x6E69616Du,
        0x00000000u, 0x00000009u, 0x00030010u, 0x00000004u,
        0x00000007u, 0x00030003u, 0x00000002u, 0x000001C2u,
        0x00040005u, 0x00000004u, 0x6E69616Du, 0x00000000u,
        0x00050005u, 0x00000009u, 0x5F74756Fu, 0x6F6C6F43u,
        0x00000072u, 0x00040047u, 0x00000009u, 0x0000001Eu,
        0x00000000u, 0x00020013u, 0x00000002u, 0x00030021u,
        0x00000003u, 0x00000002u, 0x00030016u, 0x00000006u,
        0x00000020u, 0x00040017u, 0x00000007u, 0x00000006u,
        0x00000004u, 0x00040020u, 0x00000008u, 0x00000003u,
        0x00000007u, 0x0004003Bu, 0x00000008u, 0x00000009u,
        0x00000003u, 0x0004002Bu, 0x00000006u, 0x0000000Au,
        0x00000000u, 0x0004002Bu, 0x00000006u, 0x0000000Bu,
        0x3ECCCCCDu, 0x0004002Bu, 0x00000006u, 0x0000000Cu,
        0x3F800000u, 0x0007002Cu, 0x00000007u, 0x0000000Du,
        0x0000000Au, 0x0000000Bu, 0x0000000Cu, 0x0000000Cu,
        0x00050036u, 0x00000002u, 0x00000004u, 0x00000000u,
        0x00000003u, 0x000200F8u, 0x00000005u, 0x0003003Eu,
        0x00000009u, 0x0000000Du, 0x000100FDu, 0x00010038u
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
            //  return : True if pipeline layout is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool createPipelineLayout();

            ////////////////////////////////////////////////////////////////////
            //  Create pipeline                                               //
            //  return : True if pipeline is successfully created             //
            ////////////////////////////////////////////////////////////////////
            bool createPipeline();

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
            VkPipeline          m_pipeline;             // Graphics pipeline
            VulkanCommands      m_commands;             // Commands
            VulkanSemaphores    m_semaphores;           // Semaphores
    };


#endif // VOS_RENDERER_RENDERER_HEADER

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
    //  Renderer swapchain settings                                           //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t RendererMaxSwapchainFrames = 2;
    const uint64_t RendererSwapchainFenceTimeout = 5000000000;

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer clear color                                                  //
    ////////////////////////////////////////////////////////////////////////////
    const VkClearValue RendererClearColor = {0.0f, 0.0f, 0.0f, 1.0f};

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer default vertex shader                                        //
    ////////////////////////////////////////////////////////////////////////////
    const size_t DefaultVertexShaderSize = 716;
    const uint32_t DefaultVertexShader[] =
    {
        0x07230203u, 0x00010000u, 0x00080000u, 0x0000001Au,
        0x00000000u, 0x00020011u, 0x00000001u, 0x0006000Bu,
        0x00000001u, 0x4C534C47u, 0x6474732Eu, 0x3035342Eu,
        0x00000000u, 0x0003000Eu, 0x00000000u, 0x00000001u,
        0x0008000Fu, 0x00000000u, 0x00000004u, 0x6E69616Du,
        0x00000000u, 0x0000000Au, 0x0000000Fu, 0x00000018u,
        0x00030003u, 0x00000002u, 0x000001C2u, 0x00040005u,
        0x00000004u, 0x6E69616Du, 0x00000000u, 0x00060005u,
        0x00000008u, 0x505F6C67u, 0x65567265u, 0x78657472u,
        0x00000000u, 0x00060006u, 0x00000008u, 0x00000000u,
        0x505F6C67u, 0x7469736Fu, 0x006E6F69u, 0x00030005u,
        0x0000000Au, 0x00000000u, 0x00050005u, 0x0000000Fu,
        0x6F505F69u, 0x69746973u, 0x00006E6Fu, 0x00040005u,
        0x00000018u, 0x6F435F76u, 0x00726F6Cu, 0x00050048u,
        0x00000008u, 0x00000000u, 0x0000000Bu, 0x00000000u,
        0x00030047u, 0x00000008u, 0x00000002u, 0x00040047u,
        0x0000000Fu, 0x0000001Eu, 0x00000000u, 0x00040047u,
        0x00000018u, 0x0000001Eu, 0x00000000u, 0x00020013u,
        0x00000002u, 0x00030021u, 0x00000003u, 0x00000002u,
        0x00030016u, 0x00000006u, 0x00000020u, 0x00040017u,
        0x00000007u, 0x00000006u, 0x00000004u, 0x0003001Eu,
        0x00000008u, 0x00000007u, 0x00040020u, 0x00000009u,
        0x00000003u, 0x00000008u, 0x0004003Bu, 0x00000009u,
        0x0000000Au, 0x00000003u, 0x00040015u, 0x0000000Bu,
        0x00000020u, 0x00000001u, 0x0004002Bu, 0x0000000Bu,
        0x0000000Cu, 0x00000000u, 0x00040017u, 0x0000000Du,
        0x00000006u, 0x00000003u, 0x00040020u, 0x0000000Eu,
        0x00000001u, 0x0000000Du, 0x0004003Bu, 0x0000000Eu,
        0x0000000Fu, 0x00000001u, 0x0004002Bu, 0x00000006u,
        0x00000011u, 0x3F800000u, 0x00040020u, 0x00000016u,
        0x00000003u, 0x00000007u, 0x0004003Bu, 0x00000016u,
        0x00000018u, 0x00000003u, 0x0007002Cu, 0x00000007u,
        0x00000019u, 0x00000011u, 0x00000011u, 0x00000011u,
        0x00000011u, 0x00050036u, 0x00000002u, 0x00000004u,
        0x00000000u, 0x00000003u, 0x000200F8u, 0x00000005u,
        0x0004003Du, 0x0000000Du, 0x00000010u, 0x0000000Fu,
        0x00050051u, 0x00000006u, 0x00000012u, 0x00000010u,
        0x00000000u, 0x00050051u, 0x00000006u, 0x00000013u,
        0x00000010u, 0x00000001u, 0x00050051u, 0x00000006u,
        0x00000014u, 0x00000010u, 0x00000002u, 0x00070050u,
        0x00000007u, 0x00000015u, 0x00000012u, 0x00000013u,
        0x00000014u, 0x00000011u, 0x00050041u, 0x00000016u,
        0x00000017u, 0x0000000Au, 0x0000000Cu, 0x0003003Eu,
        0x00000017u, 0x00000015u, 0x0003003Eu, 0x00000018u,
        0x00000019u, 0x000100FDu, 0x00010038u
    };

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer default fragment shader                                      //
    ////////////////////////////////////////////////////////////////////////////
    const size_t DefaultFragmentShaderSize = 372;
    const uint32_t DefaultFragmentShader[] =
    {
        0x07230203u, 0x00010000u, 0x00080000u, 0x0000000Du,
        0x00000000u, 0x00020011u, 0x00000001u, 0x0006000Bu,
        0x00000001u, 0x4C534C47u, 0x6474732Eu, 0x3035342Eu,
        0x00000000u, 0x0003000Eu, 0x00000000u, 0x00000001u,
        0x0007000Fu, 0x00000004u, 0x00000004u, 0x6E69616Du,
        0x00000000u, 0x00000009u, 0x0000000Bu, 0x00030010u,
        0x00000004u, 0x00000007u, 0x00030003u, 0x00000002u,
        0x000001C2u, 0x00040005u, 0x00000004u, 0x6E69616Du,
        0x00000000u, 0x00040005u, 0x00000009u, 0x6F435F6Fu,
        0x00726F6Cu, 0x00040005u, 0x0000000Bu, 0x6F435F76u,
        0x00726F6Cu, 0x00040047u, 0x00000009u, 0x0000001Eu,
        0x00000000u, 0x00040047u, 0x0000000Bu, 0x0000001Eu,
        0x00000000u, 0x00020013u, 0x00000002u, 0x00030021u,
        0x00000003u, 0x00000002u, 0x00030016u, 0x00000006u,
        0x00000020u, 0x00040017u, 0x00000007u, 0x00000006u,
        0x00000004u, 0x00040020u, 0x00000008u, 0x00000003u,
        0x00000007u, 0x0004003Bu, 0x00000008u, 0x00000009u,
        0x00000003u, 0x00040020u, 0x0000000Au, 0x00000001u,
        0x00000007u, 0x0004003Bu, 0x0000000Au, 0x0000000Bu,
        0x00000001u, 0x00050036u, 0x00000002u, 0x00000004u,
        0x00000000u, 0x00000003u, 0x000200F8u, 0x00000005u,
        0x0004003Du, 0x00000007u, 0x0000000Cu, 0x0000000Bu,
        0x0003003Eu, 0x00000009u, 0x0000000Cu, 0x000100FDu,
        0x00010038u
    };


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanImage data structure                                            //
    ////////////////////////////////////////////////////////////////////////////
    struct VulkanImage
    {
        VulkanImage() :
        handle(0),
        view(0),
        sampler(0),
        memory(0)
        {

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
        VulkanSwapchain() :
        handle(0),
        format(VK_FORMAT_UNDEFINED),
        frames(0),
        current(0)
        {
            extent.width = 0;
            extent.height = 0;

            for (uint32_t i = 0; i < RendererMaxSwapchainFrames; ++i)
            {
                images[i].handle = 0;
                images[i].view = 0;
                images[i].sampler = 0;
                images[i].memory = 0;
                framebuffers[i] = 0;
                imageAvailable[i] = 0;
                renderFinished[i] = 0;
                fences[i] = 0;
                commandBuffers[i] = 0;
            }
        }

        VkSwapchainKHR      handle;     // Swapchain handle
        VkFormat            format;     // Swapchain format
        VkExtent2D          extent;     // Swapchain extent
        uint32_t            frames;     // Swapchain frames
        uint32_t            current;    // swapchain current frame

        VulkanImage         images[RendererMaxSwapchainFrames];
        VkFramebuffer       framebuffers[RendererMaxSwapchainFrames];
        VkSemaphore         imageAvailable[RendererMaxSwapchainFrames];
        VkSemaphore         renderFinished[RendererMaxSwapchainFrames];
        VkFence             fences[RendererMaxSwapchainFrames];
        VkCommandBuffer     commandBuffers[RendererMaxSwapchainFrames];
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VulkanBuffer class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class VulkanBuffer
    {
        public:
            VulkanBuffer() :
            handle(0),
            memory(0),
            size(0)
            {

            }

            bool createBuffer(VkPhysicalDevice& physicalDevice,
                VkDevice& vulkanDevice, VkBufferUsageFlags usage,
                VkMemoryPropertyFlags properties)
            {
                // Check physical device
                if (!physicalDevice)
                {
                    // Invalid physical device
                    return false;
                }

                // Check Vulkan device
                if (!vulkanDevice)
                {
                    // Invalid Vulkan device
                    return false;
                }

                VkBufferCreateInfo bufferInfo;
                bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
                bufferInfo.pNext = 0;
                bufferInfo.flags = 0;
                bufferInfo.size = size;
                bufferInfo.usage = usage;
                bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
                bufferInfo.queueFamilyIndexCount = 0;
                bufferInfo.pQueueFamilyIndices = 0;

                if (vkCreateBuffer(
                    vulkanDevice, &bufferInfo, 0, &handle) != VK_SUCCESS)
                {
                    // Could not create buffer
                    return false;
                }
                if (!handle)
                {
                    // Invalid buffer
                    return false;
                }

                // Get memory requirements
                VkMemoryRequirements memoryRequirements;
                vkGetBufferMemoryRequirements(
                    vulkanDevice, handle, &memoryRequirements
                );

                // Get physical device memory properties
                VkPhysicalDeviceMemoryProperties memoryProperties;
                vkGetPhysicalDeviceMemoryProperties(
                    physicalDevice, &memoryProperties
                );

                // Allocate buffer memory
                bool memoryAllocated = false;
                for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i)
                {
                    if (memoryRequirements.memoryTypeBits & (1 << i))
                    {
                        if (memoryProperties.memoryTypes[i].propertyFlags &
                            properties)
                        {
                            VkMemoryAllocateInfo allocateInfo;
                            allocateInfo.sType =
                                VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                            allocateInfo.pNext = 0;
                            allocateInfo.allocationSize =
                                memoryRequirements.size;
                            allocateInfo.memoryTypeIndex = i;

                            if (vkAllocateMemory(vulkanDevice,
                                &allocateInfo, 0, &memory) == VK_SUCCESS)
                            {
                                memoryAllocated = true;
                                break;
                            }
                        }
                    }
                }
                if (!memoryAllocated)
                {
                    // Could not allocate buffer memory
                    return false;
                }

                // Bind buffer memory
                if (vkBindBufferMemory(
                    vulkanDevice, handle, memory, 0) != VK_SUCCESS)
                {
                    // Could not bind buffer memory
                    return false;
                }

                // Buffer successfully created
                return true;
            }

            void destroyBuffer(VkDevice& vulkanDevice)
            {
                if (vulkanDevice)
                {
                    // Destroy buffer
                    if (handle && vkDestroyBuffer)
                    {
                        vkDestroyBuffer(vulkanDevice, handle, 0);
                    }

                    // Free vertex buffer memory
                    if (memory && vkFreeMemory)
                    {
                        vkFreeMemory(vulkanDevice, memory, 0);
                    }
                }
                handle = 0;
                memory = 0;
                size = 0;
            }

        public:
            VkBuffer        handle;
            VkDeviceMemory  memory;
            uint32_t        size;
    };

    ////////////////////////////////////////////////////////////////////////////
    //  VertexData data structure                                             //
    ////////////////////////////////////////////////////////////////////////////
    struct VertexData
    {
        float   x;
        float   y;
        float   z;
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
            //  Create fences                                                 //
            //  return : True if fences are successfully created              //
            ////////////////////////////////////////////////////////////////////
            bool createFences();

            ////////////////////////////////////////////////////////////////////
            //  Create vertex buffer                                          //
            //  return : True if vertex buffer is successfully created        //
            ////////////////////////////////////////////////////////////////////
            bool createVertexBuffer();

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
            VkShaderModule      m_vertexShader;         // Vertex shader
            VkShaderModule      m_fragmentShader;       // Fragment shader
            VkPipelineLayout    m_pipelineLayout;       // Pipeline layout
            VkPipeline          m_pipeline;             // Graphics pipeline
            VkCommandPool       m_commandsPool;         // Commands pool
            VulkanBuffer        m_stagingBuffer;        // Staging buffer
            VulkanBuffer        m_vertexBuffer;         // Vertex buffer
            VulkanBuffer        m_indexBuffer;          // Index buffer
    };


#endif // VOS_RENDERER_RENDERER_HEADER

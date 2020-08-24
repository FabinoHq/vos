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
    #include "Texture.h"
    #include "../Math/Math.h"
    #include "../Math/Matrix4x4.h"

    #include <vector>


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer clear color                                                  //
    ////////////////////////////////////////////////////////////////////////////
    const VkClearValue RendererClearColor = {0.0f, 0.0f, 0.0f, 1.0f};

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer default vertex shader                                        //
    ////////////////////////////////////////////////////////////////////////////
    const size_t DefaultVertexShaderSize = 1408;
    const uint32_t DefaultVertexShader[] =
    {
        0x07230203u, 0x00010000u, 0x00080000u, 0x0000002Eu,
        0x00000000u, 0x00020011u, 0x00000001u, 0x0006000Bu,
        0x00000001u, 0x4C534C47u, 0x6474732Eu, 0x3035342Eu,
        0x00000000u, 0x0003000Eu, 0x00000000u, 0x00000001u,
        0x0009000Fu, 0x00000000u, 0x00000004u, 0x6E69616Du,
        0x00000000u, 0x0000000Au, 0x0000001Eu, 0x0000002Au,
        0x0000002Cu, 0x00030003u, 0x00000002u, 0x000001C2u,
        0x00040005u, 0x00000004u, 0x6E69616Du, 0x00000000u,
        0x00060005u, 0x00000008u, 0x505F6C67u, 0x65567265u,
        0x78657472u, 0x00000000u, 0x00060006u, 0x00000008u,
        0x00000000u, 0x505F6C67u, 0x7469736Fu, 0x006E6F69u,
        0x00030005u, 0x0000000Au, 0x00000000u, 0x00060005u,
        0x0000000Eu, 0x7274614Du, 0x73656369u, 0x66667542u,
        0x00007265u, 0x00050006u, 0x0000000Eu, 0x00000000u,
        0x6A6F7270u, 0x00000000u, 0x00050006u, 0x0000000Eu,
        0x00000001u, 0x77656976u, 0x00000000u, 0x00050006u,
        0x0000000Eu, 0x00000002u, 0x65646F6Du, 0x0000006Cu,
        0x00040005u, 0x00000010u, 0x7374616Du, 0x00000000u,
        0x00050005u, 0x0000001Eu, 0x6F505F69u, 0x69746973u,
        0x00006E6Fu, 0x00050005u, 0x0000002Au, 0x43786574u,
        0x64726F6Fu, 0x00000073u, 0x00050005u, 0x0000002Cu,
        0x65545F69u, 0x6F6F4378u, 0x00736472u, 0x00050048u,
        0x00000008u, 0x00000000u, 0x0000000Bu, 0x00000000u,
        0x00030047u, 0x00000008u, 0x00000002u, 0x00040048u,
        0x0000000Eu, 0x00000000u, 0x00000005u, 0x00050048u,
        0x0000000Eu, 0x00000000u, 0x00000023u, 0x00000000u,
        0x00050048u, 0x0000000Eu, 0x00000000u, 0x00000007u,
        0x00000010u, 0x00040048u, 0x0000000Eu, 0x00000001u,
        0x00000005u, 0x00050048u, 0x0000000Eu, 0x00000001u,
        0x00000023u, 0x00000040u, 0x00050048u, 0x0000000Eu,
        0x00000001u, 0x00000007u, 0x00000010u, 0x00040048u,
        0x0000000Eu, 0x00000002u, 0x00000005u, 0x00050048u,
        0x0000000Eu, 0x00000002u, 0x00000023u, 0x00000080u,
        0x00050048u, 0x0000000Eu, 0x00000002u, 0x00000007u,
        0x00000010u, 0x00030047u, 0x0000000Eu, 0x00000002u,
        0x00040047u, 0x00000010u, 0x00000022u, 0x00000000u,
        0x00040047u, 0x00000010u, 0x00000021u, 0x00000000u,
        0x00040047u, 0x0000001Eu, 0x0000001Eu, 0x00000000u,
        0x00040047u, 0x0000002Au, 0x0000001Eu, 0x00000000u,
        0x00040047u, 0x0000002Cu, 0x0000001Eu, 0x00000001u,
        0x00020013u, 0x00000002u, 0x00030021u, 0x00000003u,
        0x00000002u, 0x00030016u, 0x00000006u, 0x00000020u,
        0x00040017u, 0x00000007u, 0x00000006u, 0x00000004u,
        0x0003001Eu, 0x00000008u, 0x00000007u, 0x00040020u,
        0x00000009u, 0x00000003u, 0x00000008u, 0x0004003Bu,
        0x00000009u, 0x0000000Au, 0x00000003u, 0x00040015u,
        0x0000000Bu, 0x00000020u, 0x00000001u, 0x0004002Bu,
        0x0000000Bu, 0x0000000Cu, 0x00000000u, 0x00040018u,
        0x0000000Du, 0x00000007u, 0x00000004u, 0x0005001Eu,
        0x0000000Eu, 0x0000000Du, 0x0000000Du, 0x0000000Du,
        0x00040020u, 0x0000000Fu, 0x00000002u, 0x0000000Eu,
        0x0004003Bu, 0x0000000Fu, 0x00000010u, 0x00000002u,
        0x00040020u, 0x00000011u, 0x00000002u, 0x0000000Du,
        0x0004002Bu, 0x0000000Bu, 0x00000014u, 0x00000001u,
        0x0004002Bu, 0x0000000Bu, 0x00000018u, 0x00000002u,
        0x00040017u, 0x0000001Cu, 0x00000006u, 0x00000003u,
        0x00040020u, 0x0000001Du, 0x00000001u, 0x0000001Cu,
        0x0004003Bu, 0x0000001Du, 0x0000001Eu, 0x00000001u,
        0x0004002Bu, 0x00000006u, 0x00000020u, 0x3F800000u,
        0x00040020u, 0x00000026u, 0x00000003u, 0x00000007u,
        0x00040017u, 0x00000028u, 0x00000006u, 0x00000002u,
        0x00040020u, 0x00000029u, 0x00000003u, 0x00000028u,
        0x0004003Bu, 0x00000029u, 0x0000002Au, 0x00000003u,
        0x00040020u, 0x0000002Bu, 0x00000001u, 0x00000028u,
        0x0004003Bu, 0x0000002Bu, 0x0000002Cu, 0x00000001u,
        0x00050036u, 0x00000002u, 0x00000004u, 0x00000000u,
        0x00000003u, 0x000200F8u, 0x00000005u, 0x00050041u,
        0x00000011u, 0x00000012u, 0x00000010u, 0x0000000Cu,
        0x0004003Du, 0x0000000Du, 0x00000013u, 0x00000012u,
        0x00050041u, 0x00000011u, 0x00000015u, 0x00000010u,
        0x00000014u, 0x0004003Du, 0x0000000Du, 0x00000016u,
        0x00000015u, 0x00050092u, 0x0000000Du, 0x00000017u,
        0x00000013u, 0x00000016u, 0x00050041u, 0x00000011u,
        0x00000019u, 0x00000010u, 0x00000018u, 0x0004003Du,
        0x0000000Du, 0x0000001Au, 0x00000019u, 0x00050092u,
        0x0000000Du, 0x0000001Bu, 0x00000017u, 0x0000001Au,
        0x0004003Du, 0x0000001Cu, 0x0000001Fu, 0x0000001Eu,
        0x00050051u, 0x00000006u, 0x00000021u, 0x0000001Fu,
        0x00000000u, 0x00050051u, 0x00000006u, 0x00000022u,
        0x0000001Fu, 0x00000001u, 0x00050051u, 0x00000006u,
        0x00000023u, 0x0000001Fu, 0x00000002u, 0x00070050u,
        0x00000007u, 0x00000024u, 0x00000021u, 0x00000022u,
        0x00000023u, 0x00000020u, 0x00050091u, 0x00000007u,
        0x00000025u, 0x0000001Bu, 0x00000024u, 0x00050041u,
        0x00000026u, 0x00000027u, 0x0000000Au, 0x0000000Cu,
        0x0003003Eu, 0x00000027u, 0x00000025u, 0x0004003Du,
        0x00000028u, 0x0000002Du, 0x0000002Cu, 0x0003003Eu,
        0x0000002Au, 0x0000002Du, 0x000100FDu, 0x00010038u
    };

    ////////////////////////////////////////////////////////////////////////////
    //  Renderer default fragment shader                                      //
    ////////////////////////////////////////////////////////////////////////////
    const size_t DefaultFragmentShaderSize = 560;
    const uint32_t DefaultFragmentShader[] =
    {
        0x07230203u, 0x00010000u, 0x00080000u, 0x00000014u,
        0x00000000u, 0x00020011u, 0x00000001u, 0x0006000Bu,
        0x00000001u, 0x4C534C47u, 0x6474732Eu, 0x3035342Eu,
        0x00000000u, 0x0003000Eu, 0x00000000u, 0x00000001u,
        0x0007000Fu, 0x00000004u, 0x00000004u, 0x6E69616Du,
        0x00000000u, 0x00000009u, 0x00000011u, 0x00030010u,
        0x00000004u, 0x00000007u, 0x00030003u, 0x00000002u,
        0x000001C2u, 0x00040005u, 0x00000004u, 0x6E69616Du,
        0x00000000u, 0x00040005u, 0x00000009u, 0x6F435F6Fu,
        0x00726F6Cu, 0x00050005u, 0x0000000Du, 0x53786574u,
        0x6C706D61u, 0x00007265u, 0x00050005u, 0x00000011u,
        0x43786574u, 0x64726F6Fu, 0x00000073u, 0x00040047u,
        0x00000009u, 0x0000001Eu, 0x00000000u, 0x00040047u,
        0x0000000Du, 0x00000022u, 0x00000000u, 0x00040047u,
        0x0000000Du, 0x00000021u, 0x00000001u, 0x00040047u,
        0x00000011u, 0x0000001Eu, 0x00000000u, 0x00020013u,
        0x00000002u, 0x00030021u, 0x00000003u, 0x00000002u,
        0x00030016u, 0x00000006u, 0x00000020u, 0x00040017u,
        0x00000007u, 0x00000006u, 0x00000004u, 0x00040020u,
        0x00000008u, 0x00000003u, 0x00000007u, 0x0004003Bu,
        0x00000008u, 0x00000009u, 0x00000003u, 0x00090019u,
        0x0000000Au, 0x00000006u, 0x00000001u, 0x00000000u,
        0x00000000u, 0x00000000u, 0x00000001u, 0x00000000u,
        0x0003001Bu, 0x0000000Bu, 0x0000000Au, 0x00040020u,
        0x0000000Cu, 0x00000000u, 0x0000000Bu, 0x0004003Bu,
        0x0000000Cu, 0x0000000Du, 0x00000000u, 0x00040017u,
        0x0000000Fu, 0x00000006u, 0x00000002u, 0x00040020u,
        0x00000010u, 0x00000001u, 0x0000000Fu, 0x0004003Bu,
        0x00000010u, 0x00000011u, 0x00000001u, 0x00050036u,
        0x00000002u, 0x00000004u, 0x00000000u, 0x00000003u,
        0x000200F8u, 0x00000005u, 0x0004003Du, 0x0000000Bu,
        0x0000000Eu, 0x0000000Du, 0x0004003Du, 0x0000000Fu,
        0x00000012u, 0x00000011u, 0x00050057u, 0x00000007u,
        0x00000013u, 0x0000000Eu, 0x00000012u, 0x0003003Eu,
        0x00000009u, 0x00000013u, 0x000100FDu, 0x00010038u
    };


    ////////////////////////////////////////////////////////////////////////////
    //  UniformData data structure                                            //
    ////////////////////////////////////////////////////////////////////////////
    struct UniformData
    {
        float   projMatrix[16];
        float   viewMatrix[16];
        float   modelMatrix[16];
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
            //  Create default shaders                                        //
            //  return : True if default shaders are successfully created     //
            ////////////////////////////////////////////////////////////////////
            bool createDefaultShaders();

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
            //  Create uniform buffer                                         //
            //  return : True if uniform buffer is successfully created       //
            ////////////////////////////////////////////////////////////////////
            bool createUniformBuffer();

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
            VkShaderModule          m_vertexShader;         // Vertex shader
            VkShaderModule          m_fragmentShader;       // Fragment shader
            VkDescriptorSetLayout   m_descriptorSetLayout;  // Descriptor layout
            VkPipelineLayout        m_pipelineLayout;       // Pipeline layout
            VkPipeline              m_pipeline;             // Graphics pipeline
            VulkanBuffer            m_stagingBuffer;        // Staging buffer
            VertexBuffer            m_vertexBuffer;         // Vertex buffer
            VulkanBuffer            m_uniformBuffer;        // Uniform buffer
            UniformData             m_uniformData;          // Uniform data
            Texture                 m_texture;              // Test texture
            VkDescriptorPool        m_descriptorPool;       // Descriptor pool
            VkDescriptorSet         m_descriptorSet;        // Descriptor set
    };


#endif // VOS_RENDERER_RENDERER_HEADER

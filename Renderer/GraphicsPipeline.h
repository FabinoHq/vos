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
//     Renderer/GraphicsPipeline.h : Vulkan Graphics pipeline management      //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_GRAPHICSPIPELINE_HEADER
#define VOS_RENDERER_GRAPHICSPIPELINE_HEADER

    #include "../System/SysMessage.h"
    #include "Vulkan.h"
    #include "Swapchain.h"
    #include "VulkanBuffer.h"
    #include "VertexBuffer.h"
    #include "Shader.h"
    #include "../Math/Math.h"
    #include "../Math/Matrix4x4.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Descriptor sets count                                                 //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t DescriptorSetsCnt = 2;

    ////////////////////////////////////////////////////////////////////////////
    //  Descriptor sets types                                                 //
    ////////////////////////////////////////////////////////////////////////////
    enum DescriptorSetsType
    {
        DESC_MATRICES = 0,
        DESC_TEXTURE = 1
    };


    ////////////////////////////////////////////////////////////////////////////
    //  GraphicsPipeline class definition                                     //
    ////////////////////////////////////////////////////////////////////////////
    class GraphicsPipeline
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GraphicsPipeline default constructor                          //
            ////////////////////////////////////////////////////////////////////
            GraphicsPipeline();

            ////////////////////////////////////////////////////////////////////
            //  GraphicsPipeline destructor                                   //
            ////////////////////////////////////////////////////////////////////
            ~GraphicsPipeline();


            ////////////////////////////////////////////////////////////////////
            //  Create graphics pipeline                                      //
            //  return : True if graphics pipeline is successfully created    //
            ////////////////////////////////////////////////////////////////////
            bool createPipeline(VkDevice& vulkanDevice, Swapchain& swapchain,
                Shader& shader);

            ////////////////////////////////////////////////////////////////////
            //  Create descriptor pools                                       //
            //  return : True if descriptor pool is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool createDescriptorPools(VkDevice& vulkanDevice);

            ////////////////////////////////////////////////////////////////////
            //  Create descriptor set layouts                                 //
            //  return : True if descriptor layout is successfully created    //
            ////////////////////////////////////////////////////////////////////
            bool createDescriptorSetLayouts(VkDevice& vulkanDevice);

            ////////////////////////////////////////////////////////////////////
            //  Create pipeline layouts                                       //
            //  return : True if pipeline layout is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool createPipelineLayouts(VkDevice& vulkanDevice);

            ////////////////////////////////////////////////////////////////////
            //  Destroy pipeline                                              //
            ////////////////////////////////////////////////////////////////////
            void destroyPipeline(VkDevice& vulkanDevice);


        private:
            ////////////////////////////////////////////////////////////////////
            //  GraphicsPipeline private copy constructor : Not copyable      //
            ////////////////////////////////////////////////////////////////////
            GraphicsPipeline(const GraphicsPipeline&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GraphicsPipeline private copy operator : Not copyable         //
            ////////////////////////////////////////////////////////////////////
            GraphicsPipeline& operator=(const GraphicsPipeline&) = delete;


        public:
            VkPipeline              handle;             // Pipeline handle
            VkPipelineLayout        layout;             // Pipeline layout

            // Descriptor pools
            VkDescriptorPool        descPools[DescriptorSetsCnt];

            // Descriptor set layouts
            VkDescriptorSetLayout   descSetLayouts[DescriptorSetsCnt];
            VkDescriptorSetLayout
                swapSetLayouts[RendererMaxSwapchainFrames*DescriptorSetsCnt];
    };


#endif // VOS_RENDERER_GRAPHICSPIPELINE_HEADER

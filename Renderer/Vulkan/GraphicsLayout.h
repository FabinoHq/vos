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
//     Renderer/Vulkan/GraphicsLayout.h : Graphics layout management          //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_GRAPHICSLAYOUT_HEADER
#define VOS_RENDERER_VULKAN_GRAPHICSLAYOUT_HEADER

    #include "../../System/SysMessage.h"
    #include "Vulkan.h"
    #include "Swapchain.h"
    #include "VulkanBuffer.h"
    #include "VertexBuffer.h"
    #include "../Shader.h"
    #include "../../Math/Math.h"
    #include "../../Math/Matrix4x4.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Descriptor sets types                                                 //
    ////////////////////////////////////////////////////////////////////////////
    enum DescriptorSetsType
    {
        DESC_MATRICES = 0,
        DESC_TEXTURE = 1,
        DESC_SETS_COUNT = 2
    };

    ////////////////////////////////////////////////////////////////////////////
    //  PushConstant data structure                                           //
    ////////////////////////////////////////////////////////////////////////////
    struct PushConstantData
    {
        float   color[4];
        float   offset[2];
        float   size[2];
        float   time;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  GraphicsLayout class definition                                       //
    ////////////////////////////////////////////////////////////////////////////
    class GraphicsLayout
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  GraphicsLayout default constructor                            //
            ////////////////////////////////////////////////////////////////////
            GraphicsLayout();

            ////////////////////////////////////////////////////////////////////
            //  GraphicsLayout destructor                                     //
            ////////////////////////////////////////////////////////////////////
            ~GraphicsLayout();


            ////////////////////////////////////////////////////////////////////
            //  Create graphics pipeline layout                               //
            //  return : True if graphics layout is successfully created      //
            ////////////////////////////////////////////////////////////////////
            bool createLayout(VkDevice& vulkanDevice, Swapchain& swapchain);

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
            //  Destroy pipeline layout                                       //
            ////////////////////////////////////////////////////////////////////
            void destroyLayout(VkDevice& vulkanDevice);


        private:
            ////////////////////////////////////////////////////////////////////
            //  GraphicsLayout private copy constructor : Not copyable        //
            ////////////////////////////////////////////////////////////////////
            GraphicsLayout(const GraphicsLayout&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  GraphicsLayout private copy operator : Not copyable           //
            ////////////////////////////////////////////////////////////////////
            GraphicsLayout& operator=(const GraphicsLayout&) = delete;


        public:
            VkPipelineLayout        handle;         // Pipeline layout handle

            // Descriptor set layouts
            VkDescriptorSetLayout   descSetLayouts[DESC_SETS_COUNT];
            VkDescriptorSetLayout
                swapSetLayouts[RendererMaxSwapchainFrames*DESC_SETS_COUNT];
    };


#endif // VOS_RENDERER_VULKAN_GRAPHICSLAYOUT_HEADER

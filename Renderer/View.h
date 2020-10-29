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
//     Renderer/View.h : View management                                      //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VIEW_HEADER
#define VOS_RENDERER_VIEW_HEADER

    #include "../System/SysMessage.h"
    #include "Vulkan.h"
    #include "VulkanMemory.h"
    #include "Swapchain.h"
    #include "VulkanBuffer.h"
    #include "UniformBuffer.h"
    #include "GraphicsPipeline.h"
    #include "../Math/Math.h"
    #include "../Math/Vector2.h"
    #include "../Math/Matrix4x4.h"


    ////////////////////////////////////////////////////////////////////////////
    //  View class definition                                                 //
    ////////////////////////////////////////////////////////////////////////////
    class View
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  View default constructor                                      //
            ////////////////////////////////////////////////////////////////////
            View();

            ////////////////////////////////////////////////////////////////////
            //  View destructor                                               //
            ////////////////////////////////////////////////////////////////////
            ~View();


            ////////////////////////////////////////////////////////////////////
            //  Init view                                                     //
            //  return : True if the view is successfully created             //
            ////////////////////////////////////////////////////////////////////
            bool init(VkPhysicalDevice& physicalDevice, VkDevice& vulkanDevice,
                VulkanMemory& vulkanMemory, GraphicsPipeline& pipeline,
                VkCommandPool& transferCommandPool, VulkanQueue& transferQueue);

            ////////////////////////////////////////////////////////////////////
            //  Bind view                                                     //
            ////////////////////////////////////////////////////////////////////
            bool bind(VkPhysicalDevice& physicalDevice, VkDevice& vulkanDevice,
                Swapchain& swapchain, VulkanMemory& vulkanMemory,
                GraphicsPipeline& pipeline, VkCommandPool& transferCommandPool,
                VulkanQueue& transferQueue);

            ////////////////////////////////////////////////////////////////////
            //  Destroy view                                                  //
            ////////////////////////////////////////////////////////////////////
            void destroyView(VkDevice& vulkanDevice,
                VulkanMemory& vulkanMemory);


        private:
            ////////////////////////////////////////////////////////////////////
            //  View private copy constructor : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            View(const View&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  View private copy operator : Not copyable                     //
            ////////////////////////////////////////////////////////////////////
            View& operator=(const View&) = delete;


        private:
            VkDescriptorSet     m_descriptorSets[RendererMaxSwapchainFrames];
            UniformBuffer       m_uniformBuffers[RendererMaxSwapchainFrames];
            Matrix4x4           m_projMatrix;       // Projection matrix
            Matrix4x4           m_viewMatrix;       // View matrix
    };


#endif // VOS_RENDERER_VIEW_HEADER

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
//   For more information, please refer to <https://unlicense.org>            //
////////////////////////////////////////////////////////////////////////////////
//    VOS : Virtual Operating System                                          //
//     Renderer/BackRenderer.h : Offscreen renderer management                //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_BACKRENDERER_HEADER
#define VOS_RENDERER_BACKRENDERER_HEADER

    #include "../System/System.h"
    #include "../System/SysVkMemory.h"
    #include "../System/SysSettings.h"
    #include "Vulkan/Vulkan.h"
    #include "Vulkan/GraphicsLayout.h"
    #include "Vulkan/VulkanMemory.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/Backchain.h"
    #include "View.h"


    ////////////////////////////////////////////////////////////////////////////
    //  BackRenderer maximum size                                             //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t BackRendererMaxWidth = 4096;
    const uint32_t BackRendererMaxHeight = 4096;

    ////////////////////////////////////////////////////////////////////////////
    //  BackRenderer clear color                                              //
    ////////////////////////////////////////////////////////////////////////////
    const VkClearColorValue BackRendererClearColor = {0.0f, 0.0f, 0.0f, 0.0f};
    const VkClearDepthStencilValue BackRendererClearDepth = {1.0f, 0};


    ////////////////////////////////////////////////////////////////////////////
    //  BackRenderer class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class BackRenderer
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  BackRenderer default constructor                              //
            ////////////////////////////////////////////////////////////////////
            BackRenderer();

            ////////////////////////////////////////////////////////////////////
            //  BackRenderer destructor                                       //
            ////////////////////////////////////////////////////////////////////
            ~BackRenderer();


            ////////////////////////////////////////////////////////////////////
            //  Init back renderer                                            //
            //  return : True if the back renderer is successfully loaded     //
            ////////////////////////////////////////////////////////////////////
            bool init(VulkanMemoryPool memoryPool,
                uint32_t width, uint32_t height, bool smooth = true);

            ////////////////////////////////////////////////////////////////////
            //  Start back renderer pass                                      //
            //  return : True if the back renderer pass is started            //
            ////////////////////////////////////////////////////////////////////
            bool startRenderPass();

            ////////////////////////////////////////////////////////////////////
            //  End back renderer pass                                        //
            ////////////////////////////////////////////////////////////////////
            inline void endRenderPass()
            {
                vkCmdEndRenderPass(
                    GSwapchain.commandBuffers[GSwapchain.current]
                );
                current = GSwapchain.current;
            }

            ////////////////////////////////////////////////////////////////////
            //  Bind back renderer texture                                    //
            ////////////////////////////////////////////////////////////////////
            inline void bind()
            {
                vkCmdBindDescriptorSets(
                    GSwapchain.commandBuffers[GSwapchain.current],
                    VK_PIPELINE_BIND_POINT_GRAPHICS, GGraphicsLayout.handle,
                    DESC_TEXTURE, 1, &descriptorSets[current], 0, 0
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Clear depth buffer                                            //
            ////////////////////////////////////////////////////////////////////
            void clearDepth();

            ////////////////////////////////////////////////////////////////////
            //  Destroy back renderer                                         //
            ////////////////////////////////////////////////////////////////////
            void destroyBackRenderer();


            ////////////////////////////////////////////////////////////////////
            //  Compute back renderer default view                            //
            ////////////////////////////////////////////////////////////////////
            inline void computeDefaultView()
            {
                view.compute(backchain.ratio);
            }

            ////////////////////////////////////////////////////////////////////
            //  Bind back renderer default view                               //
            ////////////////////////////////////////////////////////////////////
            inline void bindDefaultView()
            {
                view.bind();
            }


            ////////////////////////////////////////////////////////////////////
            //  Resize back renderer frame                                    //
            //  return : True if the back renderer is successfully resized    //
            ////////////////////////////////////////////////////////////////////
            bool resize(VulkanMemoryPool memoryPool,
                uint32_t width, uint32_t height);


        private:
            ////////////////////////////////////////////////////////////////////
            //  BackRenderer private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            BackRenderer(const BackRenderer&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  BackRenderer private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            BackRenderer& operator=(const BackRenderer&) = delete;


        public:
            Backchain           backchain;    // Backchain
            uint32_t            current;      // Current frame

            View                view;         // Default view

            VkSampler           samplers[RendererMaxSwapchainFrames];
            VkDescriptorSet     descriptorSets[RendererMaxSwapchainFrames];
    };


    ////////////////////////////////////////////////////////////////////////////
    //  MainRenderer global instance                                          //
    ////////////////////////////////////////////////////////////////////////////
    extern BackRenderer GMainRenderer;


#endif // VOS_RENDERER_BACKRENDERER_HEADER

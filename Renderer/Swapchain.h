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
//     Renderer/Swapchain.h : Swapchain management                            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_SWAPCHAIN_HEADER
#define VOS_RENDERER_SWAPCHAIN_HEADER

    #include "Vulkan.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer swapchain settings                                           //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t RendererMaxSwapchainFrames = 2;
    const uint64_t RendererSwapchainFenceTimeout = 5000000000;


    ////////////////////////////////////////////////////////////////////////////
    //  Swapchain class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Swapchain
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Swapchain default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            Swapchain();

            ////////////////////////////////////////////////////////////////////
            //  Swapchain destructor                                          //
            ////////////////////////////////////////////////////////////////////
            ~Swapchain();


            ////////////////////////////////////////////////////////////////////
            //  Create swapchain                                              //
            //  return : True if swapchain is successfully created            //
            ////////////////////////////////////////////////////////////////////
            bool createSwapchain(VkPhysicalDevice& physicalDevice,
                VkDevice& vulkanDevice, VkSurfaceKHR& vulkanSurface,
                VkCommandPool& commandsPool);

            ////////////////////////////////////////////////////////////////////
            //  Destroy swapchain                                             //
            ////////////////////////////////////////////////////////////////////
            void destroySwapchain(VkDevice& vulkanDevice,
                VkCommandPool& commandsPool);


        public:
            VkSwapchainKHR      handle;         // Swapchain handle
            VkFormat            format;         // Swapchain format
            VkExtent2D          extent;         // Swapchain extent
            VkRenderPass        renderPass;     // Render pass
            uint32_t            frames;         // Swapchain frames count
            uint32_t            current;        // swapchain current frame

            VkImage             images[RendererMaxSwapchainFrames];
            VkImageView         views[RendererMaxSwapchainFrames];
            VkFramebuffer       framebuffers[RendererMaxSwapchainFrames];
            VkSemaphore         renderReady[RendererMaxSwapchainFrames];
            VkSemaphore         renderFinished[RendererMaxSwapchainFrames];
            VkFence             fences[RendererMaxSwapchainFrames];
            VkCommandBuffer     commandBuffers[RendererMaxSwapchainFrames];
    };

#endif // VOS_RENDERER_SWAPCHAIN_HEADER

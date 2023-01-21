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
//     Renderer/Vulkan/Uniformchain.h : Uniform chain management              //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_UNIFORMCHAIN_HEADER
#define VOS_RENDERER_VULKAN_UNIFORMCHAIN_HEADER

    #include "../../System/System.h"
    #include "Vulkan.h"
    #include "VulkanQueue.h"
    #include "Swapchain.h"

    #include <cstddef>
    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer unniformchain settings                                       //
    ////////////////////////////////////////////////////////////////////////////
    const uint64_t RendererUniformchainFenceTimeout = 5000000000;


    ////////////////////////////////////////////////////////////////////////////
    //  Uniformchain class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class Uniformchain
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Uniformchain default constructor                              //
            ////////////////////////////////////////////////////////////////////
            Uniformchain();

            ////////////////////////////////////////////////////////////////////
            //  Uniformchain destructor                                       //
            ////////////////////////////////////////////////////////////////////
            ~Uniformchain();


            ////////////////////////////////////////////////////////////////////
            //  Create uniformchain                                           //
            //  return : True if uniformchain is successfully created         //
            ////////////////////////////////////////////////////////////////////
            bool createUniformchain();

            ////////////////////////////////////////////////////////////////////
            //  Destroy uniformchain                                          //
            ////////////////////////////////////////////////////////////////////
            void destroyUniformchain();


            ////////////////////////////////////////////////////////////////////
            //  Start uniforms upload                                         //
            //  return : True if uniforms are ready to be uploaded            //
            ////////////////////////////////////////////////////////////////////
            bool startUpload();

            ////////////////////////////////////////////////////////////////////
            //  End uniforms upload                                           //
            //  return : True if uniforms are submitted for upload            //
            ////////////////////////////////////////////////////////////////////
            bool endUpload();


        private:
            ////////////////////////////////////////////////////////////////////
            //  Uniformchain private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            Uniformchain(const Uniformchain&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Uniformchain private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            Uniformchain& operator=(const Uniformchain&) = delete;


        public:
            VulkanQueue         uniformQueue;       // Uniform queue

            // Uniformchain resources
            VkSemaphore         uniformsReady[RendererMaxSwapchainFrames];
            VkFence             fences[RendererMaxSwapchainFrames];
            VkCommandPool       commandPools[RendererMaxSwapchainFrames];
            VkCommandBuffer     commandBuffers[RendererMaxSwapchainFrames];
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Uniformchain global instance                                          //
    ////////////////////////////////////////////////////////////////////////////
    extern Uniformchain GUniformchain;


#endif // VOS_RENDERER_VULKAN_UNIFORMCHAIN_HEADER

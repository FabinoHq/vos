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
//     Renderer/Vulkan/Backchain.h : Backchain management                     //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_BACKCHAIN_HEADER
#define VOS_RENDERER_VULKAN_BACKCHAIN_HEADER

    #include "../../System/System.h"
    #include "Vulkan.h"
    #include "VulkanMemory.h"

    #include <cstddef>
    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer backchain settings                                           //
    ////////////////////////////////////////////////////////////////////////////
    const uint32_t RendererMaxBackchainFrames = 2;
    const uint64_t RendererBackchainFenceTimeout = 5000000000;


    ////////////////////////////////////////////////////////////////////////////
    //  Backchain class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Backchain
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Backchain default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            Backchain();

            ////////////////////////////////////////////////////////////////////
            //  Backchain destructor                                          //
            ////////////////////////////////////////////////////////////////////
            ~Backchain();


            ////////////////////////////////////////////////////////////////////
            //  Create backchain                                              //
            //  return : True if backchain is successfully created            //
            ////////////////////////////////////////////////////////////////////
            bool createBackchain(VkDevice& vulkanDevice,
                VulkanMemory& vulkanMemory, uint32_t width, uint32_t height);

            ////////////////////////////////////////////////////////////////////
            //  Destroy backchain                                             //
            ////////////////////////////////////////////////////////////////////
            void destroyBackchain(VkDevice& vulkanDevice);


        private:
            ////////////////////////////////////////////////////////////////////
            //  Backchain private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            Backchain(const Backchain&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Backchain private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            Backchain& operator=(const Backchain&) = delete;


        public:
            VkExtent2D          extent;         // Backchain extent
            VkRenderPass        renderPass;     // Backchain render pass
            float               ratio;          // Backchain aspect ratio

            VkImage             images[RendererMaxBackchainFrames];
            VkImage             depthImages[RendererMaxBackchainFrames];
            VkImageView         views[RendererMaxBackchainFrames];
            VkImageView         depthViews[RendererMaxBackchainFrames];
            VkFramebuffer       framebuffers[RendererMaxBackchainFrames];
    };


#endif // VOS_RENDERER_VULKAN_BACKCHAIN_HEADER

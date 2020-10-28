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
//     Renderer/Texture.h : Texture management                                //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_TEXTURE_HEADER
#define VOS_RENDERER_TEXTURE_HEADER

    #include "Vulkan.h"
    #include "VulkanMemory.h"
    #include "VulkanQueue.h"
    #include "Swapchain.h"
    #include "VulkanBuffer.h"
    #include "GraphicsPipeline.h"


    ////////////////////////////////////////////////////////////////////////////
    //  Texture class definition                                              //
    ////////////////////////////////////////////////////////////////////////////
    class Texture
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  Texture default constructor                                   //
            ////////////////////////////////////////////////////////////////////
            Texture();

            ////////////////////////////////////////////////////////////////////
            //  Texture destructor                                            //
            ////////////////////////////////////////////////////////////////////
            ~Texture();


            ////////////////////////////////////////////////////////////////////
            //  Create texture                                                //
            //  return : True if texture is successfully created              //
            ////////////////////////////////////////////////////////////////////
            bool createTexture(VkPhysicalDevice& physicalDevice,
                VkDevice& vulkanDevice, VulkanMemory& vulkanMemory,
                GraphicsPipeline& pipeline,
                uint32_t texWidth, uint32_t texHeight);

            ////////////////////////////////////////////////////////////////////
            //  Update texture                                                //
            //  return : True if texture is successfully updated              //
            ////////////////////////////////////////////////////////////////////
            bool updateTexture(VkPhysicalDevice& physicalDevice,
                VkDevice& vulkanDevice, VulkanMemory& vulkanMemory,
                GraphicsPipeline& pipeline, VkCommandPool& commandsPool,
                VulkanQueue& graphicsQueue, uint32_t texWidth,
                uint32_t texHeight, uint32_t texDepth,
                const unsigned char* data);

            ////////////////////////////////////////////////////////////////////
            //  Bind texture                                                  //
            ////////////////////////////////////////////////////////////////////
            void bind(VkCommandBuffer& commandBuffer,
                GraphicsPipeline& pipeline, uint32_t currentSwapchainFrame);

            ////////////////////////////////////////////////////////////////////
            //  Destroy texture                                               //
            ////////////////////////////////////////////////////////////////////
            void destroyTexture(VkDevice& vulkanDevice,
                VulkanMemory& vulkanMemory);


        private:
            ////////////////////////////////////////////////////////////////////
            //  Texture private copy constructor : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            Texture(const Texture&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Texture private copy operator : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            Texture& operator=(const Texture&) = delete;


        public:
            VkImage             handle;         // Texture handle
            VkSampler           sampler;        // Texture sampler
            VkImageView         view;           // Texture view
            VkDescriptorSet     descriptorSets[RendererMaxSwapchainFrames];

            VkDeviceSize        memorySize;     // Memory size
            VkDeviceSize        memoryOffset;   // Memory offset

            uint32_t            width;          // Texture width
            uint32_t            height;         // texture height
    };

#endif // VOS_RENDERER_TEXTURE_HEADER

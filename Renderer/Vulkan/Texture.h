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
//     Renderer/Vulkan/Texture.h : Texture management                         //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_TEXTURE_HEADER
#define VOS_RENDERER_VULKAN_TEXTURE_HEADER

    #include "../../System/System.h"
    #include "../../Math/Math.h"
    #include "Vulkan.h"
    #include "VulkanMemory.h"
    #include "Swapchain.h"
    #include "VulkanBuffer.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  TextureRepeatMode enumeration                                         //
    ////////////////////////////////////////////////////////////////////////////
    enum TextureRepeatMode
    {
        TEXTUREMODE_CLAMP = 0,
        TEXTUREMODE_REPEAT = 1,
        TEXTUREMODE_MIRROR = 2
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;

    ////////////////////////////////////////////////////////////////////////////
    //  TextureLoader class declaration                                       //
    ////////////////////////////////////////////////////////////////////////////
    class TextureLoader;


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
            bool createTexture(Renderer& renderer, VulkanMemoryPool memoryPool,
                uint32_t width, uint32_t height, uint32_t mipLevels,
                bool smooth = true,
                TextureRepeatMode repeat = TEXTUREMODE_CLAMP);

            ////////////////////////////////////////////////////////////////////
            //  Update texture                                                //
            //  return : True if texture is successfully updated              //
            ////////////////////////////////////////////////////////////////////
            bool updateTexture(Renderer& renderer, TextureLoader& loader,
                VulkanMemoryPool memoryPool, uint32_t width, uint32_t height,
                const unsigned char* data,
                bool mipmaps = false, bool smooth = true,
                TextureRepeatMode repeat = TEXTUREMODE_CLAMP);

            ////////////////////////////////////////////////////////////////////
            //  Bind texture                                                  //
            ////////////////////////////////////////////////////////////////////
            void bind(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Destroy texture                                               //
            ////////////////////////////////////////////////////////////////////
            void destroyTexture(Renderer& renderer);


            ////////////////////////////////////////////////////////////////////
            //  Check if the texture has a valid handle                       //
            //  return : True if the texture is valid                         //
            ////////////////////////////////////////////////////////////////////
            inline bool isValid()
            {
                return m_handle;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get texture memory requirements                               //
            ////////////////////////////////////////////////////////////////////
            void getMemoryRequirements(VkDevice& vulkanDevice,
                VkMemoryRequirements* memoryRequirements);

            ////////////////////////////////////////////////////////////////////
            //  Bind texture memory                                           //
            //  return : True if texture memory is successfully binded        //
            ////////////////////////////////////////////////////////////////////
            bool bindTextureMemory(VkDevice& vulkanDevice,
                VkDeviceMemory& deviceMemory, VkDeviceSize size,
                VkDeviceSize offset);


        private:
            ////////////////////////////////////////////////////////////////////
            //  Texture private copy constructor : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            Texture(const Texture&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  Texture private copy operator : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            Texture& operator=(const Texture&) = delete;


        private:
            VkImage             m_handle;           // Texture handle
            VkSampler           m_sampler;          // Texture sampler
            VkImageView         m_view;             // Texture view
            VkDescriptorSet     m_descriptorSets[RendererMaxSwapchainFrames];

            VkDeviceSize        m_memorySize;       // Memory size
            VkDeviceSize        m_memoryOffset;     // Memory offset

            uint32_t            m_width;            // Texture width
            uint32_t            m_height;           // Texture height
    };


#endif // VOS_RENDERER_VULKAN_TEXTURE_HEADER

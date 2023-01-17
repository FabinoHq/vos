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
//     Renderer/Vulkan/TextureArray.h : Texture array management              //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_TEXTUREARRAY_HEADER
#define VOS_RENDERER_VULKAN_TEXTUREARRAY_HEADER

    #include "../../System/System.h"
    #include "../../Math/Math.h"
    #include "Vulkan.h"
    #include "VulkanMemory.h"
    #include "Swapchain.h"
    #include "VulkanBuffer.h"
    #include "Texture.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;

    ////////////////////////////////////////////////////////////////////////////
    //  TextureLoader class declaration                                       //
    ////////////////////////////////////////////////////////////////////////////
    class TextureLoader;


    ////////////////////////////////////////////////////////////////////////////
    //  TextureArray class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class TextureArray
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  TextureArray default constructor                              //
            ////////////////////////////////////////////////////////////////////
            TextureArray();

            ////////////////////////////////////////////////////////////////////
            //  TextureArray destructor                                       //
            ////////////////////////////////////////////////////////////////////
            ~TextureArray();


            ////////////////////////////////////////////////////////////////////
            //  Create texture array                                          //
            //  return : True if texture array is successfully created        //
            ////////////////////////////////////////////////////////////////////
            bool createTextureArray(VulkanMemoryPool memoryPool,
                uint32_t width, uint32_t height, uint32_t layers,
                uint32_t mipLevels, bool smooth = true,
                TextureRepeatMode repeat = TEXTUREMODE_CLAMP);

            ////////////////////////////////////////////////////////////////////
            //  Update texture array                                          //
            //  return : True if texture array is successfully updated        //
            ////////////////////////////////////////////////////////////////////
            bool updateTextureArray(
                TextureLoader& loader, VulkanMemoryPool memoryPool,
                uint32_t width, uint32_t height, uint32_t layers,
                const unsigned char* data,
                bool mipmaps = false, bool smooth = true,
                TextureRepeatMode repeat = TEXTUREMODE_CLAMP);

            ////////////////////////////////////////////////////////////////////
            //  Bind texture array                                            //
            ////////////////////////////////////////////////////////////////////
            void bind();

            ////////////////////////////////////////////////////////////////////
            //  Destroy texture array                                         //
            ////////////////////////////////////////////////////////////////////
            void destroyTextureArray();


            ////////////////////////////////////////////////////////////////////
            //  Check if the texture array has a valid handle                 //
            //  return : True if the texture array is valid                   //
            ////////////////////////////////////////////////////////////////////
            bool isValid();

            ////////////////////////////////////////////////////////////////////
            //  Get texture array memory requirements                         //
            ////////////////////////////////////////////////////////////////////
            void getMemoryRequirements(
                VkMemoryRequirements* memoryRequirements);

            ////////////////////////////////////////////////////////////////////
            //  Bind texture array memory                                     //
            //  return : True if texture array memory is successfully binded  //
            ////////////////////////////////////////////////////////////////////
            bool bindTextureArrayMemory(VkDeviceMemory& deviceMemory,
                VkDeviceSize size, VkDeviceSize offset);


        private:
            ////////////////////////////////////////////////////////////////////
            //  TextureArray private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            TextureArray(const TextureArray&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  TextureArray private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            TextureArray& operator=(const TextureArray&) = delete;


        private:
            VkImage             m_handle;           // TextureArray handle
            VkSampler           m_sampler;          // TextureArray sampler
            VkImageView         m_view;             // TextureArray view
            VkDescriptorSet     m_descriptorSets[RendererMaxSwapchainFrames];

            VkDeviceSize        m_memorySize;       // Memory size
            VkDeviceSize        m_memoryOffset;     // Memory offset

            uint32_t            m_width;            // TextureArray width
            uint32_t            m_height;           // TextureArray height
            uint32_t            m_layers;           // TextureArray layers
    };


#endif // VOS_RENDERER_VULKAN_TEXTUREARRAY_HEADER

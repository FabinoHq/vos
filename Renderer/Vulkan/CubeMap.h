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
//     Renderer/Vulkan/CubeMap.h : CubeMap management                         //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_CUBEMAP_HEADER
#define VOS_RENDERER_VULKAN_CUBEMAP_HEADER

    #include "../../System/System.h"
    #include "Vulkan.h"
    #include "VulkanMemory.h"
    #include "Swapchain.h"
    #include "GraphicsLayout.h"
    #include "VulkanBuffer.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  CubeMap class definition                                              //
    ////////////////////////////////////////////////////////////////////////////
    class CubeMap
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  CubeMap default constructor                                   //
            ////////////////////////////////////////////////////////////////////
            CubeMap();

            ////////////////////////////////////////////////////////////////////
            //  CubeMap destructor                                            //
            ////////////////////////////////////////////////////////////////////
            ~CubeMap();


            ////////////////////////////////////////////////////////////////////
            //  Create cubemap                                                //
            //  return : True if cubemap is successfully created              //
            ////////////////////////////////////////////////////////////////////
            bool createCubeMap(VulkanMemoryPool memoryPool,
                uint32_t width, uint32_t height, const unsigned char* data,
                bool smooth = true);

            ////////////////////////////////////////////////////////////////////
            //  Bind cubemap                                                  //
            ////////////////////////////////////////////////////////////////////
            void bind();

            ////////////////////////////////////////////////////////////////////
            //  Destroy cubemap                                               //
            ////////////////////////////////////////////////////////////////////
            void destroyCubeMap();


            ////////////////////////////////////////////////////////////////////
            //  Check if the cubemap has a valid handle                       //
            //  return : True if the cubemap is valid                         //
            ////////////////////////////////////////////////////////////////////
            bool isValid();

            ////////////////////////////////////////////////////////////////////
            //  Get cubemap memory requirements                               //
            ////////////////////////////////////////////////////////////////////
            void getMemoryRequirements(
                VkMemoryRequirements* memoryRequirements);

            ////////////////////////////////////////////////////////////////////
            //  Bind cubemap memory                                           //
            //  return : True if cubemap memory is successfully binded        //
            ////////////////////////////////////////////////////////////////////
            bool bindCubeMapMemory(VkDeviceMemory& deviceMemory,
                VkDeviceSize size, VkDeviceSize offset);


        private:
            ////////////////////////////////////////////////////////////////////
            //  CubeMap private copy constructor : Not copyable               //
            ////////////////////////////////////////////////////////////////////
            CubeMap(const CubeMap&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  CubeMap private copy operator : Not copyable                  //
            ////////////////////////////////////////////////////////////////////
            CubeMap& operator=(const CubeMap&) = delete;


        private:
            VkImage             m_handle;           // CubeMap handle
            VkSampler           m_sampler;          // CubeMap sampler
            VkImageView         m_view;             // CubeMap view
            VkDescriptorSet     m_descriptorSets[RendererMaxSwapchainFrames];

            VkDeviceSize        m_memorySize;       // Memory size
            VkDeviceSize        m_memoryOffset;     // Memory offset

            uint32_t            m_width;            // CubeMap width
            uint32_t            m_height;           // CubeMap height
    };


#endif // VOS_RENDERER_VULKAN_CUBEMAP_HEADER

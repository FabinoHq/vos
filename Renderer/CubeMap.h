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
//     Renderer/CubeMap.h : CubeMap management                                //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_CUBEMAP_HEADER
#define VOS_RENDERER_CUBEMAP_HEADER

    #include "Vulkan/Vulkan.h"
    #include "Vulkan/Swapchain.h"
    #include "Vulkan/VulkanBuffer.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  CubeMap settings                                                      //
    ////////////////////////////////////////////////////////////////////////////
    const uint64_t CubeMapFenceTimeout = 100000000000;


    ////////////////////////////////////////////////////////////////////////////
    //  Renderer class declaration                                            //
    ////////////////////////////////////////////////////////////////////////////
    class Renderer;


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
            bool createCubeMap(Renderer& renderer,
                uint32_t width, uint32_t height, bool smooth = true);

            ////////////////////////////////////////////////////////////////////
            //  Update cubemap                                                //
            //  return : True if cubemap is successfully updated              //
            ////////////////////////////////////////////////////////////////////
            bool updateCubeMap(Renderer& renderer,
                uint32_t width, uint32_t height, const unsigned char* data,
                bool smooth = true);

            ////////////////////////////////////////////////////////////////////
            //  Bind cubemap                                                  //
            ////////////////////////////////////////////////////////////////////
            void bind(Renderer& renderer);

            ////////////////////////////////////////////////////////////////////
            //  Destroy cubemap                                               //
            ////////////////////////////////////////////////////////////////////
            void destroyCubeMap(Renderer& renderer);


            ////////////////////////////////////////////////////////////////////
            //  Check if the cubemap has a valid handle                       //
            //  return : True if the cubemap is valid                         //
            ////////////////////////////////////////////////////////////////////
            bool isValid();

            ////////////////////////////////////////////////////////////////////
            //  Get cubemap memory requirements                               //
            ////////////////////////////////////////////////////////////////////
            void getMemoryRequirements(VkDevice& vulkanDevice,
                VkMemoryRequirements* memoryRequirements);

            ////////////////////////////////////////////////////////////////////
            //  Bind cubemap memory                                           //
            //  return : True if cubemap memory is successfully binded        //
            ////////////////////////////////////////////////////////////////////
            bool bindCubeMapMemory(VkDevice& vulkanDevice,
                VkDeviceMemory& deviceMemory, VkDeviceSize size,
                VkDeviceSize offset);


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

            VulkanBuffer        m_stagingBuffer;    // Stagging buffer
            VkDeviceSize        m_memorySize;       // Memory size
            VkDeviceSize        m_memoryOffset;     // Memory offset

            uint32_t            m_width;            // CubeMap width
            uint32_t            m_height;           // CubeMap height
    };

#endif // VOS_RENDERER_CUBEMAP_HEADER

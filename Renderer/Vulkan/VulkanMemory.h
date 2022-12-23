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
//     Renderer/Vulkan/VulkanMemory.h : Vulkan memory management              //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_VULKANMEMORY_HEADER
#define VOS_RENDERER_VULKAN_VULKANMEMORY_HEADER

    #include "../../System/System.h"
    #include "Vulkan.h"

    #include <cstdint>
    #include <cstring>


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanBuffer class declaration                                        //
    ////////////////////////////////////////////////////////////////////////////
    class VulkanBuffer;

    ////////////////////////////////////////////////////////////////////////////
    //  Texture class declaration                                             //
    ////////////////////////////////////////////////////////////////////////////
    class Texture;

    ////////////////////////////////////////////////////////////////////////////
    //  CubeMap class declaration                                             //
    ////////////////////////////////////////////////////////////////////////////
    class CubeMap;


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanMemoryType enum                                                 //
    ////////////////////////////////////////////////////////////////////////////
    enum VulkanMemoryType
    {
        VULKAN_MEMORY_DEVICE = 0,
        VULKAN_MEMORY_HOST = 1
    };


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanMemoryPool enum                                                 //
    ////////////////////////////////////////////////////////////////////////////
    enum VulkanMemoryPool
    {
        VULKAN_MEMORY_SWAPCHAIN = 0,
        VULKAN_MEMORY_RENDERDEVICE = 1,
        VULKAN_MEMORY_RENDERHOST = 2,

        VULKAN_MEMORY_TEXTUREUPLOAD = 3,

        VULKAN_MEMORY_POOLSCOUNT = 4
    };


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanMemoryList structure                                            //
    ////////////////////////////////////////////////////////////////////////////
    struct VulkanMemoryList
    {
        VulkanMemoryPool pool;
        VulkanMemoryType type;
        VkDeviceSize size;
    };


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanMemoryArray : Memory pools type and size                        //
    ////////////////////////////////////////////////////////////////////////////
    const VulkanMemoryList VulkanMemoryArray[VULKAN_MEMORY_POOLSCOUNT] =
    {
        VULKAN_MEMORY_SWAPCHAIN, VULKAN_MEMORY_DEVICE, 0x1000000,
        VULKAN_MEMORY_RENDERDEVICE, VULKAN_MEMORY_DEVICE, 0x10000000,
        VULKAN_MEMORY_RENDERHOST, VULKAN_MEMORY_HOST, 0x10000000,

        VULKAN_MEMORY_TEXTUREUPLOAD, VULKAN_MEMORY_HOST, 0x8000000
    };


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanMemory class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class VulkanMemory
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  VulkanMemory default constructor                              //
            ////////////////////////////////////////////////////////////////////
            VulkanMemory();

            ////////////////////////////////////////////////////////////////////
            //  VulkanMemory destructor                                       //
            ////////////////////////////////////////////////////////////////////
            ~VulkanMemory();


            ////////////////////////////////////////////////////////////////////
            //  Init Vulkan memory                                            //
            //  return : True if Vulkan memory is ready                       //
            ////////////////////////////////////////////////////////////////////
            bool init(VkPhysicalDevice& physicalDevice, VkDevice& vulkanDevice);

            ////////////////////////////////////////////////////////////////////
            //  Reset Vulkan memory pool                                      //
            ////////////////////////////////////////////////////////////////////
            inline void resetMemory(VulkanMemoryPool memoryPool)
            {
                m_offset[memoryPool] = 0;
            }

            ////////////////////////////////////////////////////////////////////
            //  Cleanup Vulkan memory                                         //
            ////////////////////////////////////////////////////////////////////
            void cleanup(VkDevice& vulkanDevice);


            ////////////////////////////////////////////////////////////////////
            //  Allocate swapchain image memory                               //
            //  return : True if swapchain image is successfully allocated    //
            ////////////////////////////////////////////////////////////////////
            bool allocateSwapchainImage(VkDevice& vulkanDevice, VkImage& image);


            ////////////////////////////////////////////////////////////////////
            //  Allocate buffer memory                                        //
            //  return : True if buffer memory is successfully allocated      //
            ////////////////////////////////////////////////////////////////////
            bool allocateBufferMemory(VkDevice& vulkanDevice,
                VulkanBuffer& buffer, VulkanMemoryPool memoryPool);

            ////////////////////////////////////////////////////////////////////
            //  Write buffer memory                                           //
            //  return : True if buffer memory is successfully written        //
            ////////////////////////////////////////////////////////////////////
            bool writeBufferMemory(VkDevice& vulkanDevice, VulkanBuffer& buffer,
                const void* data, VulkanMemoryPool memoryPool);


            ////////////////////////////////////////////////////////////////////
            //  Allocate texture memory                                       //
            //  return : True if texture memory is successfully allocated     //
            ////////////////////////////////////////////////////////////////////
            bool allocateTextureMemory(VkDevice& vulkanDevice,
                Texture& texture, VulkanMemoryPool memoryPool);


            ////////////////////////////////////////////////////////////////////
            //  Allocate cubemap memory                                       //
            //  return : True if cubemap memory is successfully allocated     //
            ////////////////////////////////////////////////////////////////////
            bool allocateCubeMapMemory(VkDevice& vulkanDevice,
                CubeMap& cubemap, VulkanMemoryPool memoryPool);


        private:
            ////////////////////////////////////////////////////////////////////
            //  VulkanMemory private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            VulkanMemory(const VulkanMemory&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  VulkanMemory private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            VulkanMemory& operator=(const VulkanMemory&) = delete;


        private:
            bool            m_memoryReady;          // Vulkan memory ready state
            uint32_t        m_deviceMemoryIndex;    // Device memory type index
            uint32_t        m_hostMemoryIndex;      // Host memory type index
            uint32_t        m_maxAllocationCount;   // Maximum allocation count
            VkDeviceSize    m_memoryAlignment;      // Memory alignment

            VkDeviceMemory  m_memory[VULKAN_MEMORY_POOLSCOUNT];     // Memory
            VkDeviceSize    m_offset[VULKAN_MEMORY_POOLSCOUNT];     // Offset
            uint32_t        m_index[VULKAN_MEMORY_POOLSCOUNT];      // Index
    };


#endif // VOS_RENDERER_VULKAN_VULKANMEMORY_HEADER

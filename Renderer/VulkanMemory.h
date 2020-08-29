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
//     Renderer/VulkanMemory.h : Vulkan memory management                     //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKANMEMORY_HEADER
#define VOS_RENDERER_VULKANMEMORY_HEADER

    #include "Vulkan.h"


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanBuffer class declaration                                        //
    ////////////////////////////////////////////////////////////////////////////
    class VulkanBuffer;

    ////////////////////////////////////////////////////////////////////////////
    //  Texture class declaration                                             //
    ////////////////////////////////////////////////////////////////////////////
    class Texture;


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanMemoryType enum                                                 //
    ////////////////////////////////////////////////////////////////////////////
    enum VulkanMemoryType
    {
        VULKAN_MEMORY_DEVICE = 0,
        VULKAN_MEMORY_HOST = 1
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
            //  Cleanup Vulkan memory                                         //
            ////////////////////////////////////////////////////////////////////
            void cleanup(VkDevice& vulkanDevice);


            ////////////////////////////////////////////////////////////////////
            //  Allocate buffer memory                                        //
            //  return : True if buffer memory is successfully allocated      //
            ////////////////////////////////////////////////////////////////////
            bool allocateBufferMemory(VkDevice& vulkanDevice,
                VulkanBuffer& buffer, VulkanMemoryType memoryType);

            ////////////////////////////////////////////////////////////////////
            //  Write buffer memory                                           //
            //  return : True if buffer memory is successfully written        //
            ////////////////////////////////////////////////////////////////////
            bool writeBufferMemory(VkDevice& vulkanDevice,
                VulkanBuffer& buffer, const void* data);

            ////////////////////////////////////////////////////////////////////
            //  Free buffer memory                                            //
            ////////////////////////////////////////////////////////////////////
            void freeBufferMemory(VkDevice& vulkanDevice, VulkanBuffer& buffer);


            ////////////////////////////////////////////////////////////////////
            //  Allocate texture memory                                       //
            //  return : True if texture memory is successfully allocated     //
            ////////////////////////////////////////////////////////////////////
            bool allocateTextureMemory(VkDevice& vulkanDevice,
                Texture& texture);

            ////////////////////////////////////////////////////////////////////
            //  Free texture memory                                           //
            ////////////////////////////////////////////////////////////////////
            void freeTextureMemory(VkDevice& vulkanDevice, Texture& texture);


        private:
            bool            m_memoryReady;          // Vulkan memory ready state
            uint32_t        m_deviceMemoryIndex;    // Device memory type index
            uint32_t        m_hostMemoryIndex;      // Host memory type index
            VkDeviceSize    m_nonCoherentAtomSize;  // Non coherent alignment
            VkDeviceMemory  m_deviceMemory;         // Device memory
            VkDeviceSize    m_deviceMemoryOffset;   // Device memory offset
            VkDeviceMemory  m_hostMemory;           // Host memory
            VkDeviceSize    m_hostMemoryOffset;     // Host memory offset
    };


#endif // VOS_RENDERER_VULKANMEMORY_HEADER

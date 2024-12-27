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
    #include "../../System/SysMessage.h"
    #include "Vulkan.h"

    #include <cstdint>
    #include <cstring>

    //#include <iostream>
    //#include <iomanip>


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanBuffer class declaration                                        //
    ////////////////////////////////////////////////////////////////////////////
    class VulkanBuffer;

    ////////////////////////////////////////////////////////////////////////////
    //  Texture class declaration                                             //
    ////////////////////////////////////////////////////////////////////////////
    class Texture;

    ////////////////////////////////////////////////////////////////////////////
    //  TextureArray class declaration                                        //
    ////////////////////////////////////////////////////////////////////////////
    class TextureArray;

    ////////////////////////////////////////////////////////////////////////////
    //  CubeMap class declaration                                             //
    ////////////////////////////////////////////////////////////////////////////
    class CubeMap;


    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan memory type enumeration                                        //
    ////////////////////////////////////////////////////////////////////////////
    enum VulkanMemoryType
    {
        VULKAN_MEMORY_DEVICE = 0,
        VULKAN_MEMORY_HOST = 1
    };


    ////////////////////////////////////////////////////////////////////////////
    //  Vulkan memory pool enumeration                                        //
    ////////////////////////////////////////////////////////////////////////////
    enum VulkanMemoryPool
    {
        VULKAN_MEMORY_BACKCHAIN = 0,
        VULKAN_MEMORY_BACKRENDERER = 1,

        VULKAN_MEMORY_UNIFORMUPLOAD = 2,
        VULKAN_MEMORY_TEXTUREUPLOAD = 3,
        VULKAN_MEMORY_MESHUPLOAD = 4,
        VULKAN_MEMORY_HEIGHTMAPUPLOAD = 5,
        VULKAN_MEMORY_HEIGHTFARUPLOAD = 6,

        VULKAN_MEMORY_UNIFORMS = 7,
        VULKAN_MEMORY_TEXTURES = 8,
        VULKAN_MEMORY_MESHES = 9,
        VULKAN_MEMORY_HEIGHTMAPS = 10,
        VULKAN_MEMORY_HEIGHTFARS = 11,

        VULKAN_MEMORY_POOLSCOUNT = 12
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
    //  VulkanMemoryArray : Memory pools types and sizes                      //
    ////////////////////////////////////////////////////////////////////////////
    const VulkanMemoryList VulkanMemoryArray[VULKAN_MEMORY_POOLSCOUNT] =
    {
        VULKAN_MEMORY_BACKCHAIN, VULKAN_MEMORY_DEVICE, 0x4000000,
        VULKAN_MEMORY_BACKRENDERER, VULKAN_MEMORY_DEVICE, 0x400000,

        VULKAN_MEMORY_UNIFORMUPLOAD, VULKAN_MEMORY_HOST, 0x4000,
        VULKAN_MEMORY_TEXTUREUPLOAD, VULKAN_MEMORY_HOST, 0x2000000,
        VULKAN_MEMORY_MESHUPLOAD, VULKAN_MEMORY_HOST, 0x80000,
        VULKAN_MEMORY_HEIGHTMAPUPLOAD, VULKAN_MEMORY_HOST, 0x100000,
        VULKAN_MEMORY_HEIGHTFARUPLOAD, VULKAN_MEMORY_HOST, 0x100000,

        VULKAN_MEMORY_UNIFORMS, VULKAN_MEMORY_DEVICE, 0x4000,
        VULKAN_MEMORY_TEXTURES, VULKAN_MEMORY_DEVICE, 0x4000000,
        VULKAN_MEMORY_MESHES, VULKAN_MEMORY_DEVICE, 0x100000,
        VULKAN_MEMORY_HEIGHTMAPS, VULKAN_MEMORY_DEVICE, 0x5000000,
        VULKAN_MEMORY_HEIGHTFARS, VULKAN_MEMORY_DEVICE, 0x5000000
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
            bool init();

            ////////////////////////////////////////////////////////////////////
            //  Reset Vulkan memory pool                                      //
            ////////////////////////////////////////////////////////////////////
            inline void resetMemory(VulkanMemoryPool memoryPool)
            {
                m_offset[memoryPool] = 0;
            }

            ////////////////////////////////////////////////////////////////////
            //  Destroy Vulkan memory                                         //
            ////////////////////////////////////////////////////////////////////
            void destroyVulkanMemory();


            ////////////////////////////////////////////////////////////////////
            //  Allocate backchain image memory                               //
            //  return : True if backchain image is successfully allocated    //
            ////////////////////////////////////////////////////////////////////
            bool allocateBackchainImage(VkImage& image,
                VulkanMemoryPool memoryPool);


            ////////////////////////////////////////////////////////////////////
            //  Allocate buffer memory                                        //
            //  return : True if buffer memory is successfully allocated      //
            ////////////////////////////////////////////////////////////////////
            bool allocateBufferMemory(VulkanBuffer& buffer,
                VulkanMemoryPool memoryPool);

            ////////////////////////////////////////////////////////////////////
            //  Write buffer memory                                           //
            //  return : True if buffer memory is successfully written        //
            ////////////////////////////////////////////////////////////////////
            bool writeBufferMemory(VulkanBuffer& buffer,
                const void* data, VulkanMemoryPool memoryPool);


            ////////////////////////////////////////////////////////////////////
            //  Allocate texture memory                                       //
            //  return : True if texture memory is successfully allocated     //
            ////////////////////////////////////////////////////////////////////
            bool allocateTextureMemory(Texture& texture,
                VulkanMemoryPool memoryPool);

            ////////////////////////////////////////////////////////////////////
            //  Allocate texture array memory                                 //
            //  return : True if texture array memory is allocated            //
            ////////////////////////////////////////////////////////////////////
            bool allocateTextureArrayMemory(TextureArray& textureArray,
                VulkanMemoryPool memoryPool);

            ////////////////////////////////////////////////////////////////////
            //  Allocate cubemap memory                                       //
            //  return : True if cubemap memory is successfully allocated     //
            ////////////////////////////////////////////////////////////////////
            bool allocateCubeMapMemory(CubeMap& cubemap,
                VulkanMemoryPool memoryPool);


            ////////////////////////////////////////////////////////////////////
            //  Dump Vulkan memory usage                                      //
            ////////////////////////////////////////////////////////////////////
            /*void dumpMemory()
            {
                std::cout << "Memory dump\n";
                for (int i = 0; i < VULKAN_MEMORY_POOLSCOUNT; ++i)
                {
                    std::cout << std::hex << m_usage[i] << " ( ";
                    std::cout << std::dec << (
                        (m_usage[i]*1.0)/(VulkanMemoryArray[i].size*1.0)
                    )*100.0;
                    std::cout << " % )\n";
                }
                std::cout << '\n';
            }*/


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
            uint32_t        m_deviceMemoryIndex;    // Device memory type index
            uint32_t        m_deviceMemoryHeap;     // Device memory heap index
            uint32_t        m_hostMemoryIndex;      // Host memory type index
            uint32_t        m_hostMemoryHeap;       // Host memory heap index
            uint32_t        m_maxAllocationCount;   // Maximum allocation count
            VkDeviceSize    m_memoryAlignment;      // Memory alignment

            VkDeviceMemory  m_memory[VULKAN_MEMORY_POOLSCOUNT];     // Memory
            VkDeviceSize    m_offset[VULKAN_MEMORY_POOLSCOUNT];     // Offset
            uint32_t        m_index[VULKAN_MEMORY_POOLSCOUNT];      // Index
            VkDeviceSize    m_usage[VULKAN_MEMORY_POOLSCOUNT];      // Usage
    };


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanMemory global instance                                          //
    ////////////////////////////////////////////////////////////////////////////
    extern VulkanMemory GVulkanMemory;


#endif // VOS_RENDERER_VULKAN_VULKANMEMORY_HEADER

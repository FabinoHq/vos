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
            bool init(VkPhysicalDevice& physicalDevice);


            ////////////////////////////////////////////////////////////////////
            //  Allocate buffer memory                                        //
            //  return : True if buffer memory is successfully allocated      //
            ////////////////////////////////////////////////////////////////////
            bool allocateBufferMemory(VkDevice& vulkanDevice, VkBuffer& buffer,
                VkDeviceMemory& memory, VulkanMemoryType memoryType);

            ////////////////////////////////////////////////////////////////////
            //  Map buffer memory                                             //
            //  return : True if buffer memory is successfully mapped         //
            ////////////////////////////////////////////////////////////////////
            bool mapBufferMemory(VkDevice& vulkanDevice, VkBuffer& buffer,
                VkDeviceMemory& memory, const void* data, uint32_t size);

            ////////////////////////////////////////////////////////////////////
            //  Free buffer memory                                            //
            ////////////////////////////////////////////////////////////////////
            void freeBufferMemory(VkDevice& vulkanDevice,
                VkDeviceMemory& memory);


            ////////////////////////////////////////////////////////////////////
            //  Allocate image memory                                         //
            //  return : True if image memory is successfully allocated       //
            ////////////////////////////////////////////////////////////////////
            bool allocateImageMemory(VkDevice& vulkanDevice,
                VkImage& image, VkDeviceMemory& memory);

            ////////////////////////////////////////////////////////////////////
            //  Free image memory                                             //
            ////////////////////////////////////////////////////////////////////
            void freeImageMemory(VkDevice& vulkanDevice,
                VkDeviceMemory& memory);


        private:
            bool                                m_memoryReady;
            VkPhysicalDeviceMemoryProperties    m_physicalMemoryProperties;
    };


#endif // VOS_RENDERER_VULKANMEMORY_HEADER

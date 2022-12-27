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
//     Renderer/Vulkan/VulkanBuffer.h : Vulkan buffer management              //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_VULKANBUFFER_HEADER
#define VOS_RENDERER_VULKAN_VULKANBUFFER_HEADER

    #include "../../System/System.h"
    #include "Vulkan.h"
    #include "VulkanMemory.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  VulkanBuffer class definition                                         //
    ////////////////////////////////////////////////////////////////////////////
    class VulkanBuffer
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  VulkanBuffer default constructor                              //
            ////////////////////////////////////////////////////////////////////
            VulkanBuffer();

            ////////////////////////////////////////////////////////////////////
            //  VulkanBuffer destructor                                       //
            ////////////////////////////////////////////////////////////////////
            ~VulkanBuffer();


            ////////////////////////////////////////////////////////////////////
            //  Create Vulkan buffer                                          //
            //  return : True if Vulkan buffer is successfully created        //
            ////////////////////////////////////////////////////////////////////
            bool createBuffer(VkDevice& vulkanDevice,
                VulkanMemory& vulkanMemory, VkBufferUsageFlags usage,
                VulkanMemoryPool memoryPool, uint32_t bufferSize);

            ////////////////////////////////////////////////////////////////////
            //  Destroy Vulkan buffer                                         //
            ////////////////////////////////////////////////////////////////////
            void destroyBuffer(VkDevice& vulkanDevice);

        private:
            ////////////////////////////////////////////////////////////////////
            //  VulkanBuffer private copy constructor : Not copyable          //
            ////////////////////////////////////////////////////////////////////
            VulkanBuffer(const VulkanBuffer&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  VulkanBuffer private copy operator : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            VulkanBuffer& operator=(const VulkanBuffer&) = delete;


        public:
            VkBuffer        handle;         // Buffer handle
            uint32_t        size;           // Buffer size

            VkDeviceSize    memorySize;     // Memory size
            VkDeviceSize    memoryOffset;   // Memory offset
    };


#endif // VOS_RENDERER_VULKAN_VULKANBUFFER_HEADER

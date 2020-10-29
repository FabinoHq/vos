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
//     Renderer/Vulkan/UniformBuffer.h : Uniform buffer management            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_UNIFORMBUFFER_HEADER
#define VOS_RENDERER_VULKAN_UNIFORMBUFFER_HEADER

    #include "Vulkan.h"
    #include "VulkanMemory.h"
    #include "VulkanQueue.h"
    #include "VulkanBuffer.h"


    ////////////////////////////////////////////////////////////////////////////
    //  UniformData data structure                                            //
    ////////////////////////////////////////////////////////////////////////////
    struct UniformData
    {
        float   projMatrix[16];
        float   viewMatrix[16];
    };


    ////////////////////////////////////////////////////////////////////////////
    //  UniformBuffer class definition                                        //
    ////////////////////////////////////////////////////////////////////////////
    class UniformBuffer
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  UniformBuffer default constructor                             //
            ////////////////////////////////////////////////////////////////////
            UniformBuffer();

            ////////////////////////////////////////////////////////////////////
            //  UniformBuffer destructor                                      //
            ////////////////////////////////////////////////////////////////////
            ~UniformBuffer();


            ////////////////////////////////////////////////////////////////////
            //  Create Uniform buffer                                         //
            //  return : True if Vertex buffer is successfully created        //
            ////////////////////////////////////////////////////////////////////
            bool createBuffer(VkPhysicalDevice& physicalDevice,
                VkDevice& vulkanDevice, VulkanMemory& vulkanMemory,
                uint32_t size);

            ////////////////////////////////////////////////////////////////////
            //  Update Uniform buffer                                         //
            //  return : True if Vertex buffer is successfully updated        //
            ////////////////////////////////////////////////////////////////////
            bool updateBuffer(VkPhysicalDevice& physicalDevice,
                VkDevice& vulkanDevice, VulkanMemory& vulkanMemory,
                VkCommandPool& transferCommandPool, VulkanQueue& transferQueue,
                void* data, uint32_t size);

            ////////////////////////////////////////////////////////////////////
            //  Destroy Uniform buffer                                        //
            ////////////////////////////////////////////////////////////////////
            void destroyBuffer(VkDevice& vulkanDevice,
                VulkanMemory& vulkanMemory);


        private:
            ////////////////////////////////////////////////////////////////////
            //  UniformBuffer private copy constructor : Not copyable         //
            ////////////////////////////////////////////////////////////////////
            UniformBuffer(const UniformBuffer&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  UniformBuffer private copy operator : Not copyable            //
            ////////////////////////////////////////////////////////////////////
            UniformBuffer& operator=(const UniformBuffer&) = delete;


        public:
            VulkanBuffer    uniformBuffer;      // Uniform buffer
            VulkanBuffer    stagingBuffer;      // Staging buffer
    };


#endif // VOS_RENDERER_VULKAN_UNIFORMBUFFER_HEADER

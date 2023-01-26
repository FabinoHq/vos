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
//     Renderer/Vulkan/UniformBuffer.h : Uniform buffer management            //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_RENDERER_VULKAN_UNIFORMBUFFER_HEADER
#define VOS_RENDERER_VULKAN_UNIFORMBUFFER_HEADER

    #include "../../System/System.h"
    #include "Vulkan.h"
    #include "VulkanMemory.h"
    #include "VulkanQueue.h"
    #include "VulkanBuffer.h"
    #include "Swapchain.h"
    #include "Uniformchain.h"

    #include <cstddef>
    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  UniformBuffer settings                                                //
    ////////////////////////////////////////////////////////////////////////////
    const uint64_t UniformBufferFenceTimeout = 100000000000;

    ////////////////////////////////////////////////////////////////////////////
    //  UniformData data structure                                            //
    ////////////////////////////////////////////////////////////////////////////
    struct UniformData
    {
        float   projView[16];   // Projection view combined matrix
        float   view[16];       // View matrix (optional)
    };

    ////////////////////////////////////////////////////////////////////////////
    //  UniformData data structure fixed size                                 //
    ////////////////////////////////////////////////////////////////////////////
    const size_t UniformDataSize = (sizeof(float)*32);


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
            bool createBuffer(uint32_t size);

            ////////////////////////////////////////////////////////////////////
            //  Update Uniform buffer                                         //
            //  return : True if Vertex buffer is successfully updated        //
            ////////////////////////////////////////////////////////////////////
            bool updateBuffer(void* data, uint32_t size);

            ////////////////////////////////////////////////////////////////////
            //  Destroy Uniform buffer                                        //
            ////////////////////////////////////////////////////////////////////
            void destroyBuffer();


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
